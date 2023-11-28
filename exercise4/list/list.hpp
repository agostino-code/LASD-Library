
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class List : virtual public LinearContainer<Data>,
               virtual public PreOrderMappableContainer<Data>,
               virtual public PostOrderMappableContainer<Data>,
               virtual public PreOrderFoldableContainer<Data>,
               virtual public PostOrderFoldableContainer<Data>

  {

  private:
    // ...

  protected:
      using LinearContainer<Data>::size;
    struct Node {

        Data element;
        Node* next = nullptr;

        /* ********************************************************************** */

        // Specific constructors
        Node() = default;

        Node(const Data& dat) : element(dat){};
        Node(Data&&)noexcept;

        /* ********************************************************************** */

        // Copy constructor

        Node(const Node& nod) : element(nod.element){};

        // Move constructor

        Node(Node&& nod) noexcept;

        /* ********************************************************************** */

        // Destructor
        ~Node() = default;

        /* ********************************************************************** */

        // Comparison operators
        bool operator==(const Node&) const noexcept;
        bool operator!=(const Node&) const noexcept;

        /* ********************************************************************** */

        // Specific member functions

    };
    Node *head = nullptr;
    Node *tail = nullptr;

  public:
    // Default constructor
    List() = default;

    /* ************************************************************************ */

    // Specific constructor
    List(const LinearContainer<Data> &); // A list obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    List(const List &);

    // Move constructor
    List(List &&);

    /* ************************************************************************ */

    // Destructor
    virtual ~List();

    /* ************************************************************************ */

    // Copy assignment
    List &operator=(const List &);

    // Move assignment
    List &operator=(List &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const List &) const noexcept;
    bool operator!=(const List &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions

    void InsertAtFront(const Data &); // Copy of the value
    void InsertAtFront(Data &&);      // Move of the value
    void RemoveFromFront();           // (must throw std::length_error when empty)
    Data FrontNRemove();              // (must throw std::length_error when empty)

    void InsertAtBack(const Data &); // Copy of the value
    void InsertAtBack(Data &&);      // Move of the value

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    Data &Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
    Data &Back() const override;  // Override LinearContainer member (must throw std::length_error when empty)

    Data &operator[](unsigned long) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

      /* ************************************************************************ */

      // Specific member functions (inherited from MappableContainer)

      using typename MappableContainer<Data>::MapFunctor;

      void Map(MapFunctor fun, void * par) override{
          MapPreOrder(fun,par,head);
      } // Override MappableContainer member

      /* ************************************************************************ */

      // Specific member functions (inherited from PreOrderMappableContainer)

      void MapPreOrder(MapFunctor fun, void * par) override{
          MapPreOrder(fun,par,head);
      } // Override PreOrderMappableContainer member

      /* ************************************************************************ */

      // Specific member functions (inherited from PostOrderMappableContainer)

      void MapPostOrder(MapFunctor fun, void * par) override{
          MapPreOrder(fun,par,head);
      } // Override PostOrderMappableContainer member

      /* ************************************************************************ */

      // Specific member functions (inherited from FoldableContainer)

      using typename FoldableContainer<Data>::FoldFunctor;

      void Fold(FoldFunctor fun, const void * par, void * acc) const override{
          FoldPreOrder(fun,par,acc,head);
      } // Override FoldableContainer member

      /* ************************************************************************ */

      // Specific member functions (inherited from PreOrderFoldableContainer)

      void FoldPreOrder(FoldFunctor fun, const void * par, void * acc) const override{
          FoldPreOrder(fun, par,acc,head);
      } // Override FoldableContainer member

      /* ************************************************************************ */

      // Specific member functions (inherited from PostOrderFoldableContainer)

      void FoldPostOrder(FoldFunctor fun, const void * par, void * acc) const override{
          FoldPostOrder(fun, par,acc,head);
      } // Override FoldableContainer member

  protected:
      // Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)

      void MapPreOrder(MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards
      void MapPostOrder(MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards

      /* ************************************************************************ */

      // Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

      void FoldPreOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards
      void FoldPostOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards
  };

  /* ************************************************************************** */

}

#include "list.cpp"

#endif
