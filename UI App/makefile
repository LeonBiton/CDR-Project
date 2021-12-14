
TARGET= main.out
CXX= g++
CFLAGS= -ansi -pedantic -g -std=c++11
OBJS= uiapp.o tcpclient.o main.o 

# valgring listtest
VAL= valgrind
VALFLAGS= --leak-check=full
# additional flags: --log-file=V1.log --track-origins=yes --show-leak-kinds=all


$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CXX) $(CFLAGS) -I./ -c main.cpp

tcpclient.o: tcpclient.cpp tcpclient.hpp
	$(CXX) $(CFLAGS) -I./ -c tcpclient.cpp

uiapp.o: uiapp.cpp uiapp.hpp
	$(CXX) $(CFLAGS) -I./ -c uiapp.cpp

clean:
	rm -f $(TARGET) $(OBJS)
