
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec :virtual public Stack<Data>,
                virtual protected Vector<Data>{
                  // Must extend Stack<Data>,
                  //             Vector<Data>

private:

        unsigned long tail = 0;

        static const unsigned short int INIT_SIZE = 10;
        static constexpr float FACTOR = 1.5;

protected:

        using Vector<Data>::size;
        using Vector<Data>::Elements;


  // ...

public:

  // Default constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const LinearContainer<Data>&); // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data>&);

  // Move constructor
  StackVec(StackVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec();

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec&);

  // Move assignment
  StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec&) const noexcept;
  bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

    const Data& Top() const override; // Override Stack member (constant version; must throw std::length_error when empty)
    Data& Top() override; // Override Stack member (must throw std::length_error when empty)
    void Pop() override; // Override Stack member (must throw std::length_error when empty)
    Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
    void Push(const Data&) noexcept override; // Override Stack member (copy of the value)
    void Push(Data&&) noexcept override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  bool Empty() const noexcept override; // Override Container member

  unsigned long Size() const noexcept override; // Override Container member

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  void Expand() ;
  void Reduce() ;

};


/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
