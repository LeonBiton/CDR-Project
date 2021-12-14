
TARGET= main.out
CXX= g++
CFLAGS= -ansi -pedantic -g -std=c++11 -std=c++1z
//OBJS= tcpservernet.o dataserver.o operatordata.o safequeue.o threadpool.o threadwrapper.o taskfactory.o billingrelevent.o cdrdata.o database.o billingdata.o request.o serverapp.o main.o 
OBJS= tcpservernet.o dataserver.o operatordata.o safequeue.o threadpool.o threadwrapper.o taskfactory.o billingrelevent.o cdrdata.o database.o billingdata.o request.o serverapp.o main.o -lpthread 
# valgring listtest
VAL= valgrind
VALFLAGS= --leak-check=full
# additional flags: --log-file=V1.log --track-origins=yes --show-leak-kinds=all


$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CXX) $(CFLAGS) -I./ -c main.cpp

tcpservernet.o: tcpservernet.cpp tcpservernet.hpp
	$(CXX) $(CFLAGS) -I./ -c tcpservernet.cpp

dataserver.o: dataserver.cpp dataserver.hpp
	$(CXX) $(CFLAGS) -I./ -c dataserver.cpp

operatordata.o: operatordata.cpp operatordata.hpp
	$(CXX) $(CFLAGS) -I./ -c operatordata.cpp

safequeue.o: safequeue.cpp safequeue.hpp
	$(CXX) $(CFLAGS) -I./ -c safequeue.cpp

threadpool.o: threadpool.cpp threadpool.hpp
	$(CXX) $(CFLAGS) -I./ -c threadpool.cpp 

threadwrapper.o: threadwrapper.cpp threadwrapper.hpp
	$(CXX) $(CFLAGS) -I./ -c threadwrapper.cpp 

taskfactory.o: taskfactory.cpp taskfactory.hpp
	$(CXX) $(CFLAGS) -I./ -c taskfactory.cpp

billingrelevent.o: billingrelevent.cpp billingrelevent.hpp
	$(CXX) $(CFLAGS) -I./ -c billingrelevent.cpp

cdrdata.o: cdrdata.cpp cdrdata.hpp
	$(CXX) $(CFLAGS) -I./ -c cdrdata.cpp

database.o: database.cpp database.hpp
	$(CXX) $(CFLAGS) -I./ -c database.cpp

billingdata.o: billingdata.cpp billingdata.hpp
	$(CXX) $(CFLAGS) -I./ -c billingdata.cpp

request.o: request.cpp request.hpp
	$(CXX) $(CFLAGS) -I./ -c request.cpp

serverapp.o: serverapp.cpp serverapp.hpp
	$(CXX) $(CFLAGS) -I./ -c serverapp.cpp

clean:
	rm -f $(TARGET) $(OBJS)
