//
// Created by dkuzmy3 on 11/18/2020.
//

#ifndef UNTITLED10_SOLVER_H
#define UNTITLED10_SOLVER_H

#include "word.h"

class solver{
private:
    string container[6]{};
    bool mapUsed[6][6]{};
    bool mapAvailable[6]{};
    int inputSize;
    string inputWord;
    vector<tuple<int, int>> map;

public:
    solver(){
        inputWord = "";
        inputSize = 0;
    }

    void receiver(string* tmp, int num){
        for(int i=0; i<6; i++)
            container[num-1].append(tmp[i]);
        mapAvailable[num-1] = true;
    }

    void setWord(string a){
        inputWord = a;
        inputSize = a.size();
    }

    void clear(){
        inputWord = "";
        inputSize = 0;
        for(int i=0; i<6; i++){
            mapAvailable[i] = false;
            container[i] = "";
            for(int j=0; j<6; j++){
                mapUsed[i][j] = false;
            }

        }
    }

    void printCombination();

    void printFound(){
        for(int i=0; i<6; i++) {
            for (int j = 0; j < 6; j++) {
                if (mapUsed[i][j]) {
                    cout << "Cube " << i + 1 << " letter " << container[i][j] << " on face " << j + 1 << endl;
                }
            }
        }
        cout << endl;
    }

    bool recursiveHelper(bool _mapAvailable[6], bool _mapUsed[6][6], string _inputWord, int i, int j);
    bool recursiveHelper2(vector<tuple<int, int>> map_used, vector<int> rowUsed, string _inputWord, int idx);

    void copyMap(vector<tuple<int, int>> m){
        map = m;
    }

    bool checkUsed(int i, vector<int> a){
        for(auto &b:a){
            if(b == i) return true;
        }
        return false;
    }

    void printMap(){
        for(int i=0; i<inputSize; i++){
            cout << "Cube: " << get<0>(map[i])+1 << " face: " << get<1>(map[i])+1 << " letter: " << container[get<0>(map[i])][get<1>(map[i])] <<endl;
        }
    }

    bool solve(){
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                cout << container[i][j] << " ";
            }
            cout << endl;
        }
        bool result = false;
        cout << endl;
        vector<tuple<int, int>> map_used;
        vector<int> rowUsed;
        //result = recursiveHelper(mapAvailable, mapUsed, inputWord, 0, 0);
        result = recursiveHelper2(map_used, rowUsed, inputWord, 0);
        printMap();
        //printFound();
        //printCombination();

        clear();
        if(result) return true;
        else return false;
    }

};
#endif //UNTITLED10_SOLVER_H
