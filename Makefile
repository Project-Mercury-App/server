serve: serve.cpp
	g++ -std=c++11 -o serve.o serve.cpp mongoose-cpp/libmongoose.a

clean :
	rm serve.o
