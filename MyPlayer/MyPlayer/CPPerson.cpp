//
//  CPPerson.cpp
//  MyPlayer
//
//  Created by 程倩的MacBook on 2021/9/17.
//

#include "CPPerson.hpp"
#include "MyPlayer-Bridging-Header.h"

CPPerson::CPPerson() {
    this->name = "管理员";
    this->age = 20;
    this->isNan = true;
}
CPPerson::CPPerson(const char * name,int age,bool isNan) {
    this->name = name;
    this->age = age;
    this->isNan = isNan;
}

void CPPerson::printPersonInfo() {
    cout << "i am is" << name << "my age is " << age;
    if(isNan) {
        cout << "i am a body";
    } else {
        cout << "i am a girl";
    }
}

const char* CPPerson::getPersonName() {
    return  name.data();
}


CPPerson::~CPPerson(){
    cout << "释放资源";
}

CPersonModel create() {
    return new CPPerson();
}

CPersonModel createBy(CPersonModel model) {
    CPPerson *p = (CPPerson*)model;
    return p;
}

void destoryModel(CPersonModel model) {
    CPPerson *p = (CPPerson*)model;
    delete p;
}

void printPersonInfo(CPersonModel model) {
    CPPerson *p = (CPPerson *)model;
    p->printPersonInfo();
}

const char* getPersonName(CPersonModel model) {
    CPPerson *p = (CPPerson*)model;
    return p->getPersonName();
}

