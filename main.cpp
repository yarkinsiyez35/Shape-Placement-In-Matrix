#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool rowAndColumnControl(vector<string> &inputLines)                                    //checks if every row has the same number of columns
{
    if (inputLines.size() == 0)     //returns false if it is an empty file
    {
        return false;
    }
    unsigned long int row0 = inputLines[0].size();                    //row0 is declared as the number of columns in the first row
    for (unsigned int i = 1; i<inputLines.size(); i++)
    {          //compares every rows' number of columns with the first row's
        if (row0 != inputLines[i].size()){
            return false;                               //returns false if there is a mismatch
        }
    }
    return true;                                        //returns true in case of no errors
}

bool characterControl(vector<string> &inputLines)               //checks if there are any wrong characters
{
    for (unsigned int i = 0; i< inputLines.size(); i++)     //checks for each line
    {
        for (unsigned int j =0; j<inputLines[i].size(); j++)   //checks for each letter
        {
            char c1 = inputLines[i][j];
            if(c1 != '-' && c1 != '#')
            {
                return false;                               //returns false if the character is not '-' or '#'
            }
        }
    }
    return true;                                            // returns true in case of no errors
}

void printMatrix(vector<vector<char> > &matrix)          //prints the matrix
{
    for(unsigned int i = 0; i< matrix.size(); i++)                    //prints every row of the matrix
    {
        for (unsigned int j =0; j<matrix[i].size(); j++)            //prints every column of the matrix
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

int charToInt(char character)                           //converts character to integer data type
{
    return (int) character - '0';
}

int stringToInt(string const str)                             //converts string to integer data type
{
    stringstream stream;
    stream << str;
    int n;
    stream >>n;
    return n;
}
string parsedToShape(string str)                        //turns parsed user input to shapes
{
    string empty = "";                                  //declares an empty string to add shapes
    for(unsigned int i = 0; i<str.size(); i+= 2)         //increments i by two as the next number will be 2 indices to the right
    {
        int amount = charToInt(str[i]);             //sets the value of amount to how many stars/blanks it will be
        if (str[i+1] == 's')                                 //looks for i+1 since the format is 1s2b3s...
        {
            for (unsigned int j =0; j<amount; j++)                   //adds x many stars
            {
                empty += "*";
            }
        }
        else                                                //only other condition is "b"
        {
            for (unsigned int j = 0; j<amount; j++)         //adds x many empty space
            {
                empty += " ";
            }
        }

    }
    return empty;
}

bool columnVsUser(vector<vector<char> > &matrix, vector<string> &shapedInput)                //checks for any row where user's string is longer than number of columns in the matrix
{
    for (unsigned int i = 0; i<shapedInput.size(); i++)                             //for each user input
    {
        if (shapedInput[i].size()> matrix[0].size())                               //returns false if user's string is longer than the number of columns in the matrix
        {
            return false;
        }
    }
    return true;                                            // returns true if everything is okay
}

string intToString(int n)         //converts int to string
{
    stringstream stream;
    stream <<n;
    string str;
    stream >> str;
    return str;
}


void printResults(vector<string> &placements)
{
    if(placements.size() == 0)                                          //if the storage is empty there must be no placements
    {
        cout << "No placements found.\n";
    }
    else
    {
        for(unsigned int i =0; i<placements.size(); i++)                        //prints placements one by one
        {
            cout << "Placement number " << i+1 << ":\n";
            cout << placements[i] << endl;
        }
    }
}




bool alignmentCheck(vector<vector<char> > &matrix, vector<vector<char> > &userMatrix, unsigned int beginningRow, unsigned int beginningCol)           //returns true if the user shape fits into to the matrix with starting row and col
{
    for (unsigned int i = 0; i<userMatrix.size(); i++)                   //searches for each user Row
    {
        if( beginningRow + userMatrix.size() >matrix.size())                     //prevents looking for nonexistent matrix rows
        {
            return false;
        }
        for (unsigned int j=0; j<userMatrix[i].size();j++)               //searches for each user Col
        {
            if( userMatrix[i].size() +beginningCol > matrix[0].size())          //prevents looking for nonexistent matrix columns
            {
                return false;
            }
            if (userMatrix[i][j] == '*' && matrix[i+beginningRow][j+beginningCol] == '#')
            {
                return false;
            }
        }
    }
    return true;
}

string showAlignment(vector<vector<char> > &userMatrix, unsigned int beginningRow, unsigned int beginningCol)         //returns the coordinates of the stars
{
    string str = "";
    for (unsigned int i =0; i<userMatrix.size(); i++)                    //for each row of the userMatrix
    {

        for(unsigned int j =0; j<userMatrix[i].size(); j++)              //for each column
        {
            if (userMatrix[i][j] == '*')                //finds the location of the stars
            {
                str += "(" + intToString(i+beginningRow) + "," + intToString(j+beginningCol) +") ";         //adds beginningRow and beginningCol to find the possible locations at the matrix
            }
        }
    }
    return str;
}

int main() {
    /* Taking user input*/
    cout << "Please enter the file name:\n";
    string filename;
    cin >> filename;

    /* Opening the file*/
    ifstream input;
    input.open(filename.c_str());
    while(input.fail())                                                             //gets in a loop until user writes a valid file name
    {
        cout << "Could not open the file. Please enter a valid file name: \n";
        cin >> filename;
        input.open(filename.c_str());
    }

    /*Reading the contents of the file*/
    string line;                                                    //initializes an empty string for streaming lines
    vector<string> inputLines;                                      //initializes an empty vector to add each line
    while(getline(input,line))
    {
        inputLines.push_back(line);
    }



    if(!rowAndColumnControl(inputLines) || !characterControl(inputLines))         //Finishes the program if the file content is not acceptable
    {
        cout << "Erroneous file content. Program terminates.\n";
    }
    else
    {
        /*creating the matrix*/
        unsigned int row_number = inputLines.size();
        unsigned int col_number = inputLines[0].size();
        vector<vector<char> > matrix (row_number, vector<char> (col_number));       //declares the matrix with from the inputLines vector

        /*filling the matrix*/
        for (unsigned int i = 0; i<matrix.size(); i++)                  //for each row
        {
            for (unsigned int j =0; j<matrix[i].size(); j++)            //for each column
            {
                matrix[i][j] = inputLines[i][j];                       //copies every letter to the matrix cells
            }
        }

        /*printing the matrix*/
        cout << "The matrix file contains:\n";
        printMatrix(matrix);

        /*taking input from the user*/
        while(true)                     //starts the loop for asking the query to the user, terminates only when 'Quit' is the input
        {
            cout << "Enter the string query for a shape, or \"Quit\" to terminate the program:\n";
            string query;
            cin >> query;
            if(query == "Quit")                     //terminates the program when user types Quit
            {
                break;
            }

            /*parsing the input*/
            vector<string> parsedInput;                                 //initializes an empty vector to store every line information
            while(query.find('/') != -1)                            //starts parsing from the left side of the query
            {
                int slash_index = query.find('/');                          //finds the endpoint of the parsed information
                string parsedLine = query.substr(0,slash_index);        //creates the parsed string
                parsedInput.push_back(parsedLine);                              //adds the string to the vector
                query = query.substr(slash_index+1);                        //removes the parsed part from the operated string
            }
            parsedInput.push_back(query);                   //adds the final part after the final slash

            /*converting the input into shape form*/
            vector<string> shapedInput;             //initializes an empty vector to store the user input in the shape format
            for (unsigned int i = 0; i<parsedInput.size(); i++)
            {
                string shapedFormat = parsedToShape(parsedInput[i]);                //declares shapedFormat to avoid too many paranthesis in the below line
                shapedInput.push_back(shapedFormat);                                    //adds the shaped format to the vector
            }

            /*checking the user input*/
            if(shapedInput.size() > matrix.size() || !columnVsUser(matrix, shapedInput))    //gives error if there are more user rows or more user columns than of matrix
            {
                cout << "No placements found.\n";
            }
            else
            {
                /*converting the shape form into matrix*/
                unsigned int user_input_row_number = shapedInput.size();             //number of rows depend on the user rows

                vector<vector<char> > userMatrix(user_input_row_number);         //declares an empty user matrix to place the shapes
                /* filling up the userMatrix*/
                for(unsigned int i =0; i<shapedInput.size(); i++)                        //for each row of the matrix
                {
                    for(unsigned int j =0; j<shapedInput[i].size(); j++)
                    {
                        userMatrix[i].push_back(shapedInput[i][j]);           //adds each letter to the ith row
                    }
                }
                /*checking the matrix*/
                unsigned int beginningRow = 0;               //sets the search row as 0
                unsigned int beginningCol = 0;               //sets the search col as 0
                vector<string> placements;          //this vector will store every possible placement

                while(beginningRow<matrix.size())               //this loop will check for every possible placement
                {
                    string placement = "";
                    if(alignmentCheck(matrix, userMatrix, beginningRow,beginningCol))               //if there is a possible match
                    {
                        placement = showAlignment(userMatrix, beginningRow,beginningCol);           //finds the possible placement as string
                        placements.push_back(placement);                //adds the possible placement to the vector
                    }
                    beginningCol++;     //increments the beginningCol to look for other alternatives.
                    if(beginningCol == matrix[0].size())                //prevents index going over the limit
                    {
                        beginningRow++;             //starts searching for placements in the below row
                        beginningCol =0;            //sets starting point as the beginning of that row
                    }
                }
                printResults(placements);               //prints the final results 
            }
        }
    }
    return 0;
}
