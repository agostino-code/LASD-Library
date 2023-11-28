#include "queuelst.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& lc) {
    if (!lc.Empty())
        for (unsigned long int i=0; i<lc.Size(); i++)
            List<Data>::InsertAtBack(lc[i]);
}

/* ************************************************************************** */

template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& other) {
    List<Data>::operator=(other); 
    return *this;
}

template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& other) noexcept {
    List<Data>::operator=(std::move(other)); 
    return *this;
}

/* ************************************************************************** */

template <typename Data>
const Data& QueueLst<Data>::Head() const {
    if (Empty())
        throw std::length_error("Access to an empty Queue");
    return List<Data>::Front();
}

template <typename Data>
Data& QueueLst<Data>::Head() {
    if (Empty())
        throw std::length_error("Access to an empty Queue");
    return List<Data>::Front();
}

template <typename Data>
void QueueLst<Data>::Dequeue() {
    if (Empty())
        throw std::length_error("Cannot Dequeue a Queue that is already empty");
    List<Data>::RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data>::HeadNDequeue() {
    if (Empty())
        throw std::length_error("Cannot Dequeue a Queue that is already empty");
    return List<Data>::FrontNRemove();
}

template <typename Data>
void QueueLst<Data>::Enqueue(const Data& element) noexcept {
    List<Data>::InsertAtBack(element);
}

template <typename Data>
void QueueLst<Data>::Enqueue(Data&& element) noexcept {
    List<Data>::InsertAtBack(std::move(element));
}

}
