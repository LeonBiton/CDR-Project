#include <iostream>
#include <stdio.h>
#include <sys/types.h> /* for socket */
#include <sys/socket.h>/* for socket */
#include <netinet/in.h>/* for socket */
#include <netinet/in.h>/*for inet_addr*/
#include <arpa/inet.h> /*for inet_addr*/
#include <unistd.h>
#include <string.h>
#include <exception>


class UpdateServer{
public:
    UpdateServer(int a_port , char * a_ip);
    ~UpdateServer();

    void ConnectToServer();
    void SendData(const char * a_data , size_t a_dataSize);
    void ReceiveData(size_t _dataSize);

private:
    int m_port;
    int m_socket;
    char * m_ip;
};