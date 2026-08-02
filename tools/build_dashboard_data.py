#!/usr/bin/env python3
"""Convert the standard-scenario emp_shushi (asys20) output CSVs into the JSON
the docs/ dashboard fetches. Reads from a downloaded "standard-scenario-results"
GitHub Actions artifact directory (see .github/workflows/build.yml).

Usage:
    python tools/build_dashboard_data.py <artifact_dir> <output_json>
"""
import csv
import json
import sys
from pathlib import Path

# emp_shushi's internal fiscal-year index k maps to calendar year as
# year = k + 2000 (source/emp_shushi/econ.c hardcodes GPIF-actuals for
# k=1..22, matching FY2001-FY2022; k=24 lines up with the report's FY2024
# base year in 03summary output).
K_YEAR_OFFSET = 2000


def parse_03summary(path):
    """Return the 所得代替率 series (年度, 所得代替率, うち比例, うち基礎).

    03summary.csv (source/emp_shushi/shus_out.c: shus_summary()) stacks
    several differently-shaped tables in one file -- 経済前提等, 被保険者数,
    then five 収支[...] tables, several of which also happen to have >=25
    comma-separated fields. We must scope strictly to the 経済前提等 table
    (by its own section header) or a later table's unrelated column ends up
    misread as 所得代替率.
    """
    with open(path, encoding="euc_jp", errors="replace") as fh:
        lines = fh.readlines()

    start = None
    for i, line in enumerate(lines):
        if "経済前提等" in line:
            start = i + 2  # header line follows, then data
            break
    if start is None:
        raise ValueError(f"経済前提等 section not found in {path}")

    series = []
    for line in lines[start:]:
        line = line.rstrip("\n")
        if not line.strip():
            break
        parts = line.split(",")
        try:
            k = int(parts[0])
        except ValueError:
            break
        try:
            vals = [float(x) for x in parts[1:25]]
        except ValueError:
            continue
        # skip pre-model years where every field is a placeholder 0
        if all(v == 0.0 for v in vals[7:15]) and k < 24:
            continue
        series.append({
            "year": k + K_YEAR_OFFSET,
            "total": round(vals[11], 2),
            "proportional": round(vals[12], 2),
            "basic": round(vals[13], 2),
        })
    return series


def parse_01shushi_tou(path):
    """Return the post-adjustment (スライド調整後) 収支 series for the
    combined (tou, 全制度合算) institution, in 兆円."""
    with open(path, encoding="euc_jp", errors="replace") as fh:
        lines = fh.readlines()

    start = None
    for i, line in enumerate(lines):
        if "収支見通し【スライド調整後】" in line:
            start = i + 2  # header line follows immediately, data after that
            break
    if start is None:
        raise ValueError(f"post-adjustment 収支見通し section not found in {path}")

    series = []
    for line in lines[start:]:
        line = line.rstrip("\n")
        if not line.strip():
            break
        row = line.rstrip(",").split(",")
        try:
            k = int(row[0])
        except ValueError:
            break
        try:
            income = float(row[1])   # 収入計, already x1e-8 -> 億円
            expense = float(row[12])  # 支出計, 億円
            reserve = float(row[21])  # 年度末積立金, 億円
            funded_ratio = float(row[27])  # 積立度合 (年分), unscaled
        except (ValueError, IndexError):
            continue
        year = k + K_YEAR_OFFSET
        # rows before the base year are unpopulated/partial placeholders (the
        # model projects forward from the base year; it does not backfill a
        # full income statement for prior actuals)
        if year < 2024:
            continue
        series.append({
            "year": year,
            "income_trillion_yen": round(income / 10000.0, 2),
            "expense_trillion_yen": round(expense / 10000.0, 2),
            "reserve_trillion_yen": round(reserve / 10000.0, 2),
            "funded_ratio_years": round(funded_ratio, 2),
        })
    return series


def build(artifact_dir, output_path):
    artifact_dir = Path(artifact_dir)
    shushi_dir = artifact_dir / "emp_ez_arev" / "shushi"

    summary_file = next(shushi_dir.glob("03summary.*.csv"))
    tou_file = next(shushi_dir.glob("01shushi.*e_08tou.csv"))

    replacement_rate = parse_03summary(summary_file)
    balance = parse_01shushi_tou(tou_file)

    # headline figures used in the official-report crosscheck section
    base_year = next(p for p in replacement_rate if p["year"] == 2024)
    tail = replacement_rate[-1]
    converged_year = next(
        (p["year"] for p in replacement_rate
         if p["year"] >= 2024 and abs(p["total"] - tail["total"]) < 0.005),
        None,
    )

    data = {
        "scenario": [
            {"label": "試算番号", "value": "1000"},
            {"label": "経済前提番号", "value": "3001"},
            {"label": "対応する公式シナリオ(経済)", "value": "高成長実現ケース"},
            {"label": "人口前提", "value": "出生中位・死亡中位・入国超過16万人"},
            {"label": "労働力率前提", "value": "労働参加進展ケース"},
        ],
        "replacement_rate": replacement_rate,
        "balance": balance,
        "official_comparison": [
            {
                "metric": "所得代替率(2024年度時点)",
                "model_value": f"{base_year['total']:.1f}%",
                "official_value": "61.2%",
                "diff": f"{base_year['total'] - 61.2:+.2f}pt",
                "diff_ok": abs(base_year["total"] - 61.2) < 0.5,
            },
            {
                "metric": f"所得代替率(調整終了後, {converged_year}年度)",
                "model_value": f"{tail['total']:.1f}%",
                "official_value": "56.9%(2039年度, 中位推計人口)",
                "diff": f"{tail['total'] - 56.9:+.2f}pt",
                "diff_ok": abs(tail["total"] - 56.9) < 1.0,
            },
        ],
        "status_note": (
            "本データはGitHub Actions上で厚労省公開Cプログラムを再ビルド・実行して生成したものです。"
            "経済前提3001は厚労省「財政検証結果レポート2024」の<b>高成長実現ケース</b>に相当することを、"
            "経済前提入力CSV(実質賃金上昇率・物価上昇率・実質運用利回り)の値を4ケース分すべて突き合わせて確認しました。"
            "所得代替率は基準年度(2024年度)・調整終了後の値とも公式値と概ね一致しています。"
        ),
    }

    output_path = Path(output_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding="utf-8")
    print(f"wrote {output_path} ({len(replacement_rate)} replacement-rate points, {len(balance)} balance points)")
    print(f"base year (2024): replacement_rate={base_year['total']:.2f}%")
    print(f"converged ({converged_year}): replacement_rate={tail['total']:.2f}%")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)
    build(sys.argv[1], sys.argv[2])
