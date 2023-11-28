
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>,
                 virtual protected Vector<Data> {

private:

  unsigned long int head = 0;
  unsigned long int tail = 0;

  static const unsigned short int INIT_SIZE = 10;
  static constexpr float FACTOR = 1.5;

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;

  // ...

public:

  // Default constructor
  QueueVec() {Init();}

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const LinearContainer<Data>&); // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec<Data>&);

  // Move constructor
  QueueVec(QueueVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~QueueVec();

  /* ************************************************************************ */

  // Copy assignment
  QueueVec& operator=(const QueueVec&);

  // Move assignment
  QueueVec& operator=(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec&) const noexcept;
  bool operator!=(const QueueVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const override; // Override Queue member (constant version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) noexcept override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) noexcept override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  bool Empty() const noexcept override; // Override Container member

  unsigned long int Size() const noexcept override; // Override Container member

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  void Expand() noexcept;
  void Reduce();
  void Init();

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
