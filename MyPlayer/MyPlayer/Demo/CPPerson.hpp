//
//  CPPerson.hpp
//  MyPlayer
//
//  Created by 程倩的MacBook on 2021/9/17.
//

#ifndef CPPerson_hpp
#define CPPerson_hpp

#include <stdio.h>

#endif /* CPPerson_hpp */
#include <iostream>
using namespace std;
class CPPerson {
    string name;
    int age;
    bool isNan;
    
public:
    CPPerson();
    CPPerson(const char * name,int age,bool isNam);
    ~CPPerson();
    void printPersonInfo();
    const char* getPersonName();
};
