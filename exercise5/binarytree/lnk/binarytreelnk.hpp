
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

//classica rappresentazione tramite puntatori
template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> {

protected:

  using BinaryTree<Data>::size;

  struct NodeLnk : virtual public BinaryTree<Data>::Node {

  protected:

  public:
      NodeLnk* leftnode= nullptr;
      NodeLnk* rightnode= nullptr;
      Data key;

      friend class BinaryTreeLnk<Data>;

    NodeLnk(const Data&);
    NodeLnk(Data&&);

    Data& Element() noexcept override {return key;}
    const Data& Element() const noexcept override {return key;}

    bool HasLeftChild() const noexcept override; // (concrete function should not throw exceptions)
    bool HasRightChild() const noexcept override; // (concrete function should not throw exceptions)

    NodeLnk& LeftChild() override; // (concrete function must throw std::out_of_range when not existent)
    NodeLnk& RightChild() override; // (concrete function must throw std::out_of_range when not existent)

    virtual ~NodeLnk() = default;

  };

private:


public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  //devi farlo per ampiezza, dovrà costruire un albero completo
  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
   BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
   BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk() {Clear();}

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  //in realtà non serve implementarli
  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  using Container::Empty;
  void Clear() override; // Override Container member

protected:

    NodeLnk* root= nullptr;

  //Auxiliary functions
  
  NodeLnk* CreateTree(NodeLnk*,unsigned long,const LinearContainer<Data>&);
  NodeLnk* CreateTree(NodeLnk*, NodeLnk*);
  void PostOrderDelete(NodeLnk* cur);

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
