#include "XmasProtocol.h"

#include <iostream>
#include <sstream>

using namespace std;

bool XmasProtocol::ShiftFrame(std::istream &stream, deque<unsigned long long> &frame, size_t windows_size)
{
    string line;
    unsigned long long number;
    bool is_first = frame.size() < windows_size + 1;
    bool new_data = false;

    if (frame.size() > windows_size)
    {
        frame.pop_front();
    }

    while (frame.size() < windows_size + 1 && getline(stream, line))
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

bool XmasProtocol::CheckBytes(std::istream &stream, size_t windows_size, unsigned long long &out_byte)
{
    deque<unsigned long long> frame;
    unsigned long long check_sum;

    while (ShiftFrame(stream, frame, windows_size))
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
