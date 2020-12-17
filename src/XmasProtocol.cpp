#include "XmasProtocol.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

bool XmasProtocol::ShiftFrame(fstream &sfile, deque<unsigned long long> &frame, size_t windows_size)
{
    string line;
    unsigned long long number;
    bool is_first = frame.size() < windows_size + 1;
    bool new_data = false;

    if (frame.size() > windows_size)
    {
        frame.pop_front();
    }

    while (frame.size() < windows_size + 1 && getline(sfile, line))
    {
        stringstream sline(line);
        sline >> number;
        frame.push_back(number);
        new_data = true;
    }

    if (frame.size() < windows_size + 1)
    {
        cout << "frame was not filled" << endl;
        return false;
    }

    // print frame
    // cout << "frame:";
    // for (auto &&i : frame)
    // {
    //     cout << " " << i;
    // }
    // cout << endl;

    return new_data;
}

bool XmasProtocol::CheckBytes(const string &filename, size_t windows_size, unsigned long long &out_byte)
{
    fstream sfile(filename);
    if (!sfile.is_open())
    {
        cout << "can't open file" << endl;
        return false;
    }

    deque<unsigned long long> frame;
    unsigned long long check_sum;

    while (ShiftFrame(sfile, frame, windows_size))
    {
        check_sum = frame.at(frame.size() - 1);
        cout << "check sum: " << check_sum << endl;
        if (!CheckSum(frame.begin(), frame.end() - 1, check_sum))
        {
            out_byte = check_sum;
            return false;
        }
    }

    return true;
}
