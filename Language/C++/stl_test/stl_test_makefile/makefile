CXXFLAGS += -g -std=c++11

all: stl_test

stl_test: stl_test.o gmemfunc.o gmemhook.o gmemmgr.o
	g++ -o stl_test stl_test.o gmemfunc.o gmemhook.o gmemmgr.o -ldl
clean:
	rm -f stl_test *.o

