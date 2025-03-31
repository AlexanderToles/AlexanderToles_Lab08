#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void scanFile(string fileName){
    fstream inputFile;
    inputFile.open(fileName, fstream::in);
    if(inputFile.is_open()){
        cout << "File opened successfully!";
    }
    else {
        cout << "Error: Failed to open file.";
    }
}

int main(){
    string fileName; 
    cout << ("Enter input file name: ");
    cin >> fileName;
    scanFile(fileName);
}