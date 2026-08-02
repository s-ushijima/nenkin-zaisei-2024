#!/usr/bin/env python3
"""Convert the standard-scenario emp_shushi (asys20) output CSVs into the JSON
the docs/ dashboard fetches. Reads from a downloaded "standard-scenario-results"
GitHub Actions artifact directory (see .github/workflows/build.yml).

Usage:
    python tools/build_dashboard_data.py <artifact_dir> <output_json>
"""
import json
import sys
from pathlib import Path

# emp_shushi's internal fiscal-year index k maps to calendar year as
# year = k + 2000 (source/emp_shushi/econ.c hardcodes GPIF-actuals for
# k=1..22, matching FY2001-FY2022; k=24 lines up with the report's FY2024
# base year in 03summary output).
K_YEAR_OFFSET = 2000
BASE_YEAR = 2024

# Economic-assumption catalogue. The econ-NNNN.csv files ship with the original
# program but carry no scenario names, so the mapping to the report's four named
# cases was established three independent ways:
#   1. 第3-4-29表 numbers the cases ①〜④ in descending growth order, matching the
#      ascending econ-3001..3004 file order.
#   2. Each file's real-wage-growth column (col 5, per source/emp_shushi/econ.c)
#      settles at 2.0 / 1.5 / 0.5 / 0.1 % respectively -- the same ordering and
#      values as the report's per-case assumptions.
#   3. Running econ-3001 reproduces the report's 高成長実現ケース×中位推計 output
#      figures (56.9% / 25.0% / 31.9% at FY2039) to the published precision.
# 実質経済成長率 is quoted from 第3-4-29表 (2034-2063年度の30年平均); the official
# replacement rates are from 第3-7-10図 (中位推計人口), both in 2024report3.pdf.
SCENARIOS = [
    {
        "econ": "3001",
        "name": "高成長実現ケース",
        "real_growth": "1.6%",
        "real_wage_growth": "2.0%",
        "official_rate": "56.9%",
        "official_end_year": "2039年度",
        "computed": True,
    },
    {
        "econ": "3002",
        "name": "成長型経済移行・継続ケース",
        "real_growth": "1.1%",
        "real_wage_growth": "1.5%",
        "official_rate": "57.6%",
        "official_end_year": "2037年度",
        "computed": False,
    },
    {
        "econ": "3003",
        "name": "過去30年投影ケース",
        "real_growth": "▲0.1%",
        "real_wage_growth": "0.5%",
        "official_rate": "50.4%",
        "official_end_year": "2057年度",
        "computed": False,
    },
    {
        "econ": "3004",
        "name": "1人当たりゼロ成長ケース",
        "real_growth": "▲0.7%",
        "real_wage_growth": "0.1%",
        "official_rate": "—",
        "official_end_year": "国民年金は2059年度に積立金が枯渇",
        "computed": False,
    },
]

# 第3-7-6図 (FY2024 actuals, identical across economic cases) and 第3-7-10図
# (高成長実現ケース × 中位推計人口), both from 2024report3.pdf.
OFFICIAL = {
    "base_total": 61.2,
    "base_proportional": 25.0,
    "base_basic": 36.2,
    "end_total": 56.9,
    "end_proportional": 25.0,
    "end_basic": 31.9,
    "end_year": 2039,
}


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
        if year < BASE_YEAR:
            continue
        series.append({
            "year": year,
            "income_trillion_yen": round(income / 10000.0, 2),
            "expense_trillion_yen": round(expense / 10000.0, 2),
            "reserve_trillion_yen": round(reserve / 10000.0, 2),
            "funded_ratio_years": round(funded_ratio, 2),
        })
    return series


def diff_row(metric, model, official, unit="pt", digits=2):
    """One row of the official-report comparison table."""
    delta = model - official
    return {
        "metric": metric,
        "model": f"{model:.2f}",
        "official": f"{official:.1f}",
        "diff": f"{delta:+.2f}{unit}",
        "match": abs(delta) < 0.05,
    }


