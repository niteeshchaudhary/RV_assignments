#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    string mytext = "";
    string myproperty = "";

    // Read from the text file
    // testcases/testcases/property2/system4.input
    ifstream readproperty(argv[1]);
    ifstream readfile("template.cpp");
    ofstream writefile("monitor.cpp");

    while (getline(readfile, mytext))
    {
        if (mytext == "    string exp;" && getline(readproperty, myproperty))
        {
            writefile << "string exp = \""
                      << myproperty
                      << "\";\n";
        }
        else
        {
            writefile << mytext << "\n ";
        }
    }
    readfile.close();
    writefile.close();
    return 0;
}