
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue : virtual public Container {

public:

  // Destructor
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  Queue& operator=(const Queue&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Queue& operator=(Queue&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Queue&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Queue&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& Head() const = 0;
  virtual Data& Head() = 0;
  virtual void Dequeue() = 0;
  virtual Data HeadNDequeue() = 0;
  virtual void Enqueue(const Data&) noexcept = 0;
  virtual void Enqueue(Data&&) noexcept = 0;

};

/* ************************************************************************** */

}

#endif
