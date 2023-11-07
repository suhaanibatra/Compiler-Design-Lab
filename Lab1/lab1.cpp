//WAP that takes source program of C language via file handling and counts number of lines, number of words, number of characters, and number of keywords present in the source program and display them. 
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;

bool isKeyword(string& word, vector<string>& keywords){
    return find(keywords.begin(), keywords.end(), word) != keywords.end();
}

bool isWord(string& word){
    return word.find_first_not_of("[]{}()") != std:: string:: npos;
}

int main(){
    int lines = 0, words = 0, characters = 0, keyword_count = 0;
    string filename = "check.c";
    string line;
    ifstream file(filename);

    vector<string> keywords = {"auto", "break", "case", "char", "const", "continue", "default", "do", 
    "double", "else", "enum", "extern", "float", "for", "goto", "if", 
    "int", "long", "register", "return", "short", "signed", "sizeof", "static", 
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};


    if(!file.is_open()){
        cout << "Error: Could not open the specified file."<< endl;
        return 1;
    }

    while(getline(file, line)){ 
        // Counting number of lines and total length (characters + spaces)
        ++lines;
        characters += line.length();
        
        stringstream ss(line);
        string word;

        while(ss >> word){
            if(isKeyword(word, keywords)) keyword_count++;
            if(isWord(word)) words++;
        }
    }

    cout << "Number of lines = " << lines << endl;
    cout << "Number of characters = " << characters << endl;
    cout << "Number of words = " << words << endl;
    cout << "Number of keywords = " << keyword_count << endl;
    return 0;
}
