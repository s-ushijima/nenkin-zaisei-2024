#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "set.h"
#include "cntl.h"
#include "file_open.h"

void simlpart(void)
{

  int    XEND   ;
  int    TMO    ;
  double TMP    ;
  double TMQ    ;
  double TMR    ;
  double TMS    ;
  int    pkubun ;
  int    tkubun ;
  int    ykubun ;
  double kbetu_tankoj[ENDY-STARTY+1][5][17][4]  ;
  double nbetu_tankoj[ENDY-STARTY+1][5][121][4] ;
  double kbetu_partgen[ENDY-STARTY+1][5][17][8] ;


  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ){
    for ( sei = 0 ; sei <= 4 ; sei++ ){
      for ( kubun = 0 ; kubun <= 16 ; kubun++ ){
        for ( tkubun = 0 ; tkubun <= 3 ; tkubun++ ){
          kbetu_tankoj[nendo-STARTY][sei][kubun][tkubun] = 0.0 ;
        }
      }
      for ( nenrei = 0 ; nenrei <= 120 ; nenrei++ ){
        for ( tkubun = 0 ; tkubun <= 3 ; tkubun++ ){
          nbetu_tankoj[nendo-STARTY][sei][nenrei][tkubun] = 0.0 ;
        }
      }
      for ( kubun = 0 ; kubun <= 16 ; kubun++ ){
        for ( pkubun = 0 ; pkubun <= 7 ; pkubun++ ){
          kbetu_partgen[nendo-STARTY][sei][kubun][pkubun] = 0.0 ;
        }
      }
    }
  }

  for ( nendo = PARTKYR ; nendo <= ENDY ; nendo++ ){
    for ( sei = 1 ; sei <= 2 ; sei++ ){
      for ( kubun = 1 ; kubun <= 15 ; kubun++ ){
        TMO = kubun * 5 + 12 ;
        for ( nenrei = TMO - 2 ; nenrei <= TMO + 2 ; nenrei++ ){
          kbetu_tankoj[nendo-STARTY][sei][kubun][1]
		  += ( koyou_j_m[4][nendo-STARTY][sei][nenrei] + koyou_j_m[5][nendo-STARTY][sei][nenrei] ) ;
          kbetu_tankoj[nendo-STARTY][sei][kubun][2]
          += ( koyou_j_m[1][nendo-STARTY][sei][nenrei] + koyou_j_m[2][nendo-STARTY][sei][nenrei] + koyou_j_m[6][nendo-STARTY][sei][nenrei] ) ;
          kbetu_tankoj[nendo-STARTY][sei][kubun][3]
	      += ( koyou_j_m[3][nendo-STARTY][sei][nenrei] ) ;
        }
      }
    }
  }

  for ( nendo = PARTKYR + 1 ; nendo <= ENDY ; nendo++ ){
    for ( sei = 1 ; sei <= 2 ; sei++ ){
      for ( kubun = 1 ; kubun <= 15 ; kubun++ ){
        for ( pkubun = 1 ; pkubun <= 7 ; pkubun++ ){
          if ( pkubun <= 2 || pkubun == 7 ){
            for ( tkubun = 1; tkubun <= 3 ; tkubun++ ){
              for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
                if ( kbetu_tankoj[PARTKYR-STARTY][sei][kubun][tkubun] > 0.0 ){
                  kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][tkubun][ykubun]
                  = kbetu_partkiso[sei][kubun][pkubun][tkubun][ykubun]
                    * kbetu_tankoj[nendo-STARTY][sei][kubun][tkubun]
					/ kbetu_tankoj[PARTKYR-STARTY][sei][kubun][tkubun] ;
                }
                else{
                  kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][tkubun][ykubun] = 0.0 ;
                  printf ( "パート推計で%d年度の性%d年齢区分%d時間区分%dの短雇がマイナス!\n",
						   PARTKYR, sei, kubun, tkubun );
				  fprintf( fp_err, "パート推計で%d年度の性%d年齢区分%d時間区分%dの短雇がマイナス!\n",
						   PARTKYR, sei, kubun, tkubun );
                }
              }
            }
          }
        }
        for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
          for ( ykubun = 1 ; ykubun <=3 ; ykubun++ ){
            if ( ( kubun >= 2 ) && ( kubun <= 9 ) ){
              kbetu_partnin[nendo-STARTY][sei][kubun][1][tkubun][ykubun]
			  += kbetu_partnin[nendo-STARTY][sei][kubun][7][tkubun][ykubun] ;
              kbetu_partnin[nendo-STARTY][sei][kubun][7][tkubun][ykubun] = 0.0 ;
            }
            if ( tkubun == 2 ){
              kbetu_partnin[nendo-STARTY][sei][kubun][1][tkubun][ykubun]
		      += kbetu_partnin[nendo-STARTY][sei][kubun][2][tkubun][ykubun] ;
              kbetu_partnin[nendo-STARTY][sei][kubun][2][tkubun][ykubun] = 0.0 ;
			}
            kbetu_partnin[nendo-STARTY][sei][kubun][0][tkubun][ykubun]
            = kbetu_partnin[nendo-STARTY][sei][kubun][1][tkubun][ykubun] 
            + kbetu_partnin[nendo-STARTY][sei][kubun][2][tkubun][ykubun] 
            + kbetu_partnin[nendo-STARTY][sei][kubun][7][tkubun][ykubun] ;
          }
        }
      }
    }
  }

  for ( nendo = 2024 ; nendo <= ENDY ; nendo++ ){
    for ( sei = 1 ; sei <= 2 ; sei++ ){
      for ( kubun = 2 ; kubun <= 9 ; kubun++ ){
        TMO = kubun * 5 + 12 ;
        for ( nenrei = TMO - 2 ; nenrei <= TMO + 2 ; nenrei++ ){
          kbetu_partgen[nendo-STARTY][sei][kubun][1] += ichigou[1][nendo-STARTY][sei][nenrei] ;
          kbetu_partgen[nendo-STARTY][sei][kubun][2] += sangou[0][nendo-STARTY][sei][nenrei] ;
        }
      }
      for ( kubun = 10 ; kubun <= 11 ; kubun++ ){
        TMO = kubun * 5 + 12 ;
        for ( nenrei = TMO - 2 ; nenrei <= TMO + 2 ; nenrei++ ){
          kbetu_partgen[nendo-STARTY][sei][kubun][1] += ichigou[2][nendo-STARTY][sei][nenrei] ;
        }
      }
    }
  }

  for ( nendo = 2024 ; nendo <= ENDY ; nendo++ ){
    for ( sei = 1 ; sei <= 2 ; sei++ ){
      for ( kubun = 2 ; kubun <= 9 ; kubun++ ){
        for ( pkubun = 1 ; pkubun <= 2 ; pkubun++ ){
          for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
 		      kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][0][ykubun]
              += kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][tkubun][ykubun] ;
            }
          }
 		  for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
              if ( kbetu_partgen[nendo-STARTY][sei][kubun][pkubun] < 0.0 ){
                kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][tkubun][ykubun] = 0.0 ;
				printf ( "パート %d年度の性%d、年齢区分%dの元制度%dがマイナス\n",
                          nendo, sei, kubun, pkubun ) ;
                fprintf( fp_err, "パート %d年度の性%d、年齢区分%dの元制度%dがマイナス\n",
                          nendo, sei, kubun, pkubun ) ;
			  }
              else if ( kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][0][ykubun]
                      > kbetu_partgen[nendo-STARTY][sei][kubun][pkubun] ){
				kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][tkubun][ykubun]
                *= ( kbetu_partgen[nendo-STARTY][sei][kubun][pkubun]
                   / kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][0][ykubun] ) ;
                printf ( "パート %d年度の性%d、年齢区分%d、元制度%dが減算しきれない\n",
                          nendo, sei, kubun, pkubun ) ;
                fprintf( fp_err, "パート %d年度の性%d、年齢区分%d、元制度%dが減算しきれない\n",
                          nendo, sei, kubun, pkubun ) ;
		      }
              TMO = kubun * 5 + 12 ;
              for ( nenrei = TMO - 2 ; nenrei <= TMO + 2 ; nenrei++ ){
                  p_wari[nendo-STARTY][sei][nenrei][pkubun][tkubun][ykubun]
                  = kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][tkubun][ykubun]
                  / kbetu_partgen[nendo-STARTY][sei][kubun][pkubun] ;
              }
            }
		  }
        }
      }
      
      for ( kubun = 10 ; kubun <= 11 ; kubun++ ){
        for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
          for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
 		    kbetu_partnin[nendo-STARTY][sei][kubun][1][0][ykubun]
            += kbetu_partnin[nendo-STARTY][sei][kubun][1][tkubun][ykubun] ;
          }
        }
        for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
          for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
            if ( kbetu_partgen[nendo-STARTY][sei][kubun][1] < 0.0 ){ 
              kbetu_partnin[nendo-STARTY][sei][kubun][1][tkubun][ykubun] = 0.0 ;
			  printf ( "パート %d年度の性%d、年齢区分%dの元制度1がマイナス\n",
                        nendo, sei, kubun ) ;
              fprintf( fp_err, "パート %d年度の性%d、年齢区分%dの元制度1がマイナス\n",
                        nendo, sei, kubun ) ;
			}
            else if ( kbetu_partnin[nendo-STARTY][sei][kubun][1][0][ykubun]
                      > kbetu_partgen[nendo-STARTY][sei][kubun][1] ){
			  kbetu_partnin[nendo-STARTY][sei][kubun][1][tkubun][ykubun]
              *= ( kbetu_partgen[nendo-STARTY][sei][kubun][1]
                 / kbetu_partnin[nendo-STARTY][sei][kubun][1][0][ykubun] ) ;
              printf ( "パート %d年度の性%d、年齢区分%d、元制度1が減算しきれない\n",
                        nendo, sei, kubun ) ;
              fprintf( fp_err, "パート %d年度の性%d、年齢区分%d、元制度1が減算しきれない\n",
                        nendo, sei, kubun ) ;
		    }
            TMO = kubun * 5 + 12 ;
            for ( nenrei = TMO - 2 ; nenrei <= TMO + 2 ; nenrei++ ){
              p_wari[nendo-STARTY][sei][nenrei][1][tkubun][ykubun]
              = kbetu_partnin[nendo-STARTY][sei][kubun][1][tkubun][ykubun]
              / kbetu_partgen[nendo-STARTY][sei][kubun][1] ;
            }
          }
        }
      }
    }
    for ( sei = 3 ; sei <= 4 ; sei++ ){
      for ( nenrei = 20 ; nenrei <= 69 ; nenrei++ ){
        for ( pkubun = 1 ; pkubun <= 7 ; pkubun++ ){
          for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
              p_wari[nendo-STARTY][sei][nenrei][pkubun][tkubun][ykubun]
              = p_wari[nendo-STARTY][2][nenrei][pkubun][tkubun][ykubun] ;
            }
          }
        }
      }
    }
  }

  for ( nendo = PARTKYR ; nendo <= ENDY ; nendo++ ){
    for ( sei = 1 ; sei <= 4 ; sei++ ){
      for ( nenrei = 15 ; nenrei <= 100 ; nenrei ++ ){
        nbetu_tankoj[nendo-STARTY][sei][nenrei][1]
        = koyou_j_m[4][nendo-STARTY][sei][nenrei] + koyou_j_m[5][nendo-STARTY][sei][nenrei] ;
        nbetu_tankoj[nendo-STARTY][sei][nenrei][2]
        = koyou_j_m[1][nendo-STARTY][sei][nenrei] + koyou_j_m[2][nendo-STARTY][sei][nenrei] + koyou_j_m[6][nendo-STARTY][sei][nenrei] ;
        nbetu_tankoj[nendo-STARTY][sei][nenrei][3]
	    = koyou_j_m[3][nendo-STARTY][sei][nenrei] ;
      }
    }
  }

  for ( nendo = 2024 ; nendo <= ENDY ; nendo++ ){
    for ( nenrei = 15 ; nenrei <= 19 ; nenrei++ ){
      for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
        for ( sei = 1 ; sei <= 2 ; sei++ ){
          for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun]
            = kbetu_partnin[nendo-STARTY][sei][1][7][tkubun][ykubun]
            * nbetu_tankoj[nendo-STARTY][sei][nenrei][tkubun] / kbetu_tankoj[nendo-STARTY][sei][1][tkubun] ;
          }
        }
        for ( sei = 3 ; sei <= 4 ; sei++ ){
          for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun]
            = partnin[nendo-STARTY][2][nenrei][7][tkubun][ykubun] 
            * nbetu_tankoj[nendo-STARTY][sei][nenrei][tkubun] / nbetu_tankoj[nendo-STARTY][2][nenrei][tkubun] ;
          }
        }
        for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
          partnin[nendo-STARTY][0][nenrei][7][tkubun][ykubun]
          = partnin[nendo-STARTY][1][nenrei][7][tkubun][ykubun]
          + partnin[nendo-STARTY][2][nenrei][7][tkubun][ykubun] ;
        }
      }
    }
    for ( nenrei = 20 ; nenrei <= 59 ; nenrei++ ){
      for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
        for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
          for ( sei = 1 ; sei <= 4 ; sei++ ){
            partnin[nendo-STARTY][sei][nenrei][1][tkubun][ykubun]
            = ichigou[1][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][1][tkubun][ykubun] ;
            partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun]
            = sangou[0][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][2][tkubun][ykubun] ;
            partnin[nendo-STARTY][sei][nenrei][3][tkubun][ykubun]
            = sangou[1][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][2][tkubun][ykubun] ;
            partnin[nendo-STARTY][sei][nenrei][4][tkubun][ykubun]
            = sangou[4][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][2][tkubun][ykubun] ;
            partnin[nendo-STARTY][sei][nenrei][5][tkubun][ykubun]
            = sangou[5][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][2][tkubun][ykubun] ;
            partnin[nendo-STARTY][sei][nenrei][6][tkubun][ykubun]
            = sangou[6][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][2][tkubun][ykubun] ;
          }
          for ( pkubun = 1 ; pkubun <= 6 ; pkubun++ ){
            partnin[nendo-STARTY][0][nenrei][pkubun][tkubun][ykubun]
            = partnin[nendo-STARTY][1][nenrei][pkubun][tkubun][ykubun]
            + partnin[nendo-STARTY][2][nenrei][pkubun][tkubun][ykubun] ;
          }
        }
      }
      if ( nendo < PARTYR1 ){
        for ( sei = 1 ; sei <= 4 ; sei++ ){
          for( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            ichigou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][1][tkubun][1] ;
            sangou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][3][tkubun][1] ;
            sangou[4][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][4][tkubun][1] ;
            sangou[5][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][5][tkubun][1] ;
            sangou[6][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][6][tkubun][1] ;
          }
        }
      }
      else if ( nendo < PARTYR2 ){
        for ( sei = 1 ; sei <= 4 ; sei++ ){
          for( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            ichigou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][1][tkubun][2] ;
            sangou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][3][tkubun][2] ;
            sangou[4][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][4][tkubun][2] ;
            sangou[5][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][5][tkubun][2] ;
            sangou[6][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][6][tkubun][2] ;
          }
        }
      }
      else{
        for ( sei = 1 ; sei <= 4 ; sei++ ){
          for( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            ichigou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][1][tkubun][3] ;
            sangou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][3][tkubun][3] ;
            sangou[4][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][4][tkubun][3] ;
            sangou[5][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][5][tkubun][3] ;
            sangou[6][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][6][tkubun][3] ;
          }
        }
      }
      ichigou[1][nendo-STARTY][0][nenrei]
      = ichigou[1][nendo-STARTY][1][nenrei] + ichigou[1][nendo-STARTY][2][nenrei] ;
      sangou[1][nendo-STARTY][0][nenrei]
      = sangou[1][nendo-STARTY][1][nenrei] + sangou[1][nendo-STARTY][2][nenrei] ;
      sangou[4][nendo-STARTY][0][nenrei]
      = sangou[4][nendo-STARTY][1][nenrei] + sangou[4][nendo-STARTY][2][nenrei] ;
      sangou[5][nendo-STARTY][0][nenrei]
      = sangou[5][nendo-STARTY][1][nenrei] + sangou[5][nendo-STARTY][2][nenrei] ;
      sangou[6][nendo-STARTY][0][nenrei]
      = sangou[6][nendo-STARTY][1][nenrei] + sangou[6][nendo-STARTY][2][nenrei] ;
    }
    for ( nenrei = 60 ; nenrei <= 69 ; nenrei++ ){
      for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
        for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
          for ( sei = 1 ; sei <= 4 ; sei++ ){
            partnin[nendo-STARTY][sei][nenrei][1][tkubun][ykubun]
            = ichigou[2][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][1][tkubun][ykubun] ;
          }
          partnin[nendo-STARTY][0][nenrei][1][tkubun][ykubun]
          = partnin[nendo-STARTY][1][nenrei][1][tkubun][ykubun]
          + partnin[nendo-STARTY][2][nenrei][1][tkubun][ykubun] ; 
        }
      }
      if ( nendo < PARTYR1 ){
        for ( sei = 1 ; sei <= 4 ; sei++ ){
          for( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            ichigou[2][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][1][tkubun][1] ;
          }
        }
      }
      else if ( nendo < PARTYR2 ){
        for ( sei = 1 ; sei <= 4 ; sei++ ){
          for( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            ichigou[2][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][1][tkubun][2] ;
          }
        }
      }
      else{
        for ( sei = 1 ; sei <= 4 ; sei++ ){
          for( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            ichigou[2][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][1][tkubun][3] ;
          }
        }
      }
      ichigou[2][nendo-STARTY][0][nenrei]
      = ichigou[2][nendo-STARTY][1][nenrei] + ichigou[2][nendo-STARTY][2][nenrei] ;
    }
    for ( kubun = 10 ; kubun <= 11 ; kubun++ ){
      TMO = kubun * 5 + 12 ;
      for ( nenrei = TMO - 2 ; nenrei <= TMO + 2 ; nenrei++ ){
        for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
          for ( sei = 1 ; sei <= 2 ; sei++ ){
            for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
              partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun]
              = kbetu_partnin[nendo-STARTY][sei][kubun][7][tkubun][ykubun]
              * nbetu_tankoj[nendo-STARTY][sei][nenrei][tkubun] / kbetu_tankoj[nendo-STARTY][sei][kubun][tkubun] ;
            }
          }
          for ( sei = 3 ; sei <= 4 ; sei++ ){
            for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
              partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun]
              = partnin[nendo-STARTY][2][nenrei][7][tkubun][ykubun] 
              * nbetu_tankoj[nendo-STARTY][sei][nenrei][tkubun] / nbetu_tankoj[nendo-STARTY][2][nenrei][tkubun] ;
			}
          }
          for( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            partnin[nendo-STARTY][0][nenrei][7][tkubun][ykubun]
            = partnin[nendo-STARTY][1][nenrei][7][tkubun][ykubun]
            + partnin[nendo-STARTY][2][nenrei][7][tkubun][ykubun] ;
          }
        }
      }
    }
    XEND = xend[nendo-STARTY] ;
    for( nenrei = 60 ; nenrei <= XEND - 1 ; nenrei++ ){
      for ( sei = 1 ; sei <= 4 ; sei++ ){
        for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
          for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
            partnin[nendo-STARTY][sei][nenrei][7][0][ykubun]
            += partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun] ;
          }
        }
        if ( ichigou[1][nendo-STARTY][sei][nenrei] < 0. || sangou[0][nendo-STARTY][sei][nenrei] < 0. ){
		  printf ( "パート(45年化) %d年度の性%d、年齢%dの１号または３号がマイナス\n",
                    nendo, sei, nenrei ) ;
          fprintf( fp_err, "パート(45年化) %d年度の性%d、年齢%dの１号または３号がマイナス\n",
                    nendo, sei, nenrei ) ;
          exit(2) ;
		}
        else{
          for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
              if ( partnin[nendo-STARTY][sei][nenrei][7][0][ykubun]
                 > ichigou[1][nendo-STARTY][sei][nenrei] + sangou[0][nendo-STARTY][sei][nenrei] ){
                partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun]
                *= ( ( ichigou[1][nendo-STARTY][sei][nenrei] + sangou[0][nendo-STARTY][sei][nenrei] )
                     / partnin[nendo-STARTY][sei][nenrei][7][0][ykubun] ) ;
              }
              if ( tkubun != 2 ){
                p_wari[nendo-STARTY][sei][nenrei][7][tkubun][ykubun]
                = partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun]
                / ( ichigou[1][nendo-STARTY][sei][nenrei] + sangou[0][nendo-STARTY][sei][nenrei] ) ;
              }
              else{
                p_wari[nendo-STARTY][sei][nenrei][7][tkubun][ykubun]
                = partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun]
                / ichigou[1][nendo-STARTY][sei][nenrei] ;
              }
              partnin[nendo-STARTY][sei][nenrei][1][tkubun][ykubun]
              += ichigou[1][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][7][tkubun][ykubun] ;
              if ( tkubun != 2 ) {
                partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun]
                = sangou[0][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][7][tkubun][ykubun] ;
                partnin[nendo-STARTY][sei][nenrei][3][tkubun][ykubun]
                = sangou[1][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][7][tkubun][ykubun] ;
                partnin[nendo-STARTY][sei][nenrei][4][tkubun][ykubun]
                = sangou[4][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][7][tkubun][ykubun] ;
                partnin[nendo-STARTY][sei][nenrei][5][tkubun][ykubun]
                = sangou[5][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][7][tkubun][ykubun] ;
                partnin[nendo-STARTY][sei][nenrei][6][tkubun][ykubun]
                = sangou[6][nendo-STARTY][sei][nenrei] * p_wari[nendo-STARTY][sei][nenrei][7][tkubun][ykubun] ;
              }
              partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun] = 0.0 ;
            }
          }
        }
        for ( pkubun = 1 ; pkubun <= 2 ; pkubun++ ){
          for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
              partnin[nendo-STARTY][sei][nenrei][pkubun][0][ykubun]
              += partnin[nendo-STARTY][sei][nenrei][pkubun][tkubun][ykubun] ;
            }
          }
        }
        for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
          for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
            if ( tkubun != 2 ){
              if ( partnin[nendo-STARTY][sei][nenrei][1][0][ykubun] > ichigou[1][nendo-STARTY][sei][nenrei] ){
                TMP = partnin[nendo-STARTY][sei][nenrei][1][0][ykubun] - ichigou[1][nendo-STARTY][sei][nenrei] ;
                TMQ = partnin[nendo-STARTY][sei][nenrei][1][tkubun][ykubun] ;
                TMR = partnin[nendo-STARTY][sei][nenrei][1][1][ykubun] + partnin[nendo-STARTY][sei][nenrei][1][3][ykubun] ;
				if ( TMR > 0.0 ){
                  TMS = TMP * ( TMQ / TMR ) ;
				}
				else {
				  printf ( "パート %d年度の性%d、年齢%dの元１号の時間計がマイナス\n", nendo, sei, nenrei ) ;
                  fprintf( fp_err, "パート %d年度の性%d、年齢%dの元１号の時間計がマイナス\n", nendo, sei, nenrei ) ;
				  TMS = 0.0 ;
				}
                partnin[nendo-STARTY][sei][nenrei][1][tkubun][ykubun] -= TMS ;
                partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun] += TMS ;
              }
              else if ( partnin[nendo-STARTY][sei][nenrei][2][0][ykubun] > sangou[0][nendo-STARTY][sei][nenrei] ){
                TMP = partnin[nendo-STARTY][sei][nenrei][2][0][ykubun] - sangou[0][nendo-STARTY][sei][nenrei] ;
                TMQ = partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun] ;
                TMR = partnin[nendo-STARTY][sei][nenrei][2][1][ykubun] + partnin[nendo-STARTY][sei][nenrei][2][3][ykubun] ;
				if ( TMR > 0.0 ) {
                  TMS = TMP * ( TMQ / TMR ) ;
				}
				else {
				  if ( sei != 4 ) {
  				    printf ( "パート %d年度の性%d、年齢%dの元３号の時間計がマイナス\n", nendo, sei, nenrei ) ;
                    fprintf( fp_err, "パート %d年度の性%d、年齢%dの元３号の時間計がマイナス\n", nendo, sei, nenrei ) ;
				  }
				  TMS = 0.0 ;
				}
                partnin[nendo-STARTY][sei][nenrei][1][tkubun][ykubun] += TMS ;
                partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun] -= TMS ;
              }
            }
			if ( sei != 4 ) {
              partnin[nendo-STARTY][sei][nenrei][3][tkubun][ykubun]
              = partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun]
              * sangou[1][nendo-STARTY][sei][nenrei] / sangou[0][nendo-STARTY][sei][nenrei] ;
              partnin[nendo-STARTY][sei][nenrei][4][tkubun][ykubun]
              = partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun]
              * sangou[4][nendo-STARTY][sei][nenrei] / sangou[0][nendo-STARTY][sei][nenrei] ;
              partnin[nendo-STARTY][sei][nenrei][5][tkubun][ykubun]
              = partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun]
              * sangou[5][nendo-STARTY][sei][nenrei] / sangou[0][nendo-STARTY][sei][nenrei] ;
              partnin[nendo-STARTY][sei][nenrei][6][tkubun][ykubun]
              = partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun]
              * sangou[6][nendo-STARTY][sei][nenrei] / sangou[0][nendo-STARTY][sei][nenrei] ;
			}
          }
        }
        for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
          if ( nendo < PARTYR1 ){
            ichigou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][1][tkubun][1] ;
            sangou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][3][tkubun][1] ;
            sangou[4][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][4][tkubun][1] ;
            sangou[5][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][5][tkubun][1] ;
            sangou[6][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][6][tkubun][1] ;
          }
          else if ( nendo < PARTYR2 ){
            ichigou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][1][tkubun][2] ;
            sangou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][3][tkubun][2] ;
            sangou[4][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][4][tkubun][2] ;
            sangou[5][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][5][tkubun][2] ;
            sangou[6][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][6][tkubun][2] ;
          }
          else{
            ichigou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][1][tkubun][3] ;
            sangou[1][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][3][tkubun][3] ;
            sangou[4][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][4][tkubun][3] ;
            sangou[5][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][5][tkubun][3] ;
            sangou[6][nendo-STARTY][sei][nenrei] -= partnin[nendo-STARTY][sei][nenrei][6][tkubun][3] ;
          }
        }
      }
      ichigou[1][nendo-STARTY][2][nenrei]
      = ichigou[1][nendo-STARTY][3][nenrei] + ichigou[1][nendo-STARTY][4][nenrei] ;
      ichigou[1][nendo-STARTY][0][nenrei]
      = ichigou[1][nendo-STARTY][1][nenrei] + ichigou[1][nendo-STARTY][2][nenrei] ;
      for ( seido = 0 ; seido <= 6 ; seido++ ){
        sangou[seido][nendo-STARTY][2][nenrei] = sangou[seido][nendo-STARTY][3][nenrei] ; 
        sangou[seido][nendo-STARTY][0][nenrei]
        = sangou[seido][nendo-STARTY][1][nenrei] + sangou[seido][nendo-STARTY][2][nenrei] ;
      }
      for ( pkubun = 1 ; pkubun <= 7 ; pkubun++ ){
        for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
          for( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
            partnin[nendo-STARTY][2][nenrei][pkubun][tkubun][ykubun]
            = partnin[nendo-STARTY][3][nenrei][pkubun][tkubun][ykubun]
            + partnin[nendo-STARTY][4][nenrei][pkubun][tkubun][ykubun] ;
            partnin[nendo-STARTY][0][nenrei][pkubun][tkubun][ykubun]
            = partnin[nendo-STARTY][1][nenrei][pkubun][tkubun][ykubun]
            + partnin[nendo-STARTY][2][nenrei][pkubun][tkubun][ykubun] ;
          }
        }
      }
    }
  }

  for ( nendo = 2024 ; nendo <= ENDY ; nendo++ ){
    for ( sei = 0 ; sei <= 4 ; sei++ ){
      for ( nenrei = 15 ; nenrei <= 79 ; nenrei++ ){
        for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
          for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
            partnin[nendo-STARTY][sei][nenrei][0][tkubun][ykubun]
            = partnin[nendo-STARTY][sei][nenrei][1][tkubun][ykubun]
            + partnin[nendo-STARTY][sei][nenrei][2][tkubun][ykubun]
            + partnin[nendo-STARTY][sei][nenrei][7][tkubun][ykubun] ;
          }
        }
      }
    }
  }
  for ( nendo = 2024 ; nendo <= ENDY ; nendo++ ){
    for ( sei = 0 ; sei <= 4 ; sei++ ){
      for ( nenrei = 15 ; nenrei <= 79 ; nenrei++ ){
        for ( pkubun = 0 ; pkubun <= 7 ; pkubun++ ){
          for ( tkubun = 1 ; tkubun <= 3 ; tkubun++ ){
            for ( ykubun = 1 ; ykubun <= 3 ; ykubun++ ){
              partnin[nendo-STARTY][sei][nenrei][pkubun][0][ykubun]
              = partnin[nendo-STARTY][sei][nenrei][pkubun][1][ykubun]
			  + partnin[nendo-STARTY][sei][nenrei][pkubun][2][ykubun]
			  + partnin[nendo-STARTY][sei][nenrei][pkubun][3][ykubun] ;
            }
          }
        }
      }
    }
  }
  for ( nendo = 2024 ; nendo <= ENDY ; nendo++ ){
    for ( sei = 0 ; sei <= 4 ; sei++ ){
      for ( nenrei = 15 ; nenrei <= 79 ; nenrei++ ){
        if ( nendo < PARTYR1 ){
          partnin[nendo-STARTY][sei][nenrei][0][0][0] += partnin[nendo-STARTY][sei][nenrei][0][0][1] ;
        }
        else if ( nendo < PARTYR2 ){
          partnin[nendo-STARTY][sei][nenrei][0][0][0] += partnin[nendo-STARTY][sei][nenrei][0][0][2] ;
        }
        else{
          partnin[nendo-STARTY][sei][nenrei][0][0][0] += partnin[nendo-STARTY][sei][nenrei][0][0][3] ;
        }
      }
    }
  }

  for ( nendo = 2024 ; nendo <= ENDY ; nendo++ ){
    if ( nendo == 2024 ){
      tashikomi( 0, 1, 1 ) ;
    }
    else if ( nendo <  PARTYR1 ){
      tashikomi( 1, 1, 0 ) ;
    }
    else if ( nendo == PARTYR1 ){
      tashikomi( 1, 2, 0 ) ;
    }
    else if ( nendo <  PARTYR2 ){
      tashikomi( 2, 2, 0 ) ;
    }
    else if ( nendo == PARTYR2 ){
      tashikomi( 2, 3, 0 ) ;
    }
    else{
      tashikomi( 3, 3, 0 ) ;
    }
  }

  for ( nendo = 2024 ; nendo <= ENDY ; nendo++ ){
    TMP = 0.0 ;  TMQ = 0.0 ;  TMR = 0.0 ;  TMS = 0.0 ;
    for ( nenrei = 15 ; nenrei <= 69 ; nenrei++ ){
      TMP += koyou_j_m[7][nendo-STARTY][0][nenrei] ;
      TMQ += soroudh_m[9][nendo-STARTY][0][nenrei] ;
      TMR += koyou_j_c[7][nendo-STARTY][0][nenrei] ;
      TMS += soroudh_c[9][nendo-STARTY][0][nenrei] ;
    }
    heikinh_m[10][nendo-STARTY] = TMQ / TMP ;
    heikinh_c[10][nendo-STARTY] = TMS / TMR ;
  }

  for ( nendo = 2024 ; nendo <= ENDY ; nendo++ ){
    XEND = xend[nendo-STARTY] ;
    for ( sei = 0 ; sei <= 4 ; sei++ ){
      for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ){
        ichigou[0][nendo-STARTY][sei][nenrei]
        = ichigou[1][nendo-STARTY][sei][nenrei] + ichigou[2][nendo-STARTY][sei][nenrei] ;
      }
      for ( nenrei = 20 ; nenrei <= XEND - 1 ; nenrei++ ){
        sangou[0][nendo-STARTY][sei][nenrei]
        = sangou[1][nendo-STARTY][sei][nenrei] + sangou[4][nendo-STARTY][sei][nenrei]
        + sangou[5][nendo-STARTY][sei][nenrei] + sangou[6][nendo-STARTY][sei][nenrei] ;
      }
    }
  }
}


