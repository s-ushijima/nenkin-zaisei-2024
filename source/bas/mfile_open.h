#ifdef MFILE_OPEN_H_INCLUDED
	#define MFILE_OPEN_H_INCLUDED
	#define EXTERN 
#else
	#define EXTERN extern
#endif

#define INFILE_NUM			23
#define OUTFILE_NUM			8

EXTERN FILE *fp_in[INFILE_NUM];
EXTERN FILE *fp_out[ OUTFILE_NUM];
EXTERN char infile_name[INFILE_NUM][BUFFER_MAX];
EXTERN char outfile_name[OUTFILE_NUM][BUFFER_MAX];

#define DOKUZI		0
#define KEIZAI		6
#define KAITEI		7
#define TANNEN_CUT	8
#define HOKEN		9
#define YUUSHI		10
#define zisseki_hosei	11
#define SOTOWAKU_START	12
#define KOKUNEN_1GOU	12
#define KOUNEN_2GOU		13
#define KOKKYOU_2GOU	14
#define CHIKYOU_2GOU	15
#define SHIGAKU_2GOU	16
#define KOUNEN_3GOU		17
#define KOKKYOU_3GOU	18
#define CHIKYOU_3GOU	19
#define SHIGAKU_3GOU	20
#define CUT				21
#define CUT_K			22

#define SETTEI				0
#define KYOSHUTUKIN				1
#define TUMATUMI_OUT			2
#define KEKKA_b					3
#define KEKKA_a					4
#define CUTA					5
#define OUTPUT					6
#define PROVIDE					7
