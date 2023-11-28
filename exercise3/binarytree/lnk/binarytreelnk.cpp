
namespace lasd {

/* ************************************************************************** */

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data& element) {
    key = element; 
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& lc) {
    root = CreateTree(root, 0, lc);
    size = lc.Size();
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::CreateTree(NodeLnk* node, unsigned long i, const LinearContainer<Data> & lc) {
    if (i < lc.Size())
    {
        node = new NodeLnk(lc[i]);
        node->leftnode = CreateTree(node->leftnode, 2 * i + 1, lc);
        node->rightnode = CreateTree(node->rightnode, 2 * i + 2, lc);
    }
    return node;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::CreateTree(NodeLnk* node, NodeLnk* other_node) {
    if (other_node != nullptr) {
        node = new NodeLnk(other_node->Element());
        node->leftnode = CreateTree(node->leftnode, other_node->leftnode);
        node->rightnode = CreateTree(node->rightnode, other_node->rightnode);
    }
    return node;
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return leftnode!=nullptr;
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    return rightnode!=nullptr;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() {
    return *rightnode;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild(){
    return *leftnode;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    return *root;
}

template<typename Data>
void BinaryTreeLnk<Data>::Clear() {
    if(!Empty()) {
        PostOrderDelete(root);
        size=0;
    }
}

template<typename Data>
void BinaryTreeLnk<Data>::PostOrderDelete(BinaryTreeLnk::NodeLnk *cur) {
    if (cur->HasLeftChild())
        PostOrderDelete(&cur->LeftChild());
    if (cur->HasRightChild())
        PostOrderDelete(&cur->RightChild());
    delete cur;
    cur = nullptr;
}

template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& other) {
    // root=other.root;
    if (this != &other) {
        Clear();
        if (!other.Empty()) {
            size=other.size;
            root = CreateTree(root, other.root);
        }
    }
    return *this;
}

template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk <Data>&& other) noexcept {
    if (this != &other) {
        std::swap(root,other.root);
        std::swap(size,other.size);
    }
    return *this;
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> & other){
    *this = other;
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> && other) noexcept {
    *this = std::move(other);
}

/* ************************************************************************** */

}
