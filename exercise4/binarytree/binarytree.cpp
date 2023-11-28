
// #include "..."
#include "binarytree.hpp"
namespace lasd {

/* ************************************************************************** */

template<typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& other) const noexcept {
        BTPostOrderIterator<Data> it1(*this);
        BTPostOrderIterator<Data> it2(other);

        if (Size() != other.Size())
            return false;

        while (!it1.Terminated()) {
            if (*it1 != *it2)
                return false;
            ++it1;
            ++it2;
        }

        return true;
}

    template<typename Data>
    bool BinaryTree<Data>::operator!=(const BinaryTree<Data> & other) const noexcept {
        return !(*this==other);
    }

    template <typename Data>
    void BinaryTree<Data>::MapPreOrder(MapFunctor fun, void* par, Node* node) {
        if(node != nullptr){
            fun(node->Element(), par);

            if(node->HasLeftChild())
                MapPreOrder(fun, par, &node->LeftChild());

            if(node->HasRightChild())
                MapPreOrder(fun, par, &node->RightChild());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapPostOrder(MapFunctor fun, void* par, Node* node) {
        if(node != nullptr){
            if(node->HasLeftChild())
                MapPostOrder(fun, par, &node->LeftChild());

            if(node->HasRightChild())
                MapPostOrder(fun, par, &node->RightChild());

            fun(node->Element(), par);
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
        if(node != nullptr){
            fun(node->Element(), par, acc);

            if(node->HasLeftChild())
                FoldPreOrder(fun, par, acc, &node->LeftChild());

            if(node->HasRightChild())
                FoldPreOrder(fun, par, acc, &node->RightChild());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
        if(node != nullptr){
            if(node->HasLeftChild())
                FoldPostOrder(fun, par, acc, &node->LeftChild());

            if(node->HasRightChild())
                FoldPostOrder(fun, par, acc, &node->RightChild());

            fun(node->Element(), par, acc);
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapInOrder(MapFunctor fun, void* par, Node* node) {
        if(node != nullptr){
            if(node->HasLeftChild())
                MapInOrder(fun, par, &node->LeftChild());

            fun(node->Element(), par);

            if(node->HasRightChild())
                MapInOrder(fun, par, &node->RightChild());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldInOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
        if(node != nullptr){
            if(node->HasLeftChild())
                FoldInOrder(fun, par, acc, &node->LeftChild());

            fun(node->Element(), par, acc);

            if(node->HasRightChild())
                FoldInOrder(fun, par, acc, &node->RightChild());
        }
    }

    template<typename Data>
    void BinaryTree<Data>::MapBreadth(MapFunctor fun, void *par) {
        if (!Empty())
            for (BTBreadthIterator<Data> i(*this); !i.Terminated(); ++i)
                fun(*i, par);
    }

    template<typename Data>
    void BinaryTree<Data>::FoldBreadth(FoldFunctor fun, const void *par, void *acc) const {
        if (!Empty())
            for (BTBreadthIterator<Data> i(*this); !i.Terminated(); ++i)
                fun(*i, par, acc);
    }


/* ************************************************************************** */

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt){
    T=&bt;
    if(!T->Empty()){
        current = &bt.Root();
        if (current->HasRightChild()) {
            stack.Push(&current->RightChild());
        }
        if (current->HasLeftChild()) {
            stack.Push(&current->LeftChild());
        }
    }else{current = nullptr;}

//        terminated= false;
//        operator++();
}

template<typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
    if (T != nullptr) {
        if (!T->Empty()) {
            index = 0;
            stack.Clear();
            current = &T->Root();
            if (current->HasRightChild()) {
                stack.Push(&current->RightChild());
            }
            if (current->HasLeftChild()) {
                stack.Push(&current->LeftChild());
            }
        }
    }
}

template<typename Data>
Data &BTPreOrderIterator<Data>::operator*() const {
    if(!Terminated()) {
        return current->Element();
    }
    else {
        throw std::out_of_range("The BTPreOrderIterator is pointing nullptr");
    }
}

template<typename Data>
void BTPreOrderIterator<Data>::operator++() {
    if(current== nullptr){
        throw std::out_of_range("The BTPreOrderIterator is pointing nullptr");
    }
    else{
        if(!stack.Empty()){
        current = stack.Top();
        stack.Pop();
        if (current->HasRightChild()) {
            stack.Push(&current->RightChild());
        }
        if (current->HasLeftChild()) {
            stack.Push(&current->LeftChild());
        }
        index++;
        }
        else{current= nullptr;}
    }
}

template<typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> & other) const noexcept {
    return (T == other.T) && (index == other.index);
}

template<typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> & other) const noexcept {
    return !(*this==other);
}

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data> && other) noexcept {
    *this=std::move(other);
}

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data> & other) {
    *this=other;
}

template<typename Data>
BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& other) {
    if(this != &other) {
        T = other.T;
        index = other.index;
        current=other.current;
        stack = other.stack;
    }
}

template<typename Data>
BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& other) noexcept {
    if(this != &other) {
        std::swap(T, other.T);
        std::swap(index, other.index);
        std::swap(current, other.current);
        stack = std::move(other.stack);
    }
    return *this;
}

/* ************************************************************************** */

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) {
    T = &bt;
    if (!T->Empty()) {
        LeftEndOf(T->Root());
    }else{
        current= nullptr;
    }
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& other) {
    *this = other;
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& other) noexcept {
    *this = std::move(other);
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& other) {
    if (this != &other) {
        T = other.T;
        index = other.index;
        current = other.current;
        stack = other.stack;
    }
    return *this;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& other) noexcept {
    if (this != &other) {
        std::swap(T, other.T);
        std::swap(index, other.index);
        std::swap(current, other.current);
        stack = std::move(other.stack);
    }
    return *this;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& other) const noexcept {
    return (T == other.T) && (index == other.index);
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& other) const noexcept {
    return !(*this == other);
}