void tashikomi( int yykubun1, int yykubun2, int just ){

  for ( sei = 0 ; sei <= 4 ; sei++ ){
    for ( nenrei = 15 ; nenrei <= 79 ; nenrei++ ){
      koyou_j_m[7][nendo-STARTY][sei][nenrei]  += partnin[nendo-STARTY][sei][nenrei][0][0][yykubun2] ;
      koyou_j_m[9][nendo-STARTY][sei][nenrei]  += partnin[nendo-STARTY][sei][nenrei][0][2][yykubun2] ;
      koyou_j_m[10][nendo-STARTY][sei][nenrei] += partnin[nendo-STARTY][sei][nenrei][0][1][yykubun2]  
                                                + partnin[nendo-STARTY][sei][nenrei][0][3][yykubun2] ;
      if ( just == 1 ){
        koyou_j_c[7][nendo-STARTY][sei][nenrei]  += partnin[nendo-STARTY][sei][nenrei][0][0][yykubun2] / 2.0 ;
        koyou_j_c[9][nendo-STARTY][sei][nenrei]  += partnin[nendo-STARTY][sei][nenrei][0][2][yykubun2] / 2.0 ;
        koyou_j_c[10][nendo-STARTY][sei][nenrei] += partnin[nendo-STARTY][sei][nenrei][0][1][yykubun2] / 2.0
                                                  + partnin[nendo-STARTY][sei][nenrei][0][3][yykubun2] / 2.0 ;
      }
      else if ( just == 0 ){
        koyou_j_c[7][nendo-STARTY][sei][nenrei]  += partnin[nendo-1-STARTY][sei][nenrei][0][0][yykubun1] / 2.0 
                                                  + partnin[nendo-STARTY]  [sei][nenrei][0][0][yykubun2] / 2.0 ;
        koyou_j_c[9][nendo-STARTY][sei][nenrei]  += partnin[nendo-1-STARTY][sei][nenrei][0][2][yykubun1] / 2.0
                                                  + partnin[nendo-STARTY]  [sei][nenrei][0][2][yykubun2] / 2.0 ;
        koyou_j_c[10][nendo-STARTY][sei][nenrei] += partnin[nendo-1-STARTY][sei][nenrei][0][1][yykubun1] / 2.0
                                                  + partnin[nendo-STARTY]  [sei][nenrei][0][1][yykubun2] / 2.0
                                                  + partnin[nendo-1-STARTY][sei][nenrei][0][3][yykubun1] / 2.0
                                                  + partnin[nendo-STARTY]  [sei][nenrei][0][3][yykubun2] / 2.0 ;
      }
      soroudh_m[9][nendo-STARTY][sei][nenrei] += partnin[nendo-STARTY][sei][nenrei][0][2][yykubun2] * 120.0
                                               + partnin[nendo-STARTY][sei][nenrei][0][1][yykubun2] * 100.0
                                               + partnin[nendo-STARTY][sei][nenrei][0][3][yykubun2] *  60.0 ;
      soroudh_m[7][nendo-STARTY][sei][nenrei] += partnin[nendo-STARTY][sei][nenrei][0][2][yykubun2] * 120.0 ;
      soroudh_m[8][nendo-STARTY][sei][nenrei] += partnin[nendo-STARTY][sei][nenrei][0][1][yykubun2] * 100.0
                                               + partnin[nendo-STARTY][sei][nenrei][0][3][yykubun2] *  60.0 ;
      if ( just == 1 ){
        soroudh_c[9][nendo-STARTY][sei][nenrei] += partnin[nendo-STARTY][sei][nenrei][0][2][yykubun2] * 60.0
                                                 + partnin[nendo-STARTY][sei][nenrei][0][1][yykubun2] * 50.0
                                                 + partnin[nendo-STARTY][sei][nenrei][0][3][yykubun2] * 30.0 ;
        soroudh_c[7][nendo-STARTY][sei][nenrei] += partnin[nendo-STARTY][sei][nenrei][0][2][yykubun2] * 60.0 ;
        soroudh_c[8][nendo-STARTY][sei][nenrei] += partnin[nendo-STARTY][sei][nenrei][0][1][yykubun2] * 50.0
                                                 + partnin[nendo-STARTY][sei][nenrei][0][3][yykubun2] * 30.0 ;
      }
      else if ( just == 0 ){
        soroudh_c[9][nendo-STARTY][sei][nenrei] += partnin[nendo-1-STARTY][sei][nenrei][0][2][yykubun1] * 60.0
                                                 + partnin[nendo-STARTY]  [sei][nenrei][0][2][yykubun2] * 60.0
                                                 + partnin[nendo-1-STARTY][sei][nenrei][0][1][yykubun1] * 50.0
                                                 + partnin[nendo-STARTY]  [sei][nenrei][0][1][yykubun2] * 50.0
                                                 + partnin[nendo-1-STARTY][sei][nenrei][0][3][yykubun1] * 30.0
                                                 + partnin[nendo-STARTY]  [sei][nenrei][0][3][yykubun2] * 30.0 ;
        soroudh_c[7][nendo-STARTY][sei][nenrei] += partnin[nendo-1-STARTY][sei][nenrei][0][2][yykubun1] * 60.0
                                                 + partnin[nendo-STARTY]  [sei][nenrei][0][2][yykubun2] * 60.0 ;
        soroudh_c[8][nendo-STARTY][sei][nenrei] += partnin[nendo-1-STARTY][sei][nenrei][0][1][yykubun1] * 50.0
                                                 + partnin[nendo-STARTY]  [sei][nenrei][0][1][yykubun2] * 50.0
                                                 + partnin[nendo-1-STARTY][sei][nenrei][0][3][yykubun1] * 30.0
                                                 + partnin[nendo-STARTY]  [sei][nenrei][0][3][yykubun2] * 30.0 ;
      }
    }
  }
}
