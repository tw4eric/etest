export TOP_DIR = $(shell pwd)

CXX=g++
CPPFLAGS=-fPIC
CPPFLAGS+= -DLINUX -DPOSIX_THREADS -ggdb
OBJDIR=${TOP_DIR}
INCLUDES = -I$(TOP_DIR)
LINKER_FLAGS = -shared -ggdb

MODULENAME=etest
LIBRARY_FILE = lib$(MODULENAME).so

.SUFFIXES: .cc .hh .h .exe .o

SOURCE_FILES=$(shell ls *.cc)
OBJECTS=$(SOURCE_FILES:.cc=.o)

all: library

.cc.o:
	${CXX} ${INCLUDES} ${CPPFLAGS} -c -o ${OBJDIR}/$@ $<

.cpp.exe:
	${CXX} ${CPPFLAGS} ${INCLUDES} -L. -l${MODULENAME} $< -o $@

library: ${LIBRARY_FILE}

${LIBRARY_FILE}: ${OBJECTS}
	${CXX} $(LINKER_FLAGS) -o ${LIBRARY_FILE} ${OBJDIR}/*.o 

${OBJECTS}: ${SOURCE_FILES} *.hh

TEST_SRC=sampletest.cpp
TEST_EXE=sampletest.exe
GTEST_EXE=gsampletest.exe

all: library testexe

clean:
	rm -f $(LIBRARY_FILE) *.o ${TEST_EXE}

testexe: library ${TEST_EXE}

test: testexe
	LD_LIBRARY_PATH=. ./${TEST_EXE}

gtestexe: ${TEST_SRC}
	g++ -DLINUX -DUSE_GTEST `gtest-config --cppflags` $< `gtest-config --ldflags` -lgtest -lpthread -o ${GTEST_EXE}

gtest: gtestexe
	LD_LIBRARY_PATH=`gtest-config --libdir`:$${LD_LIBRARY_PATH} ./${GTEST_EXE}
