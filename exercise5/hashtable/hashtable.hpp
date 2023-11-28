
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hash {

public:

  unsigned long operator()(const Data&) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
    class HashTable : virtual public DictionaryContainer<Data>,
                      virtual public  MappableContainer<Data>,
                      virtual public FoldableContainer<Data>{ // Must extend DictionaryContainer<Data>,
                  //             MappableContainer<Data>,
                  //             FoldableContainer<Data>

private:

  // ...

protected:

        using DictionaryContainer<Data>::size;
        static const unsigned long prime=1163;
        static const unsigned long INIT_TABLE_SIZE=127;

        unsigned long tablesize=INIT_TABLE_SIZE;
        unsigned long a;
        unsigned long b;
        Hash<Data> hash;

  // ...

  // Copy assignment
  HashTable& operator=(const HashTable&); // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept; // Move assignment of abstract types should not be possible.
public:

  HashTable();
  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */


  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable<Data>&) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const HashTable<Data>& other) const noexcept{return !(*this==other);}; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

        using MappableContainer<Data>::Map;
        using FoldableContainer<Data>::Fold;
  // Specific member function

  virtual void Resize(unsigned long) =0; // Resize the hashtable to a given size

protected:

  // Auxiliary member functions

  unsigned long HashKey(const Data&) const noexcept;
  //unsigned long HashKey(unsigned long) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
