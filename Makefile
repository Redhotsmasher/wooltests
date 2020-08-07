CFLAGS = -Wall -O0 -g -std=gnu99
IFLAGS = -I../wool/src -L../wool/src
LFLAGS = -lwool -lpthread

.PHONY: all build ll unroll bin clean

all: rmdummy ll unroll bin

build: ll bin

ll: simple1.ll simple2.ll simple3.ll simple4.ll simple5.ll array.ll recursion.ll fibonacci.ll typepun.ll pointerarith1.ll

simple1.ll simple2.ll simple3.ll simple4.ll simple5.ll array.ll recursion.ll fibonacci.ll typepun.ll pointerarith1.ll:
	clang $(CFLAGS) $(IFLAGS) src/$(patsubst %.ll,%.c,$@) -S -emit-llvm -c -o bin/$(patsubst %.ll,%-main.ll,$@)
	llvm-link -S bin/$(patsubst %.ll,%-main.ll,$@) ../wool/src/wool.ll -o bin/$@

unroll: simple1_u.ll simple2_u.ll simple3_u.ll simple4_u.ll simple5_u.ll array_u.ll recursion_u.ll fibonacci_u.ll typepun_u.ll pointerarith1_u.ll

simple1_u.ll simple2_u.ll simple3_u.ll simple4_u.ll simple5_u.ll array_u.ll recursion_u.ll fibonacci_u.ll typepun_u.ll pointerarith1_u.ll:
	nidhugg --transform=bin/$@ --unroll=5 bin/$(patsubst %_u.ll,%.ll,$@)

bin: simple1 simple2 simple3 simple4 simple5 array recursion fibonacci typepun pointerarith1

simple1 simple2 simple3 simple4 simple5 array recursion fibonacci typepun pointerarith1:
	clang $(CFLAGS) $(IFLAGS) src/$@.c -o bin/$@ $(LFLAGS)

rmdummy:
	rm -rf bin/dummy

clean:
	rm -rf bin/*
	echo "This folder intentionally left blank." > bin/dummy
