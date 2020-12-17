#include "XmasProtocol.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        // at least 2 arguments
        // filename windows_size
        return 1;
    }

    const string filename = argv[1];
    const size_t windows_size = atol(argv[2]);

    cout << "Filename: " << filename << endl;
    cout << "Window size: " << windows_size << endl;

    XmasProtocol proto;
    unsigned long long bad_byte;

    if (!proto.CheckBytes(filename, windows_size, bad_byte))
        cout << "There is a wrong number: " << bad_byte << endl;
    else
        cout << "All numbers are OK" << endl;

    return 0;
}
