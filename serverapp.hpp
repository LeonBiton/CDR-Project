#ifndef __SERVERAPP_HPP__
#define __SERVERAPP_HPP__

#include <iostream>
#include "request.hpp"
#include "json.hpp"
#include "database.hpp"
using json = nlohmann::json;


class ServerApp{
public:
    ServerApp(DataBase * a_db);
    ~ServerApp() = default;

    json GotMsg(Request &a_request);

    json GotUpdate(Request &a_request);

private:
    DataBase * m_db;
};

#endif