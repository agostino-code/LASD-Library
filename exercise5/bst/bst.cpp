#include "bst.hpp"

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    bool BST<Data>::operator==(const BST & other) const noexcept {
        BTInOrderIterator<Data> it1(*this);

        if (size != other.Size())
            return false;

        while (!it1.Terminated()) {
            if (!other.Exists(*it1))
                return false;
            ++it1;
        }

        return true;
       //return BinaryTreeLnk<Data>::operator==(other);
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *BST<Data>::Skip2Left(typename BinaryTreeLnk<Data>::NodeLnk *& node) noexcept {
        typename BinaryTreeLnk<Data>::NodeLnk* left= nullptr;
        if(node != nullptr){
            std::swap(left,node->leftnode);
            std::swap(left,node);
            //size--;
        }
        return left;
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *BST<Data>::Skip2Right(typename BinaryTreeLnk<Data>::NodeLnk *& node) noexcept {
        typename BinaryTreeLnk<Data>::NodeLnk* right= nullptr;
        if(node != nullptr){
            std::swap(right,node->rightnode);
            std::swap(right,node);
            //size--;
        }
        return right;
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *const *BST<Data>::FindPointerToSuccessor(typename BinaryTreeLnk<Data>::NodeLnk *const & node, const Data & data) const noexcept {
        typename BinaryTreeLnk<Data>::NodeLnk* const* pointer=&node;
        typename BinaryTreeLnk<Data>::NodeLnk* const* pre= nullptr;
        while(true){
            typename BinaryTreeLnk<Data>::NodeLnk& cur = **pointer;
            if(cur.key > data){
                pre= pointer;
                        if(cur.leftnode== nullptr){
                            return pre;
                        }
                        else{
                            pointer= &cur.leftnode;
                        }
            }
            else{
                if(cur.rightnode== nullptr) {
                    return pre;
                }else{
                    if(cur.key< data){
                        pointer= &cur.rightnode;
                    }else{
                        return &FindPointerToMin(cur.rightnode);
                    }
                }
            }
        }
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk ** BST<Data>::FindPointerToSuccessor(typename BinaryTreeLnk<Data>::NodeLnk *& node, const Data & data) noexcept {
        return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node,data));
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *const *BST<Data>::FindPointerToPredecessor(typename BinaryTreeLnk<Data>::NodeLnk *const & node, const Data & data) const noexcept {
        typename BinaryTreeLnk<Data>::NodeLnk* const* pointer=&node;
        typename BinaryTreeLnk<Data>::NodeLnk* const* pre= nullptr;
        while(true){
            typename BinaryTreeLnk<Data>::NodeLnk& cur = **pointer;
            if(cur.key < data){
                pre= pointer;
                if(cur.rightnode== nullptr){
                    return pre;
                }
                else{
                    pointer= &cur.rightnode;
                }
            }
            else{
                if(cur.leftnode== nullptr) {
                    return pre;
                }else{
                    if(cur.key> data){
                        pointer= &cur.leftnode;
                    }else{
                        return &FindPointerToMax(cur.leftnode);
                    }
                }
            }
        }
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk ** BST<Data>::FindPointerToPredecessor(typename BinaryTreeLnk<Data>::NodeLnk *& node, const Data & data) noexcept {
        return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node,data));
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *const &BST<Data>::FindPointerTo(typename BinaryTreeLnk<Data>::NodeLnk *const & node,const Data& data) const noexcept {
        typename BinaryTreeLnk<Data>::NodeLnk* const* pointer=&node;
        typename BinaryTreeLnk<Data>::NodeLnk* cur=node;
        while(cur!= nullptr){
            if(cur->key<data){
                pointer=&cur->rightnode;
                cur=cur->rightnode;
            } else if(cur->key>data){
                pointer= &cur->leftnode;
                cur=cur->leftnode;
            }else{
                break;
            }
        }
        return *pointer;
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *&BST<Data>::FindPointerTo(typename BinaryTreeLnk<Data>::NodeLnk *& node, const Data & data) noexcept {
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node,data));
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *const &BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk *const & node) const noexcept {
        typename BinaryTreeLnk<Data>::NodeLnk* const* pointer=&node;
        typename BinaryTreeLnk<Data>::NodeLnk* cur=node;
        if(cur!= nullptr){
            while(cur->rightnode != nullptr){
                pointer = &cur->rightnode;
                cur=cur->rightnode;
            }
        }
        return *pointer;
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *&BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk *& node) noexcept {
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(node));
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *const &BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk *const & node) const noexcept {
        typename BinaryTreeLnk<Data>::NodeLnk* const* pointer=&node;
        typename BinaryTreeLnk<Data>::NodeLnk* cur=node;
        if(cur!= nullptr){
            while(cur->leftnode != nullptr){
                pointer = &cur->leftnode;
                cur=cur->leftnode;
            }
        }
        return *pointer;
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *&BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk *& node) noexcept {
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *BST<Data>::Detach(typename BinaryTreeLnk<Data>::NodeLnk *& node) noexcept {
        DeleteNode(root,node->key);
        return node;
    }

    template<typename Data>
    void BST<Data>::DeleteNode(typename BinaryTreeLnk<Data>::NodeLnk *& node, const Data & data)
    {
        if (node == nullptr) {
            return;
        }
        if (data < node->key) {
            DeleteNode(node->leftnode, data);
        }
        else if (data > node->key) {
            DeleteNode(node->rightnode, data);
        }
        else {
            if (node->leftnode == nullptr && node->rightnode == nullptr)
            {
                delete node;
                node = nullptr;
            }
            else if (node->leftnode && node->rightnode)
            {
                typename BinaryTreeLnk<Data>::NodeLnk* predecessor = FindPointerToMax(node->leftnode);
                node->key = predecessor->key;
                DeleteNode(node->leftnode, predecessor->key);
            }
            else {
                typename BinaryTreeLnk<Data>::NodeLnk* child = (node->leftnode)? node->leftnode: node->rightnode;
                typename BinaryTreeLnk<Data>::NodeLnk* curr = node;

                node = child;

                delete curr;
            }
        }
    }


    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *BST<Data>::DetachMin(typename BinaryTreeLnk<Data>::NodeLnk *& node) noexcept {
        return Skip2Right(FindPointerToMin(node));
    }

    template<typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *BST<Data>::DetachMax(typename BinaryTreeLnk<Data>::NodeLnk *& node) noexcept {
        return Skip2Left(FindPointerToMax(node));
    }

    template<typename Data>
    Data BST<Data>::DataNDelete(typename BinaryTreeLnk<Data>::NodeLnk * node) {
        return Detach(node)->key;
    }

    template<typename Data>
    const Data &BST<Data>::Min() const {
        if(!Empty()) {
            return FindPointerToMin(root)->Element();
        }
        else{throw std::length_error("The Binary Search Tree is Empty.");}
    }

    template<typename Data>
    Data BST<Data>::MinNRemove() {
        if(!Empty()) {
        size--;
        return DetachMin(root)->key;
        }else{throw std::length_error("The Binary Search Tree is Empty.");}
    }

    template<typename Data>
    void BST<Data>::RemoveMin() {
        if(!Empty()) {
        size--;
        DetachMin(root);
        }else{throw std::length_error("The Binary Search Tree is Empty.");}
    }

    template<typename Data>
    const Data &BST<Data>::Max() const {
        if(!Empty()) {
            return FindPointerToMax(root)->Element();
        }
        else{
            throw std::length_error("The Binary Search Tree is Empty.");
        }
    }

    template<typename Data>
    Data BST<Data>::MaxNRemove() {
        if(!Empty()) {
        size--;
        return DetachMax(root)->key;
        }else{throw std::length_error("The Binary Search Tree is Empty.");}
    }

    template<typename Data>
    void BST<Data>::RemoveMax() {
        if(!Empty()) {
        size--;
        DetachMax(root);
        }else{throw std::length_error("The Binary Search Tree is Empty.");}
    }

    template<typename Data>
    const Data &BST<Data>::Predecessor(const Data & data) const {
        if(Empty()){ throw std::length_error("The Binary Search Tree is Empty.");}
        typename BinaryTreeLnk<Data>::NodeLnk* const* current = FindPointerToPredecessor(root,data);
        if(current!= nullptr) {
            return (*current)->Element();
        }else{throw std::length_error("Predecessor not found.");}
    }

    template<typename Data>
    Data BST<Data>::PredecessorNRemove(const Data & data) {
        if(Empty()){ throw std::length_error("The Binary Search Tree is Empty.");}
        typename BinaryTreeLnk<Data>::NodeLnk** current = FindPointerToPredecessor(root,data);
        if(current!= nullptr) {
            size--;
            return DataNDelete(*current);
        }else{throw std::length_error("Predecessor not found.");}
    }

    template<typename Data>
    void BST<Data>::RemovePredecessor(const Data & data) {
        if(Empty()){ throw std::length_error("The Binary Search Tree is Empty.");}
        typename BinaryTreeLnk<Data>::NodeLnk** current = FindPointerToPredecessor(root,data);
        if(current!= nullptr) {
        size--;
        Detach(*current);
        }else{throw std::length_error("Predecessor not found.");}
    }

    template<typename Data>
    const Data &BST<Data>::Successor(const Data & data) const {
        if(Empty()){ throw std::length_error("The Binary Search Tree is Empty.");}
        typename BinaryTreeLnk<Data>::NodeLnk* const* current = FindPointerToSuccessor(root,data);
        if(current!= nullptr) {
        return (*current)->Element();
        }else{throw std::length_error("Successor not found.");}
    }

    template<typename Data>
    Data BST<Data>::SuccessorNRemove(const Data & data) {
        if(Empty()){ throw std::length_error("The Binary Search Tree is Empty.");}
        typename BinaryTreeLnk<Data>::NodeLnk** current = FindPointerToSuccessor(root,data);
        if(current!= nullptr) {
        size--;
        return DataNDelete(*current);
        }else{throw std::length_error("Successor not found.");}
    }

    template<typename Data>
    void BST<Data>::RemoveSuccessor(const Data & data) {
        if(Empty()){ throw std::length_error("The Binary Search Tree is Empty.");}
        typename BinaryTreeLnk<Data>::NodeLnk** current = FindPointerToSuccessor(root,data);
        if(current!= nullptr) {
        Detach(*current);
        size--;
        }else{throw std::length_error("Successor not found.");}
    }

    template<typename Data>
    void BST<Data>::Insert(const Data & data) {
        if(root!= nullptr) {
            if(!Exists(data)) {
                FindPointerTo(root, data) = new NodeLnk(data);
                size++;
            }
        }else{root=new NodeLnk(std::move(data)); size++;}
    }

    template<typename Data>
    void BST<Data>::Remove(const Data & data) {
        if(Exists(data)){
        typename BinaryTreeLnk<Data>::NodeLnk* curr= FindPointerTo(root,data);
            Detach(curr);
            size--;
        }
    }

    template<typename Data>
    void BST<Data>::Insert(Data && data) {
        if(root!= nullptr) {
            if(!Exists(data)) {
                FindPointerTo(root, data) = new NodeLnk(std::move(data));
                size++;
            }
        }else{root=new NodeLnk(std::move(data)); size++;}
    }

    template<typename Data>
    bool BST<Data>::Exists(const Data & data) const noexcept {
        typename BinaryTreeLnk<Data>::NodeLnk* current=root;
        while(current != nullptr)
        {
            if(current->Element() == data) return true;
            if(current->Element() > data) current = current->leftnode;
            else current = current->rightnode;
        }

        return false;
    }

    template<typename Data>
    BST<Data>::BST(const LinearContainer<Data> & lc){
        for(unsigned long i=0;i<lc.Size();i++){
            Insert(lc.operator[](i));
        }
    }
}




/* ************************************************************************** */

