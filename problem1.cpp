#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
class Matrix {
    public:
    int size;
    string name;
    std::vector<std::vector<int> >matrix;

    int getSize(){
        return size;
    }
    void printMatrix(){
        cout << name << ":\n";
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                cout << matrix[i][j] << " ";
            }
            cout << "\n";
        }
    }
    void setValue(int i, int j, int val){
        matrix[i][j] = val;    
    }
    Matrix operator+(const Matrix &other){
        Matrix result;
        result.size = size;
        result.name = "Result";
        result.matrix.resize(size, vector<int>(size, 0));
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                int sum = matrix[i][j] + other.matrix[i][j];
                result.matrix[i][j] = sum;
            }
        }
        return result;
    }
};

void readMatrix(vector<string> lines,int start,int end, Matrix &inMatrix){
    int linePos = 0;
    std::vector<std::vector<int> > tempMatrix;
    for(int i = start;i < end; i++){
        vector<int> row;
        //cout << lines[i] << "\n";
        std::regex pattern("\\d+");  // Create a named regex variable
        auto searchBegin = std::sregex_iterator(lines[i].begin(), lines[i].end(), pattern);
        auto searchEnd = std::sregex_iterator();
        for (sregex_iterator j = searchBegin; j != searchEnd; ++j)
        {
            smatch match = *j;
            int match_int = stoi(match.str());
            row.push_back(match_int);
        }
        tempMatrix.push_back(row);
    }
    inMatrix.matrix = tempMatrix;

}

void scanFile(string fileName){
    fstream inputFile;
    inputFile.open(fileName, fstream::in);
    if(inputFile.is_open()){

        cout << "File opened successfully!\n";

        string line; //current line from file
        smatch match; //matches from regex search
        int linePos = 0; //current line position
        vector<string> lines;
        Matrix matrixA, matrixB; //create matrix
        matrixA.name = "Matrix A";
        matrixB.name = "Matrix B";

        while(getline(inputFile,line)){
            lines.push_back(line);
        }

        for(int i = 0; i < lines.size(); i++){
            if(regex_search(lines[i],match,regex ("^\\d+")) && i==0){ //only want the number located in the first line

                int size = stoi(match[0]); //convert string to integer
                cout << "size: " << size << "\n";
                matrixA.size = size;
                matrixB.size = size;
            }
            else{
                if(lines[i] != ""){
                    int m2 = i+matrixA.size;
                    readMatrix(lines,i,m2,matrixA);
                    readMatrix(lines,m2,m2+matrixB.size,matrixB);
                    break;
                } 
            }

        }
        matrixA.printMatrix();
        matrixB.printMatrix();
        (matrixA + matrixB).printMatrix();


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