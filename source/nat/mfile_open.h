#ifdef MFILE_OPEN_H_INCLUDED
	#define MFILE_OPEN_H_INCLUDED
	#define EXTERN 
#else
	#define EXTERN extern
#endif

#define INFILE_NUM			86
#define OUTFILE_NUM			11

EXTERN FILE *fp_in[INFILE_NUM ];
EXTERN FILE *fp_out[OUTFILE_NUM ];
EXTERN char infile_name[INFILE_NUM][BUFFER_MAX];
EXTERN char outfile_name[OUTFILE_NUM][BUFFER_MAX];

#define KEIZAI						0
#define SOTOWAKU_JINKO				1
#define SOTOWAKU_1GOU				2
#define SOTOWAKU_3GOU				3
#define SOTOWAKU_2GOU_KOU			4
#define SOTOWAKU_2GOU_KOK			5
#define SOTOWAKU_2GOU_REN			6
#define SOTOWAKU_2GOU_SIG			7
#define SOTOWAKU_JINKO_JURAI		8
#define SOTOWAKU_1GOU_JURAI			9
#define SOTOWAKU_3GOU_JURAI			10
#define LIFETABLE				11
#define BIRTH					12
#define NOUFU_MENJO_WARIAI		13
#define TUINOU					14
#define MOKUHYOUNOUFUSAISHU		15
#define FUKANOUFU				16
#define DTST_1M				17
#define DTST_3M				30
#define DTST_1F				34
#define DTST_3F				45
#define KISO_1M				49
#define KISO_3M				62
#define KISO_1F				65
#define KISO_3F				78
#define WARIBIKI			82
#define KYUFU				83
#define KYUFU2				84
#define IZOKU_KEINEN		85

#define PRINT_HIHO			0
#define PRINT_ROREI			1
#define PRINT_ROREI_SHINKI	2
#define PRINT_SHOGAI		3
#define PRINT_IZOKU			4
#define KISONENKIN			5
#define DOKUZI				6
#define SEITEI_KAITEI		7
#define KAITEI				8
#define BUNPU				9
#define PENSION				10
