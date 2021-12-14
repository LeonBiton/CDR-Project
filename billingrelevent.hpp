#include <iostream>
#include <string>



class BillingRelevent{
public:
    BillingRelevent(std::string a_duration ,std::string a_useageType 
, std::string a_bitsRec , std::string a_bitsSent , std::string a_imsi);

    std::string GetUseageType()const {return m_usageType;}
    std::string GetDuration()const{return m_duration;}
    std::string GetBitsRec()const{return m_bitsRec;}
    std::string GetBitsSent()const{return m_bitsSent;}
    std::string GetImsi()const{return m_imsi;}

    void Print();

private:
    std::string m_duration;
    std::string m_usageType;
    std::string m_bitsRec;
    std::string m_bitsSent;
    std::string m_imsi;
};