#include "sepscommon.h"
#include "sepslib.h"
#include <stdio.h>

void seps::outkn(void) {

  REV_FOR(k, KE, KIJUN) 
  FOR(ss, 1, 2)
  FOR(i, 1, 3)
  FOR(j, 1, 6)
  FOR(x, 0, 62) {
    okiso2x.AT(k, 63, ss, i, j) += okiso2x.AT(k, x, ss, i, j);
    okiso2x.AT(k, x, ss, i, j) = 0.0;
  }


  FOR(k, KIJUN, KE)
  FOR(ss, 1, 2)
  FOR(i, 1, 6)
  FOR(x, 0, 115) {
    dk3x.AT(k, x,  0, i, 0) += dk3x.AT(k, x, ss, i, 0);
    dk3x.AT(k, x, ss, 0, 0) += dk3x.AT(k, x, ss, i, 0);
    dk3x.AT(k, x,  0, 0, 0) += dk3x.AT(k, x, ss, i, 0);
  }

  FILE *fp = fp_map["kiso"];

  FOR(k, FLKS, FLKE) {
    FOR(x, 63, 115) {
      FOR(ss, 1, 2) {
        fprintf(fp, "%d, 1, %d, 1, 1, %d, %21.14e, %21.14e, %21.14e, %21.14e\n",
            k, x, ss, okiso2x.AT(k, x, ss, 1, 1), 0.0, 0.0, okiso2x.AT(k, x, ss, 1, 3));
      }
      FOR(ss, 1, 2) {
        fprintf(fp, "%d, 1, %d, 1, 2, %d, %21.14e, %21.14e, %21.14e, %21.14e, %21.14e\n",
            k, x, ss, okiso2x.AT(k, x, ss, 2, 1), okiso2x.AT(k, x, ss, 2, 2), okiso2x.AT(k, x, ss, 2, 3), 0.0, 0.0);
      }
      FOR(ss, 1, 2) {
        fprintf(fp, "%d, 1, %d, 1, 3, %d, %21.14e, %21.14e\n",
            k, x, ss, okiso2x.AT(k, x, ss, 3, 1), okiso2x.AT(k, x, ss, 3, 2));
      }
      FOR(ss, 1, 2) {
        fprintf(fp,
            "%d, 1, %d, 2, 1, %d, "
            "%21.14e, %21.14e, %21.14e, %21.14e, %21.14e, %21.14e, %21.14e, %21.14e\n",
            k, x, ss,
            okiso2x.AT(k, x, ss, 1, 4), 0.0,
            okiso2x.AT(k, x, ss, 1, 5), 0.0,
            okiso2x.AT(k, x, ss, 1, 6), 0.0,
            0.0, 0.0);
      }
      FOR(ii, 2, 3) FOR(ss, 1, 2) {
        fprintf(fp, "%d, 1, %d, 2, %d, %d, %21.14e, %21.14e, %21.14e, %21.14e\n",
        k, x, ii, ss, okiso2x.AT(k, x, ss, ii, 4), 0.0, okiso2x.AT(k, x, ss, ii, 5), 0.0);
      }
    }

    FOR(ss, 1, 2) {
      fprintf(fp,
          "%d, 2, 1, %d, "
          "%21.14e, %21.14e, "
          "%21.14e, %21.14e, "
          "%21.14e, %21.14e, "
          "%21.14e, %21.14e, "
          "%21.14e\n",
          k, ss,
          okisor.AT(k, ss, 1, 2), okisor.AT(k, ss, 1, 3),
          okisor.AT(k, ss, 3, 2), okisor.AT(k, ss, 3, 3),
          okisor.AT(k, ss, 5, 2), okisor.AT(k, ss, 5, 3),
          okisor.AT(k, ss, 7, 2), okisor.AT(k, ss, 7, 3),
          0.0);
    }
    FOR(ss, 1, 2) {
      fprintf(fp, "%d, 2, 2, %d, %21.14e, %21.14e, %21.14e, %21.14e\n",
          k, ss,
          okisor.AT(k, ss, 9, 2), okisor.AT(k, ss, 9, 3),
          okisor.AT(k, ss, 10, 2), okisor.AT(k, ss, 10, 3));
    }
    FOR(ss, 1, 2) {
      fprintf(fp, "%d, 2, 3, %d, "
          "%21.14e, %21.14e, %21.14e, "
          "%21.14e, %21.14e, %21.14e\n",
          k, ss,
          okisor.AT(k, ss, 11, 2), okisor.AT(k, ss, 11, 3),
          okisor.AT(k, ss, 12, 2), okisor.AT(k, ss, 12, 3),
          okisor.AT(k, ss, 13, 2), okisor.AT(k, ss, 13, 3));
    }
  }

}