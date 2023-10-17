#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
int main()
{
    fstream input("./text",ios::in);
    stringstream content;
    string contents;
    content << input.rdbuf();
    contents = content.str();

    cout<<"Length of file is"<<contents.length();
    if(contents[7] == '\0')
    {
        cout<<"Nuill CHaracter";
    }   
    

    



}