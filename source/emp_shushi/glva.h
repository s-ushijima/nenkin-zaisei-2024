extern int Cntlset;
extern int Seidn;
extern int Pseid;
extern int Useid;
extern int Kijun;
extern int Saimu;
extern int Fpset;

extern int Kyoskijun;

extern int Ks;
extern int Ke;

extern double Shunor;
extern double Ca;
extern double nendohosei;

extern int Kozai;
extern int Flg_Kaisho;
extern int Flg_Jimu;
extern int Flg_Dmakuro;
extern int Dmakuro_Yr;
extern int Flg_Kmakuro;
extern int Kmakuro_Yr, Kmakuro_Yr2;
extern double Kmakuro_Min;
extern int Kkuci;
extern int Sienset;
extern int Nenbeex;
extern int Nenbeex2;

extern int Flg_Rima;
extern int Rima_Yr_Str;
extern int Rima_Yr_End;
extern double Drima;

extern int Flg_Part;
extern int Part_Yr1, Part_Yr2, Part_Yr3;
extern double Cbm_Pt1, Cbm_Pt2;

extern int Flg_Sigo;

extern int Flg_Houjou;
extern int Houjou_Yr;
extern double Houjou_R1,  Houjou_R2;

extern double Misyu;
extern double Tumawake;

extern int Psly, Pslsi, Pslsi2;
extern int Kzn, Kzny;
extern int Seitaikey;
extern int Gaisan;
extern int zaichou;
extern int hiho74;
extern int Touitu,Touitu_mode;
extern int zan_jimu;
extern int zan_nof;
extern int zan_ave;
extern int zan_fund;
extern int zan_model;
extern int Flg_hanei;
extern int kakusa;
extern int Flg_shunor;
extern int Flg_nendo;
extern int zan_tobashi;
extern int Flg_matsu;

extern char Nfile[5];
extern char Nfile2[5];
extern char Nfile3[5];
extern char Nkfile[5];
extern char Ecfile[5];
extern char Wcfile[5];
extern char Wcfile2[5];

extern char Sifile[4];

extern char Cutrfile1[2];
extern char Cutrfile2[2];
extern char Cutrfile3[3];
extern char Cutrfile4[4];
extern char Cutrfile5[4];

extern char Tumafile[3];

extern char Saimushu[3];
extern char Saimuski[3];
extern char Siencha[13];

extern double Prema[6][ENDY-STTY+1];
extern double Premb[6][ENDY-STTY+1];
 
extern double Ci[ECEDY-ECSTY+1], H[ECEDY-ECSTY+1];
extern double Ri[ECEDY-ECSTY+1], Ri2[ECEDY-ECSTY+1];
extern double HCdum[ECEDY-ECSTY+1];
extern double Id_Hhd[ECEDY-ECSTY+1];
extern double Kra[ECEDY-ECSTY+1][116-ECXA], Krb[ECEDY-ECSTY+1][116-ECXA];
extern double Id_Cid[ECEDY-ECSTY+1], Id_Cid_2[ECEDY-ECSTY+1];

extern double Ap[5][4][ENDY-STTY+1];
extern double Apdum[5][4][ENDY-STTY+1];
extern double Ap65[5][4][ENDY-STTY+1];
extern double Ap70[5][4][ENDY-STTY+1];
extern double Ap75[5][4][ENDY-STTY+1];


extern double A[5][4][ENDY-STTY+1];
extern double Adum[5][4][ENDY-STTY+1];
extern double A60[5][4][ENDY-STTY+1];
extern double A65[5][4][ENDY-STTY+1];
extern double A70[5][4][ENDY-STTY+1];

extern double Aiku[5][4][ENDY-STTY+1];
extern double Aikudum[5][4][ENDY-STTY+1];
extern double Aal[5][4][ENDY-STTY+1];

extern double Apart[4][ENDY-STTY+1];
extern double Aikupart[4][ENDY-STTY+1];
extern double A60part[4][ENDY-STTY+1];
extern double A65part[4][ENDY-STTY+1];
extern double A70part[4][ENDY-STTY+1];

extern double An[5][4][ENDY-STTY+1];
extern double Aniku[5][4][ENDY-STTY+1];
extern double Anpart[4][ENDY-STTY+1];
extern double Anikupart[4][ENDY-STTY+1];

extern double Keikagen[ENDY-STTY+1][116];
extern double T4xtp[5][4][7][ENDY-STTY+1][116];
extern double D3bxtp[5][4][14][8][ENDY-STTY+1][116];
extern double Kfpbxtp[5][4][14][8][ENDY-STTY+1][116];
extern double Kofbxtp[5][4][14][ENDY-STTY+1][116];
extern double Kofte[5][4][14][ENDY-STTY+1][116];
extern double Kofkk[5][4][14][ENDY-STTY+1][116];
extern double Daikbxtp[5][4][9][ENDY-STTY+1][116];
extern double Kyosdx[2][9][2][ENDY-STTY+1][116];
extern double Kfkyosdx[2][9][2][ENDY-STTY+1][116];
extern double Sien[2][5][ENDY-STTY+1];
extern double Nofu[5][ENDY-STTY+1];
extern double Jyutaku[ENDY-STTY+1];

extern double Kokusyushi[10][ENDY-STTY+1];

extern double Scutrk1[ECEDY-ECSTY+1], Scutrk2[ECEDY-ECSTY+1];
extern double Scutrrh[ECEDY-ECSTY+1][116-ECXA];
extern double Scutrrt[ECEDY-ECSTY+1][116-ECXA];
extern double Scutrrki[ECEDY-ECSTY+1][116-ECXA];


extern double Cc[5][31][ENDY-STTY+1];
extern double Dc[5][31];

extern double Ukyu[2][5][4][ENDY-STTY+1];

extern double Siwake[5];
extern double Jisout[5];
extern double Tumazumi[5][ENDY-STTY+1];

 
extern double E3dxb[5][14][ENDY-STTY+1][116];

extern double Escutrrh[ECEDY-ECSTY+1][116-ECXA];
extern double Escutrrt[ECEDY-ECSTY+1][116-ECXA];

extern double Tokutyo[ECEDY-ECSTY+1][116-ECXA];

extern double W[ENDY-STTY+1][5], Kw[ENDY-STTY+1][5];
extern double Mkiso[ENDY-STTY+1], Mhirei[ENDY-STTY+1][5];

extern double Np[24][ENDY-STTY+1];

extern FILE *ifp_econ;

extern FILE *ifp10_usys[5];

extern FILE *ifp_kyos;
extern FILE *ifp27_tuma;

extern FILE *ifp_sien;
extern FILE *ifp_nofu;

extern FILE *ifp_kaiteb;
extern FILE *ifp_kaitea;
extern FILE *ifp_kokukaite;

extern FILE *ifp_wakum;
extern FILE *ifp_bas_cuta;
extern FILE *ifp_asys_cuta;
extern FILE *ifp_asys_cutb;

extern FILE *ofp01_shushi[5];
extern FILE *ofp03_summary;
extern FILE *ofp90_nenbe[5];
                
extern FILE *ofp_cuta, *ofp_cutb;
extern FILE *ofp_cuta2, *ofp_cutb2;

extern FILE *ofp_siwake;
extern FILE *ofp_Tokutyo;

extern FILE *ofp_NPBPkekka;
extern FILE *ofp_EPsummary;

extern FILE *ofp_test;
extern FILE *ifp_Touitu;

