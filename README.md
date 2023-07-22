# seed_randomly
Header `tbx.seed_randomly.cpp14.h` provides tools for randomly seeding random number engines in the C++ Standard Library. They work with any random number engine that can be seeded using a seed sequence, including all the engines in the C++ Standard Library.

The tools use only the features of C++14, nothing later.

## seed_randomly
This function takes a random number engine as argument, and seeds it with random seeds generated from `std::random_device`.
````cpp
// Declaration:
   template< typename RandomNumberEngine >
   void seed_randomly( RandomNumberEngine& );

// Example:
   std::mt19937 mt;
   tbx::seed_randomly( mt );
````

## class seed_seq_rd
This class mimics the interface of std::seed_seq, but uses `std::random_device` to generate seeds. Objects of this type are seed sequences that can be used as arguments to member function `seed` in a random number engine.
````cpp
Example:
   std::mt19937 mt;
   tbx::seed_seq_rd s;
   mt.seed(s);
````