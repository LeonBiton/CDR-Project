#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__
#include <map>
#include <algorithm>
#include "billingdata.hpp"
#include "cdrdata.hpp"
#include "operatordata.hpp"


class DataBase{
public:

    DataBase() = default;
    ~DataBase() = default;


    BillingData GetAllData(std::string a_imsi);

    std::map<std::string , BillingData>& GetBillingHash(){return m_billingHash;};

private:
    std::map<std::string , BillingData> m_billingHash;
    std::map<std::string , OperatorData> m_operatorHash;
};

#endif