#include <iostream>
#include <vector>
#include <algorithm>

#include <fstream>
#include <sstream>
#include <deque>

using namespace std;

bool find_day9_sum(const deque<unsigned long long> &data, unsigned long long sum)
{
    const size_t N = data.size();
    const size_t K = 2;

    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // check sum and permute bitmask
    do {
        unsigned long long calculated_sum = 0;
        for (size_t i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) {
                // std::cout << " " << data.at(i);
                calculated_sum += data.at(i);
                if (data.at(i) > sum) {
                    // cout << " > early exit by: " << data.at(i) << endl;
                    continue;
                }
            }
            if (i == N-1) {
                // cout << " > calculated_sum: " << calculated_sum;
                if (calculated_sum == sum )
                    return true;
            }
        }
        // std::cout << std::endl;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return false;
}

bool shift_frame( fstream& sfile, deque<unsigned long long>& frame, size_t windows_size )
{
    string line;
    unsigned long long number;
    bool is_first = frame.size() < windows_size + 1;
    bool new_data = false;

    if (frame.size() > windows_size)
        frame.pop_front();

    while ( frame.size() < windows_size + 1 && getline(sfile, line) )
    {
        stringstream sline(line);
        sline >> number;
        frame.push_back(number);
        new_data = true;
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

bool find_day9_wrong_sum( const string& filename, size_t windows_size, unsigned long long& sum )
{
    fstream sfile( filename );
    deque<unsigned long long> window;
    unsigned long long check_sum;

    while ( shift_frame( sfile, window, windows_size ) )
    {
        check_sum = window.at(window.size() - 1);
        cout << "check sum: " << check_sum << endl;
        window.pop_back();
        if( !find_day9_sum( window, check_sum ) ) {
            sum = check_sum;
            return true;
        }
        window.push_back(check_sum);
    }

    return false;
}

int main(int argc, char const *argv[])
{
    size_t WINDOW_SIZE = 25;
    unsigned long long sum;
    if (find_day9_wrong_sum("day9.data", WINDOW_SIZE, sum))
        cout << "It's a wrong number: " << sum << endl;
    else
        cout << "All numbers are OK" << endl;

    return 0;
}
