#ifndef TBX_SEED_RANDOMLY_CPP14_H
#define TBX_SEED_RANDOMLY_CPP14_H
#include <array>             // array, cbegin, cend
#include <cstddef>           // size_t
#include <cstdint>           // uint_least32_t
#include <initializer_list>  // initializer_list
#include <iterator>          // iterator_traits
#include <random>            // random_device
#include <type_traits>       // is_integral_v, is_unsigned_v
namespace tbx
{
    class seed_seq_rd
    {
        // This class mimics the interface of std::seed_seq, but 
        // uses std::random_device to generate seeds. 
        //
        // It performs only minimal checking of its template arguments. 
        // Other than that, it complies with all requirements of a seed 
        // sequence as defined in the C++ standard.
    public:
        using result_type = typename std::random_device::result_type;
    private:
        // No matter what ctor you use, all you get is this array 
        // with one element. Best practice, therefore, is to use the 
        // default ctor.
        enum : std::size_t { zero, one };
        std::array<result_type, one> seeds{};
    public:
        seed_seq_rd() noexcept
            = default;
        template< typename InputIt >
        seed_seq_rd(InputIt begin, InputIt end) {
            using value_type = typename std::iterator_traits<InputIt>::value_type;
            static_assert(std::is_integral_v<value_type>, "");
        }
        template< typename T >
        seed_seq_rd(std::initializer_list<T> li) {
            using value_type = typename std::initializer_list<T>::value_type;
            static_assert(std::is_integral_v<value_type>, "");
        }
        seed_seq_rd(seed_seq_rd const&)
            = delete;
        seed_seq_rd& operator=(seed_seq_rd const&)
            = delete;
        template< typename RandomIt >
        void generate(RandomIt begin, RandomIt end) {
            using value_type = typename std::iterator_traits<RandomIt>::value_type;
            static_assert(std::is_integral_v<value_type>, "");
            static_assert(std::is_unsigned_v<value_type>, "");
            static_assert(sizeof(value_type) >= sizeof(std::uint_least32_t), "");
            std::random_device rd;
            while (begin != end)
                *begin++ = rd();
        }
        template <typename OutputIt>
        void param(OutputIt dest) const {
            *dest = seeds.front();
        }
        auto size() const noexcept {
            return seeds.size();
        }
    };

    template <typename RandomEngine>
    void seed_randomly(RandomEngine& e) {
        tbx::seed_seq_rd s;
        e.seed(s);
    }
}
#endif  // TBX_SEED_RANDOMLY_CPP14_H
// end file: tbx.seed_randomly.cpp14.h
