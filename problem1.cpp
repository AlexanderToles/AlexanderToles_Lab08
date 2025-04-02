//  EECS 348 LAB 08
//  MATRIX OPERATIONS
//  INPUT: Test file, menu selection
//  OUTPUT: Menu, matricies
//  ALEXANDER TOLES      
//  APRIL 01 2025
//  COLLABORATORS: Stack Overflow (Line 40) 

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

        //This section takes the maximum value of the matrix, finds the number of digits
        //and then adds leading zeros to the rest of the numbers 

        vector<int> max; //create a vector to store the max of each row
        for(int i = 0; i < size; i++){ //iterate over rows
            max.push_back(*max_element(matrix[i].begin(),matrix[i].end())); //get the max element, add to max vector
        }

        int width = *max_element(max.begin(),max.end()); //number of digits in max value

    
        for(int i = 0; i < size; i++){ //for ever column in every row
            for(int j = 0; j < size; j++){

                //The following print command is based off of this stack overflow answer
                //https://stackoverflow.com/questions/530614/print-leading-zeros-with-c-output-operator

                //The following code sets the width of the output to the width of the maximum value, filling every
                //nubmer in between with 0's

                cout << internal << setw(to_string(width).size()) << setfill('0') << matrix[i][j] << " ";
                
            }
            cout << "\n";
        }
    }
    
    Matrix operator+(const Matrix &other){ //overload addition
        Matrix result; //initialize the result matrix
        result.size = size;
        result.name = "Result";
        result.matrix.resize(size, vector<int>(size, 0)); //make empty matrix of size N
        for(int i = 0; i < size; i++){ //iterate through every element
            for(int j = 0; j < size; j++){
                int sum = matrix[i][j] + other.matrix[i][j]; //add the elements of both matrixies together, append it to the result matrix
                result.matrix[i][j] = sum;
            }
        }
        return result;
    }
    Matrix operator*(const Matrix &other){ //overload multiplication
        Matrix result; //initialize result matrix
        result.size = size;
        result.name = "Result";
        result.matrix.resize(size, vector<int>(size, 0));
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){ //multply rows against columns, sum the results, and append result matrix
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
        for(int i = 0; i < size; i++){ //go through every diagonal entry, summing them together
            sum+=matrix[i][i];
        }
        cout << sum << "\n";
        return(sum);
    }
    int sumMinorDiagonal(){
        int sum = 0;
        for(int i = size-1; i >= 0; i--){ //start at last column and move backward
            sum+=matrix[size-1-i][i]; //iterate over each row, picking the i column
        }
        cout << sum << "\n";
        return(sum);
    }
    void swapRows(int r1, int r2){
            vector<int> tempRow = matrix[r1];
            matrix[r1] = matrix[r2];
            matrix[r2] = tempRow;
            printMatrix();
        
    }
    void swapCols(int c1, int c2){
        for(int i = 0; i < size; i++){ //similar to swapRow, but need to iterate over each row
            int tempval = matrix[i][c1];
            matrix[i][c1] = matrix[i][c2];
            matrix[i][c2] = tempval;
        }
        printMatrix();
    }
    void setValue(int i, int j, int val){
        matrix[i][j] = val;
        printMatrix();  
    }
};

void readMatrix(vector<string> lines,int start,int end, Matrix &inMatrix){
    std::vector<std::vector<int> > tempMatrix; //initialize temp matrix we add values to
    for(int i = start;i < end; i++){//go from matrixA start pos to matrixB start position
        vector<int> row;
        std::regex pattern("\\d+");  // Create a named regex variable

        //iterate through each regex match, adding them to the row

        auto searchBegin = std::sregex_iterator(lines[i].begin(), lines[i].end(), pattern); 
        auto searchEnd = std::sregex_iterator();
        for (sregex_iterator j = searchBegin; j != searchEnd; ++j)
        {
            smatch match = *j;
            int match_int = stoi(match.str()); //conver the match to a string object, then to a integer
            row.push_back(match_int); //add the match to the row
        }
        tempMatrix.push_back(row); //add the row to the matrix
    }
    inMatrix.matrix = tempMatrix; //set the input matrix to the temp matrix

}

void printMenu(Matrix matrixA,Matrix matrixB){
    while(true){ //loop to handle exit
        int choice;
    
        cout << "1) Add matricies" << "\n";
        cout << "2) Multiply matricies" << "\n";
        cout << "3) Sum diagonals" << "\n";
        cout << "4) Swap rows" << "\n";
        cout << "5) Swap columns" << "\n";
        cout << "6) Set element" << "\n";
        cout << "7) Exit" << "\n";

        cin >> choice; //get choice from user

        switch(choice){ //call respective functions
            case 1:
                (matrixA + matrixB).printMatrix();
                break;
            case 2:
                (matrixA * matrixB).printMatrix();
                break;
            case 3:
                cout << "Major: ";
                matrixA.sumMajorDiagonal();
                cout << "Minor: ";
                matrixA.sumMinorDiagonal();
                break;
            case 4:
                
                while(true){ //loop to prompt user until in-bounds selection is chosen
                    int r1,r2;
                    cout << "Enter first row: ";
                    cin >> r1;
                    cout << "Enter second row: ";
                    cin >> r2;
                    if((r1 < matrixA.size && r1 >= 0)&&(r2 < matrixA.size && r2 >= 0)){
                        matrixA.swapRows(r1,r2);
                        break;
                    }
                    else{
                        cout << "Selection out of bounds.";
                    }
                }
                break;
            case 5:
                
                while(true){ //loop to prompt user until in-bounds selection is chosen
                    int c1,c2;
                    cout << "Enter first column: ";
                    cin >> c1;
                    cout << "Enter second column: ";
                    cin >> c2;
                    if((c1 < matrixA.size && c1 >= 0)&&(c2 < matrixA.size && c2 >= 0)){
                    matrixA.swapCols(c1,c2);
                    break;
                    }
                    else{
                        cout << "Selection out of bounds.";
                    }
                }
                break;
            case 6:
                
                while(true){ //loop to prompt user until in-bounds selection is chosen
                    int row,col,val;
                    cout << "Enter row: ";
                    cin >> row;
                    cout << "Enter column: ";
                    cin >> col;
                    cout << "Enter value: ";
                    cin >> val;
                    if((row < matrixA.size && row >= 0)&&(col < matrixA.size && col >= 0)){
                    matrixA.setValue(row,col,val);
                    break;
                    }
                    else{
                        cout << "Selection out of bounds.";
                    }
                }
                break;
            case 7:
                return; //return from function, exiting program
            default: 
                cout << "Invalid selection";
                printMenu(matrixA,matrixB);
                break;
        }
    }
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
        printMenu(matrixA,matrixB);
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