//
//  main.cpp
//  TestDemo
//
//  Created by 程倩的MacBook on 2022/8/26.
//


#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;
int main(int argc, const char * argv[]) {
    ifstream stream;
    stream.open("/Users/chengqian/Desktop/ypsc/in.pcm");
    if(stream.is_open() == false) {
        cout << "file.open error" << "/Users/chengqian/Desktop/ypsc/in.pcm" << endl;
        return 0;
    }
    cout << "success" << endl;
    return 0;
}
