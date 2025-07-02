#pragma once

#include "DS/Array.h"
#include "DS/String.h"
#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace dsa
{
template<std::size_t N>
class Bitset
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
        const std::size_t wi = dsa::Bitset<N>::word_index(idx);
        const std::size_t bi = dsa::Bitset<N>::bit_index(idx);

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

    dsa::Array<std::size_t, WORD_COUNT> data;

public:
    Bitset()
    {
    }

    Bitset(const unsigned long long val)
    {
        for (std::size_t idx = 0; idx < WORD_COUNT; ++idx)
        {
            this->data[idx] = 0;
        }

        this->data[0] = val;
    }

    Bitset(const dsa::String& str,
           const std::size_t  pos  = 0,
           const std::size_t  n    = dsa::String::npos,
           const char         zero = '0',
           const char         one  = '1')
    {
        if (pos > str.size())
        {
            throw std::out_of_range("Bitset constructor: pos out of range");
        }

        std::size_t bitsCnt = 0;
        if (n == dsa::String::npos)
        {
            bitsCnt = str.size() - pos;
        }
        else if (pos + n > str.size())
        {
            throw std::out_of_range("Bitset constructor: pos + n out of range");
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
                throw std::invalid_argument("Bitset string contains invalid character");
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
        const std::size_t wi = dsa::Bitset<N>::word_index(idx);
        const std::size_t bi = dsa::Bitset<N>::bit_index(idx);

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
        return !dsa::Bitset<N>::any();
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
        return dsa::Bitset<N>::test(idx);
    }

    bool operator==(const dsa::Bitset<N>& other) const
    {
        return !(*this != other);
    }

    bool operator!=(const dsa::Bitset<N>& other) const
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
                    throw std::overflow_error("Bitset too large for to_uulong()");
                }
            }
        }

        return static_cast<unsigned long long>(this->data[0]);
    }

    dsa::String to_string() const
    {
        dsa::String res;
        res.reserve(N);
        for (std::size_t idx = 0; idx < N; ++idx)
        {
            dsa::Bitset<N>::test(N - idx - 1) == true
                ? res.push_back('1')
                : res.push_back('0');
        }

        return res;
    }

    dsa::Bitset<N> operator&(const dsa::Bitset<N>& other) const
    {
        dsa::Bitset<N> res;
        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            res.data[i] = this->data[i] & other.data[i];
        }

        return res;
    }

    dsa::Bitset<N> operator|(const dsa::Bitset<N>& other) const
    {
        dsa::Bitset<N> res;
        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            res.data[i] = this->data[i] | other.data[i];
        }

        return res;
    }

    dsa::Bitset<N> operator^(const dsa::Bitset<N>& other) const
    {
        dsa::Bitset<N> res;
        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            res.data[i] = this->data[i] ^ other.data[i];
        }

        return res;
    }

    dsa::Bitset<N> operator~() const
    {
        dsa::Bitset<N> res;
        for (std::size_t i = 0; i < WORD_COUNT; ++i)
        {
            res.data[i] = ~this->data[i];
        }
        res.clear_unused_bits();

        return res;
    }

    dsa::Bitset<N> operator<<(const std::size_t bitsNum) const
    {
        dsa::Bitset<N> res;

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

    dsa::Bitset<N> operator>>(const std::size_t bitsNum) const
    {
        dsa::Bitset<N> res;

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
} // namespace dsa