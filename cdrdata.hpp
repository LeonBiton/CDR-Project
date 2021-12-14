#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "json.hpp"
using json = nlohmann::json;

class CdrData{
public:
    CdrData(std::vector<std::string> a_headers ,std::vector<std::string> a_singleLineData);
    CdrData(json &a_json);
    ~CdrData() = default;

    size_t GetIndex(std::string a_header);
    std::string GetImsi() const;

    std::string GetUseageType()const;
    std::string GetDuration()const;
    std::string GetBitsRec()const;
    std::string GetBitsSent()const;

    void Print();

private:
    std::vector<std::string> m_header;

    std::string m_sequence;
    std::string m_imsi;
    std::string m_imei;
    std::string m_usageType;
    std::string m_msisdn;
    std::string m_callDate;
    std::string m_callTime;
    std::string m_duration;
    std::string m_bytesReceived;
    std::string m_bytesTransmitted;
    std::string m_2ndPartiImsi;
    std::string m_2ndPartiMsisdn;
};