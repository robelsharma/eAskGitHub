
CC = g++
FILES = CurlCore.cpp \
		eAskGit.cpp

OUT_EXE = eAskGit
LIB = -lcurl -lpthread

.PHONY: all build

build: $(FILES)
	$(CC) $(LIB) -o $(OUT_EXE) -g $^
	

clean:
	rm -f *.o core
	rm -f $(OUT_EXE)

all: clean build

