#ifdef SNAPS_H_INCLUDED
	#define SNAPS_H_INCLUDED
	#define EXTERN
#else
	#define EXTERN	extern
#endif

#define KAKO                 "AK"
#define KAKO_J               "AJ"

#define SHONENDO				2020
#define SUIKEISHONENDO			2021
#define ECON_SHONENDO			2001
#define SOTOWAKU_SHONENDO		2021

#define LIFETABLE_NENDO			2020
#define R_KEINEN_SHONENDO		2015
#define R_KEINEN_SAISHUNENDO	2030
#define I_KEINEN_SHONENDO		2020
#define I_KEINEN_SAISHUNENDO	2070

#define SAISHUNENDO				2125
#define SUIKEISAISHUNENDO		2125
#define SOTOWAKU_SAISHUNENDO	2125

#define SHIKKENRITU_MIN			2019
#define SHIKKENRITU_MAX			2070

#define NENDO_JISSEKI			2022

#define N_O_NENDO            1926
#define HenkouSeinendo       1941
#define TINSURA_KAISHI       2021
#define TANSHUKU_NENDO       2017
#define TANSHUKU_HOSEI (2. / 3.)

#define TOKUTEI_NENDO        2009
#define TOKUTEI_TUKI            4

#define WAKAMONO_HENKO_NENDO 2016
#define WAKAMONO_HENKO_RITU 0.75

#define IKUKYU_HENKO_NENDO  2026
#define IKUKYU_HENKO_RITU	0.5

#define SUM 0

#define MAX_SHUBETU 7

#define OTOKO_1GOU	2
#define OTOKO_3GOU	3
#define ONNA_1GOU	5
#define ONNA_3GOU	6

#define SEIBETU		3
#define OTOKO		1
#define ONNA		2

#define MAX_HIHO_NENREI 70
#define MIN_HIHO_NENREI 20
#define MAX_KYOSHUTU_NENREI 60

#define MAX_HIHO_KIKAN (MAX_HIHO_NENREI-MIN_HIHO_NENREI)
#define HIHO_NENREI_SUM (MAX_HIHO_NENREI+1-MIN_HIHO_NENREI)

#define MAX_WAKU_NENREI 100
#define MIN_WAKU_NENREI  15

#define MIN_ROREI_JUKYU   60
#define MAX_ROREI_JUKYU  115
#define KURI_AGE_SAGE_SHIKYU_KUBUN (70-60+1)

#define MIN_SHOGAI_JUKYU  20
#define MAX_SHOGAI_JUKYU 115

#define MIN_IZOKU_TUMA_JUKYU  16
#define MAX_IZOKU_TUMA_JUKYU 115

#define MIN_IZOKU_OTTO_JUKYU  18
#define MAX_IZOKU_OTTO_JUKYU 115

#define MIN_IZOKU_KO_JUKYU  0
#define MAX_IZOKU_KO_JUKYU 19

#define MIN_KAFU_JUKYU 26
#define MAX_KAFU_JUKYU 64

#define UNDER_67   67
#define NENREI_SUM 62
#define UNDER_64   64
#define UNDER_63   63

#define SHUBETU_SUM           0
#define SHUBETU_OTOKO         7
#define SHUBETU_ONNA          8
#define SHUBETU_SUM_NENDOKAN  9

#define KURI_AGE_SAGE_SUM KURI_AGE_SAGE_SHIKYU_KUBUN

#define SANKYU_START 15
#define SANKYU_END	 49

#define MENJO_JOKYO 11
#define NOUFU_KUBUN 5
#define MENJO_DANKAI 5
#define NOUFU     		1
#define MENJO_3_4 		2
#define MENJO_1_2 		3
#define MENJO_1_4 		4
#define MENJO_HOUTEI	5
#define MENJO_SHINSEI	6
#define GAKUSEI   		7
#define WAKAMONO  		8
#define SANKYU			9
#define IKUKYU			10
#define ZENGAKU		1
#define START     1

#define KOKKO_HIKIAGE 3

#define SHOGAI_TOKYU 3

#define BUFFER_MAX 1000
#define DATA_MAX 120
#define EPSILON 1.e-14

#define SHIBOU_KUBUN	7

#define TUINOU_NENSU	10
#define TUINOU_NENSU_KUBUN	3
#define KANENDO_NENSU	2
#define KANENDO_NENSU_KUBUN	3
#define KOUNOU_NENSU	10

void cntl(int argc , char *argv[]);
void file_open(char *file_list , FILE *fp_io[] ,char file_name[][BUFFER_MAX]);
void seid();
void econ();
void zero();
void waku();
void kiso( int shubetu );
void dtst( int shubetu );
void noufuritu();
void siml( int nendo , int shubetu );
void shke( int nendo , int shubetu );
void stat();
void printout();
void kaizen();
void file_close();
int PerformSiml( int shubetu );

