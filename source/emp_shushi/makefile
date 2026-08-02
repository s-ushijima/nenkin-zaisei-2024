OBJS = main.o cntl.o stdfun.o fopn.o fcls.o flck.o econ.o rdfl.o\
       shus.o shus_calc.o shus_out.o shus_fullout.o

/suuri/rev2024/emp/exec/asys20: ${OBJS}
	cc -g -o $@ ${OBJS} -lm

.c.o:
	cc -c -g $<

clean:
	rm -f *.o

startm:
	nkf -w --overwrite *.c
	nkf -w --overwrite *.h
	header_maker2 glvam.h glva.h

startn:
	header_maker2 glvam.h glva.h
