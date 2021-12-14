#include <iostream>
#include <string>

class BillingData{
public:
    BillingData(size_t a_totalCallsIn , size_t a_totalCallsOut , size_t a_totalDataIn , size_t a_totalDataOut,
    size_t a_totalSmsIn ,size_t a_totalSmsOut);

    BillingData& operator+=(const BillingData& a_billingData);

    size_t GetCallsIn()const{return m_totalCallsIn;};
    size_t GetCallsOut()const{return m_totalCallsOut;};
    size_t GetDataIn()const{return m_totalDataIn;};
    size_t GetDataOut()const{return m_totalDataOut;};
    size_t GetSmsIn()const{return m_totalSmsIn;};
    size_t GetSmsOut()const{return m_totalSmsOut;};


    void Print();

private:
    size_t m_totalCallsIn;
    size_t m_totalCallsOut;
    size_t m_totalDataIn;
    size_t m_totalDataOut;
    size_t m_totalSmsIn;
    size_t m_totalSmsOut;
};