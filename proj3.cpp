//
// Created by dkuzmy3 on 11/17/2020.
//

#include "solver.h"

bool solver::recursiveHelper(bool _mapAvailable[6], bool _mapUsed[6][6], string _inputWord, int i, int j){

    bool solution = false;
    if(_inputWord.empty()) {
        //printFound(_mapUsed);
        return true;
    }
    if(!_mapAvailable[0]&&!_mapAvailable[1]&&!_mapAvailable[2]&&!_mapAvailable[3]&&!_mapAvailable[4]&&!_mapAvailable[5] && !_inputWord.empty()) {
        /*cout << "No solution." << endl;*/ return false; }
    if(_mapAvailable[i]){
        for(int tmp = 0; tmp < _inputWord.size(); tmp++){
            if(_inputWord[tmp] == container[i][j]){ // scan word
                //cout << "found " << _inputWord[tmp] << " in cube " << i+1 << " face " << j+1 << endl;

                if(j>=0 && j<6) {/*cout << "ignore, move on j " << endl;*/
                    recursiveHelper(_mapAvailable, _mapUsed ,_inputWord, i, j+1);
                } // exclude found
                else if(i>=0 && i<6) {
                    _mapAvailable[i] = false;
                    /*cout << "ignore, move on i " << endl;*/
                    recursiveHelper(_mapAvailable, _mapUsed ,_inputWord, i+1, 0);
                }
                else {
                    /*cout << "end of j, move on i " << endl;*/
                    recursiveHelper(_mapAvailable, _mapUsed, _inputWord, 0, 0);
                }

                if(i>=0 && i<6) {
                    //cout << "include, move on i" << endl;
                    //cout << "new word: " << _inputWord.erase(tmp) << endl;
                    _mapAvailable[i] = false;
                    _mapUsed[i][j] = true;
                    recursiveHelper(_mapAvailable, _mapUsed ,_inputWord.erase(tmp), i++, 0);
                } // include found

                else{
                    //cout << "reset i, j" << endl;
                    //cout << "new word: " << _inputWord.erase(tmp) << endl;
                    _mapAvailable[i] = false;
                    _mapUsed[i][j] = true;
                    recursiveHelper(_mapAvailable, _mapUsed ,_inputWord.erase(tmp), 0, 0);
                }

            }
            else{
                if(j>=0 && j<6) {/*cout << "ignore, move on j " << endl;*/ recursiveHelper(_mapAvailable, _mapUsed ,_inputWord, i, j+1);} // exclude found
                else if(i>=0 && i<6) {_mapAvailable[i] = false;  /*cout << "ignore, move on i " << endl;*/ recursiveHelper(_mapAvailable, _mapUsed ,_inputWord, i+1, 0);}
                else {/*cout << "end of j, move on i " << endl;*/ recursiveHelper(_mapAvailable, _mapUsed, _inputWord, 0, 0);}
            }
        } // end word scan
    } // if available
    else{

        if(i>=0 && i<6) {recursiveHelper(_mapAvailable, _mapUsed ,_inputWord, i+1, 0);
            //cout << "ignore, move on i " << endl;
        }
        else {_mapAvailable[i] = false; recursiveHelper(_mapAvailable, _mapUsed, _inputWord, 0, 0);
            //cout << "end of j, move on i " << endl;
        }
    }
}

bool solver::recursiveHelper2(vector<tuple<int, int>> map_used, vector<int> rowUsed, string _input, int idx){

    bool ret = false;
    if(_input.size() == idx) {
        copyMap(map_used);
        return true;
    }

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(_input[idx] == container[i][j] && !checkUsed(i,rowUsed)) {
                map_used.emplace_back(i,j);
                rowUsed.emplace_back(i);
                ret = recursiveHelper2(map_used, rowUsed, _input, idx+1);
                rowUsed.pop_back();
                map_used.pop_back();
            }
        }
    }
    return ret;
}

void solver::printCombination() {
        int i = 0;
        int j = 0;
        int k = 0;
        int safe = 0;
        cout << "Combination: " << endl;
        while(k < inputSize){
            bool mapBackup[6][6];
            for(int p=0; p < 6; p++){
                for(int q=0; q < 6; q++){
                    mapBackup[i][j] = mapUsed[i][j];
                }
            }

            if(mapUsed[i][j] && (container[i][j] == inputWord[k])){
                for(int p=0; p < 6; p++) mapUsed[i][p] = false;
                cout << "Cube " << i+1 << " face " << j+1 << " letter " << inputWord[k] << "; "<< endl;
                k++;
            }

            if(j<6) j++;
            if(j>=6){j=0; i++;}
            if(i>=6){i=0;}
            safe++;
            if(safe>20000) {cout << "No valid solution" << endl; k=inputSize+1;}
        }
        cout << endl;
    }

