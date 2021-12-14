#include <iostream>

class OperatorData{
public:
    OperatorData(size_t a_totalCallsIn ,size_t a_totalCallsOut , size_t a_totalSmsIn ,size_t a_totalSmsOut);
    ~OperatorData() = default;

    OperatorData& operator+=(const OperatorData& a_operatorData);

private:
    size_t m_totalCallsIn;
    size_t m_totalCallsOut;
    size_t m_totalSmsIn;
    size_t m_totalSmsOut;
};