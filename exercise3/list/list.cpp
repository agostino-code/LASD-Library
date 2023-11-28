
#include <iostream>
#include "list.hpp"
/* ************************************************************************** */
namespace lasd
{
    template<typename Data>
    List<Data>::Node::Node(Data && dat) noexcept {
        std::swap(element, dat);
    }

    template<typename Data>
    List<Data>::Node::Node(Node && nod) noexcept {
        std::swap(element,nod.element);
        std::swap(next, nod.next);
    }

//    template<typename Data>
//    List<Data>::Node::~Node() {
//           delete next;
//    }

    template<typename Data>
    bool List<Data>::Node::operator==(const Node & nod) const noexcept {
        return (element == nod.element) \
        && ((next == nullptr && nod.next == nullptr)||( next != nullptr && nod.next != nullptr) && (*next == *nod.next));
    }

    template<typename Data>
    bool List<Data>::Node::operator!=(const Node & nod) const noexcept {
        return !(*this == nod);
    }
    template <typename Data>
    List<Data>::List(const LinearContainer<Data> &con)
    {
        for (unsigned int i = 0; i < con.Size(); i++)
        {
            InsertAtBack(con[i]);
        }
    }

    // Move constructor
    template <typename Data>
    List<Data>::List(List<Data> &&other)
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }

    // Copy constructor
    template <typename Data>
    List<Data>::List(const List<Data> &other)
    {
        if (this == &other)
            return;

        for (unsigned int i = 0; i < other.size; i++)
        {
            InsertAtBack(other[i]);
        }
    }

    // Operatori di Copia
    template <typename Data>
    List<Data> &List<Data>::operator=(const List<Data> &other)
    {
        if (this == &other)
            return *this;

        Clear();

        Node *temp = other.head;
        while (temp != nullptr)
        {
            InsertAtBack(temp->element);
            temp = temp->next;
        }

        return *this;
    }

    template <typename Data>
    List<Data> &List<Data>::operator=(List<Data> &&other) noexcept
    {
        std::swap(this->head, other.head);
        std::swap(this->tail, other.tail);
        std::swap(this->size, other.size);

        return *this;
    }

    template <typename Data>
    List<Data>::~List()
    {
        Clear();
    }

    template <typename Data>
    void List<Data>::InsertAtFront(const Data &newData)
    {
        if (head == nullptr)
        {
            head = new Node(newData);
            tail = head;
        }
        else
        {
            Node *newNode = new Node(newData);
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    template <typename Data>
    void List<Data>::InsertAtFront(Data &&newData)
    {
        if (head == nullptr)
        {
            head = new Node(std::move(newData));
            tail = head;
        }
        else
        {
            Node *newNode = new Node(std::move(newData));
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    template <typename Data>
    void List<Data>::RemoveFromFront()
    {
        if (this->Size() == 0)
            throw std::out_of_range("The List is empty");

        Node *temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    template <typename Data>
    Data List<Data>::FrontNRemove()
    {
        if (this->Size() == 0)
            throw std::out_of_range("The List is empty");

        Node *temp = head;
        Data returnedData = temp->element;
        head = head->next;
        delete temp;

        size--;
        return returnedData;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(const Data &newData)
    {

        if (tail == nullptr)
        {
            tail = new Node(newData);
            head = tail;
        }
        else
        {
            Node *newNode = new Node(newData);
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data &&newValue)
    {
        if (tail == nullptr)
        {
            Node *newNode = new Node(std::move(newValue));
            head = newNode;
            tail = head;
        }
        else
        {
            Node *newNode = new Node(std::move(newValue));
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    template <typename Data>
    bool List<Data>::operator==(const List<Data> &other) const noexcept
    {
        if (size != other.size)
            return false;

        Node *temp1 = head;
        Node *temp2 = other.head;

        while (temp1 != nullptr)
        {
            if (temp1->element != temp2->element)
                return false;

            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        return true;
    }

    template <typename Data>
    bool List<Data>::operator!=(const List<Data> &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    Data &List<Data>::Front() const
    {
        if (this->Size() == 0)
            throw std::length_error("The List is empty");

        return head->element;
    }

    template <typename Data>
    Data &List<Data>::Back() const
    {
        if (this->Size() == 0)
            throw std::length_error("The List is empty");

        return tail->element;
    }

    template <typename Data>
    Data &List<Data>::operator[](unsigned long index) const
    {
        if (index >= size)
            throw std::out_of_range("Operator[]: Index out of range");

        Node *temp = head;
        for (unsigned int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->element;
    }

    template <typename Data>
    void List<Data>::Clear()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            Node *temp2 = temp;
            temp = temp->next;
            delete temp2;
        }

        size = 0;
        head = nullptr;
        tail = nullptr;
    }

    template<typename Data>
    void List<Data>::MapPreOrder(MapFunctor fun, void * par, Node * cur) {
        for(; cur!= nullptr; cur=cur->next)
            fun(cur->element, par);
    }

    template<typename Data>
    void List<Data>::MapPostOrder(MapFunctor fun, void * par, Node * cur) {
        if(cur != nullptr){
            this->MapPostOrder(fun,par,cur->next);
            fun(cur->element, par);
        }
    }

    template<typename Data>
    void List<Data>::FoldPreOrder(FoldFunctor fun, const void * par, void * acc, Node * cur) const {
        for(; cur!= nullptr; cur=cur->next)
            fun(cur->element, par, acc);
    }

    template<typename Data>
    void List<Data>::FoldPostOrder(FoldFunctor fun, const void * par, void * acc, Node * cur) const {
        if(cur != nullptr){
            this->FoldPostOrder(fun,par,acc,cur->next);
            fun(cur->element, par, acc);
        }
    }

};
