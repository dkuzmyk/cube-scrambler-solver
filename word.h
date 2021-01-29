//
// Created by dkuzmy3 on 11/18/2020.
//

#ifndef UNTITLED10_WORD_H
#define UNTITLED10_WORD_H

#include "cube.h"

class word{
private:
    string w;

public:
    word(){
        w = "";
    }
    void updateWord(string &a){
        w = a;
    }

    void clearWord(){
        w = "";
    }

    void printWord(){
        cout << w << endl;
    }

    string getWord(){
        return w;
    }

};

#endif //UNTITLED10_WORD_H
