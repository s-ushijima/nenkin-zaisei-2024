int Cntlset;
int Seidn;
int Pseid;
int Useid;
int Kijun;
int Saimu;
int Fpset;

int Kyoskijun;

int Ks;
int Ke;

double Shunor;
double Ca;
double nendohosei;

int Kozai;
int Flg_Kaisho;
int Flg_Jimu;
int Flg_Dmakuro;
int Dmakuro_Yr;
int Flg_Kmakuro;
int Kmakuro_Yr, Kmakuro_Yr2;
double Kmakuro_Min;
int Kkuci;
int Sienset;
int Nenbeex;
int Nenbeex2;

int Flg_Rima;
int Rima_Yr_Str;
int Rima_Yr_End;
double Drima;

int Flg_Part;
int Part_Yr1, Part_Yr2, Part_Yr3;
double Cbm_Pt1, Cbm_Pt2;

int Flg_Sigo;

int Flg_Houjou;
int Houjou_Yr;
double Houjou_R1, Houjou_R2;

double Misyu;
double Tumawake;

int Psly, Pslsi, Pslsi2;
int Kzn, Kzny;
int Seitaikey;
int Gaisan;
int zaichou;
int hiho74;
int Touitu, Touitu_mode;
int zan_jimu, zan_nof, zan_ave, zan_fund, zan_model, Flg_hanei, zan_tobashi;
int kakusa;
int Flg_shunor, Flg_nendo,Flg_matsu;

char Nfile[5];
char Nfile2[5];
char Nfile3[5];
char Nkfile[5];
char Ecfile[5];
char Wcfile[5];
char Wcfile2[5];

char Sifile[4];

char Cutrfile1[2];
char Cutrfile2[2];
char Cutrfile3[3];
char Cutrfile4[4];
char Cutrfile5[4];

char Tumafile[3];

char Saimushu[3];
char Saimuski[3];
char Siencha[13];

double Prema[6][ENDY-STTY+1];
double Premb[6][ENDY-STTY+1];
 
double Ci[ECEDY-ECSTY+1], H[ECEDY-ECSTY+1];
double Ri[ECEDY-ECSTY+1], Ri2[ECEDY-ECSTY+1];
double HCdum[ECEDY-ECSTY+1];
double Id_Hhd[ECEDY-ECSTY+1];
double Kra[ECEDY-ECSTY+1][116-ECXA], Krb[ECEDY-ECSTY+1][116-ECXA];
double Id_Cid[ECEDY-ECSTY+1], Id_Cid_2[ECEDY-ECSTY+1];

double Ap[5][4][ENDY-STTY+1];
double Apdum[5][4][ENDY-STTY+1];
double Ap65[5][4][ENDY-STTY+1];
double Ap70[5][4][ENDY-STTY+1];
double Ap75[5][4][ENDY-STTY+1];

double A[5][4][ENDY-STTY+1];
double Adum[5][4][ENDY-STTY+1];
double A60[5][4][ENDY-STTY+1];
double A65[5][4][ENDY-STTY+1];
double A70[5][4][ENDY-STTY+1];

double Aiku[5][4][ENDY-STTY+1];
double Aikudum[5][4][ENDY-STTY+1];
double Aal[5][4][ENDY-STTY+1];

double Apart[4][ENDY-STTY+1];
double Aikupart[4][ENDY-STTY+1];
double A60part[4][ENDY-STTY+1];
double A65part[4][ENDY-STTY+1];
double A70part[4][ENDY-STTY+1];

double An[5][4][ENDY-STTY+1];
double Aniku[5][4][ENDY-STTY+1];
double Anpart[4][ENDY-STTY+1];
double Anikupart[4][ENDY-STTY+1];

double Keikagen[ENDY-STTY+1][116];
double T4xtp[5][4][7][ENDY-STTY+1][116];
double D3bxtp[5][4][14][8][ENDY-STTY+1][116];
double Kfpbxtp[5][4][14][8][ENDY-STTY+1][116];
double Kofbxtp[5][4][14][ENDY-STTY+1][116];
double Kofte[5][4][14][ENDY-STTY+1][116];
double Kofkk[5][4][14][ENDY-STTY+1][116];
double Daikbxtp[5][4][9][ENDY-STTY+1][116];  
double Kyosdx[2][9][2][ENDY-STTY+1][116];
double Kfkyosdx[2][9][2][ENDY-STTY+1][116];
double Sien[2][5][ENDY-STTY+1];
double Nofu[5][ENDY-STTY+1];
double Jyutaku[ENDY-STTY+1]; 

double Kokusyushi[10][ENDY-STTY+1];

double Scutrk1[ECEDY-ECSTY+1], Scutrk2[ECEDY-ECSTY+1];
double Scutrrh[ECEDY-ECSTY+1][116-ECXA];
double Scutrrt[ECEDY-ECSTY+1][116-ECXA];
double Scutrrki[ECEDY-ECSTY+1][116-ECXA];


double Cc[5][31][ENDY-STTY+1];
double Dc[5][31];

double Ukyu[2][5][4][ENDY-STTY+1];

double Siwake[5];
double Jisout[5];
double Tumazumi[5][ENDY-STTY+1];

 
double E3dxb[5][14][ENDY-STTY+1][116];

double Escutrrh[ECEDY-ECSTY+1][116-ECXA];
double Escutrrt[ECEDY-ECSTY+1][116-ECXA];

double Tokutyo[ECEDY-ECSTY+1][116-ECXA];

double W[ENDY-STTY+1][5], Kw[ENDY-STTY+1][5];
double Mkiso[ENDY-STTY+1], Mhirei[ENDY-STTY+1][5];

double Np[24][ENDY-STTY+1];

FILE *ifp_econ;

FILE *ifp10_usys[5];

FILE *ifp_kyos;
FILE *ifp27_tuma;

FILE *ifp_sien;
FILE *ifp_nofu;

FILE *ifp_kaiteb;
FILE *ifp_kaitea;
FILE *ifp_kokukaite;

FILE *ifp_wakum;
FILE *ifp_bas_cuta;
FILE *ifp_asys_cuta;
FILE *ifp_asys_cutb;

FILE *ofp01_shushi[5];
FILE *ofp03_summary;
FILE *ofp90_nenbe[5];

FILE *ofp_cuta, *ofp_cutb;
FILE *ofp_cuta2, *ofp_cutb2;

FILE *ofp_siwake;
FILE *ofp_Tokutyo;

FILE *ofp_NPBPkekka;
FILE *ofp_EPsummary;

FILE *ofp_test;
FILE *ifp_Touitu;
