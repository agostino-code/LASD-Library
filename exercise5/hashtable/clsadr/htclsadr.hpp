
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data>{ // Must extend HashTable<Data>

private:

  // ...

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::tablesize;
  Vector<BST<Data>> table;
  // ...

public:

  // Default constructor
  HashTableClsAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const unsigned long); // A hash table of a given size
  HashTableClsAdr(const LinearContainer<Data>&); // A hash table obtained from a LinearContainer
  HashTableClsAdr(const unsigned long, const LinearContainer<Data>&); // A hash table of a given size obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr& other){*this=other;};

  // Move constructor
  HashTableClsAdr(HashTableClsAdr&& other) noexcept{*this=std::move(other);};

  /* ************************************************************************ */

  // Destructor
  ~HashTableClsAdr();

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr& operator=(const HashTableClsAdr&);

  // Move assignment
  HashTableClsAdr& operator=(HashTableClsAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr<Data>&) const noexcept;
  bool operator!=(const HashTableClsAdr<Data>& other) const noexcept{return HashTable<Data>::operator!=(other);};

  /* ************************************************************************ */

  // Specific member functions (inherited from HashTable)

  void Resize(unsigned long); // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  void Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  void Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  void Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */
  using typename MappableContainer<Data>::MapFunctor;
  using typename FoldableContainer<Data>::FoldFunctor;

  // Specific member functions (inherited from MappableContainer)

    void Map(MapFunctor,void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

    void Fold(FoldFunctor,const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
