#include "operatordata.hpp"

OperatorData::OperatorData(size_t a_totalCallsIn ,size_t a_totalCallsOut , size_t a_totalSmsIn ,size_t a_totalSmsOut)
:m_totalCallsIn(a_totalCallsIn),
m_totalCallsOut(a_totalCallsOut),
m_totalSmsIn(a_totalSmsIn),
m_totalSmsOut(a_totalSmsOut){}


OperatorData& OperatorData::operator+=(const OperatorData& a_operatorData){
    m_totalCallsIn += a_operatorData.m_totalCallsIn;
    m_totalCallsOut += a_operatorData.m_totalCallsOut;
    m_totalSmsIn += a_operatorData.m_totalSmsIn;
    m_totalSmsOut += a_operatorData.m_totalSmsOut;

    return *this;
}