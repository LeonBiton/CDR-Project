#ifndef __CDREXTRACTOR_HPP__
#define __CDREXTRACTOR_HPP__
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include "updateserver.hpp"
#include "cdrdata.hpp"
#include "json.hpp"
using json = nlohmann::json;


class CdrExtractor{
public:
    CdrExtractor(std::string a_fileName, UpdateServer &a_server);
    ~CdrExtractor() = default;

    void ExtractCdr();

private:
    void ExtractHeaders();

    std::ifstream m_file; 
    UpdateServer &m_server;
    std::vector<std::string> m_headers;
};

#endif