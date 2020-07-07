CFLAGS= -Wall -o0 -g -std=gnu99

all:  wooltest.ll wooltest2.ll wooltest3.ll wooltest0.ll wooltest5.ll wooltest wooltest2 wooltest3 wooltest0 wooltest5

wooltest:
	clang $(CFLAGS) -I../wool/src -L../wool/src wooltest.c -o wooltest -lwool -lpthread

wooltest.ll:
	clang $(CFLAGS) -I../wool/src wooltest.c -S -emit-llvm -c -o wooltest-main.ll
	llvm-link -S wooltest-main.ll ../wool/src/wool.ll -o wooltest.ll

wooltest2:
	clang $(CFLAGS) -I../wool/src -L../wool/src wooltest2.c -o wooltest2 -lwool -lpthread

wooltest2.ll:
	clang $(CFLAGS) -I../wool/src wooltest2.c -S -emit-llvm -c -o wooltest2-main.ll
	llvm-link -S wooltest2-main.ll ../wool/src/wool.ll -o wooltest2.ll

wooltest3:
	clang $(CFLAGS) -I../wool/src -L../wool/src wooltest3.c -o wooltest3 -lwool -lpthread

wooltest3.ll:
	clang $(CFLAGS) -I../wool/src wooltest3.c -S -emit-llvm -c -o wooltest3-main.ll
	llvm-link -S wooltest3-main.ll ../wool/src/wool.ll -o wooltest3.ll

wooltest0:
	clang $(CFLAGS) -I../wool/src -L../wool/src wooltest0.c -o wooltest0 -lwool -lpthread

wooltest0.ll:
	clang $(CFLAGS) -I../wool/src wooltest0.c -S -emit-llvm -c -o wooltest0-main.ll
	llvm-link -S wooltest0-main.ll ../wool/src/wool.ll -o wooltest0.ll

wooltest5:
	clang $(CFLAGS) -I../wool/src -L../wool/src wooltest5.c -o wooltest5 -lwool -lpthread

wooltest5.ll:
	clang $(CFLAGS) -I../wool/src wooltest5.c -S -emit-llvm -c -o wooltest5-main.ll
	llvm-link -S wooltest5-main.ll ../wool/src/wool.ll -o wooltest5.ll

clean:
	rm -rf *.ll
	rm -rf wooltest
	rm -rf wooltest2
	rm -rf wooltest3
	rm -rf wooltest0
	rm -rf wooltest5
