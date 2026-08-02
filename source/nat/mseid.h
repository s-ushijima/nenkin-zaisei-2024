#ifdef MSEID_H_INCLUDED
	#define MSEID_H_INCLUDED
	#define EXTERN
#else
	#define EXTERN extern
#endif

EXTERN double Kanou_Nensu[SAISHUNENDO - SHONENDO + 1][SAISHUNENDO - N_O_NENDO + 1];
EXTERN double Full_Pension_Shonendo[SAISHUNENDO - SHONENDO + 1][SAISHUNENDO - N_O_NENDO + 1];
EXTERN double Full_Pension_Fuka;
EXTERN double Kakyu_Tanka_12shi_Shonendo;
EXTERN double Kakyu_Tanka_3shiiko_Shonendo;
EXTERN double Tanka_Shibou_Shonendo[SHIBOU_KUBUN];
EXTERN double Tanka_Shibou_Fuka;
EXTERN double Hokenryou_Wariai[MENJO_DANKAI];
EXTERN double Shogai_Bairitu[SHOGAI_TOKYU];
EXTERN double Kokko_Wariai[KOKKO_HIKIAGE];
