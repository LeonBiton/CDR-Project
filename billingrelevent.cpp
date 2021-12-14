#include "billingrelevent.hpp"

BillingRelevent::BillingRelevent(std::string a_duration ,std::string a_useageType 
, std::string a_bitsRec , std::string a_bitsSent, std::string a_imsi)
:m_bitsRec(a_bitsRec),
m_bitsSent(a_bitsSent),
m_duration(a_duration),
m_usageType(a_useageType),
m_imsi(a_imsi){}

void BillingRelevent::Print(){
    std::cout << "imsi: " << m_imsi << std::endl;
    std::cout << "duration: " << m_duration << std::endl;
    std::cout << "usage type: " << m_usageType << std::endl;
    std::cout << "bits rec: " << m_bitsRec << std::endl;
    std::cout << "bits sent: " << m_bitsSent << std::endl;

}