int read_str( char buffer[][BUFFER_MAX] , FILE *fp , int *data_number_ptr );
int read_data( double buffer[] , FILE *fp , int *data_number_ptr );
int buffer_set1( double buffer[] , FILE *fp ,int *data_number_ptr , int buf_0 , const char *msg);
int buffer_set2( double buffer[] , FILE *fp ,int *data_number_ptr , int buf_0 ,int buf_1 , const char *msg);
int data_skip( FILE *fp, int cnt );
int chg_str( char *buf, const char *str1, const char *str2 );
void read_headder( FILE *fp );
void write_BeginData( char ver[] , char ShisanNaiyou[] , FILE *fp );
double max( double a , double b );
double min( double a , double b );
double fdiv( double a , double b );
double array_sum(double x[] ,int min ,int max);
int encho_year( int nendo );
int encho_nensu( int nendo , int nenrei );
int extenda( int nendo , int nenrei );
int extendb( int nendo , int nenrei );
int extendc( int nendo , int nenrei );
int extendd( int nendo , int nenrei );

struct hihokensha scalar( double scalar , struct hihokensha InputStruct );
struct rorei scalar( double scalar , struct rorei InputStruct );
struct rorei_kyu scalar( double scalar , struct rorei_kyu InputStruct );
struct gonen scalar( double scalar , struct gonen InputStruct );
struct shogai scalar( double scalar , struct shogai InputStruct );
struct izoku scalar( double scalar , struct izoku InputStruct );
struct kafu scalar( double scalar , struct kafu InputStruct );
struct hihokensha scalar_2( double scalar , struct hihokensha InputStruct , int nendo );
struct hihokensha add( struct hihokensha InputStruct1 , struct hihokensha InputStruct2 );
struct rorei add( struct rorei InputStruct1 , struct rorei InputStruct2 );
struct rorei_kyu add( struct rorei_kyu InputStruct1 , struct rorei_kyu InputStruct2 );
struct gonen add( struct gonen InputStruct1 , struct gonen InputStruct2 );
struct shogai add( struct shogai InputStruct1 , struct shogai InputStruct2 );
struct izoku add( struct izoku InputStruct1 , struct izoku InputStruct2 );
struct kafu add( struct kafu InputStruct1 , struct kafu InputStruct2 );
struct ichijikin add( struct ichijikin InputStruct1 , struct ichijikin InputStruct2 );
struct hihokensha average_by_ninzu( struct hihokensha InputStruct );
struct rorei multiply( struct rorei InputStruct1 , struct rorei InputStruct2 );
struct rorei_kyu multiply( struct rorei_kyu InputStruct1 , struct rorei_kyu InputStruct2 );
struct shogai multiply( struct shogai InputStruct1 , struct shogai InputStruct2 );
struct izoku multiply( struct izoku InputStruct1 , struct izoku InputStruct2 );
struct kafu multiply( struct kafu InputStruct1 , struct kafu InputStruct2 );
struct rorei adjustbenefit( double scalar , struct rorei InputStruct );
struct rorei_kyu adjustbenefit( double scalar , struct rorei_kyu InputStruct );
struct gonen adjustbenefit( double scalar , struct gonen InputStruct );
struct shogai adjustbenefit( double scalar , struct shogai InputStruct );
struct izoku adjustbenefit( double scalar , struct izoku InputStruct );
struct kafu adjustbenefit( double scalar , struct kafu InputStruct );
struct rorei nendokan( struct rorei InputStruct1 , struct rorei InputStruct2 , double kaiteiritu );
struct rorei_kyu nendokan( struct rorei_kyu InputStruct1 , struct rorei_kyu InputStruct2 , double kaiteiritu );
struct gonen nendokan( struct gonen InputStruct1 , struct gonen InputStruct2 , double kaiteiritu );
struct shogai nendokan( struct shogai InputStruct1 , struct shogai InputStruct2 , 
	double kaiteiritu1 , double kaiteiritu2 );
struct izoku nendokan( struct izoku InputStruct1 , struct izoku InputStruct2 , 
	double kaiteiritu1 , double kaiteiritu2 );
struct kafu nendokan( struct kafu InputStruct1 , struct kafu InputStruct2 , double kaiteiritu );
struct ichijikin nendokan( struct ichijikin InputStruct1 , struct ichijikin InputStruct2 , double kaiteiritu );
struct rorei nendokan_64( struct rorei InputStruct1 , struct rorei InputStruct2 , 
	struct rorei InputStruct3 , double kaiteiritu );
struct rorei_kyu nendokan_64( struct rorei_kyu InputStruct1 , struct rorei_kyu InputStruct2 , 
	struct rorei_kyu InputStruct3 , double kaiteiritu );
struct gonen nendokan_64( struct gonen InputStruct1 , struct gonen InputStruct2 , 
	struct gonen InputStruct3 , double kaiteiritu );
struct shogai nendokan_64( struct shogai InputStruct1 , struct shogai InputStruct2 , 
	struct shogai InputStruct3 , double kaiteiritu );
struct izoku nendokan_64( struct izoku InputStruct1 , struct izoku InputStruct2 , 
	struct izoku InputStruct3 , double kaiteiritu );
struct ichijikin nendokan_64( struct ichijikin InputStruct1 , struct ichijikin InputStruct2 , 
	struct ichijikin InputStruct3 , double kaiteiritu );
