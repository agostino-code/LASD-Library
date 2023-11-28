#include "stackvec.hpp"

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    StackVec<Data>::StackVec() {
        size = INIT_SIZE;
        Elements = new Data[INIT_SIZE];
        tail = 0;
    }

    template<typename Data>
    StackVec<Data>::~StackVec() {
        if (size!=0) {
            size=0;
            delete[] Elements;
            Elements = nullptr;
            tail = 0;
        }
    }

    template<typename Data>
    StackVec<Data>::StackVec(const LinearContainer<Data> & lc){
        size = (lc.Size()>INIT_SIZE) ? lc.Size() : INIT_SIZE;
        Elements = new Data[size];
        for (unsigned long i=0; i<lc.Size(); i++)
            Push(lc[i]);
    }

    template<typename Data>
    StackVec<Data>::StackVec(const StackVec<Data> & stackVec) {
        *this = stackVec;
    }

    template<typename Data>
    StackVec<Data>::StackVec(StackVec<Data>&& stackVec) noexcept {
    *this = std::move(stackVec);
    }

    template<typename Data>
    StackVec<Data> &StackVec<Data>::operator=(const StackVec<Data> & other) {
        if(this != &other) {
            //Clear(); //NO, memory leakage
            delete[] Elements;
            size = other.size;
            tail = other.tail;
            Elements = new Data[other.size];
            for (unsigned long i=0; i<other.size; i++)
                Elements[i]=other.Elements[i];
        }
        return *this;
    }

    template<typename Data>
    StackVec<Data> &StackVec<Data>::operator=(StackVec && other) noexcept {
        if(this != &other) {
        std::swap(size, other.size);
        std::swap(Elements, other.Elements);
        std::swap(tail, other.tail);
        }
        return *this;
    }

    template<typename Data>
    bool StackVec<Data>::operator==(const StackVec & other) const noexcept {
        if(Size()!=other.Size()){
            return false;
        }
        for(unsigned long i=0; i<tail; i++){

            if(Elements[i] != other.Elements[i]){
                return false;
            }
        }
        return true;
    }

    template<typename Data>
    bool StackVec<Data>::operator!=(const StackVec & stackVec) const noexcept {
        return !(*this == stackVec);
    }

    template<typename Data>
    const Data &StackVec<Data>::Top() const {
        if (Empty())
            throw std::length_error("The Stack is empty");
        return Elements[tail-1];
    }

    template<typename Data>
    Data &StackVec<Data>::Top() {
        if (Empty())
            throw std::length_error("The Stack is empty");
        return Elements[tail-1];
    }

    template<typename Data>
    void StackVec<Data>::Pop() {
        if (Empty())
            throw std::length_error("Cannot Pop a Stack that is already empty");
        tail--;
        if(size>INIT_SIZE && Size() <= size/FACTOR)
            Reduce();
    }

    template<typename Data>
    Data StackVec<Data>::TopNPop() {
        if (Empty()) { throw std::length_error("The Stack is empty");}
        else{
            Data temp=Top();
            Pop();
            return temp;}
    }

    template<typename Data>
    void StackVec<Data>::Push(const Data & newValue) noexcept {
        if (Size()>=size-1){Expand();}
        Elements[tail] = newValue;
        tail++;
    }

    template<typename Data>
    void StackVec<Data>::Push(Data && newValue) noexcept {
        if (Size()>=size-1){Expand();}
        Elements[tail] = std::move(newValue);
        tail++;
    }

    template<typename Data>
    bool StackVec<Data>::Empty() const noexcept {
        return tail==0;
    }

    template<typename Data>
    unsigned long StackVec<Data>::Size() const noexcept {
        return tail;
    }

    template<typename Data>
    void StackVec<Data>::Clear() {
        if (Size()!=0) {
            delete[] Elements;
            size = INIT_SIZE;
            Elements = new Data[INIT_SIZE];
            tail = 0;
        }
    }

    template<typename Data>
    void StackVec<Data>::Expand() {
        unsigned long new_size = size*FACTOR;
        Data *tmp = new Data[new_size];
        // for (unsigned long int i=0, j=head; i<Size(); i++, j++) {
        //     if (j>=size)
        //         j=0;
        //     std::cout << Elements[j] << " ";
        //     tmp[i] = Elements[j];
        // } std::cout << std::endl;
        for (unsigned long j=0; true; j++) {
            if (j == tail) { break; }
            tmp[j] = Elements[j];
        }
        delete[] Elements;
        Elements = tmp;
        size = new_size;
        tmp = nullptr;
        //std::cout << "Espansione, nuova size: " << size << std::endl;
    }

    template<typename Data>
    void StackVec<Data>::Reduce() {
        unsigned long int new_size = size/FACTOR;
        Data *tmp = new Data[new_size];
        // for (unsigned long int i=0, j=head; i<Size(); i++, j++) {
        //     if (j>=size)
        //         j=0;
        //     std::cout << Elements[j] << " ";
        //     tmp[i] = Elements[j];
        // } std::cout << std::endl;
        for (unsigned long int j=tail; true; j++) {
            if (j == tail) { break; }
            tmp[j] = Elements[j];
        }
        delete[] Elements;
        Elements = tmp;
        size = new_size;
        tmp = nullptr;
        //std::cout << "Riduzione, nuova size: " << size << std::endl;
    }




/* ************************************************************************** */

}
