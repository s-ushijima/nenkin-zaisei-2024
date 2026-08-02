SRCS=main.cpp prog01.cpp prog02.cpp prog03.cpp prog04.cpp prog05.cpp prog06.cpp prog07.cpp prog08.cpp prog09.cpp prog10.cpp prog11.cpp prog12.cpp prog13.cpp

OBJS=$(SRCS:.cpp=.o)
CC=g++
CC_FLAGS=-c -I ext -I common -I lib
DB=dbx
DEBUG_OUT=/suuri/rev2024/bunpu/exec/programme_bunpu_cpp.dbg
RELEASE_OUT=/suuri/rev2024/bunpu/exec/programme_bunpu_cpp
PROGPATH=/suuri/rev2024/bunpu/rslt/PROG.log

.PHONY: default
default: release # change here if needed
draft: OUTFILE=$(DEBUG_OUT)
draft: CC_FLAGS+=-g +d -xo0 -xcheck -erroff $(OP)
draft: build

.PHONY: debug
debug: OUTFILE=$(DEBUG_OUT)
debug: CC_FLAGS+=-g -O0 -Wall -Wextra $(OP)
debug: build

.PHONY: release
release: OUTFILE=$(RELEASE_OUT)
release: CC_FLAGS+=-Ofast $(OP)
release: build

.PHONY: build
build: $(OBJS)
	$(CC) -o $(OUTFILE) $(OBJS)

.cpp.o:
	$(CC) $(CC_FLAGS) $<

.PHONY: clean
clean:
	@ /bin/rm -f *.o

.PHONY: clean_all
clean_all:
	@ /bin/rm -f *.o $(DEBUG_OUT) $(RELEASE_OUT) $(PROGPATH)

.PHONY: run
run:
	@ $(RELEASE_OUT)

.PHONY: dbrun
dbrun:
	@ $(DEBUG_OUT)

.PHONY: bt
bt:
	@ $(DB) $(DEBUG_OUT) core

.PHONY: db
db:
	@ $(DB) $(DEBUG_OUT)

.PHONY: backup
backup:
	@ mkdir -p .bak
	@ /bin/cp -f Makefile .bak
	@ /bin/cp -f *.cpp .bak
	@ /bin/cp -f -r ext .bak
	@ /bin/cp -f -r common .bak
	@ /bin/cp -f -r lib .bak
	@ echo "backup has been made."

.PHONY: restore
restore:
	@ /bin/cp -f .bak/Makefile .
	@ /bin/cp -f .bak/*.cpp .
	@ /bin/cp -f -r .bak/ext .
	@ /bin/cp -f -r .bak/common .
	@ /bin/cp -f -r .bak/lib .
	@ echo "restored from backup."

.PHONY: ckprog
ckprog:
	@ tail -20 $(PROGPATH)

.PHONY: rmprog
rmprog:
	@ /bin/rm $(PROGPATH)
	@ echo "$(PROGPATH) has been removed."
