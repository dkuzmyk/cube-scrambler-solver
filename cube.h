//
// Created by dkuzmy3 on 11/18/2020.
//


#ifndef UNTITLED10_CUBE_H
#define UNTITLED10_CUBE_H

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Cube{
private:
    string faces[6];
    bool used;
    int num;

public:
    Cube(){
        num = 0;
        used = false;
        for(auto & face : faces)
            face = "";
    }
    void printCube(){
        cout << "Cube " << num << ": ";
        for (auto & face : faces){
            cout << face << ", ";
        }
        cout << endl;
    }
    void updateCube(const char a[], int n){
        num = n;
        for (int i=0; i < 6; i++){
            faces[i] = a[i];
        }
    }
    void clearFaces(){
        for (auto & face : faces){
            face = "";
        }
    }

    void setUsed(){
        used = true;
    }

    void setUnused(){
        used = false;
    }

    bool isUsed(){
        return used;
    }

    string* getFaces(){
        return faces;
    }

};
#endif //UNTITLED10_CUBE_H
