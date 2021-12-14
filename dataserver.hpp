#ifndef __DATASERVER_HPP__
#define __DATASERVER_HPP__
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
#include "threadpool.hpp"
#include "taskfactory.hpp"
using json = nlohmann::json;

class DataServer{
public:
    inline static const std::string PROTOCOL = "http://";
    inline static const std::string URL_DEL = "/";

    DataServer(int a_port , DataBase * a_db);
    ~DataServer();

    void * RunServer();

    void SendData(const char * data, int a_socket);

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
    ServerApp m_app;

    ThreadPool m_dataPool;
    ThreadPool m_updatePool;
    DataBase * m_db;
};

#endif