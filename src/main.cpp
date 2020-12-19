#include "XmasProtocol.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        // at least 2 arguments
        // filename windows_size
        cout << "Usage: " << argv[0] << " FILENAME WINDOWS_SIZE\n";
        return 1;
    }

    const string filename = argv[1];
    const size_t windows_size = atol(argv[2]);

    cout << "Filename: " << filename << endl;
    cout << "Window size: " << windows_size << endl;

    XmasProtocol proto;
    unsigned long long invalid_number;

    // open file
    fstream file_stream(filename);
    if (!file_stream.is_open())
    {
        cout << "can't open file: " << filename << endl;
        return false;
    }

    // Part 1. Check bytes for invalid number
    if (!proto.CheckBytes(file_stream, windows_size, invalid_number))
        cout << "There is an invalid number: " << invalid_number << endl;
    else
        cout << "All numbers are OK" << endl;

    file_stream.clear();
    file_stream.seekg(0);

    // Part2. find Min Max sum in sequance
    unsigned long long sum;
    if (proto.FindSumMinMax(file_stream, invalid_number, sum))
        cout << "Found Min Max sequence sum: " << sum << " for " << invalid_number << endl;
    else
        cout << "Min Max sequence sum not found for " << invalid_number << endl;

    return 0;
}
