#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
string read(string &fileName)
{
    string readText{};
    string returnText{};
    ifstream file_in{fileName};
    if (!file_in)
    {
        cout << "File read error";
        exit(1);
    }
    while (getline(file_in, readText))
    {
        if (readText.empty()) continue;
        returnText += (readText + "\n");
    }
    file_in.close();
    return returnText;
}

void write(string & fileName , string& text)
{
    ofstream file_out{fileName};
    if(!file_out){
        cout << "Could not read file";
        exit(1);
    }
    file_out << text;
    file_out.close();
    cout << "Write complete" << endl;
}
int main()
{

    string fileName{"../text.txt"};
    auto text = read(fileName);
    write(fileName, text);




    return 0;
}
