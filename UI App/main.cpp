#include "json.hpp"
#include "tcpclient.hpp"
using json = nlohmann::json;

void ClientServer();
void ClientServerWithJson();
void anotherClient();

int main(){
    //ClientServer();
    ClientServerWithJson();

    return 0;
}

void ClientServer(){
    char buffer [100];
    char ip[20] = "127.0.0.1";
    char message[100] = "Hello from Client!";
    TcpClient clientServer(2008,ip );
    clientServer.ConnectToServer();
    clientServer.SendData(message ,100);
    clientServer.ReceiveData(100);
}


void ClientServerWithJson() {
    char buffer[100];
    char ip[20] = "127.0.0.1";
    TcpClient clientServer(2010, ip);
    json j;
    j["URL Request"] = "http://server:8080/query/billing/424028198155273";
    clientServer.ConnectToServer();
    clientServer.SendData(j.dump().c_str(), 100);
    clientServer.ReceiveData(100);
    json j2;
    j2["URL Request"] = "http://server:8080/query/billing/425164747588824";
    clientServer.SendData(j2.dump().c_str(), 100);
    clientServer.ReceiveData(100);
}