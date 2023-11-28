
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include "../hashtable/hashtable.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"

template <typename Data>
lasd::HashTable<Data>* hashTable;

void CreateHashTable();

void CreateOpn();
void CreateCls();

void RandomOpn();
void RandomCls();

void MenuHashTable();

void HashStamp();

void HashInsertMenu();
void HashInsertCopy();
void HashInsertMove();

void HashRemove();

void HashExist();
void HashFold();

template <typename Data>
void MapPrint(const Data& dat, void* _) {
    std::cout << dat << " ";
}

template <typename Data>
void MapInt( Data& dat, void* _) {
    dat *= 3;
}

template <typename Data>
void MapString(std::string& dat, void* par) {
    dat=(*((std::string*) par))+dat;
}
template <typename Data>
void MapDouble( Data& dat, void* _) {
    dat = pow(dat,3);
}

template <typename Data>
void FoldInt(const Data& dat, const void* par, void* acc) {
    if( dat < *((Data*) par)){
        *((Data*) acc) *= dat;
    }
}

template <typename Data>
void FoldDouble(const Data& dat, const void* par, void* acc) {
    if( dat < *((Data*) par)){
        *((Data*) acc) += dat;
    }
}

template <typename Data>
void FoldString(const std::string& dat, const void* par, void* acc) {
    if( dat.length() <= *((int*) par)){
        ((std::string*) acc)->append(dat);
    }
}

int RandomInt();
std::string RandomString();
double RandomDouble();


/* ************************************************************************** */

#endif
