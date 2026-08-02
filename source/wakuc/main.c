#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "set.h"
#include "mcntl.h"
#include "mfile_open.h"


int main(void)
{

  printf("start\n");
  
  zero();
  printf("zero姜位\n");
  
  cntl();
  printf("cntl姜位\n");
  
  readdata();
  printf("readdata姜位\n");
  
  setjinko();
  printf("setjinko姜位\n");
  
  simlroud();
  printf("simlroud姜位\n");
  
  simlkyos();
  printf("simlkyos姜位\n");
  
  simlkou();
  printf("simlkou姜位\n");
  
  simlichisan();
  printf("simlichisan姜位\n");
  
  simlpart();
  printf("simlpart姜位\n");
  
  fout();
  printf("fout姜位\n");
  
  roudfout();
  printf("roudfout姜位\n");
  
  cutout();
  printf("cutout姜位\n");
  
  fclose ( fp_err );
  
  printf("end\n"); 
  
  return 0;
}
