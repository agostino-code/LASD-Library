#include "container.hpp"

namespace lasd {

    template <typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer<Data>& lc) const noexcept{
        if(size == lc.size){
            for(unsigned long i=0; i<size; i++){
                if(operator[](i) != lc[i]){
                    return false;
                }
            }
            return true;
        }
        else{
            return false;

        }
    }

    template <typename Data>
    bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& lc) const noexcept{
        return !(*this == lc);
    }

    template <typename Data>
    Data& LinearContainer<Data>::Front() const{
        if (size!=0){
            return operator[](0);
        } else {
            throw std::length_error("Accesso ad un linear conatiner vuoto");
        }
    }

    template <typename Data>
    Data& LinearContainer<Data>::Back() const{
        if (size!=0){
            return operator[](size - 1);
        } else {
            throw std::length_error("Accesso ad un linear conatiner vuoto");
        }
    }

    template <typename Data>
    void AuxFoldExists(const Data& dat, const void* val, void* exists) noexcept{
        if( dat == *((Data*) val)){
            *((bool*)exists ) = true;
        }
    }

    template <typename Data>
    bool FoldableContainer<Data>::Exists(const Data& dat) const noexcept{
        bool exists =false;
        Fold(&AuxFoldExists<Data>, &dat, &exists);
        return exists;
    }

    template <typename Data>
    void PreOrderMappableContainer<Data>::Map(MapFunctor fun, void* par){
        MapPreOrder(fun,par);
    }

    template <typename Data>
    void PreOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void * par, void * acc) const {
        FoldPreOrder(fun, par, acc);
    }

    template <typename Data>
    void PostOrderMappableContainer<Data>::Map(MapFunctor fun, void * par) {
        MapPostOrder(fun, par);
    }

    template <typename Data>
    void PostOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void * par, void * acc) const {
        FoldPostOrder(fun, par , acc);
    }

}
