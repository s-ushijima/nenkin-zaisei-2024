#!/bin/sh

path=`pwd`
ver=`basename ${path}`

LOG="/suuri/rev2024/bas/log"

JIKKO_DIR="/suuri/rev2024/bas/exec"

echo "Version${ver}のコンパイルを実行しますか？（y/n）"

read ans01

if [ "$ans01" = "y" ]
then
	echo "コンパイル実行開始（Ver${ver}）" >> ${LOG}
	date >> ${LOG}
	echo "">> ${LOG}

	echo "*****実行ファイル作成*****"
	CC -g -o ${JIKKO_DIR}/"ver${ver}.out" \
	 Atamawari.c Atamawari_cut.c cntl.c econ.c file_open.c file_write_cut.c file_write_kakyu.c main.c printout.c \
	 read_cut.c read_file.c ReadHiyousha.c ReadKokunen_jisseki.c stdfm.c tumatumi_cal_jisseki.c tyousei.c \
	 waku.c dtst.c dokuzi_cal.c

	echo "コンパイル終了" >> ${LOG}
	date >> ${LOG}
	echo "">> ${LOG}
fi
