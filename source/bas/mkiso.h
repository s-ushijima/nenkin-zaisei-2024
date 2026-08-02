#ifdef MKISO_H_INCLUDED
	#define MKISO_H_INCLUDED
	#define EXTERN 
#else
	#define EXTERN extern
#endif

EXTERN double Hokenryou_m[SAISHUNENDO - SHONENDO + 1][2];
EXTERN double Hokenryou_y[SAISHUNENDO - SHONENDO + 1];
EXTERN double Fuka_Hokenryou_m[SAISHUNENDO - SHONENDO + 1];
EXTERN double Fuka_Hokenryou_y[SAISHUNENDO - SHONENDO + 1];
EXTERN double Kodomo_Noufukin[SAISHUNENDO - SHONENDO + 1];
EXTERN double Fuka_Ninzu[SAISHUNENDO - SHONENDO + 1];
EXTERN double Ichijikin[SAISHUNENDO - SHONENDO + 1][3];
EXTERN double Ichijikin_Nendomatu[SAISHUNENDO - SHONENDO + 1][3];
EXTERN double Ichijikin_Cut[SAISHUNENDO - SHONENDO + 1][3];
EXTERN double Kafu[SAISHUNENDO - SHONENDO + 1][4];
EXTERN double Kafu_Nendomatu[SAISHUNENDO - SHONENDO + 1][4];
EXTERN double Kafu_Cut[SAISHUNENDO - SHONENDO + 1][4];
EXTERN double Fuka[SAISHUNENDO - SHONENDO + 1][4];
EXTERN double Fuka_Nendomatu[SAISHUNENDO - SHONENDO + 1][4];
EXTERN double Kyoshutukin_Cut[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1];
EXTERN double Kyoshutukin_Kokko_Cut[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1];
EXTERN double Tokubetukokko_Cut[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI];
EXTERN double Tumitate[SAISHUNENDO - SHONENDO + 1];
EXTERN double Fukushi[SAISHUNENDO - SHONENDO + 1];
EXTERN double Fukushi_Cut[SAISHUNENDO - SHONENDO + 1];
EXTERN double Yuushi_Saiken[SAISHUNENDO - SHONENDO + 1];
