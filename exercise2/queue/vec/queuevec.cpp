#include "queuevec.hpp"
namespace lasd {

    template <typename Data>
    QueueVec<Data>::QueueVec() {
        size = INIT_SIZE;
        Elements = new Data[INIT_SIZE];
        head = 0;
        tail = 0;
    }

template <typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& lc) {
    size = (lc.Size()>INIT_SIZE) ? lc.Size() : INIT_SIZE;
    Elements = new Data[size];
    for (unsigned long int i=0; i<lc.Size(); i++)
        Enqueue(lc[i]);
}

/* ************************************************************************** */

template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& other) {
    *this = other;
}

template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& other) noexcept {
    *this = std::move(other);
}

/* ************************************************************************** */

template <typename Data>
QueueVec<Data>::~QueueVec() {
    if (size!=0) {
        size=0;
        delete[] Elements;
        Elements = nullptr;
        head = 0;
        tail = 0;
    }
}

/* ************************************************************************** */

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& other) {
    if(this != &other) {
        //Clear(); //NO, memory leakage
        delete[] Elements;
        size = other.size;
        head = other.head;
        tail = other.tail;
        Elements = new Data[other.size];
        for (unsigned long int i=0; i<other.size; i++)
            Elements[i]=other.Elements[i];
    }
    return *this;
}

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& other) noexcept {
    if(this != &other) {
        std::swap(size, other.size);
        std::swap(Elements, other.Elements);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }
    return *this;
}

/* ************************************************************************** */

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& other) const noexcept {
    bool ret = Size()==other.Size();
    if(this != &other)
        for(unsigned long int i=head, j=other.head; i<Size(); i++, j++)
            if(!ret)
                return ret;
            else {
                if (i>=size)
                    i=0;
                if (j>=other.size)
                    j=0;
                ret*= (Elements[i] == other.Elements[j]);
            }
    return ret;
}

template <typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& other) const noexcept{
    return !(operator==(other));
}

/* ************************************************************************** */

template <typename Data>
const Data& QueueVec<Data>::Head() const {
    if (Empty())
        throw std::length_error("Access to an empty Queue");
    return Elements[head];
}

template <typename Data>
Data& QueueVec<Data>::Head() {
    if (Empty())
        throw std::length_error("Access to an empty Queue");
    return Elements[head];
}

template <typename Data>
void QueueVec<Data>::Dequeue() {
    if (Empty())
        throw std::length_error("Cannot Dequeue a Queue that is already empty");
    head++;
    if (head>=size)
        head = 0;
    if(size>INIT_SIZE && Size() <= size/FACTOR)
        Reduce();
}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue() {
    if (Empty())
        throw std::length_error("Cannot Dequeue a Queue that is already empty");
    unsigned long int tmp = head;
    head++;
    if (head>=size)
        head = 0;
    if (size>INIT_SIZE && Size() <= size/FACTOR)
        Reduce();
    return Elements[tmp];
}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data& element) noexcept {
    if (Size()>=size-1)
        Expand();
    Elements[tail] = element;
    tail++;
    if (tail>=size)
        tail = 0;
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data&& element) noexcept {
    if (Size()>=size-1)
        Expand();
    Elements[tail] = std::move(element);
    tail++;
    if (tail>=size)
        tail = 0;
}

/* ************************************************************************** */

template <typename Data>
bool QueueVec<Data>::Empty() const noexcept {
    return Size()==0;
}

template <typename Data>
unsigned long int QueueVec<Data>::Size() const noexcept {
    return tail>=head ? tail-head : tail+size-head;
}

template <typename Data>
void QueueVec<Data>::Clear() {
    if (Size()!=0) {
        delete[] Elements;
        size = INIT_SIZE;
        Elements = new Data[INIT_SIZE];
        head = 0;
        tail = 0;
    }
}

/* ************************************************************************** */

template <typename Data>
void QueueVec<Data>::Expand() noexcept {
    unsigned long int new_size = size*FACTOR;
    Data *tmp = new Data[new_size];
    // for (unsigned long int i=0, j=head; i<Size(); i++, j++) {
    //     if (j>=size)
    //         j=0;
    //     std::cout << Elements[j] << " ";
    //     tmp[i] = Elements[j];
    // } std::cout << std::endl;
    for (unsigned long int i=0, j=head; true; i++, j++) {
        if (j>=size)
            j=0;
        if (j==tail)
            break;
        tmp[i] = Elements[j];
    }
    delete[] Elements;
    Elements = tmp;
    tail = Size();
    head = 0;
    size = new_size;
    tmp = nullptr;
    std::cout << "Espansione, nuova size: " << size << std::endl;
}

template <typename Data>
void QueueVec<Data>::Reduce() {
    unsigned long int new_size = size/FACTOR;
    Data *tmp = new Data[new_size];
    // for (unsigned long int i=0, j=head; i<Size(); i++, j++) {
    //     if (j>=size)
    //         j=0;
    //     std::cout << Elements[j] << " ";
    //     tmp[i] = Elements[j];
    // } std::cout << std::endl;
    for (unsigned long int i=0, j=head; true; i++, j++) {
        if (j>=size)
            j=0;
        if (j==tail)
            break;
        tmp[i] = Elements[j];
    }
    delete[] Elements;
    Elements = tmp;
    tail = Size();
    head = 0;
    size = new_size;
    tmp = nullptr;
    std::cout << "Riduzione, nuova size: " << size << std::endl;
}


}
