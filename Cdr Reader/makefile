
TARGET= main.out
CXX= g++
CFLAGS= -ansi -pedantic -g -std=c++11
OBJS= cdrextractor.o updateserver.o cdrdata.o main.o 

# valgring listtest
VAL= valgrind
VALFLAGS= --leak-check=full
# additional flags: --log-file=V1.log --track-origins=yes --show-leak-kinds=all


$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CXX) $(CFLAGS) -I./ -c main.cpp

updateserver.o: updateserver.cpp updateserver.hpp
	$(CXX) $(CFLAGS) -I./ -c updateserver.cpp

cdrdata.o: cdrdata.cpp cdrdata.hpp
	$(CXX) $(CFLAGS) -I./ -c cdrdata.cpp

cdrextractor.o: cdrextractor.cpp cdrextractor.hpp
	$(CXX) $(CFLAGS) -I./ -c cdrextractor.cpp

clean:
	rm -f $(TARGET) $(OBJS)
