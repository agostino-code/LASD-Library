
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>,
                 virtual protected List<Data> {

protected:

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst<Data>& other) {List<Data>::operator=(other);}

  // Move constructor
  QueueLst(QueueLst<Data>&& other) noexcept {List<Data>::operator=(std::move(other));}

  /* ************************************************************************ */

  // Destructor
  ~QueueLst() {Clear();}

  /* ************************************************************************ */

  // Copy assignment
  QueueLst& operator=(const QueueLst&);

  // Move assignment
  QueueLst& operator=(QueueLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst& other) const noexcept {return List<Data>::operator==(other);}
  bool operator!=(const QueueLst& other) const noexcept {return List<Data>::operator!=(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  inline const Data& Head() const override; // Override Queue member (constant version; must throw std::length_error when empty)
  inline Data& Head() override; // Override Queue member (must throw std::length_error when empty)
  inline void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline void Enqueue(const Data&) noexcept override; // Override Queue member (copy of the value)
  inline void Enqueue(Data&&) noexcept override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  using List<Data>::Size;
  using List<Data>::Empty;
  using List<Data>::Clear;


};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
