
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <stdexcept>
#include <functional>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

    class Container {

    protected:

        unsigned long size= 0;

    public:
        // Destructor
        virtual ~Container() = default;

        /* ************************************************************************ */

        // Copy assignment
        Container& operator=(const Container&) = delete; // Copy assignment of abstract types should not be possible.

        // Move assignment
        Container& operator=(Container&&) noexcept = delete; // Move assignment of abstract types should not be possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const Container&) const noexcept = delete; // Comparison of abstract types might not be possible.
        bool operator!=(const Container&) const noexcept = delete; // Comparison of abstract types might not be possible.

        /* ************************************************************************ */

        // Specific member functions

        virtual bool Empty() const noexcept{
            return (size==0);
        }// (concrete function should not throw exceptions)

        virtual unsigned long Size() const noexcept{
            return size;
        } // (concrete function should not throw exceptions)

        virtual void Clear() = 0;

    };

/* ************************************************************************** */

    template <typename Data>
    class LinearContainer : virtual public Container{ // Must extend Container

    public:

        // Destructor
        ~LinearContainer() override = default;

        /* ************************************************************************ */

        // Copy assignment
        LinearContainer& operator=(const LinearContainer&) = delete; // Copy assignment of abstract types should not be possible.

        // Move assignment
        LinearContainer& operator=(LinearContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

        bool operator==(const LinearContainer&) const noexcept; // Comparison of abstract types is possible.
        bool operator!=(const LinearContainer&) const noexcept; // Comparison of abstract types is possible.

        virtual Data& Front() const; // (concrete function must throw std::length_error when empty)
        virtual Data& Back() const; // (concrete function must throw std::length_error when empty)

        virtual Data& operator[](unsigned long) const = 0; // (concrete function must throw std::out_of_range when out of range)

    };

/* ************************************************************************** */

    template <typename Data>
    class TestableContainer : virtual public Container{ // Must extend Container

    public:

        // Destructor
        ~TestableContainer() override = default;

        virtual bool Exists(const Data&) const noexcept = 0; // (concrete function should not throw exceptions)

    };

/* ************************************************************************** */

    template <typename Data>
    class MappableContainer : virtual public Container{ // Must extend Container

    public:

        // Destructor
        ~MappableContainer() override = default;

        typedef std::function<void(Data&, void*)> MapFunctor;

        virtual void Map(MapFunctor,void*) = 0;

    };

/* ************************************************************************** */

    template <typename Data>
    class FoldableContainer : virtual public TestableContainer<Data>{ // Must extend TestableContainer<Data>

    public:

        // Destructor
        virtual ~FoldableContainer() = default;

        typedef std::function<void(const Data&, const void*, void*)> FoldFunctor;

        virtual void Fold(FoldFunctor,const void*, void*) const = 0;
        // const void valore iniziale es somma 0 prodotto 1

        bool Exists(const Data&) const noexcept override; // Override TestableContainer member

    };

/* ************************************************************************** */

    template <typename Data>
    class PreOrderMappableContainer : virtual public MappableContainer<Data> { // Must extend MappableContainer<Data>

    public:

        // Destructor
        virtual ~PreOrderMappableContainer() = default;

        using typename MappableContainer<Data>::MapFunctor;

        virtual void MapPreOrder(MapFunctor, void*) = 0;

        void Map(MapFunctor, void*) override; // Override MappableContainer member

    };

/* ************************************************************************** */

    template <typename Data>
    class PreOrderFoldableContainer : virtual public FoldableContainer<Data> { // Must extend FoldableContainer<Data>

    private:

        // ...

    protected:

        // ...

    public:

        // Destructor
        virtual ~PreOrderFoldableContainer() = default;

        // Specific member functions

        using typename FoldableContainer<Data>::FoldFunctor;

        virtual void FoldPreOrder(FoldFunctor, const void*, void*) const = 0;

        /* ************************************************************************ */

        // Specific member functions (inherited from FoldableContainer)

        void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

    };

/* ************************************************************************** */

    template <typename Data>
    class PostOrderMappableContainer : virtual public MappableContainer<Data>{ // Must extend MappableContainer<Data>

    private:

        // ...

    protected:

        // ...

    public:

        // Destructor
        virtual ~PostOrderMappableContainer() = default;

        using typename MappableContainer<Data>::MapFunctor;

        virtual void MapPostOrder(MapFunctor, void*) = 0;

        /* ************************************************************************ */

        // Specific member functions (inherited from MappableContainer)

        void Map(MapFunctor, void*) override; // Override MappableContainer member

    };

/* ************************************************************************** */

    template <typename Data>
    class PostOrderFoldableContainer : virtual FoldableContainer<Data>{ // Must extend FoldableContainer<Data>

    private:

        // ...

    protected:

        // ...

    public:

        // Destructor
        virtual ~PostOrderFoldableContainer() = default;

        using typename FoldableContainer<Data>::FoldFunctor;

        virtual void FoldPostOrder(FoldFunctor, const void*, void*) const = 0;

        /* ************************************************************************ */

        // Specific member functions (inherited from FoldableContainer)

        void Fold(FoldFunctor,const void*, void*) const override; // Override FoldableContainer member

    };

    template <typename Data>
    class InOrderMappableContainer { // Must extend MappableContainer<Data>

    private:

      // ...

    protected:

      // ...

    public:

      // Destructor
      // ~InOrderMappableContainer() specifiers

      /* ************************************************************************ */

      // Copy assignment
      // type operator=(argument); // Copy assignment of abstract types should not be possible.

      // Move assignment
      // type operator=(argument); // Move assignment of abstract types should not be possible.

      /* ************************************************************************ */

      // Comparison operators
      // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
      // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

      /* ************************************************************************ */

      // Specific member functions

      // using typename MappableContainer<Data>::MapFunctor;

      // type MapInOrder(arguments) specifiers;

      /* ************************************************************************ */

      // Specific member functions (inherited from MappableContainer)

      // type Map(argument) specifiers; // Override MappableContainer member

    };

    /* ************************************************************************** */

    template <typename Data>
    class InOrderFoldableContainer { // Must extend FoldableContainer<Data>

    private:

      // ...

    protected:

      // ...

    public:

      // Destructor
      // ~InOrderFoldableContainer() specifiers

      /* ************************************************************************ */

      // Copy assignment
      // type operator=(argument); // Copy assignment of abstract types should not be possible.

      // Move assignment
      // type operator=(argument); // Move assignment of abstract types should not be possible.

      /* ************************************************************************ */

      // Comparison operators
      // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
      // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

      /* ************************************************************************ */

      // Specific member functions

      // using typename MappableContainer<Data>::MapFunctor;

      // type FoldInOrder(arguments) specifiers;

      /* ************************************************************************ */

      // Specific member functions (inherited from FoldableContainer)

      // type Fold(argument) specifiers; // Override FoldableContainer member

    };

    /* ************************************************************************** */

    template <typename Data>
    class BreadthMappableContainer { // Must extend MappableContainer<Data>

    private:

      // ...

    protected:

      // ...

    public:

      // Destructor
      // ~BreadthMappableContainer() specifiers

      /* ************************************************************************ */

      // Copy assignment
      // type operator=(argument); // Copy assignment of abstract types should not be possible.

      // Move assignment
      // type operator=(argument); // Move assignment of abstract types should not be possible.

      /* ************************************************************************ */

      // Comparison operators
      // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
      // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

      /* ************************************************************************ */

      // Specific member functions

      // using typename MappableContainer<Data>::MapFunctor;

      // type MapBreadth(arguments) specifiers;

      /* ************************************************************************ */

      // Specific member functions (inherited from MappableContainer)

      // type Map(argument) specifiers; // Override MappableContainer member

    };

    /* ************************************************************************** */

    template <typename Data>
    class BreadthFoldableContainer { // Must extend FoldableContainer<Data>

    private:

      // ...

    protected:

      // ...

    public:

      // Destructor
      // ~BreadthFoldableContainer() specifiers

      /* ************************************************************************ */

      // Copy assignment
      // type operator=(argument); // Copy assignment of abstract types should not be possible.

      // Move assignment
      // type operator=(argument); // Move assignment of abstract types should not be possible.

      /* ************************************************************************ */

      // Comparison operators
      // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
      // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

      /* ************************************************************************ */

      // Specific member functions

      // using typename FoldableContainer<Data>::FoldFunctor;

      // type FoldBreadth(arguments) specifiers;

      /* ************************************************************************ */

      // Specific member functions (inherited from FoldableContainer)

      // type Fold(argument) specifiers; // Override FoldableContainer member
    };

}

#include "container.cpp"

#endif

