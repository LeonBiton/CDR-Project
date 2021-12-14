#ifndef __TASKFACTORY_HPP__
#define __TASKFACTORY_HPP__
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <fstream>
#include <vector>
#include "billingrelevent.hpp"
#include "database.hpp"
#include "threadpool.hpp"

class BillingCommand : public ICommand{
public:
	BillingCommand(const BillingRelevent &a_billingRel , DataBase *db);
    ~BillingCommand() = default;
	void Execute();

private:
    BillingRelevent m_billingRel;
    DataBase *m_db;
};

class TestIcommand : public ICommand{
public:
    TestIcommand()= default;
    ~TestIcommand() = default;

    void Execute();



private:
};

class rawDataToCdrData : public ICommand{
public:
    rawDataToCdrData(CdrData &a_data, DataBase * a_db , ThreadPool * a_nextThreadPool);

    void Execute();

private:
    CdrData m_data;
    DataBase * m_db;
    ThreadPool * m_nextThreadPool;
};

class CdrDataToHash : public ICommand{
public:
    CdrDataToHash() = default;

    void Execute();


private:

};

class TaskFactory{
public:
    enum Operation{
    BILLING,
    OPERATOR
    };

    static ICommand* create(Operation a_operation, CdrData &a_data , DataBase *db){
        switch(a_operation){
        case BILLING:
            BillingRelevent newRel(a_data.GetDuration() , a_data.GetUseageType() , a_data.GetBitsRec() , a_data.GetBitsSent() , a_data.GetImsi());
            return new BillingCommand(newRel , db);
        }
    }
    static ICommand* createRawDataToCdr(CdrData &a_data , DataBase * a_db, ThreadPool * a_nextThreadPool){
        return new rawDataToCdrData(a_data, a_db, a_nextThreadPool);
    }
};



#endif