#pragma once

#include <string>
#include <algorithm>
#include <deque>
#include <istream>

class XmasProtocol
{
private:
    template <class InputIt>
    bool CheckSum(InputIt first, InputIt last, unsigned long long sum)
    {
        const size_t N = last - first;
        const size_t K = 2;

        std::string bitmask(K, 1); // K leading 1's
        bitmask.resize(N, 0);      // N-K trailing 0's

        // check sum and permute bitmask
        do
        {
            unsigned long long calculated_sum = 0;
            for (size_t i = 0; i < N; ++i) // [0..N-1] integers
            {
                if (bitmask[i])
                {
                    // std::cout << " " << *(first + i);
                    calculated_sum += *(first + i);
                    if (*(first + i) > sum)
                    {
                        // cout << " > early exit by: " << *(first + i) << endl;
                        continue;
                    }
                }
                if (i == N - 1)
                {
                    // cout << " > calculated_sum: " << calculated_sum;
                    if (calculated_sum == sum)
                        return true;
                }
            }
            // std::cout << std::endl;
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

        return false;
    }

    bool ShiftFrame(std::istream &stream, std::deque<unsigned long long> &frame, size_t windows_size);

public:
    bool CheckBytes(std::istream &stream, size_t windows_size, unsigned long long &invalid_number);
    bool FindSumMinMax(std::istream &stream, const unsigned long long &in_number, unsigned long long &out_sum);
};
