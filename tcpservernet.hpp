#ifndef __TCPSERVERNET_HPP__
#define __TCPSERVERNET_HPP__
#include <iostream>
#include <string.h>    /*for memset*/
#include <unistd.h>    /*for fcntl*/
#include <fcntl.h>     /*for fcntl*/
#include <sys/types.h> /* for socket */
#include <sys/socket.h>/* for socket */
#include <netinet/in.h>/* for socket */
#include <sys/select.h>/*for FD_SET*/
#include <sys/time.h>  /*for FD_SET*/
#include <exception>
#include <list>
#include <sstream>
#include <queue>
#include "json.hpp"
#include "serverapp.hpp"
using json = nlohmann::json;

class TcpServer{
public:
    inline static const std::string PROTOCOL = "http://";
    inline static const std::string URL_DEL = "/";

    TcpServer(int a_port , DataBase * a_db);
    ~TcpServer();

    void RunServer();

    void SendData(const char * data, int a_socket);

    Request CreateRequest(const json& a_json);
    Request ParseReq(std::vector<std::string> a_vec);

    std::string GetOperation()const;



private:
    void CheckNewClients();
    int AcceptConnection();
    void CheckCurClients(int& a_activity);
    void CheckClient(int& a_activity);

    int m_port;
    int m_listeningSocket;
    fd_set m_master;
    fd_set m_temp;
    std::list<int> m_socketList;
    //std::queue<Request> m_requests;
    ServerApp m_app;
};

#endif