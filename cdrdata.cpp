#include "cdrdata.hpp"
#include <sstream>

static size_t strTosizet(std::string a_string);

CdrData::CdrData(std::vector<std::string> a_headers ,std::vector<std::string> a_singleLineData)
:m_header(a_headers){
    m_sequence = a_singleLineData[GetIndex("Sequence")];
    m_imsi = a_singleLineData[GetIndex("IMSI")];
    m_imei = a_singleLineData[GetIndex("IMEI")];
    m_usageType = a_singleLineData[GetIndex("Usage Type")];
    m_msisdn = a_singleLineData[GetIndex("MSISDN")];
    m_callDate = a_singleLineData[GetIndex("Call date")];
    m_callTime = a_singleLineData[GetIndex("Call time")];
    m_duration = a_singleLineData[GetIndex("Duration(sec)")];
    m_bytesReceived = a_singleLineData[GetIndex("Bytes Rx")];
    m_bytesTransmitted = a_singleLineData[GetIndex("Bytes Tx")];
    m_2ndPartiImsi = a_singleLineData[GetIndex("2nd Party IMSI")];
    m_2ndPartiMsisdn = a_singleLineData[GetIndex("2nd Party MSISDN") - 1];
}

CdrData::CdrData(json &a_json){
    m_imsi = a_json["IMSI"];
    m_2ndPartiImsi = a_json["2ndImsi"];
    m_2ndPartiMsisdn = a_json["2ndMsisdn"];
    m_bytesReceived = a_json["BitsRec"];
    m_bytesTransmitted = a_json["BitsSent"];
    m_callDate = a_json["CallDate"];
    m_callTime = a_json["CallTime"];
    m_duration = a_json["Duration"];
    m_imei = a_json["IMEI"];
    m_msisdn = a_json["MSISDN"];
    m_usageType = a_json["UseageType"];
    m_sequence = a_json["Sequence"];
}

size_t CdrData::GetIndex(std::string a_header){
    size_t index = std::find(m_header.begin(), m_header.end() , a_header) - m_header.begin();
    return index;
}

void CdrData::Print(){
    std::cout << "Sequence: " << m_sequence << std::endl;
    std::cout << "IMSI: " << m_imsi << std::endl;
    std::cout << "IMEI: " << m_imei << std::endl;
    std::cout << "Usage Type: " << m_usageType << std::endl;
    std::cout << "MSISDN: " << m_msisdn << std::endl;
    std::cout << "Call date: " << m_callDate << std::endl;
    std::cout << "Call time: " << m_callTime << std::endl;
    std::cout << "Duration: " <<  m_duration << std::endl;
    std::cout << "Bytes Rx: " <<  m_bytesReceived << std::endl;
    std::cout << "Bytes Tx: " << m_bytesTransmitted << std::endl;
    std::cout << "2nd Party IMSI: " << m_2ndPartiImsi << std::endl;
    std::cout << "2nd Party MSISDN: " << m_2ndPartiMsisdn << std::endl;
    std::cout << std::endl;

}

std::string CdrData::GetImsi() const{
    return m_imsi;
}

static size_t strTosizet(std::string a_string){
    size_t result = 0;
    std::stringstream str(a_string);
    str >> result;
    return result;
}

std::string CdrData::GetUseageType()const{
    return m_usageType;
}

std::string CdrData::GetDuration()const{
    return m_duration;
}

std::string CdrData::GetBitsRec()const{
    return m_bytesReceived;
}

std::string CdrData::GetBitsSent()const{
    return m_bytesTransmitted;
}