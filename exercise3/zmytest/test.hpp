
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"


template <typename Data>
lasd::BinaryTree<Data>* binaryTree;

void CreateBinaryTree();

void CreateBinaryTreeLnk();
void CreateBinaryTreeVec();

void RandomBinaryTreeLnk();
void RandomBinaryTreeVec();

void MenuBinaryTree();

void BinaryTreeStamp();

void StampPreOrder();
void StampPostOrder();
void StampInOrder();
void StampBreadth();

void BinaryTreeExist();
void BinaryTreeMap();
void BinaryTreeFold();

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
