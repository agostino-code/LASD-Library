
namespace lasd {

/* ************************************************************************** */

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& lc) {
    if (!lc.Empty()) {
        size = lc.Size();
        elements.Resize(lc.Size());
        for (unsigned long int i=0; i<elements.Size(); i++)
            elements[i] = new NodeVec(elements, lc[i], i);
    }
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& other) {
    *this = other;
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& other) noexcept {
    *this = std::move(other);
}

template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& other) {
    if (this != &other) {
        Clear();
        size = other.size;
        elements.Resize(other.elements.Size());
        for (unsigned long int i=0; i<elements.Size(); i++)
            elements[i] = new NodeVec(elements, other.elements[i]->Element(), i);
    }
    return *this;
}

template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& other) noexcept {
    if (this != &other) {
        std::swap(size, other.size);
        elements = std::move(other.elements);
    }
    return *this;
}


template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if (Empty())
        throw std::length_error("Access to the Root of an Empty BinaryTree");
    return *elements[0];
}


template<typename Data>
void BinaryTreeVec<Data>::Clear() {
    if (!Empty()) {
        size = 0;
        for (unsigned long int i=0; i<elements.Size(); i++)
            delete elements[i];
        elements.Clear();
    }
}


template<typename Data>
void BinaryTreeVec<Data>::MapBreadth(MapFunctor fun, void* par) {
    for (unsigned long int i=0; i<elements.Size(); i++)
        fun(elements[i]->Element(), par);
}

template<typename Data>
void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor fun, const void* par, void* acc) const {
    for (unsigned long int i=0; i<elements.Size(); i++)
        fun(elements[i]->Element(), par, acc);
}

/* ************************************************************************** */

}
