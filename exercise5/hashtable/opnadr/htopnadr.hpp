
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> {

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::INIT_TABLE_SIZE;
  using HashTable<Data>::tablesize;

  unsigned long int dirtysize = 0;
  static constexpr float FACTOR = 2;
  
  Vector<Data> table;
  Vector<char> flags;
  // '0' empty cell
  // '~' special cell (is empty for Insert and full for Find)
  // '1' full cell

public:

  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(unsigned long int); // A hash table of a given size
  HashTableOpnAdr(const LinearContainer<Data>&); // A hash table obtained from a LinearContainer
  HashTableOpnAdr(unsigned long int, const LinearContainer<Data>&); // A hash table of a given size obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data>& other) {*this = other;}

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data>&& other) noexcept {*this = std::move(other);}

  /* ************************************************************************ */

  // Destructor
  ~HashTableOpnAdr() {
    table.Clear();
    flags.Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr<Data>& operator=(const HashTableOpnAdr<Data>&);

  // Move assignment
  HashTableOpnAdr<Data>& operator=(HashTableOpnAdr<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr<Data>& other) const noexcept {return HashTable<Data>::operator==(other);}
  bool operator!=(const HashTableOpnAdr<Data>& other) const noexcept {return HashTable<Data>::operator!=(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from HashTable)

  void Resize(unsigned long) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  void Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  void Insert(Data&&) noexcept override; // Override DictionaryContainer member (Move of the value)
  void Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;
  void Map(MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  using Container::Empty;
  void Clear() override; // Override Container member

public:

  // Auxiliary member functions

  void InitFlags();
  void Init(unsigned long newsize=INIT_TABLE_SIZE);

  using HashTable<Data>::HashKey;
  unsigned long HashKey(const Data&, unsigned long) const noexcept;

  unsigned long* Find(const Data&) const noexcept;
  unsigned long* FindEmpty(const Data&) const noexcept;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
