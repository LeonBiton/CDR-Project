#include "updateserver.hpp"

UpdateServer::UpdateServer(int a_port, char * a_ip)
:m_port(a_port),
m_ip(a_ip){
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0){
      throw "Socket Failed";
    }
}

UpdateServer::~UpdateServer(){
    close(m_socket);
}

void UpdateServer::ConnectToServer(){
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(m_ip);
    sin.sin_port = htons(m_port);
    if (connect(m_socket, (struct sockaddr *)&sin, sizeof(sin)) < 0){
        printf("connection failed\n");
        throw "connection failed";
    }
}

void UpdateServer::SendData(const char * a_data , size_t a_dataSize){
    int send_bytes = send(m_socket, a_data, a_dataSize, 0);
    if (send_bytes < 0){
        printf("send failed\n");
        throw "send failed";
    }
}

void UpdateServer::ReceiveData(size_t _dataSize){
    char buffer[1000];
    int read_bytes = recv(m_socket, buffer, _dataSize, 0);
    if (read_bytes == 0){
        close(m_socket);
    }
    else if (read_bytes < 0){
        printf("recv failed\n");
        throw "recv failed";
    }
    buffer[read_bytes] = '\0';
    printf("%s\n", buffer);
}