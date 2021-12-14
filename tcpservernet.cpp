#include "tcpservernet.hpp"
#define BUFFER_SIZE 4000

static int StrToInt(string a_str);
static std::string GetIPFromDomain(string a_str);
static int GetPortFromDomain(string a_str);

TcpServer::TcpServer(int a_port , DataBase * a_db): m_port(a_port),
m_app(a_db){
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

TcpServer::~TcpServer(){
    close(m_listeningSocket);
}

int TcpServer::AcceptConnection(){
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(m_listeningSocket, (struct sockaddr *)&client_sin, &addr_len);
    return client_sock;
}

void TcpServer::CheckNewClients(){
    int client_sock = AcceptConnection();
    if (client_sock < 0){
        throw "error at accept";
    }
        printf("add new client, socket number %d\n", client_sock);
        FD_SET(client_sock, &m_master);
        m_socketList.push_back(client_sock);
}

void TcpServer::CheckCurClients(int& a_activity){
     if (m_socketList.empty()){
        return;
    }
    CheckClient(a_activity);
}

void TcpServer::CheckClient(int& a_activity){
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
            Request request =  CreateRequest(j);
            json response = m_app.GotMsg(request);
            SendData(response.dump().c_str(), *it);
            a_activity--;
        }
        ++it;
    }
}

void TcpServer::SendData(const char * data, int a_socket){
    int send_bytes, data_len;
    data_len = strlen(data);
    send_bytes = send(a_socket, data, data_len, 0);
    if (send_bytes < 0){
        throw "send failed";
    }
}

void TcpServer::RunServer(){
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



Request TcpServer::CreateRequest(const json& a_json){
    std::string req = a_json["URL Request"];
    req.erase(0, PROTOCOL.length());
    std::cout << req << std::endl;
    int counter = 0 , lastIndex = 0;
    std::vector<std::string> requestVector;
    for(int i =0 ; req[i] != '\0' ; ++i){
            if(req[i] == '/'){
                std::string res = req.substr(lastIndex , counter);
                counter = 0;
                lastIndex = i + 1;
                requestVector.push_back(res);
                continue;
            }
            if(req[i+1] == '\0'){
                std::string res = req.substr(lastIndex , counter + 1);
                requestVector.push_back(res);
                continue;
            }
            ++counter;
        }
        Request newReq =  ParseReq(requestVector);
        return newReq;
}

Request TcpServer::ParseReq(std::vector<std::string> a_vec){
    std::string domain = a_vec[0];
    std::string operation = a_vec[2];
    std::string key = a_vec[3];

    std::string ip = GetIPFromDomain(domain);
    int port = GetPortFromDomain(domain);
    return Request(ip, port, operation, key);
}

static int StrToInt(string a_str) {
    int res = 0;
    std::stringstream str(a_str);
    str >> res;
    return res;
}

static std::string GetIPFromDomain(string a_str) {
    int start = 0;
    int end = a_str.find(":");
    return a_str.substr(start, end - start);
}

static int GetPortFromDomain(string a_str) {
    int start = a_str.find(":") + 1;
    int end = a_str.size();
    return StrToInt(a_str.substr(start, end - start));
}
