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
    if(readproperty){
        ifstream readfile("./template/template.cpp");
        ofstream writefile("test_monitor.cpp");

        while (getline(readfile, mytext))
        {
            if (mytext == "    string exp;" && getline(readproperty, myproperty))
            {
                writefile << "\tstring exp = \""
                        << myproperty
                        << "\";\n";
            }
            else
            {
                writefile << mytext << "\n ";
            }
        }
        cout<<"Succeed"<<endl;
        readfile.close();
        writefile.close();
    }else{
    cout<<"file not found"<<endl;
    }
    return 0;
}