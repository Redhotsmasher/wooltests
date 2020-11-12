
CFLAGS = -Wall -o0 -g -fno-debug-macro -std=gnu99
IFLAGS = -I../wool/src -L../wool/src
LFLAGS = -lwool -lpthread

.DEFAULT_GOAL := unroll

.PHONY: all build ll unroll bin clean rmdummy

all: rmdummy ll unroll bin

build: ll bin

ll: simple1.ll simple2.ll simple3.ll simple4.ll simple5.ll array.ll recursion.ll fibonacci.ll nondet.ll

simple1.ll simple2.ll simple3.ll simple4.ll simple5.ll array.ll recursion.ll fibonacci.ll nondet.ll:
	clang $(CFLAGS) $(IFLAGS) src/$(patsubst %.ll,%.c,$@) -E -C -CC -o bin/$(patsubst %.ll,%_demacroed.c,$@)
	clang $(CFLAGS) $(IFLAGS) bin/$(patsubst %.ll,%_demacroed.c,$@) -S -emit-llvm -c -o bin/$(patsubst %.ll,%-main.ll,$@)
	llvm-link -S bin/$(patsubst %.ll,%-main.ll,$@) ../wool/src/wool.ll -o bin/$@

unroll: simple1_u.ll simple2_u.ll simple3_u.ll simple4_u.ll simple5_u.ll array_u.ll recursion_u.ll fibonacci_u.ll nondet_u.ll

simple1_u.ll simple2_u.ll simple3_u.ll simple4_u.ll simple5_u.ll array_u.ll recursion_u.ll fibonacci_u.ll nondet_u.ll: simple1.ll simple2.ll simple3.ll simple4.ll simple5.ll array.ll recursion.ll fibonacci.ll nondet.ll
	nidhugg --transform=bin/$@ --unroll=5 bin/$(patsubst %_u.ll,%.ll,$@)

bin: simple1 simple2 simple3 simple4 simple5 array recursion fibonacci

simple1 simple2 simple3 simple4 simple5 array recursion fibonacci:
	clang $(CFLAGS) $(IFLAGS) src/$@.c -o bin/$@ $(LFLAGS)

rmdummy:
	rm -rf bin/dummy

clean:
	rm -rf bin/*.c
	rm -rf bin/*.ll
	rm -rf bin/*.log
	echo "This folder intentionally left blank." > bin/dummy
