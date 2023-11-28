#include <random>
#include <cstdlib>
#include "htopnadr.hpp"
namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() {
    Init();
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long newsize) {
    Init(newsize);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data> & lc) {
    Init();
    DictionaryContainer<Data>::Insert(lc);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long newsize, const LinearContainer<Data>& lc) {
    Init(newsize);
    DictionaryContainer<Data>::Insert(lc);
}

/* ************************************************************************** */

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& other) {
    if(this != &other) {
        HashTable<Data>::operator=(other);
        dirtysize = other.dirtysize;
        table = other.table;
        flags = other.flags;
    }
    return *this;
}

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& other) noexcept {
    if(this != &other) {
        HashTable<Data>::operator=(other);
        std::swap(dirtysize, other.dirtysize);
        table = std::move(other.table);
        flags = std::move(other.flags);
    }
    return *this;
}

/* ************************************************************************** */

template <typename Data>
void AuxMapResizeOpnAdr(const Data& dat, const void* val) noexcept{
    ((HashTableOpnAdr<Data>*) val)->Insert(std::move(dat));
}

template <typename Data>
void HashTableOpnAdr<Data>::Resize(unsigned long newsize) {
    HashTableOpnAdr other(newsize);
    Map(&AuxMapResizeOpnAdr<Data>, &other);
    *this = std::move(other);
}

/* ************************************************************************** */

template <typename Data>
void HashTableOpnAdr<Data>::Insert(const Data& dat) {
    if(tablesize == 0)
        Init();
    unsigned long* index = FindEmpty(dat);
    if(index != nullptr) {
        table.operator[](*index) = dat;
        flags.operator[](*index) = '1';
        size++;
        dirtysize++;
        if(size > tablesize/FACTOR)
            Resize(tablesize*FACTOR);
        delete index;
    }
}

template <typename Data>
void HashTableOpnAdr<Data>::Insert(Data&& dat) noexcept {
    if(tablesize == 0)
        Init();
    unsigned long* index = FindEmpty(dat);
    if(index != nullptr) {
        table.operator[](*index) = std::move(dat);
        flags.operator[](*index) = '1';
        size++;
        dirtysize++;
        if(size > tablesize/FACTOR)
            Resize(tablesize*FACTOR);
        delete index;
    }
}

template <typename Data>
void HashTableOpnAdr<Data>::Remove(const Data& dat) {
    unsigned long* index = Find(dat);
    if(index != nullptr) {
        flags.operator[](*index) = '~';
        size--;
        if(dirtysize > size*FACTOR)
            Resize(tablesize); //ReHash
        delete index;
    }
}

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& dat) const noexcept {
    return Find(dat) != nullptr;
}

/* ************************************************************************** */

template <typename Data>
void HashTableOpnAdr<Data>::Map(MapFunctor method, void* par) {
    for(unsigned long int i=0; i<tablesize; i++)
        if(flags.operator[](i) == '1')
            method(table.operator[](i), par);
}

template <typename Data>
void HashTableOpnAdr<Data>::Fold(FoldFunctor method, const void* par, void* acc) const {
    for(unsigned long int i=0; i<tablesize; i++)
        if(flags.operator[](i) == '1')
            method(table.operator[](i), par, acc);
}

/* ************************************************************************** */

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    InitFlags();
}

/* ************************************************************************** */

template <typename Data>
void HashTableOpnAdr<Data>::InitFlags() {
    size = 0;
    dirtysize = 0;
    for(unsigned long i=0; i<tablesize; i++)
        flags.operator[](i) = '0';
}

template <typename Data>
void HashTableOpnAdr<Data>::Init(unsigned long int newsize) {
    tablesize = newsize;
    table.Resize(tablesize);
    flags.Resize(tablesize);
    InitFlags();
}

template <typename Data>
unsigned long int HashTableOpnAdr<Data>::HashKey(const Data& dat, unsigned long int i) const noexcept {
    std::srand(i);
    return (HashKey(dat) + (i==0 ? 0 : std::rand()))%tablesize;
}

template <typename Data>
unsigned long* HashTableOpnAdr<Data>::Find(const Data& dat) const noexcept {
    if(Empty())
        return nullptr;
    unsigned long i=0;
    while( !(table.operator[](HashKey(dat, i)) == dat && flags.operator[](HashKey(dat, i)) == '1') ) {
        if(flags.operator[](HashKey(dat, i)) == '0')
            return nullptr;
        i++;
    }
    return new unsigned long (HashKey(dat, i));
}

template <typename Data>
unsigned long* HashTableOpnAdr<Data>::FindEmpty(const Data& dat) const noexcept {
    unsigned long i=0;
    while(flags.operator[](HashKey(dat, i)) == '1') {
        if(table.operator[](HashKey(dat, i)) == dat)
            return nullptr;
        i++;
    }
    unsigned long int j=i;
    while(flags.operator[](HashKey(dat, j)) != '0') {
        if(table.operator[](HashKey(dat, j)) == dat && flags.operator[](HashKey(dat, j)) == '1')
            return nullptr;
        j++;
    }
    return new unsigned long (HashKey(dat, i));
}

/* ************************************************************************** */

}
