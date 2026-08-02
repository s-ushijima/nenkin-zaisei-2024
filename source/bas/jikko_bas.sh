#!/bin/bash

LOG="/suuri/rev2024/bas/log"


VER="0000"
KOUNEN="0000"
KOKUNEN="0000"
ECON="0000"
SOTOWAKU="0000"
SOTOWAKU_CUT="0000"
YOBI="000"
KAKO="0"
CARRY="1"
DMACRO="0"
OPTION="0"
OP_START="2031"
OP_HIKIAGE_KANKAKU="3"
TOUGOU="0"
CUT_KOTEI="0"
CUT_ONE_SHUTU="0"


IO_DIR="/suuri/rev2024/bas/io_file"
INFILE="/infile.csv"
OUTFILE="/outfile.csv"
JIKKO_DIR="/suuri/rev2024/bas/exec"


echo "プログラム（Version:${VER} , 試算番号:${KOUNEN}-${KOKUNEN}-${ECON}-${SOTOWAKU}-${YOBI} , Part=${KAKUDAI} , Option=${OPTION}）を実行しますか？（y/n）"
read ans

if [ "$ans" = "y" ]
then
	:> /suuri/rev2024/bas/rslt/output.csv
	
	echo "プログラム実行開始（Version:${VER} , 試算番号：${KOKUNEN}-${ECON}-${SOTOWAKU}-${YOBI} , Option=${OPTION} ）" >> ${LOG}
	date >> ${LOG}
	echo "">> ${LOG}
	echo "*****プログラム実行*****"
	
	"${JIKKO_DIR}/ver${VER}.out" \
		"${IO_DIR}${INFILE}" \
		"${IO_DIR}${OUTFILE}" \
		${KOUNEN} \
		${KOKUNEN} \
		${ECON} \
		${SOTOWAKU} \
		${SOTOWAKU_CUT} \
		${YOBI} \
		${KAKO} \
		${CARRY} \
		${DMACRO} \
		${OPTION} \
		${OP_START} \
		${OP_HIKIAGE_KANKAKU} \
		${TOUGOU} \
		${CUT_KOTEI} \
		${CUT_ONE_SHUTU}
	
	echo "実行終了" >> ${LOG}
	date >> ${LOG}
	echo "" >> ${LOG}
fi