int main(){
    bool end = false;
    char cubeLettersArray[11];
    int howManyCubes = 0;
    Cube a, b, c, d, e, f;
    solver s;
    word w;

    char command;
    string wordCommand;
    string cubeLetters;

    cout << "Welcome to the cube scrambler game! You have 6 cubes, 6 faces each." << endl;
    while(!end){
        cout << "Enter command: " << endl;
        cin >> command;

        switch (command) {
            case 'r':
                w.clearWord();
                if(a.isUsed()) {a.setUnused(); a.clearFaces();}
                if(b.isUsed()) {b.setUnused(); b.clearFaces();}
                if(c.isUsed()) {c.setUnused(); c.clearFaces();}
                if(d.isUsed()) {d.setUnused(); d.clearFaces();}
                if(e.isUsed()) {e.setUnused(); e.clearFaces();}
                if(f.isUsed()) {f.setUnused(); f.clearFaces();}
                howManyCubes = 0;
                s.clear();
                cout << "Reset!" << endl;
                break;

            case'c':
                cout << "Enter the letters separated by a comma. EG: A,B,C,d,e,f" << endl;
                cin >> cubeLetters;
                if(cubeLetters.size() != 11) {cout << "Invalid letter size." << endl; break;}

                transform(cubeLetters.begin(), cubeLetters.end(), cubeLetters.begin(), [](unsigned char c){
                    return tolower(c); });

                // debug
                //for (auto &tmp : cubeLetters)
                //    cout << tmp << " ";

                cubeLetters.erase(remove(cubeLetters.begin(), cubeLetters.end(), ','), cubeLetters.end());
                strcpy(cubeLettersArray, cubeLetters.c_str());
                cubeLetters = "";

                if(!a.isUsed()) {a.setUsed(); a.updateCube(cubeLettersArray, 1);}
                else if(!b.isUsed()) {b.setUsed(); b.updateCube(cubeLettersArray, 2);}
                else if(!c.isUsed()) {c.setUsed(); c.updateCube(cubeLettersArray, 3);}
                else if(!d.isUsed()) {d.setUsed(); d.updateCube(cubeLettersArray, 4);}
                else if(!e.isUsed()) {e.setUsed(); e.updateCube(cubeLettersArray, 5);}
                else if(!f.isUsed()) {f.setUsed(); f.updateCube(cubeLettersArray, 6);}
                else cout << "Sorry! you've reached the max limit of cubes!" << endl;
                break;

            case 'a':
                if(a.isUsed()) a.printCube();
                if(b.isUsed()) b.printCube();
                if(c.isUsed()) c.printCube();
                if(d.isUsed()) d.printCube();
                if(e.isUsed()) e.printCube();
                if(f.isUsed()) f.printCube();
                break;

            case 'w':
                cout << "Enter the new word: " << endl;
                cin >> wordCommand;
                if(wordCommand.size()>6){cout << "Word too long!" << endl; break;}
                transform(wordCommand.begin(), wordCommand.end(), wordCommand.begin(), [](unsigned char c){
                    return tolower(c); });

                w.updateWord(wordCommand);
                cout << "Updated word to: ";
                w.printWord();
                break;

            case 's':
                cout << endl << "Solving: " << endl;
                if(a.isUsed()) {howManyCubes++; s.receiver(a.getFaces(), 1);}
                if(b.isUsed()) {howManyCubes++; s.receiver(b.getFaces(), 2);}
                if(c.isUsed()) {howManyCubes++; s.receiver(c.getFaces(), 3);}
                if(d.isUsed()) {howManyCubes++; s.receiver(d.getFaces(), 4);}
                if(e.isUsed()) {howManyCubes++; s.receiver(e.getFaces(), 5);}
                if(f.isUsed()) {howManyCubes++; s.receiver(f.getFaces(), 6);}

                if(howManyCubes>0) {
                    s.setWord(w.getWord());
                    s.solve();
                    //cout<<"solve activated"<<endl; // debug
                }

                break;

            case 'q':
                cout << "Quitting.." << endl;
                end = true;
                break;

            default:
                cout << "No such command.." << endl;
                break;
        }
        command = ' ';
    }

    return 0;
}
