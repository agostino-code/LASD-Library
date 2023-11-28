
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../iterator/iterator.hpp"

#include "../stack/lst/stacklst.hpp"
#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree :  virtual public PreOrderMappableContainer<Data>,
                    virtual public PostOrderMappableContainer<Data>,
                    virtual public InOrderMappableContainer<Data>,
                    virtual public BreadthMappableContainer<Data>,
                    virtual public PreOrderFoldableContainer<Data>,
                    virtual public PostOrderFoldableContainer<Data>,
                    virtual public InOrderFoldableContainer<Data>,
                    virtual public BreadthFoldableContainer<Data> {

private:

  // ...

protected:

  // ...

public:

  struct Node {

  private:

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    Node& operator=(Node&&) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ********************************************************************** */
    // Comparison operators
    bool operator==(const Node&) const noexcept = delete; // Comparison of abstract types is possible, but should not be visible.
    bool operator!=(const Node&) const noexcept = delete; // Comparison of abstract types is possible, but should not be visible.

    /* ********************************************************************** */

    // Specific member functions

    virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)
    virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    bool IsLeaf() const noexcept {return !HasLeftChild() && !HasRightChild();} // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual Node& LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual Node& RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree<Data>& operator=(const BinaryTree<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BinaryTree<Data>& operator=(BinaryTree<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  using Container::Empty;
  using Container::Size;

  /* ************************************************************************ */

  //tutte le map e le fold sono implementabili già qui

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;
    void Map(MapFunctor fun, void* par) override{
        if (!Empty())
        MapPreOrder(fun,par,&Root());
    }; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    using typename FoldableContainer<Data>::FoldFunctor;

    void Fold(FoldFunctor fun, const void* par, void* acc) const override{
        if (!Empty())
        FoldPreOrder(fun,par,acc,&Root());
    }; // Override FoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderMappableContainer)

    void MapPreOrder(MapFunctor fun, void* par) override{
        if (!Empty())
        MapPreOrder(fun,par,&Root());
    }; // Override PreOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderFoldableContainer)

    void FoldPreOrder(FoldFunctor fun, const void* par, void* acc) const override{
        if (!Empty())
        FoldPreOrder(fun,par,acc,&Root());
    }; // Override PreOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderMappableContainer)

    void MapPostOrder(MapFunctor fun, void* par) override{
        if (!Empty())
        MapPostOrder(fun,par,&Root());
    }; // Override PostOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderFoldableContainer)

    void FoldPostOrder(FoldFunctor fun, const void* par, void* acc) const override{
        if (!Empty())
        FoldPostOrder(fun,par,acc,&Root());
    } // Override PostOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from InOrderMappableContainer)

    void MapInOrder(MapFunctor fun, void* par) override{
        if (!Empty())
        MapInOrder(fun,par,&Root());
    }; // Override InOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from InOrderFoldableContainer)

    void FoldInOrder(FoldFunctor fun, const void* par, void* acc) const override{
        if (!Empty())
        FoldInOrder(fun,par,acc,&Root());
    } // Override InOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthMappableContainer)

    void MapBreadth(MapFunctor fun, void* par) override;// Override BreadthMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthFoldableContainer)

    void FoldBreadth(FoldFunctor fun, const void* par, void* acc) const override;// Override BreadthFoldableContainer member

protected:

    // Auxiliary member functions (for PreOrderMappableContainer)

    void MapPreOrder(MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PreOrderFoldableContainer)

    void FoldPreOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PostOrderMappableContainer)

    void MapPostOrder(MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PostOrderFoldableContainer)

    void FoldPostOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderMappableContainer)

    void MapInOrder(MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderFoldableContainer)

    void FoldInOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for BreadthMappableContainer)

//    void MapBreadth(MapFunctor, void*, Node*); // Accessory function executing from one node of the tree
//
//  /* ************************************************************************ */
//
//  // Auxiliary member functions (for BreadthFoldableContainer)
//
//    void FoldBreadth(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

    };

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>,
        virtual public ResettableIterator<Data>{

private:

  // ...
  const BinaryTree<Data>* T = nullptr;
  unsigned long int index = 0;
  typename BinaryTree<Data>::Node* current = nullptr;
  StackLst<typename BinaryTree<Data>::Node*> stack;

protected:

  // ...

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator&);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() {stack.Clear();}

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator& operator=(const BTPreOrderIterator&);

  // Move assignment
  BTPreOrderIterator& operator=(BTPreOrderIterator&&) noexcept;

  /* ************************************************************************ */

  //Iteratore nello stesso stato.
  // Comparison operators
  bool operator==(const BTPreOrderIterator&) const noexcept;
  bool operator!=(const BTPreOrderIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override {return current==nullptr;}; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  void operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data> {

private:

  const BinaryTree<Data>* T = nullptr;
  unsigned long int index = 0;
  typename BinaryTree<Data>::Node* current = nullptr;
  StackLst<typename BinaryTree<Data>::Node*> stack;

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator<Data>&);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() {stack.Clear();}

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator<Data>& operator=(const BTPostOrderIterator<Data>&);

  // Move assignment
  BTPostOrderIterator<Data>& operator=(BTPostOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTPostOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override {return current==nullptr;} // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  void operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

protected:

  // Auxiliary function
  void LeftEndOf(typename BinaryTree<Data>::Node&) noexcept;

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data> {

private:

  // ...
  const BinaryTree<Data>* T = nullptr;
  unsigned long int index = 0;
  typename BinaryTree<Data>::Node* current = nullptr;
  typename BinaryTree<Data>::Node* out = nullptr;
  StackLst<typename BinaryTree<Data>::Node*> stack;


protected:

  // ...

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator&);

  // Move constructor
  BTInOrderIterator(BTInOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator(){stack.Clear();};

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator& operator=(const BTInOrderIterator&);

  // Move assignment
  BTInOrderIterator& operator=(BTInOrderIterator &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator&) const noexcept;
  bool operator!=(const BTInOrderIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override{return current==nullptr;}; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  void operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

protected:

    // Auxiliary function
    void LeftMove(typename BinaryTree<Data>::Node&) noexcept;

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data> {

private:

  const BinaryTree<Data>* T = nullptr;
  unsigned long int index = 0;
  typename BinaryTree<Data>::Node* current = nullptr;
  //current non può essere const perché operator* cambia il valore di current->Element()
  QueueLst<typename BinaryTree<Data>::Node*> queue;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator<Data>&);

  // Move constructor
  BTBreadthIterator(BTBreadthIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthIterator() {queue.Clear();}

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator<Data>& operator=(const BTBreadthIterator<Data>&);

  // Move assignment
  BTBreadthIterator<Data>& operator=(BTBreadthIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator<Data>&) const noexcept;
  bool operator!=(const BTBreadthIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override {return current==nullptr;} // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  void operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

protected:

  //Auxiliary function
  void EnqueueChildren() noexcept;

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
