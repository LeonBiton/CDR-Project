#include "cdrextractor.hpp"

CdrExtractor::CdrExtractor(std::string a_fileName ,UpdateServer &a_server)
:m_file(),
m_headers(),
m_server(a_server){
    m_file.open(a_fileName);
}

void CdrExtractor::ExtractCdr(){
    ExtractHeaders();
    std::string buffer;   
    while(getline(m_file , buffer)){
        int counter = 0 , lastIndex = 0;
        std::vector<std::string> dataVector;
        for(int i =0 ; buffer[i] != '\0' ; ++i){
            if(buffer[i] == '|'){
                if(buffer[i + 1] == '\0'){
                    std::string res = "0";
                    dataVector.push_back(res);
                    dataVector.push_back(res);
                    continue;
                }
                std::string res = buffer.substr(lastIndex , counter);
                counter = 0;
                lastIndex = i + 1;
                dataVector.push_back(res);
                continue;
            }
            if(buffer[i+1] == '\0'){
                std::string res = buffer.substr(lastIndex , counter + 1);
                dataVector.push_back(res);
                continue;
            }
            ++counter;
        }
        CdrData data(m_headers , dataVector);
        json j;
        j["IMSI"] = data.GetImsi();
        j["UseageType"] = data.GetUseageType();
        j["Duration"] = data.GetDuration();
        j["BitsRec"] = data.GetBitsRec();
        j["BitsSent"] = data.GetBitsSent();
        j["IMEI"] = data.GetImei();
        j["MSISDN"] = data.GetMsisdn();
        j["CallTime"] = data.GetCallTime();
        j["CallDate"] = data.GetCallDate();
        j["2ndImsi"] = data.Get2ndPartyImsi();
        j["2ndMsisdn"] = data.Get2ndPartymsisdn();
        j["Sequence"] = data.GetSequence();
        //std::cout << j.dump().c_str() << std::endl;
        m_server.SendData(j.dump().c_str(), 1000);
        m_server.ReceiveData(100);
    }
    //m_file.close();
}

void CdrExtractor::ExtractHeaders(){
    std::string buffer;
    getline(m_file , buffer);
    int counter = 0 , lastIndex = 0;
    for(int i =0 ; buffer[i] != '\0' ; ++i){
        if( buffer[i] == '|' || buffer[i+1] == '\0'){
            std::string res = buffer.substr(lastIndex , counter);
            counter = 0;
            lastIndex = i + 1;
            m_headers.push_back(res);
            continue;
        }
        ++counter;
    }
}
