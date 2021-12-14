#include "dataserver.hpp"
#define BUFFER_SIZE 4000

static CdrData CreateData(json &a_json);



DataServer::DataServer(int a_port , DataBase * a_db): m_port(a_port),
m_app(a_db),
m_dataPool(100 , 1),
m_updatePool(100,1),
m_db(a_db){
    int optval = 1;
    FD_ZERO(&m_master);
    FD_ZERO(&m_temp);
    struct sockaddr_in sin;
    m_listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_listeningSocket < 0){
        throw "socket failed";
    }
    FD_SET(m_listeningSocket, &m_master);
    if (setsockopt(m_listeningSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0){
        throw "reuse failed";
    }
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_port);
    if (bind(m_listeningSocket, (struct sockaddr *)&sin, sizeof(sin)) < 0){
        throw "bind failed";
    }
    if (listen(m_listeningSocket, 32) < 0){
        throw "listen failed";
    }
}

DataServer::~DataServer(){
    close(m_listeningSocket);
}

int DataServer::AcceptConnection(){
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(m_listeningSocket, (struct sockaddr *)&client_sin, &addr_len);
    return client_sock;
}

void DataServer::CheckNewClients(){
    int client_sock = AcceptConnection();
    if (client_sock < 0){
        throw "error at accept";
    }
        printf("add new client, socket number %d\n", client_sock);
        FD_SET(client_sock, &m_master);
        m_socketList.push_back(client_sock);
}

void DataServer::CheckCurClients(int& a_activity){
     if (m_socketList.empty()){
        return;
    }
    CheckClient(a_activity);
}

void DataServer::CheckClient(int& a_activity){
    char buffer[BUFFER_SIZE];
    std::list<int>::iterator it = m_socketList.begin();
    int expect_data_len = sizeof(buffer), read_bytes;
    while (it != m_socketList.end() && a_activity > 0){
        if (FD_ISSET(*it, &m_temp) == 0){
            ++it;
            continue;
        }
        read_bytes = recv(*it, buffer, expect_data_len, 0);
        if (read_bytes < 0){
            throw "recv failed";
        }
        else if (read_bytes == 0){
            m_socketList.erase(it++);
            printf("deleted client socket number %d\n", *it);
            FD_CLR(*it, &m_master);
            close(*it);
            a_activity--;
        }
        else{
            buffer[read_bytes] = '\0';
            json j = json::parse(buffer);
            CdrData newData = CreateData(j);
            ICommand * cdrTask = TaskFactory::createRawDataToCdr(newData, m_db , &m_updatePool);
            m_dataPool.AddTask(cdrTask);
            newData.Print();
            SendData("sucsses", *it);
            m_db->GetAllData(j["IMSI"]).Print();
            printf("\n");
            a_activity--;
        }
        ++it;
    }
}

void DataServer::SendData(const char * data, int a_socket){
    int send_bytes, data_len;
    data_len = strlen(data);
    send_bytes = send(a_socket, data, data_len, 0);
    if (send_bytes < 0){
        throw "send failed";
    }
}

void * DataServer::RunServer(){
    int activity;
    while (1)
    {
        m_temp = m_master;
        activity = select(1024, &m_temp, NULL, NULL, NULL);
        if (FD_ISSET(m_listeningSocket, &m_temp) > 0){
            CheckNewClients();
            if (activity == 1){
                continue;
            }
            activity--;
        }
        CheckCurClients(activity);
    } 
}

static CdrData CreateData(json &a_json){
    CdrData newData(a_json);
    return newData;
}


