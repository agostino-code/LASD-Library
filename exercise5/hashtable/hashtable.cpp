#include <random>
#include <string>
#include "hashtable.hpp"

namespace lasd {

/* ************************************************************************** */

    template <>
    class Hash<int> {
    public:
        unsigned long int operator()(const int& k) const noexcept {
            return k*k;
        }
    };

    template <>
    class Hash<double> {
    public:
        unsigned long int operator()(const double& k) const noexcept {
            long int integer_part = std::floor(k);
            long int fractional_part = pow(2, 24) * (k - integer_part);
            return integer_part*fractional_part;
        }
    };

    template <>
    class Hash<std::string> {
    public:
        unsigned long int operator()(const std::string& k) const noexcept {
            unsigned long int hash = 6359;
            for(unsigned long int i=0; i << k.length(); i++)
                hash = (hash << 5) + k[i];
            return hash;
        }
    };

/* ************************************************************************** */

    template<typename Data>
    HashTable<Data>::HashTable() {
        std::default_random_engine gen(std::random_device{}());
        std::uniform_int_distribution<unsigned long> dist(0, prime);
        a=dist(gen);
        b= 1 + dist(gen);
    }

    template<typename Data>
    HashTable<Data> &HashTable<Data>::operator=(HashTable&& other) noexcept {
        if(this != &other) {
            std::swap(a, other.a);
            std::swap(b, other.b);
            std::swap(tablesize, other.tablesize);
            std::swap(size, other.size);
        }
        return *this;
    }

    template<typename Data>
    HashTable<Data> &HashTable<Data>::operator=(const HashTable& other) {
        if(this != &other) {
            a = other.a;
            b = other.b;
            tablesize=other.tablesize;
            size=other.size;
        }
        return *this;
    }

    template<typename Data>
    bool HashTable<Data>::operator==(const HashTable<Data>& other) const noexcept {
        bool ret = (size==other.size);
        if(!ret)
            return false;
        if(this != &other) {
            //checking if *this is a subset of other:
            Fold([] (const Data& k, const void* par, void* acc) {
                if(*static_cast<bool*>(acc) != false)
                    (*static_cast<bool*>(acc)) *= (static_cast<const HashTable<Data>*>(par)->Exists(k));
            }, &other, &ret);

            if(!ret)
                return false;

            //checking if other is a subset of *this:
            other.Fold([] (const Data& k, const void* par, void* acc) {
                if(*static_cast<bool*>(acc) != false)
                    (*static_cast<bool*>(acc)) *= (static_cast<const HashTable<Data>*>(par)->Exists(k));
            }, this, &ret);
        }
        return ret;
    }

    template<typename Data>
    unsigned long HashTable<Data>::HashKey(const Data& k) const noexcept {
        return ((a*hash(k)+b)%prime)%tablesize;
    }
/* ************************************************************************** */

}
