#include "XmasProtocol.h"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// print sequance
template <class InputIt>
void print(const string &name, InputIt first, InputIt last)
{
    cout << name;
    std::for_each(first, last, [](const auto &n) { cout << " " << n; });
    cout << endl;
}

bool XmasProtocol::ShiftFrame(std::istream &stream, deque<unsigned long long> &frame, size_t windows_size)
{
    string line;
    unsigned long long number;
    bool is_first = frame.size() < windows_size + 1;
    bool new_data = false;

    if (frame.size() > windows_size)
        frame.pop_front();

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

    // print("frame:", begin(frame), end(frame));

    return new_data;
}

bool XmasProtocol::CheckBytes(std::istream &stream, size_t windows_size, unsigned long long &invalid_number)
{
    deque<unsigned long long> frame;
    unsigned long long check_sum;

    while (ShiftFrame(stream, frame, windows_size))
    {
        check_sum = frame.at(frame.size() - 1);
        // cout << "check sum: " << check_sum << endl;
        if (!CheckSum(frame.begin(), frame.end() - 1, check_sum))
        {
            invalid_number = check_sum;
            return false;
        }
    }

    return true;
}

bool XmasProtocol::FindSumMinMax(std::istream &stream, const unsigned long long &in_number, unsigned long long &out_sum)
{
    deque<unsigned long long> seq;
    string line;
    unsigned long long number = 0;

    out_sum = 0;
    while (getline(stream, line))
    {
        stringstream sline(line);
        sline >> number;

        seq.push_back(number);
        out_sum += number;

        while (out_sum > in_number)
        {
            // cout << "remove element as " << out_sum << " > " << in_number << endl;
            auto n = seq.front();
            seq.pop_front();
            out_sum -= n;
        }

        // print("sequence:", begin(seq), end(seq));

        if (out_sum == in_number)
        {
            const auto [min, max] = minmax_element(begin(seq), end(seq));
            out_sum = *min + *max;

            cout << "sum: " << *min << " + " << *max << " = " << out_sum << endl;
            return true;
        }
    }

    return false;
}
