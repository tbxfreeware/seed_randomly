# seed_randomly
Header `tbx.seed_randomly.cpp14.h` provides tools for seeding a C++ random number engine with random seeds from `std:random_device`. It works with any engine that can be seeded with a seed sequence, including those in the C++ Standard Library.

This header uses only the features of C++14, nothing later.

##Is `std::random_device` a good source of entropy?
Before using this library, you should satisfy yourself that `std::random_device` is a good source of entropy on your system. Sometimes, it is not.

[Microsoft Visual C++](https://learn.microsoft.com/en-us/cpp/standard-library/random-device-class?view=msvc-170), for instance, generates "non-deterministic and cryptographically secure" values, and never blocks, which is excellent. Prior to version 9.2, however, [MinGW distributions of GCC](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85494) used std::mt19937 with a fixed seed! Those systems generated the same sequence every time.

##A good choice for `mt19937`
The tools here are particularly useful for seeding `std::mt19937` and `std::19937_64`. Those engines have almost 20,000 bits of state, so trying to seed them with a single seed of only 32 or 64 bits is borderline foolish. The functions in this header supply separate seeds for each of the 624 state variables in `mt19937`. 

Using one of the two methods below is far superior to seeding with something like `std::time(nullptr)` or `std::chrono::high_resolution_clock::now().time_since_epoch().count()`, which, respectively, have only 32 and 64 bits of entropy.

## seed_randomly
This function takes a random number engine as argument, and seeds it with random seeds generated from `std::random_device`.
````cpp
// Example: Seed mt19937 with random seeds from std::random_device.
std::mt19937 mt;
tbx::seed_randomly( mt );

// Example: Seed pcg32, one of the PCG engines by Melissa O'Neill.
pcg32 e;
tbx::seed_randomly( e );
````

## class seed_seq_rd
This class mimics the interface of `std::seed_seq`, but uses `std::random_device` to generate seeds. Objects of this type are seed sequences that can be used as arguments to member function `seed` in a random number engine.

Function `seed_randomly` is a trivial wrapper around a `seed_seq_rd` object.
````cpp
// Example: Seed mt19937 with random seeds from std::random_device.
std::mt19937 mt;
tbx::seed_seq_rd s;
mt.seed( s );

// Example: Seed pcg32, one of the PCG engines by Melissa O'Neill.
pcg32 e;
e.seed( s );  // seed_seq_rd object can be reused.

// Example: Implementation of seed_randomly:
template< typename RandomNumberEngine >
void seed_randomly( RandomNumberEngine& e);
{
    tbx::seed_seq_rd s;
    e.seed(s);
}
````