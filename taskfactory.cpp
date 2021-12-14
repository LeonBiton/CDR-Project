#include "taskfactory.hpp"


static size_t strTosizet(std::string a_string);


BillingCommand::BillingCommand(const BillingRelevent &a_billingRel , DataBase *db)
:m_billingRel(a_billingRel),
m_db(db){}

void BillingCommand::Execute(){
    size_t smsIn = 0, smsOut = 0 , voiceIn = 0 , voiceOut = 0;
    std::string useageType = m_billingRel.GetUseageType();
    std::string duration = m_billingRel.GetDuration();
    if(useageType == "MOC"){
    voiceOut = strTosizet(duration);
    }
    else if(useageType == "MTC"){
    voiceIn = strTosizet(duration);
    }
    else if(useageType == "SMS-MO"){
    smsIn = strTosizet(duration);
    }
    else if(useageType == "SMS-MT"){
    smsOut = strTosizet(duration);
    }
    size_t bitsRec = strTosizet(m_billingRel.GetBitsRec());
    size_t bitsSent = strTosizet(m_billingRel.GetBitsSent());
    BillingData newBilling (voiceIn , voiceOut , bitsRec , bitsSent,smsIn , smsOut);
    std::map<std::string , BillingData>::iterator it = m_db->GetBillingHash().begin();
        if(m_db->GetBillingHash().find(m_billingRel.GetImsi()) != m_db->GetBillingHash().end()){
            it->second += newBilling;
            return;
        }
        m_db->GetBillingHash().insert({m_billingRel.GetImsi(), newBilling});
}

rawDataToCdrData::rawDataToCdrData(CdrData &a_data, DataBase * a_db , ThreadPool * a_nextThreadPool)
:m_data(a_data),
m_nextThreadPool(a_nextThreadPool),
m_db(a_db){}

void rawDataToCdrData::Execute(){
    ICommand * newBilling = TaskFactory::create(TaskFactory::BILLING ,m_data , m_db);
    m_nextThreadPool->AddTask(newBilling);
}

void TestIcommand::Execute(){
    std::cout << "******" << std::endl; 
}

static size_t strTosizet(std::string a_string){
    size_t result = 0;
    std::stringstream str(a_string);
    str >> result;
    return result;
}