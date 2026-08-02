#define SYSPATH "/suuri/rev2024"

#define STTY   9
#define ENDY  125

#define FLKS  15
#define FLKE 125


#define ECSTY   0
#define ECEDY 128

#define ECXA   60

#define MAX_REC_LEN 19999

#define XA  64
#define XB 115


int  rd_drec(char *, double *, int);
void rd_crec(char *, char *, int, int);
void strncpy2(char *, char *, int, int);
void rd_header(FILE *);
double nround(double, int);

void print_number(void);

int ii2usd(int);
int ii2psd(int);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAX3(a, b, c) ((a) > (MAX(b, c)) ? (a) : (MAX(b, c)))
#define MIN3(a, b, c) ((a) < (MIN(b, c)) ? (a) : (MIN(b, c)))