template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
    if (Terminated())
        throw std::out_of_range("The BTPostOrderIterator is pointing nullptr");
    return current->Element();
}

template <typename Data>
void BTPostOrderIterator<Data>::operator++() {
    if (Terminated())
        throw std::out_of_range("The BTPostOrderIterator is pointing nullptr");

    if (stack.Empty())
        current = nullptr;
    else {
        typename BinaryTree<Data>::Node* parent = stack.Top();
        if (parent->HasRightChild() && current==&parent->RightChild()) {
            current = parent;
            stack.Pop();
        }
        else if (parent->HasLeftChild() && current==&parent->LeftChild()) {
            if (parent->HasRightChild())
                LeftEndOf(parent->RightChild());
            else {
                current = parent;
                stack.Pop();
            }
        }
    }
    index++;
}

template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {
    if (T != nullptr) {
        if(!T->Empty()) {
            index = 0;
            stack.Clear();
            LeftEndOf(T->Root());
        }
    }
}

template <typename Data>
void BTPostOrderIterator<Data>::LeftEndOf(typename BinaryTree<Data>::Node& root) noexcept {
    current = &root;
    while (!current->IsLeaf()) {

        while (current->HasLeftChild()) {
            stack.Push(current);
            current = &current->LeftChild();
        }

        if (current->HasRightChild()) {
            stack.Push(current);
            current = &current->RightChild();
        }
    }
}

/* ************************************************************************** */

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> & bt){
    T=&bt;
    if(!T->Empty()) {
        LeftMove(T->Root());
        out=current;
    }else{current= nullptr;}
}

template<typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {
    if (T != nullptr) {
        if (!T->Empty()) {
            index = 0;
            stack.Clear();
            LeftMove(T->Root());
            out=current;
        }
    }
}

template<typename Data>
Data &BTInOrderIterator<Data>::operator*() const {
    if(!Terminated()) {
        return out->Element();
    }
    else {
        throw std::out_of_range("The BTInOrderIterator is pointing nullptr");
    }
}

template<typename Data>
void BTInOrderIterator<Data>::operator++() {
        if (Terminated()) {
            throw std::out_of_range("The BTInOrderIterator is pointing nullptr");
        }
        if(!stack.Empty()) {
            current = stack.Top();
            stack.Pop();
            out=current;
            if(current->HasRightChild()) {
                LeftMove(current->RightChild());
            }
            index++;
        }else{current= nullptr;}
}

template<typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data> & other) const noexcept {
    return (T == other.T) && (index == other.index);
}

template<typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data> & other) const noexcept {
    return !(*this==other);
}

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data> && other) noexcept {
    *this=std::move(other);
}

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data> & other) {
    *this=other;
}

template<typename Data>
BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> & other) {
    if(this != &other) {
        T = other.T;
        index = other.index;
        current = other.current;
        out = other.out;
        stack = other.stack;
        //delete other.stack;
    }
    return *this;
}

template<typename Data>
BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> && other) noexcept {
    if(this != &other) {
        std::swap(T, other.T);
        std::swap(index, other.index);
        std::swap(current, other.current);
        std::swap(out, other.out);
        stack = std::move(other.stack);
    }
    return *this;
}

    template<typename Data>
    void BTInOrderIterator<Data>::LeftMove(typename BinaryTree<Data>::Node& root) noexcept {
        current=&root;
        if(current->HasLeftChild()) {
            while (current->HasLeftChild()) {
                stack.Push(current);
                current = &current->LeftChild();
            }
        }
        else{stack.Push(current);}
    }

/* ************************************************************************** */

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {
    T = &bt;
    if (!T->Empty()) {
        current = &T->Root();
        EnqueueChildren();
    }
    else{
        current= nullptr;
    }
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& other) {
    *this = other;
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& other) noexcept {
    *this = std::move(other);
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& other) {
    if (this != &other) {
        T = other.T;
        index = other.index;
        current = other.current;
        queue = other.queue;
    }
    return *this;
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& other) noexcept {
    if (this != &other) {
        std::swap(T, other.T);
        std::swap(index, other.index);
        std::swap(current, other.current);
        queue = std::move(other.queue);
    }
    return *this;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& other) const noexcept {
    return (T == other.T) && (index == other.index);
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& other) const noexcept {
    return !(*this == other);
}

template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
    if (Terminated())
        throw std::out_of_range("The BTBreadthIterator is pointing nullptr");
    return current->Element();
}

template <typename Data>
void BTBreadthIterator<Data>::operator++() {
    if (Terminated())
        throw std::out_of_range("The BTBreadthIterator is pointing nullptr");

    if (queue.Empty())
        current = nullptr;
    else {
        current = queue.Head();
        EnqueueChildren();
        queue.Dequeue();
    }
    index++;
}

template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
    if (T != nullptr) {
        if(!T->Empty()) {
            index = 0;
            queue.Clear();
            current = &T->Root();
            EnqueueChildren();
        }
    }
}

template <typename Data>
void BTBreadthIterator<Data>::EnqueueChildren() noexcept {
    if (current->HasLeftChild())
        queue.Enqueue(&current->LeftChild());
    if (current->HasRightChild())
        queue.Enqueue(&current->RightChild());
}

/* ************************************************************************** */

}
