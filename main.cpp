#include "tcpservernet.hpp"
#include "dataserver.hpp"
#include <thread>

void UpdateServer();

int main(){
    UpdateServer();

    return 0;
}


void UpdateServer(){
    DataBase db;
    DataServer server(2008 , &db);
    TcpServer clientServer(2010 , &db);
    std::thread t(&DataServer::RunServer , &server);
    std::thread t2(&TcpServer::RunServer , &clientServer);
    t.join();
    t2.join();
}


