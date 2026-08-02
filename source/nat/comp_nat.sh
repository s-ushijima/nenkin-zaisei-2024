#!/bin/sh

path=`pwd`
ver=`basename ${path}`

LOG="/suuri/rev2024/nat/log"

JIKKO_DIR="/suuri/rev2024/nat/exec"

echo "Version${ver}のコンパイルを実行しますか？（y/n）"

read ans01

if [ "$ans01" = "y" ]
then
	echo "コンパイル実行開始（Ver${ver}）" >> ${LOG}
	date >> ${LOG}
	echo "">> ${LOG}

	echo "*****実行ファイル作成*****"
	CC -g -o ${JIKKO_DIR}/"ver${ver}.out" \
		main.c stdfm.c cntl.c file_open.c seid.c econ.c waku.c kaizen.c dtst.c \
		kiso.c noufuritu.c siml.c str_op.c shke.c stat.c printout.c

	echo "コンパイル終了" >> ${LOG}
	date >> ${LOG}
	echo "">> ${LOG}
fi
