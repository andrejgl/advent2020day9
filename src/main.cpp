#include <iostream>
#include <vector>
#include <algorithm>

#include <fstream>
#include <sstream>
#include <deque>
#include <cstdlib>

using namespace std;

template< class InputIt>
bool find_day9_sum(const InputIt first, const InputIt last, unsigned long long sum)
{
    const size_t N = last - first;
    const size_t K = 2;

    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // check sum and permute bitmask
    do {
        unsigned long long calculated_sum = 0;
        for (size_t i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) {
                // std::cout << " " << *(first + i);
                calculated_sum += *(first + i);
                if (*(first + i) > sum) {
                    // cout << " > early exit by: " << *(first + i) << endl;
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

    if (frame.size() > windows_size) {
        frame.pop_front();
    }

    while ( frame.size() < windows_size + 1 && getline(sfile, line) )
    {
        stringstream sline(line);
        sline >> number;
        frame.push_back(number);
        new_data = true;
    }

    if (frame.size() < windows_size + 1) {
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

bool find_day9_wrong_sum( const string& filename, size_t windows_size, unsigned long long& sum )
{
    fstream sfile( filename );
    if (!sfile.is_open()) {
        cout << "can't open file" << endl;
        return false;
    }

    deque<unsigned long long> frame;
    unsigned long long check_sum;

    while ( shift_frame( sfile, frame, windows_size ) )
    {
        check_sum = frame.at(frame.size() - 1);
        cout << "check sum: " << check_sum << endl;
        if( !find_day9_sum( frame.begin(), frame.end() - 1, check_sum ) ) {
            sum = check_sum;
            return true;
        }
    }

    return false;
}

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

    unsigned long long sum;
    if ( find_day9_wrong_sum( filename, windows_size, sum ) )
        cout << "There is a wrong number: " << sum << endl;
    else
        cout << "All numbers are OK" << endl;

    return 0;
}
