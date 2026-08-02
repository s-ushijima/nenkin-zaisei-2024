#define   STARTY      2020
#define   ENDY        2150
#define   KIJUN       2022
#define   KIJUNMAP    2023
#define   KS          2021
#define   KF          2125
#define   CNENDO      2005
#define   CUT_JY      2024
#define   DATA_MAX    130
#define   BUFFER_MAX  31

void zero(void) ;
void cntl(void) ;
void readdata(void) ;
void setjinko(void) ;
void simlroud(void) ;
void simlkyos(void) ;
void simlkou(void) ;
void simlichisan(void) ;
void simlpart(void) ;
void fout(void) ;
void roudfout(void) ;
void cutout(void) ;

double raund( double a, int b);
int read_csv(double buffer[], FILE *fp, int *data_number_ptr);
void karayomi( FILE *fp );
void read_map( FILE *fp, int nendo);
void read_roud( FILE *fp, int ynendo1, int ynendo2 );
void tashikomi( int yykubun1, int yykubun2, int just ); 
