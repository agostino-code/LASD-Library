
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

//come rappresentare gli spazi vuoti dentro il vettore?
//o decido un valore che corrisponde al vuoto
//o creo un vettore di puntatori e metto a nullptr quelli vuoti
//se faccio così devo ricordarmi che la delete[] del vettore non basta
//devo fare io prima la delete di tutti i puntatori salvati nell'array
template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data> {

protected:

  using BinaryTree<Data>::size;

  // ...

  //dentro BinaryTreeVec, il nodo è una strattura che mi complica solo la vita
  //Però sono costretto ad usarla perchè sennò non posso ereditare da BinaryTree, che palle
  //vediamo di rendere questo nodo quanto più incompleto possibile allora
  //ci metto solo l'essenziale, poi tutta l'implementazione vera la voglio gestire solo dentro l'albero
  struct NodeVec : public BinaryTree<Data>::Node {

  private:

    //l'elemento
    //l'indice
    //un puntatore al vettore (????)
    //è solo un modo di implementarlo, non è detto che sia la migliore
    Vector<NodeVec*>* elements = nullptr;
    Data key;
    unsigned long int index = 0;

    // Data key;
    // NodeVec* left = nullptr;
    // NodeVec* right = nullptr;

  public:

    //friend class BinaryTreeVec<Data>; OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

    //Specific constructors
    //NodeVec(const Vector<Data>& vec, unsigned long int index) : elements(&vec), this->index(index) {}
    //NodeVec(const Data& key) : this->key(key) {}
    NodeVec(Vector<NodeVec*>& vec, const Data& key, unsigned long int index) : elements(&vec), key(key), index(index) {}

    //Copy constrcutor
    //NodeVec(const NodeVec& other) : index(other.index), elements(other.elements) {}
    //NodeVec(const NodeVec& other) : key(other.key) {}
    //NodeVec(const NodeVec& other) : elements(other.elements), key(other.key), index(other.index) {}
    // NodeVec(const NodeVec&) = delete;
    // NodeVec(NodeVec&&) noexcept = delete;

    //Copy assignment
    // NodeVec& operator=(const NodeVec& other) {
    //   if (this != &other) {
    //     index = other.index;
    //     elements = other.elements;
    //   }
    //   return *this;
    // }
    // NodeVec& operator=(const NodeVec& other) {
    //   if (this != &other)
    //     key = other.key;
    //   return *this;
    // }
    // NodeVec& operator=(const NodeVec& other) {
    //   if (this != &other) {
    //     elements = other.elements;
    //     key = other.key;
    //     index = other.index;
    //   }
    //   return *this;
    // }
    // Copy assignment
    NodeVec& operator=(const NodeVec&) = delete;

    // Move assignment
    NodeVec& operator=(NodeVec&&) noexcept = delete;

    //Destructor
    ~NodeVec() = default;

    /* ********************************************************************** */

    // Specific member functions

    Data& Element() noexcept override {return key;}
    const Data& Element() const noexcept override {return key;}

    //SE L'OVERRIDE DI LEFT E RIGHT NON FUNZIONA ALLORA TOGLILO E DECOMMENTA QUESTA PARTE
    //bool HasLeftChild() const noexcept override {return LeftChild()!=nullptr;}
    //bool HasRightChild() const noexcept override {return RightChild()!=nullptr;}

    bool HasLeftChild() const noexcept override {
      return (2*(index+1) - 1)<elements->Size() && (*elements)[2*(index+1) - 1]!=nullptr;
    }

    bool HasRightChild() const noexcept override {
      return (2*(index+1))<elements->Size() && (*elements)[2*(index+1)]!=nullptr;
    }

    // NodeVec* LeftChild() override {
    //   unsigned long int left = 2*(index+1) - 1;
    //   if (left < elements->Size()) {
    //     if (elements[index] == nullptr)
    //       return nullptr;
    //     else
    //       return new NodeVec{*elements, left};
    //   }
    //   else
    //     return nullptr;
    // }

    // NodeVec* RightChild() override {
    //   unsigned long int right = 2*(index+1);
    //   if (right < elements->Size()) {
    //     if (elements[index] == nullptr)
    //       return nullptr;
    //     else
    //       return new NodeVec{*elements, right};
    //   }
    //   else
    //     return nullptr;

    NodeVec& LeftChild() override {
      if(!HasLeftChild())
        throw std::out_of_range("Called the Left Child of a Node with no Left Child");
      return *(*elements)[2*(index+1) - 1];
    }

    NodeVec& RightChild() override {
      if(!HasRightChild())
        throw std::out_of_range("Called the Right Child of a Node with no Right Child");
      return *(*elements)[2*(index+1)];
    }

  };

private:

  Vector<NodeVec*> elements; //Where each empty cell is represented by nullptr
  //NodeVec* root;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  //banale
  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeVec() {Clear();}

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec<Data>& operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  BinaryTreeVec<Data>& operator=(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // bool operator==(const BinaryTreeVec<Data>&) const noexcept;
  // bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  using BinaryTree<Data>::Empty;
  using BinaryTree<Data>::Size;
  void Clear() override; // Override Container member

  /* ************************************************************************ */

  //da implementare perchè qui l'ampiezza è molto più efficiente, non serve neanche la coda

  // Specific member functions (inherited from BreadthMappableContainer)

  using typename BinaryTree<Data>::MapFunctor;
  void MapBreadth(MapFunctor, void*) override; // Override BreadthMappableContainer member

  // Specific member functions (inherited from BreadthFoldableContainer)

  using typename BinaryTree<Data>::FoldFunctor;
  void FoldBreadth(FoldFunctor, const void*, void*) const override; // Override BreadthFoldableContainer member

  //e tutte le altre fold e map? non si possono rendere più efficienti?

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
