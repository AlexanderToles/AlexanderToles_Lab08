#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

class Matrix { //matrix class
    public: 
    int size; //initialize the size, name, and 2d vector
    string name;
    std::vector<std::vector<int> >matrix;

    int getSize(){
        return size;
    }

    void printMatrix(){
        cout << name << ":\n"; //print the name of the matrix
        vector<int> max;
        int lead;
        int max_lead;
        for(int i = 0; i < size; i++){
            max.push_back(*max_element(matrix[i].begin(),matrix[i].end()));
        }
        int width = *max_element(max.begin(),max.end());

    
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                cout << internal << setw(to_string(width).size()) << setfill('0') << matrix[i][j] << " ";
            }
            cout << "\n";
        }
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
    Matrix operator*(const Matrix &other){
        Matrix result;
        result.size = size;
        result.name = "Result";
        result.matrix.resize(size, vector<int>(size, 0));
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                int sum = 0;
                for(int k = 0; k < size; k++){
                    sum+=matrix[i][k]*other.matrix[k][j];
                }
                result.matrix[i][j] = sum;
            }
        }
        return result;
    }
    int sumMajorDiagonal(){
        int sum = 0;
        for(int i = 0; i < size; i++){
            sum+=matrix[i][i];
        }
        cout << sum << "\n";
        return(sum);
    }
    int sumMinorDiagonal(){
        int sum = 0;
        for(int i = size-1; i >= 0; i--){
            sum+=matrix[i][i];
        }
        cout << sum << "\n";
        return(sum);
    }
    void swapRows(int r1, int r2){
        if((r1 < size-1 && r1 >= 0)&&(r2 < size-1 && r2 >= 0)){
            vector<int> tempRow = matrix[r1];
            matrix[r1] = matrix[r2];
            matrix[r2] = tempRow;
            printMatrix();
        }
        
    }
    void swapCols(int c1, int c2){
        if((c1 < size-1 && c1 >= 0)&&(c2 < size-1 && c2 >= 0)){
        for(int i = 0; i < size; i++){
            int tempval = matrix[i][c1];
            matrix[i][c1] = matrix[i][c2];
            matrix[i][c2] = tempval;
        }
        }
        printMatrix();
    }
    void setValue(int i, int j, int val){
        matrix[i][j] = val;
        printMatrix();  
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
    fstream inputFile; //declare file
    inputFile.open(fileName, fstream::in); //open file, set it to read from file
    if(inputFile.is_open()){ //check if file was opened successfully
 
        cout << "File opened successfully!\n";

        string line; //current line from file
        smatch match; //matches from regex search
        int linePos = 0; //current line position
        vector<string> lines; //vector to store all lines
        Matrix matrixA, matrixB; //create matrix

        matrixA.name = "Matrix A"; //initialize the two matricies
        matrixB.name = "Matrix B";

        while(getline(inputFile,line)){ //go through each line in the file, and add it to the vector
            lines.push_back(line);
        }

        for(int i = 0; i < lines.size(); i++){ //go through each line in the vector
            if(regex_search(lines[i],match,regex ("^\\d+")) && i==0){ //only want the number located in the first line

                int size = stoi(match[0]); //convert string to integer

                matrixA.size = size; //set the size of the two matricies
                matrixB.size = size;
            }

            else{
                if(lines[i] != ""){ //read through lines until you hit the first matrix
                    int m2 = i+matrixA.size; //set matrixB start position
                    readMatrix(lines,i,m2,matrixA);
                    readMatrix(lines,m2,m2+matrixB.size,matrixB);
                    break;
                } 
            }

        }
        matrixA.printMatrix();
        matrixB.printMatrix();
        (matrixA + matrixB).printMatrix();
        (matrixA * matrixB).printMatrix();
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