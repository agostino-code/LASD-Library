
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include "../bst/bst.hpp"


template <typename Data>
lasd::BST<Data>* binaryTree;

void CreateBinaryTree();

void CreateBST();

void RandomBST();

void MenuBinaryTree();

void BinaryTreeStamp();

void BinaryTreeInsertMenu();
void BinaryTreeInsertCopy();
void BinaryTreeInsertMove();

void BinaryTreeRemoveMenu();
void BinaryTreeRemove();
void BinaryTreeRemovePredecessor();
void BinaryTreeRemoveSuccessor();
void BinaryTreeRemoveMin();
void BinaryTreeRemoveMax();

void BinaryTreeVisit();
void BinaryTreePredecessor();
void BinaryTreeSuccessor();
void BinaryTreeMin();
void BinaryTreeMax();

void StampPreOrder();
void StampPostOrder();
void StampInOrder();
void StampBreadth();

void BinaryTreeExist();
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
