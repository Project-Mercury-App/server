FLAGS = -std=c++11 -Wall -O1 -o serve.o

all: serve

serve: serve.cpp
	g++ ${FLAGS} serve.cpp mongoose-cpp/libmongoose.a  -lpthread -lpq -lpqxx

clean :
	rm serve.o
