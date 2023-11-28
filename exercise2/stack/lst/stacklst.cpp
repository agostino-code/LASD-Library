#include "stacklst.hpp"

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    StackLst<Data>::StackLst() {
        list=new List<Data>;
        size=0;
    }

    template<typename Data>
    StackLst<Data>::StackLst(const LinearContainer<Data> & lc){
        list=new List<Data>(lc);
        size=lc.Size();
    }

    template<typename Data>
    StackLst<Data>::StackLst(const StackLst<Data> & stackLst) {
        List<Data>* temp = new List<Data>(*stackLst.list);
        size=stackLst.size;
        std::swap(list,temp);
    }

    template<typename Data>
    StackLst<Data>::StackLst(StackLst<Data> && stackLst) noexcept {
        std::swap(list,stackLst.list);
        size=std::move(stackLst.size);
    }

    template<typename Data>
    StackLst<Data> &StackLst<Data>::operator=(const StackLst & stackLst) {
        List<Data>* temp= new List<Data>(*stackLst.list);
        std::swap(list,temp);
        size=stackLst.size;
        delete temp;
        return *this;
    }

    template<typename Data>
    StackLst<Data> &StackLst<Data>::operator=(StackLst && stackLst) noexcept {
        std::swap(list,stackLst.list);
        size=std::move(stackLst.size);
        return *this;
    }

    template<typename Data>
    const Data &StackLst<Data>::Top() const {
        return list->Front();
    }

    template<typename Data>
    Data &StackLst<Data>::Top() {
        return list->Front();
    }

    template<typename Data>
    bool StackLst<Data>::operator==(const StackLst<Data> & stackLst) const noexcept {
        if(list->operator!=(*stackLst.list)){ return false;}
        return true;
    }

    template<typename Data>
    bool StackLst<Data>::operator!=(const StackLst<Data> & stackLst) const noexcept {
        return !(*this == stackLst);
    }

    template<typename Data>
    void StackLst<Data>::Pop() {
        if (list->Empty()) { throw std::length_error("The Stack is empty"); }
        else { list->RemoveFromFront(); size--;
        }
    }

    template<typename Data>
    Data StackLst<Data>::TopNPop() {
        if (list->Empty()) { throw std::length_error("The Stack is empty");}
        else{ return list->FrontNRemove(); size--;
        }
    }

    template<typename Data>
    void StackLst<Data>::Push(const Data & newValue) noexcept {
        list->InsertAtFront(newValue); size++;
    }

    template<typename Data>
    void StackLst<Data>::Push(Data && newValue) noexcept {
        list->InsertAtFront(newValue); size++;
    }

    template<typename Data>
    void StackLst<Data>::Clear() {
        list->Clear();
        size=0;
    }



/* ************************************************************************** */

}
