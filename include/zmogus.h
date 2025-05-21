#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
using std::string;

class Zmogus {
protected:
    string vardas_;
    string pavarde_;

public:
    Zmogus()=default;
    Zmogus(const string& v, const string& p) : vardas_(v), pavarde_(p) {}

    virtual ~Zmogus()= default;

    virtual string vardas() const= 0; //0 - ABSTRAKTI FUNKC
    virtual string pavarde() const= 0;

    virtual void setVardas(const string&)= 0;
    virtual void setPavarde(const string&)= 0;
};

#endif
