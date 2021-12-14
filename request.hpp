#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include <iostream>
#include <string>


using namespace std;

class Request {
   public:
    Request(const string& a_ip, const int a_port, string a_operation, const string& a_firstKey)
        : m_ip(a_ip),
          m_port(a_port),
          m_operation(a_operation),
          m_firstKey(a_firstKey){}

    int GetPort() const { return m_port; }
    string GetIP() const { return m_ip; }
    string GetOperation() const { return m_operation; }
    string GetKey1() const { return m_firstKey; }

    void Print() {
        cout << "ip: " << m_ip << endl;
        cout << "port: " << m_port << endl;
        cout << "operation: " << m_operation << endl;
        cout << "key1: " << m_firstKey << endl;
    }

   private:
    string m_ip;
    int m_port;
    string m_operation;
    string m_firstKey;
};

#endif /* #ifndef __REQUEST_HPP__ */
