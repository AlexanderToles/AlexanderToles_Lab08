#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
class Matrix {
    public:
    int size;
    std::vector<std::vector<int> > matrix;

    int getSize(){
        return size;
    }
    void setValue(int i, int j, int val){
        matrix[i][j] = val;    
    }
};

void scanFile(string fileName){
    fstream inputFile;
    inputFile.open(fileName, fstream::in);
    if(inputFile.is_open()){

        cout << "File opened successfully!\n";

        string line; //current line from file
        smatch match; //matches from regex search
        int linePos = 0; //current line position

        Matrix newMatrix; //create matrix

        while(getline(inputFile,line)){
            if(regex_search(line,match,regex ("^\\d+")) && linePos==0){ //only want the number located in the first line

                int size = stoi(match[0]); //convert string to integer
                cout << "size: " << size << "\n";
                newMatrix.size = size;
                linePos++;
            }
            if (linePos > 0){
                if (line != "\n"){
                    if(linePos < linePos + newMatrix.size){
                        std::regex pattern("\\d+");  // Create a named regex variable
                        auto searchBegin = std::sregex_iterator(line.begin(), line.end(), pattern);
                        auto searchEnd = std::sregex_iterator();
                        for (sregex_iterator i = searchBegin; i != searchEnd; ++i)
                        {
                            smatch match = *i;
                            string match_str = match.str();
                            cout << match_str << '\n';
                        }

                    }
                }
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