#include "billingdata.hpp"


BillingData::BillingData(size_t a_totalCallsIn , size_t a_totalCallsOut , size_t a_totalDataIn , size_t a_totalDataOut,
    size_t a_totalSmsIn ,size_t a_totalSmsOut)
:m_totalCallsIn(a_totalCallsIn),
m_totalCallsOut(a_totalCallsOut),
m_totalDataIn(a_totalDataIn),
m_totalDataOut(a_totalDataOut),
m_totalSmsIn(a_totalSmsIn),
m_totalSmsOut(a_totalSmsOut){}


BillingData& BillingData::operator+=(const BillingData& a_billingData){
    m_totalCallsIn += a_billingData.m_totalCallsIn;
    m_totalCallsOut += a_billingData.m_totalCallsOut;
    m_totalDataIn += a_billingData.m_totalDataIn;
    m_totalDataOut += a_billingData.m_totalCallsOut;
    m_totalSmsIn += a_billingData.m_totalSmsIn;
    m_totalSmsOut += a_billingData.m_totalSmsOut;

    return *this;
}

void BillingData::Print(){
    std::cout << "Total calls in : " << m_totalCallsIn << std::endl;
    std::cout << "Total calls out : " << m_totalCallsOut << std::endl;
    std::cout << "Total data in : " << m_totalDataIn << std::endl;
    std::cout << "Total data out : " << m_totalDataOut << std::endl;
    std::cout << "Total sms in : " << m_totalSmsIn << std::endl;
    std::cout << "Total sms out : " << m_totalSmsOut << std::endl;
}