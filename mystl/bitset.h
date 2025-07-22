#pragma once

#include "array.h"
#include "string.h"
#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace mystl
{
template<std::size_t N>
class bitset
{
    static constexpr std::size_t BITS_PER_WORD  = sizeof(std::size_t) * 8;
    static constexpr std::size_t WORD_COUNT     = (N + BITS_PER_WORD - 1) / BITS_PER_WORD;
    static constexpr std::size_t LAST_WORD_BITS = N % BITS_PER_WORD;

    static constexpr std::size_t word_index(const std::size_t bit)
    {
        return bit / BITS_PER_WORD;
    }

    static constexpr std::size_t bit_index(const std::size_t bit)
    {
        return bit % BITS_PER_WORD;
    }

    void modify_by_idx(const bool        toOne,
                       const std::size_t idx)
    {
        const std::size_t wi = mystl::bitset<N>::word_index(idx);
        const std::size_t bi = mystl::bitset<N>::bit_index(idx);

        toOne == true
            ? this->data[wi] |= (1ULL << bi)
            : this->data[wi] &= ~(1ULL << bi);
    }

    void clear_unused_bits()
    {
        if (LAST_WORD_BITS != 0)
        {
            data[WORD_COUNT - 1] &= (1ULL << LAST_WORD_BITS) - 1;
        }
    }

    mystl::array<std::size_t, WORD_COUNT> data;

public:
    bitset()
    {
    }

    bitset(const unsigned long long val)
    {
        for (std::size_t idx = 0; idx < WORD_COUNT; ++idx)
        {
            this->data[idx] = 0;
        }

        this->data[0] = val;
    }

    bitset(const mystl::string& str,
           const std::size_t    pos  = 0,
           const std::size_t    n    = mystl::string::npos,
           const char           zero = '0',
           const char           one  = '1')
    {
        if (pos > str.size())
        {
            throw std::out_of_range("bitset constructor: pos out of range");
        }

        std::size_t bitsCnt = 0;
        if (n == mystl::string::npos)
        {
            bitsCnt = str.size() - pos;
        }
        else if (pos + n > str.size())
        {
            throw std::out_of_range("bitset constructor: pos + n out of range");
        }
        else
        {
            bitsCnt = n;
        }

        bitsCnt = std::min(bitsCnt, N);

        for (std::size_t idx = 0; idx < WORD_COUNT; ++idx)
        {
            this->data[idx] = 0;
        }

        for (std::size_t idx = 0; idx < bitsCnt; ++idx)
        {
            if (str[idx + pos] == one)
            {
                this->modify_by_idx(true, bitsCnt - idx - 1);
            }
            else if (str[idx + pos] != zero)
            {
                throw std::invalid_argument("bitset string contains invalid character");
            }
        }
    }

    void set()
    {
        for (std::size_t idx = 0; idx < WORD_COUNT; ++idx)
        {
            this->data[idx] = static_cast<std::size_t>(-1);
        }
        this->clear_unused_bits();
    }

    void set(const std::size_t idx)
    {
        this->modify_by_idx(true, idx);
    }

    void reset()
    {
        for (std::size_t idx = 0; idx < WORD_COUNT; ++idx)
        {
            this->data[idx] = 0;
        }
    }

    void reset(const std::size_t idx)
    {
        this->modify_by_idx(false, idx);
    }

    void flip()
    {
        for (std::size_t idx = 0; idx < WORD_COUNT; ++idx)
        {
            this->data[idx] = ~this->data[idx];
        }
        this->clear_unused_bits();
    }

    void flip(const std::size_t idx)
    {
        this->modify_by_idx(!this->test(idx), idx);
    }

    bool test(const std::size_t idx) const
    {
        const std::size_t wi = mystl::bitset<N>::word_index(idx);
        const std::size_t bi = mystl::bitset<N>::bit_index(idx);

        return (this->data[wi] & (1ULL << bi)) != 0;
    }

    bool any() const
    {
        for (std::size_t idx = 0; idx < WORD_COUNT; ++idx)
        {
            if (this->data[idx] != 0)
            {
                return true;
            }
        }

        return false;
    }

    bool none() const
    {
        return !mystl::bitset<N>::any();
    }

    bool all() const
    {
        constexpr std::size_t FULL_MASK = ~std::size_t { 0 };
        for (std::size_t idx = 0; idx < WORD_COUNT - 1; ++idx)
        {
            if (this->data[idx] != FULL_MASK)
            {
                return false;
            }
        }

        if (LAST_WORD_BITS == 0)
        {
            return this->data[WORD_COUNT - 1] == FULL_MASK;
        }

        return this->data[WORD_COUNT - 1] == FULL_MASK >> (BITS_PER_WORD - LAST_WORD_BITS);
    }

    bool operator[](const std::size_t idx) const
    {
        return mystl::bitset<N>::test(idx);
    }

    bool operator==(const mystl::bitset<N>& other) const
    {
        return !(*this != other);
    }

    bool operator!=(const mystl::bitset<N>& other) const
    {
        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            if (this->data[i] != other.data[i])
            {
                return true;
            }
        }

        return false;
    }

    std::size_t count() const
    {
        std::size_t cnt = 0;
        for (std::size_t idx = 0; idx < WORD_COUNT; ++idx)
        {
            std::size_t x = this->data[idx];
            while (x != 0)
            {
                x &= (x - 1);
                cnt++;
            }
        }

        return cnt;
    }

    std::size_t size() const
    {
        return N;
    }

    unsigned long long to_uulong() const
    {
        if (N > 64)
        {
            for (std::size_t idx = 1; idx < WORD_COUNT; ++idx)
            {
                if (this->data[idx] != 0)
                {
                    throw std::overflow_error("bitset too large for to_uulong()");
                }
            }
        }

        return static_cast<unsigned long long>(this->data[0]);
    }

    mystl::string to_string() const
    {
        mystl::string res;
        res.reserve(N);
        for (std::size_t idx = 0; idx < N; ++idx)
        {
            mystl::bitset<N>::test(N - idx - 1) == true
                ? res.push_back('1')
                : res.push_back('0');
        }

        return res;
    }

    mystl::bitset<N> operator&(const mystl::bitset<N>& other) const
    {
        mystl::bitset<N> res;
        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            res.data[i] = this->data[i] & other.data[i];
        }

        return res;
    }

    mystl::bitset<N> operator|(const mystl::bitset<N>& other) const
    {
        mystl::bitset<N> res;
        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            res.data[i] = this->data[i] | other.data[i];
        }

        return res;
    }

    mystl::bitset<N> operator^(const mystl::bitset<N>& other) const
    {
        mystl::bitset<N> res;
        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            res.data[i] = this->data[i] ^ other.data[i];
        }

        return res;
    }

    mystl::bitset<N> operator~() const
    {
        mystl::bitset<N> res;
        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            res.data[i] = ~this->data[i];
        }
        res.clear_unused_bits();

        return res;
    }

    mystl::bitset<N> operator<<(const std::size_t bitsNum) const
    {
        mystl::bitset<N> res;

        std::size_t curVal = 0;
        std::size_t preVal = 0;

        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            curVal      = this->data[i] >> (BITS_PER_WORD - bitsNum);
            res.data[i] = this->data[i] << bitsNum;
            res.data[i] |= preVal;
            preVal = curVal;
        }
        res.clear_unused_bits();

        return res;
    }

    mystl::bitset<N> operator>>(const std::size_t bitsNum) const
    {
        mystl::bitset<N> res;

        std::size_t curVal = 0;
        std::size_t preVal = 0;

        for (std::size_t i = WORD_COUNT - 1; i > 0; --i)
        {
            curVal      = this->data[i] | ((1 << bitsNum) - 1);
            res.data[i] = this->data[i] >> bitsNum;
            res.data[i] |= preVal << (BITS_PER_WORD - bitsNum);
            preVal = curVal;
        }

        res.data[0] = this->data[0] >> bitsNum;
        res.data[0] |= preVal << (BITS_PER_WORD - bitsNum);

        res.clear_unused_bits();

        return res;
    }
};
} // namespace mystl