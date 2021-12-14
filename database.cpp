#include "database.hpp"


BillingData DataBase::GetAllData(std::string a_imsi){
    std::map<std::string , BillingData>::iterator it = m_billingHash.find(a_imsi);
    return it->second;
}