def build(artifact_dir, output_path):
    artifact_dir = Path(artifact_dir)
    shushi_dir = artifact_dir / "emp_ez_arev" / "shushi"

    summary_file = next(shushi_dir.glob("03summary.*.csv"))
    tou_file = next(shushi_dir.glob("01shushi.*e_08tou.csv"))

    replacement_rate = parse_03summary(summary_file)
    balance = parse_01shushi_tou(tou_file)

    base = next(p for p in replacement_rate if p["year"] == BASE_YEAR)
    tail = replacement_rate[-1]
    # the adjustment ends the first year the rate reaches its terminal level
    end = next(p for p in replacement_rate
               if p["year"] >= BASE_YEAR and abs(p["total"] - tail["total"]) < 0.005)
    base_bal = next(p for p in balance if p["year"] == BASE_YEAR)

    data = {
        "meta": {
            "run": "試算番号1000 / 経済前提3001 / 外枠1000",
            "scenario_name": "高成長実現ケース",
            "population": "出生中位・死亡中位・入国超過16万人",
            "labor": "労働参加進展ケース",
            "sources": [summary_file.name, tou_file.name],
        },
        "scenarios": SCENARIOS,
        "kpis": [
            {
                "label": "所得代替率",
                "sub": f"{BASE_YEAR}年度（足下）",
                "value": f"{base['total']:.1f}",
                "unit": "%",
                "delta": None,
                "spark": "replacement_total",
            },
            {
                "label": "調整終了後の所得代替率",
                "sub": f"{end['year']}年度に給付水準調整が終了",
                "value": f"{end['total']:.1f}",
                "unit": "%",
                "delta": f"▼ {base['total'] - end['total']:.1f}pt（{BASE_YEAR}年度比）",
                "spark": "replacement_total",
            },
            {
                "label": "年度末積立金",
                "sub": f"{BASE_YEAR}年度・厚生年金全制度合算",
                "value": f"{base_bal['reserve_trillion_yen']:.0f}",
                "unit": "兆円",
                "delta": None,
                "spark": "reserve",
            },
            {
                "label": "積立度合",
                "sub": f"{BASE_YEAR}年度・支出の何年分か",
                "value": f"{base_bal['funded_ratio_years']:.1f}",
                "unit": "年分",
                "delta": None,
                "spark": "funded_ratio",
            },
        ],
        "adjustment_end": {
            "year": end["year"],
            "total": end["total"],
            "label": f"{end['year']}年度 給付水準調整の終了",
        },
        "replacement_rate": replacement_rate,
        "balance": balance,
        "official_comparison": [
            diff_row(f"所得代替率（{BASE_YEAR}年度）", base["total"], OFFICIAL["base_total"]),
            diff_row(f"　うち報酬比例部分（{BASE_YEAR}年度）", base["proportional"], OFFICIAL["base_proportional"]),
            diff_row(f"　うち基礎年金部分（{BASE_YEAR}年度）", base["basic"], OFFICIAL["base_basic"]),
            diff_row(f"所得代替率（調整終了後・{end['year']}年度）", end["total"], OFFICIAL["end_total"]),
            diff_row("　うち報酬比例部分（調整終了後）", end["proportional"], OFFICIAL["end_proportional"]),
            diff_row("　うち基礎年金部分（調整終了後）", end["basic"], OFFICIAL["end_basic"]),
            {
                "metric": "給付水準調整の終了年度",
                "model": f"{end['year']}年度",
                "official": f"{OFFICIAL['end_year']}年度",
                "diff": "一致" if end["year"] == OFFICIAL["end_year"] else "不一致",
                "match": end["year"] == OFFICIAL["end_year"],
            },
        ],
    }

    output_path = Path(output_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding="utf-8")

    matched = sum(1 for r in data["official_comparison"] if r["match"])
    print(f"wrote {output_path}")
    print(f"  {len(replacement_rate)} replacement-rate points, {len(balance)} balance points")
    print(f"  base FY{BASE_YEAR}: {base['total']:.2f}%  (official {OFFICIAL['base_total']})")
    print(f"  adjustment ends FY{end['year']}: {end['total']:.2f}%  (official {OFFICIAL['end_total']} at FY{OFFICIAL['end_year']})")
    print(f"  official comparison: {matched}/{len(data['official_comparison'])} rows match")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)
    build(sys.argv[1], sys.argv[2])
