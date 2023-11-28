#include "vector.hpp"

namespace lasd {

    template<typename Data>
    Vector<Data>::Vector(const unsigned long newsize) {
        Elements= new Data[newsize];
        size = newsize;
    }

    template <typename Data>
    Vector<Data>::Vector(const LinearContainer<Data>& con){
        size = con.Size();
        Elements = new Data[size];
        for (unsigned long index=0; index<size ; ++index){
            Elements[index] = con[index];
        }
    }

    template<typename Data>
    Vector<Data>::Vector(const Vector<Data> & vec) {
        Elements = new Data[vec.size];
        std::copy(vec.Elements,vec.Elements + vec.size,Elements);
        size = vec.size;
    }

    template<typename Data>
    Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
        std::swap(Elements,vec.Elements);
        std::swap(size, vec.size);
    }

    template <typename Data>
    Vector<Data>::~Vector(){
        delete[] Elements;
    }

    template<typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector<Data> & vec) {
        Vector<Data>* tmpvec = new Vector<Data>(vec);
        std::swap(*tmpvec,*this);
        delete tmpvec;
        return *this;
    }

    template<typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector && vec) noexcept {
        std::swap(Elements,vec.Elements);
        std::swap(size, vec.size);
        return *this;
    }

    template<typename Data>
    bool Vector<Data>::operator==(const Vector & vec) const noexcept {
        if (size == vec.size){
            for (unsigned long i=0; i<size; ++i){
                if(Elements[i] != vec.Elements[i]){
                    return false;
                }
            }
            return true;
        }else{
            return false;
        }
    }

    template<typename Data>
    bool Vector<Data>::operator!=(const Vector & vec) const noexcept {
        return !(*this == vec);
    }

    template<typename Data>
    void Vector<Data>::Resize(const unsigned long newsize) {
        if(newsize == 0){
            Clear();
        }
        else if (size != newsize){
            unsigned long limit;
            if(size<newsize){
                limit = size;
            }
            else{
                limit= newsize;
            }
            Data* TmpElements = new Data[newsize];
            for (unsigned long i = 0; i< limit; ++i ){
                std::swap(Elements[i], TmpElements[i]);
            }
            std::swap(Elements, TmpElements);
            size = newsize;
            delete[] TmpElements;
        }
    }

    template<typename Data>
    void Vector<Data>::Clear() {
        delete[] Elements;
        Elements = nullptr;
        size = 0;
    }

    template<typename Data>
    Data &Vector<Data>::operator[](const unsigned long i) const {
        if (i<size){
            return Elements[i];
        }
        else
        {
            throw std::out_of_range("Operator[]: Index out of range");
        }
    }

    template<typename Data>
    void Vector<Data>::Map(MapFunctor fun, void * par) {
        MapPreOrder(fun,par);
    }

    template<typename Data>
    void Vector<Data>::MapPreOrder(MapFunctor fun, void * par) {
        for(unsigned long i=0; i<size; ++i){
            fun(Elements[i],par);
        }
    }

    template<typename Data>
    void Vector<Data>::MapPostOrder(MapFunctor fun, void * par) {
        unsigned long i = size;
        while(i>0){
            while (i>0){
                fun(Elements[--i],par);
            }
        }
    }

    template<typename Data>
    void Vector<Data>::Fold(FoldFunctor fun, const void * par, void * acc) const{
        FoldPreOrder(fun,par,acc);
    }

    template<typename Data>
    void Vector<Data>::FoldPreOrder(FoldFunctor fun, const void * par, void * acc) const{
        for(unsigned long i=0; i<size; ++i){
            fun(Elements[i],par,acc);
        }
    }

    template<typename Data>
    void Vector<Data>::FoldPostOrder(FoldFunctor fun, const void * par, void * acc) const {
        unsigned long i = size;
        while(i>0){
            while (i>0){
                fun(Elements[--i],par, acc);
            }
        }
    }
}