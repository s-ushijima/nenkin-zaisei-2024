#ifdef MECON_H_INCLUDED
	#define MECON_H_INCLUDED
	#define EXTERN 
#else
	#define EXTERN extern
#endif

EXTERN double Full_Pension[SAISHUNENDO - SHONENDO + 1][MAX_ROREI_JUKYU + 1];
EXTERN double Kakyu_Tanka_12shi[SAISHUNENDO - SHONENDO + 1][MAX_ROREI_JUKYU + 1];
EXTERN double Kakyu_Tanka_3shiiko[SAISHUNENDO - SHONENDO + 1][MAX_ROREI_JUKYU + 1];
EXTERN double Tanka_Shibou[SAISHUNENDO - SHONENDO + 1][SHIBOU_KUBUN];
EXTERN double kaiteiritu_tannen[SAISHUNENDO - ECON_SHONENDO + 1][MAX_ROREI_JUKYU + 1];
