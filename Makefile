FLAGS = -std=c++11 -Wall -O1

all: serve

serve: serve.cpp
	g++ ${FLAGS} -o serve.o serve.cpp mongoose-cpp/libmongoose.a

clean :
	rm serve.o
