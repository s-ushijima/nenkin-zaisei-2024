
### conditions ###

# CPP files
SRCS=sepslib.cpp main.cpp zero.cpp cntl.cpp sepsd.cpp fileio.cpp flck.cpp \
	waku.cpp econ.cpp seid.cpp krgn.cpp kiso.cpp sknr.cpp subrh.cpp subrj.cpp \
	dtst.cpp shke.cpp shkehiho.cpp shkejken.cpp shkejsha.cpp siku.cpp \
	shkejuk.cpp shkekiso.cpp dsitk.cpp siml.cpp simlg.cpp simlbzw.cpp \
	simlsaite1.cpp simlsaite2.cpp simlrhnf.cpp outkn.cpp rousaki.cpp \
	pstat.cpp stat.cpp outhou.cpp crshfl.cpp


# O files (string-replacement .cpp -> .o)
OBJS=$(SRCS:.cpp=.o)


# C++ compiler and compile flags
CC=g++
#CC=/opt/OSS124/SolarisStudio12.4-solaris-sparc-bin/solarisstudio12.4/bin/CC
CC_FLAGS=-c -I ext -I common -I lib


# debugger
DB=dbx


# names of output files (arbitrary)
DEBUG_OUT=/suuri/rev2024/emp/exec/usys20.dbg
RELEASE_OUT=/suuri/rev2024/emp/exec/usys20


# path of PROG.log
PROGPATH=/suuri/rev2024/emp/rslt/u-rev/PROG.log


### compile and build (link) ###

# default setting
# [usage] make (= make default)
.PHONY: default
default: release # change here if needed


# compile and build in debug mode, ignoring warnings
# [usage] make draft
draft: OUTFILE=$(DEBUG_OUT)
draft: CC_FLAGS+=-g +d -xo0 -xcheck -erroff $(OP)
draft: build


# compile and build in debug mode
# [usage] make debug
# [usage] make debug OP=-DDEBUG
.PHONY: debug
debug: OUTFILE=$(DEBUG_OUT)
# debug: CC_FLAGS+=-g +d -xo0 -xcheck +w2 $(OP)
debug: CC_FLAGS+=-g -O0 -Wall -Wextra $(OP)
debug: build


# compile and build in release mode
# [usage] make release
# [usage] make release OP=-DNDEBUG
.PHONY: release
release: OUTFILE=$(RELEASE_OUT)
# release: CC_FLAGS+=-fast -w -xo2 -xcheck $(OP)
# release: CC_FLAGS+=$(OP)¡¡it takes a lot of time
release: CC_FLAGS+=-O2 $(OP)
release: build


# need not use this
.PHONY: build
build: $(OBJS)
	$(CC) -o $(OUTFILE) $(OBJS)


# just order how to compile .cpp files
.cpp.o:
	$(CC) $(CC_FLAGS) $<



### clean ###

# remove intermediate files
# [usage] make clean
.PHONY: clean
clean:
	@ /bin/rm -f *.o


# remove unnecessary files
# [usage] make clean_all
.PHONY: clean_all
clean_all:
	@ /bin/rm -f *.o $(DEBUG_OUT) $(RELEASE_OUT) $(PROGPATH)



### run (with debugger) ###

# run release-outfile
# [usage] make run
.PHONY: run
run:
	@ $(RELEASE_OUT)
	
# run debug-outfile
# [usage] make dbrun
.PHONY: dbrun
dbrun:
	@ $(DEBUG_OUT)

# back-trace core-dump file with debugger (if core was dumped, try this)
# [usage] make bt
#   (dbx) print x
#   (dbx) quit
.PHONY: bt
bt:
	@ $(DB) $(DEBUG_OUT) core


# run debug-outfile with debugger
# [note] using `dbx` as a debugger here
# [note] please refer to some manual/tips of debugger; I hope this helps.
# [usage] make db
#   (dbx) run
#   (dbx) where (= stack-trace) ; try this if program crashed; you may detect the error point.
# [appendix]
#   (dbx) stop at waku.cpp:62 (= set breakpoint in waku.cpp at line 62) ; set a breakpoint (at the error point).
#   (dbx) run
#   (dbx) print k
#   (dbx) print kk
#   (dbx) print vals.at(1)
#
#   (dbx) cont
#
#   (dbx) quit
.PHONY: db
db:
	@ $(DB) $(DEBUG_OUT)



### backup and restore ###

# backup source files (owerwrite)
# [usage] make backup
.PHONY: backup
backup:
	@ mkdir -p .bak
	@ /bin/cp -f Makefile .bak
	@ /bin/cp -f *.cpp .bak
	@ /bin/cp -f -r ext .bak
	@ /bin/cp -f -r common .bak
	@ /bin/cp -f -r lib .bak
	@ echo "backup has been made."

# restore from backup (overwrite)
# [usage] make restore
.PHONY: restore
restore:
	@ /bin/cp -f .bak/Makefile .
	@ /bin/cp -f .bak/*.cpp .
	@ /bin/cp -f -r .bak/ext .
	@ /bin/cp -f -r .bak/common .
	@ /bin/cp -f -r .bak/lib .
	@ echo "restored from backup."



### PROG.log (if no dumps) ###

.PHONY: ckprog
ckprog:
	@ tail -20 $(PROGPATH)

.PHONY: rmprog
rmprog:
	@ /bin/rm $(PROGPATH)
	@ echo "$(PROGPATH) has been removed."
