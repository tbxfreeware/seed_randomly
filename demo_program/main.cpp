//================================================================================
// "MIT License"
//================================================================================
// Copyright 2023 Michael J. Mannon
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//================================================================================
#include <array>      // array, cbegin, cend
#include <cstddef>    // size_t
#include <iostream>   // basic_ostream, cout, ostream_iterator
#include <random>     // mt19937, mt19937_64
#include "tbx.seed_randomly.cpp14.h"
namespace tbx
{
    template< typename charT, typename traits >
    void demo_seed_randomly(std::basic_ostream<charT, traits>& log)
    {
        std::mt19937 mt;
        log << "std::mt19937 - Default seeding:\n" << mt << "\n\n";

        tbx::seed_randomly(mt);
        log << "std::mt19937 - Random seeding:\n" << mt << "\n\n";

        tbx::seed_randomly(mt);
        log << "std::mt19937 - A different random seeding:\n" << mt << "\n\n";

        std::mt19937_64 mt64;
        log << "std::mt19937_64 - Default seeding:\n" << mt64 << "\n\n";

        tbx::seed_randomly(mt64);
        log << "std::mt19937_64 - Random seeding:\n" << mt64 << "\n\n";

        tbx::seed_randomly(mt64);
        log << "std::mt19937_64 - A different random seeding:\n" << mt64 << "\n\n";

        // Other ctors work, and here's the proof, but there is 
        // no reason to use anything but the default ctor.
        {
            enum : std::size_t { ten = 10u };
            std::array<int, ten> primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
            tbx::seed_seq_rd s(std::cbegin(primes), std::cend(primes));
            log << "tbx::seed_seq_rd - Construct from iterator range:\n"
                << "sseq.size(): " << s.size()
                << "\nsseq.param(): ";
            s.param(std::ostream_iterator
                <tbx::seed_seq_rd::result_type>(log, " "));
            log << "\n\n";
        }
        {
            tbx::seed_seq_rd s{ -1ll, 0ll, 1ll };
            log << "tbx::seed_seq_rd - Construct from std::initializer_list<long long>:\n"
                << "sseq.size(): " << s.size()
                << "\nsseq.param(): ";
            s.param(std::ostream_iterator
                <tbx::seed_seq_rd::result_type>(log, " "));
            log << "\n\n";
        }
    }
}
int main()
{
    auto& log{ std::cout };
    tbx::demo_seed_randomly(log);
    return 0;
}
// end file: main.cpp
