#include "serverapp.hpp"

ServerApp::ServerApp(DataBase * a_db)
:m_db(a_db){}

json ServerApp::GotMsg(Request &a_request){
    json response;
    BillingData data = m_db->GetAllData(a_request.GetKey1());
    response["voice-out"] = data.GetCallsOut();
    response["voice-in"] = data.GetCallsIn();
    response["data-out"] = data.GetDataOut();
    response["data-in"] = data.GetDataIn();
    response["sms-out"] = data.GetSmsOut();
    response["sms-in"] = data.GetSmsIn();
    return response;
} 

json ServerApp::GotUpdate(Request &a_request){
    
}