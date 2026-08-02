#ifdef SNAPS_H_INCLUDED
	#define SNAPS_H_INCLUDED
	#define EXTERN
#else
	#define EXTERN	extern
#endif

#define EPSILON 1.e-14

#define KAKO                  	"AK"
#define KAKO_J                  "AJ"

#define SHONENDO          2020
#define ECON_SHONENDO     2001
#define SOTOWAKU_SHONENDO 2021
#define KAKAKU_NENDO      2004
#define SUIKEISHONENDO    2020
#define SAISHUNENDO       2125
#define SUIKEISAISHUNENDO 2125
#define R_S_C_NENDO  2120
#define TUMATUMI_NENDO   2015
#define TUMATUMI_KIKAN   10
#define SOTOWAKU_SAISHUNENDO 2125

#define SUM 0
#define SEIDO_KUBUN	6
#define KOKUNEN	1
#define KOUNEN	2
#define KOKKYO	3
#define CHIKYO	4
#define SHIGAKU	5
#define BUNPAI	6

#define SHIKYU_KEITAI 3
#define KIHON 1
#define KAKYU 2

#define SHINKYU	3
#define NEW 1
#define OLD 2

#define SEIBETU 3
#define OTOKO 1
#define ONNA  2

#define NOUFU_JOTAI_SHIN	4
#define NOUFU				1
#define MENJO_ZENHAN		2
#define MENJO_KOUHAN		3
#define NOUFU_JOTAI_KYU		9
#define MENJO				2
#define KAKYU_NOUFU			3
#define KAKYU_MENJO			4
#define KASANOUFU			5
#define KASAMENJO			6
#define ROFUKU_SHITASASAE	7
#define GONEN				8

#define KYUFU_HOUHOU	3
#define IPPAN			1
#define HATACHIMAE		2

#define KYUFU_TAISHOU	3
#define KYOSHUTU		1
#define TOKUBETU		2

#define KYUFU_KUBUN	4
#define ROREI		1
#define SHOGAI		2
#define IZOKU		3

#define TOKUBETU_SHURUI		7
#define TOKUBETU_MENJO		1
#define TOKUBETU_KASAAGE	2
#define TOKUBETU_KASAMENJO	3
#define TOKUBETU_SHITASASAE	4
#define TOKUBETU_GONEN		5
#define TOKUBETU_20MAE		6

#define FUKA 2

#define OLD_NOUFU 2
#define OLD_MENJO 3
#define OLD_ROREI 2
#define OLD_TURO  3

#define MAX_JUKYU      115
#define MAX_HIHO_NENREI 70
#define MIN_HIHO_NENREI 20
#define HIHO_NENREI_SUM 19
#define MAX_KYOSHUTU_NENREI 60
#define NENREI_SUM 62
#define UNDER_63   63
#define UNDER_64   64
#define UNDER_67   67

#define DATA_MAX   1000
#define DATA_MAX_C 1000
#define BUFFER_MAX 1000

void cntl( int argc , char *argv[] );
void file_open( char *file_list , FILE *fp_io[] , char file_name[][BUFFER_MAX] );
void dtst();
void ReadKokunen();
void ReadHiyousha( int seido );
void ReadKokunen_jisseki();
void ReadHiyousha_jisseki( int seido );
void waku();
void Atamawari();
void Atamawari_cut( int c_nendo );
void file_write();
void file_write_kakyu();
void file_write_2();
void file_write_cut();
void printout( int cut_ba );
void econ();
void read_file();
void tyousei();
void read_cut();
void tumatumi_cal();
void tumatumi_cal_jisseki();
void dokuzi_cal();

int read_str( char buffer[][BUFFER_MAX] , FILE *fp , int *data_number_ptr );
int read_data( double buffer[] , FILE *fp , int *data_number_ptr );
int chg_str( char *buf , const char *str1 , const char *str2 );
void read_headder( FILE *fp );
void write_BeginData( FILE *fp );
int Round( double a ,int b );
double min( double a , double b );
double max( double a , double b );
void readkiso_error( int shurui );
