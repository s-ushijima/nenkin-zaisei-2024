#!/bin/bash

LOG="/suuri/rev2024/nat/log"


VER="0000"
KOKUNEN="0000"
ECON="0000"
SOTOWAKU="0000"
BIRTH="0"
DEATH="M"
KAKO="0"
TINSURA="1"
KAKUDAI="0"
KAKUDAI_YEAR="2027"
OPTION="0"
OP_START="2031"
OP_HIKIAGE_KANKAKU="3"
SOTOWAKU_JURAI="0000"


IO_DIR="/suuri/rev2024/nat/io_file"
INFILE="/infile.csv"
OUTFILE="/outfile.csv"
JIKKO_DIR="/suuri/rev2024/nat/exec"


echo "プログラム（Version:${VER} , 試算番号:${KOKUNEN}-${ECON}-${SOTOWAKU} , Part=${KAKUDAI} , Option=${OPTION}）を実行しますか？（y/n）"
read ans

if [ "$ans" = "y" ]
then
	echo "プログラム実行開始（Version:${VER} , 試算番号：${KOKUNEN}-${ECON}-${SOTOWAKU} , Part=${KAKUDAI} , Option=${OPTION} ）" >> ${LOG}
	date >> ${LOG}
	echo "">> ${LOG}
	echo "*****プログラム実行*****"
	
	${JIKKO_DIR}/ver${VER}.out \
		"${IO_DIR}${INFILE}" \
		"${IO_DIR}${OUTFILE}" \
		${KOKUNEN} \
		${ECON} \
		${SOTOWAKU} \
		${BIRTH} \
		${DEATH} \
		${KAKO} \
		${TINSURA} \
		${KAKUDAI} \
		${KAKUDAI_YEAR} \
		${OPTION} \
		${OP_START} \
		${OP_HIKIAGE_KANKAKU} \
		${SOTOWAKU_JURAI}
	
	echo "実行終了" >> ${LOG}
	date >> ${LOG}
	echo "" >> ${LOG}
fi
