
#include "htclsadr.hpp"

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(unsigned long newsize) {
        if(newsize!=0) {
            table.Resize(newsize);
            tablesize=newsize;
        }else{
            table.Resize(tablesize);
        }
        size=0;
    }

    template<typename Data>
    void HashTableClsAdr<Data>::Insert(const Data & dat) {
        if(!Exists(dat)) {
            table.operator[](HashTable<Data>::HashKey(dat)).Insert(dat);
            size++;
        }
    }

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data> & lc) {
        table.Resize(tablesize);
        size=0;
        DictionaryContainer<Data>::Insert(lc);
    }

    template<typename Data>
    void HashTableClsAdr<Data>::Insert(Data && dat) {
        if(!Exists(dat)) {
            table.operator[](HashTable<Data>::HashKey(dat)).Insert(std::move(dat));
            size++;
        }
    }

    template<typename Data>
    void HashTableClsAdr<Data>::Remove(const Data & dat) {
        if(Exists(dat)) {
            table.operator[](HashTable<Data>::HashKey(dat)).Remove(dat);
            size--;
        }
    }

    template<typename Data>
    bool HashTableClsAdr<Data>::Exists(const Data & dat) const noexcept {
        if(table.Empty()){return false;}
        return table.operator[](HashTable<Data>::HashKey(dat)).Exists(dat);
    }

    template<typename Data>
    void HashTableClsAdr<Data>::Map(MapFunctor fun, void * par) {
        for(unsigned long i=0;i<table.Size();i++){
            table.operator[](i).Map(fun,par);
        }
    }

    template<typename Data>
    void HashTableClsAdr<Data>::Fold(FoldFunctor fun, const void * par, void * acc) const {
        for(unsigned long i=0;i<table.Size();i++){
            table.operator[](i).Fold(fun,par,acc);
        }
    }

    template<typename Data>
    void HashTableClsAdr<Data>::Clear() {
//        HashTableClsAdr<Data> other(tablesize);
//        operator=(std::move(other));
        Vector<BST<Data>> temp(tablesize);
        table=std::move(temp);
        size=0;
    }

    template <typename Data>
    void AuxFoldEquals(const Data& dat, const void* val, void* exists) noexcept{
        if(!((HashTableClsAdr<Data>*) val)->Exists(dat)){
            *((bool*)exists ) = false;
        }
    }

    template <typename Data>
    void AuxMapResizeClsAdr(const Data& dat, const void* val) noexcept{
        ((HashTableClsAdr<Data>*) val)->Insert(std::move(dat));
    }

//    template <typename Data>
//    void AuxMapDestructor(const Data& dat, const void* val) noexcept{
//    }

    template<typename Data>
    HashTableClsAdr<Data>::~HashTableClsAdr() {
        for(unsigned long i=0;i<table.Size();i++){
            table.operator[](i).Clear();
        }
    }

    template<typename Data>
    bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr &other) const noexcept {
//        bool result=true;
//        if(size!=other.size){
//            return false;
//        }
//
//        Fold(&AuxFoldEquals<Data>,&other,&result);
//        return result;
        if (size != other.Size())
            return false;

        for(unsigned long i=0;i<table.Size();i++) {
                BTInOrderIterator<Data> it1(table.operator[](i));

                while (!it1.Terminated()) {
                    if (!other.Exists(*it1))
                        return false;
                    ++it1;
                }
        }
        return true;
        //return HashTable<Data>::operator==(other);
    }

//    template<typename Data>
//    HashTableClsAdr<Data>::HashTableClsAdr() {
//        table= new Vector<BST<Data>>(tablesize);
//        size=0;
//    }

    template<typename Data>
    void HashTableClsAdr<Data>::Resize(unsigned long newsize) {
        if(newsize!=0 && newsize!=tablesize) {
            HashTableClsAdr<Data> other(newsize);
            Map(&AuxMapResizeClsAdr<Data>,&other);
            operator=(std::move(other));
        }
    }

    template<typename Data>
    HashTableClsAdr<Data> &HashTableClsAdr<Data>::operator=(const HashTableClsAdr & other) {
        if(*this!=other) {
            HashTable<Data>::operator=(other);
            table=other.table;
        }
        return *this;
    }

    template<typename Data>
    HashTableClsAdr<Data> &HashTableClsAdr<Data>::operator=(HashTableClsAdr && other) noexcept {
        if(*this!=other) {
            HashTable<Data>::operator=(std::move(other));
            table=std::move(other.table);
        }
        return *this;
    }

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newsize, const LinearContainer<Data> & lc) {
        if(newsize!=0) {
            table.Resize(newsize);
            tablesize=newsize;
        }else{
            table.Resize(tablesize);
        }
        size=0;
        DictionaryContainer<Data>::Insert(lc);
    }

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr() {
        table.Resize(tablesize);
    }


/* ************************************************************************** */

}
