#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
class Matrix {
    public:
    int size;
    int getSize(){
        return size;
    }
    void setValue(){

    }
};

void scanFile(string fileName){
    fstream inputFile;
    inputFile.open(fileName, fstream::in);
    if(inputFile.is_open()){
        cout << "File opened successfully!\n";
        string line;
        smatch match;
        int linePos = 0;
        while(getline(inputFile,line)){
            if(regex_search(line,match,regex ("^\\d+")) && linePos==0){

                int size = stoi(match[0]);

                cout << "size: " << size << "\n";
                Matrix newMatrix;
                newMatrix.size = size;
                linePos++;
            }
        }

    }
    else {
        cout << "Error: Failed to open file.\n";
    }
}

int main(){
    string fileName; 
    cout << ("Enter input file name: ");
    cin >> fileName;
    scanFile(fileName);
}