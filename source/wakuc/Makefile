OBJS = main.o  cntl.o  stdfm.o  zero.o  readdata.o\
	   setjinko.o  simlroud.o  simlkyos.o simlkou.o\
       simlichisan.o  simlpart.o\
       roudfout.o  fout.o  cutout.o
FFLAGS = -g
/suuri/rev2024/wakuc/exec/wakuc_4_1: ${OBJS}
	gcc -g -o $@ ${OBJS} -lm
#
.c.o:
	gcc -c -g -Wall -Wextra $<

clean:
	rm -f *.o

