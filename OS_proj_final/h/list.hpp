#ifndef PROJECT_BASE_LIST_HPP
#define PROJECT_BASE_LIST_HPP
#include "../h/Memory_allocator.hpp"



template< typename T>
class List{
private:
    struct Node{
        T* data;
        Node* next;
        Node(T* d, Node* n): data(d),next(n){}
    };
    Node* head;
    Node* tail;
    uint64 count=0;//broj elemenata u listi



public:

    void* operator new(size_t size)
    {

        size = size % MEM_BLOCK_SIZE == 0 ? size / MEM_BLOCK_SIZE : (size / MEM_BLOCK_SIZE + 1 );
        //if (size<MEM_BLOCK_SIZE)size=MEM_BLOCK_SIZE;
        return kernel::Memory_allocator::mem_alloc(size);
    }
    void* operator new[](size_t size)
    {

        size = size % MEM_BLOCK_SIZE == 0 ? size / MEM_BLOCK_SIZE : (size / MEM_BLOCK_SIZE + 1 );
       // if (size<MEM_BLOCK_SIZE)size=MEM_BLOCK_SIZE;
        return kernel::Memory_allocator::mem_alloc(size);
    }

    void operator delete(void* p)noexcept{kernel::Memory_allocator::mem_free(p);}
    void operator delete[](void* p)noexcept{kernel::Memory_allocator::mem_free(p);}

    List(){
        head=nullptr;
        tail=nullptr;
        count=0;
    }
    List(const List<T>&)=delete;
    List<T>& operator=(const List<T>&)=delete;

    uint64 size(){return count;}
    void push_front(T* d)//postavljamo kao 1. element
    {
        Node* new_node= (Node*)operator new (sizeof(Node));
        new_node->data=d;
        new_node->next=head;

        head=new_node;
        new_node=nullptr;

        if (!tail) tail=head;
        count++;
    }
    void push_back(T* d)//postavljamo kao poslednji
    {
        size_t size = sizeof(Node);

        Node* new_node=(Node*)operator new(size);
        new_node ->data=d;
        new_node->next=nullptr;

        count++;

        if (tail)//tail je na kraju liste
        {
            tail->next=new_node;
            tail=new_node;

        }
        else if(head==nullptr)//nema ni head ni tail
        {
            head=tail=new_node;
        }

        new_node=nullptr;
    }
    T* get(int index)
    {
        int n=0;
        Node* temp=head;

        while (n!=index)
        {
            if (temp==nullptr)return nullptr;
            temp=temp->next;
            n++;
        }
        return temp->data;
    }
    T* pop_front()//vraca prvi element
    {
        Node* ret=head;

        if (head)
        {
            if (head==tail)//jedan element u listi
            {
                head=tail=nullptr;
            }
            else
            {
                head=head->next;
            }

            count--;
            T* ret_val=ret->data;
            //operator delete(ret);
            return ret_val;
        }
        return nullptr;//ako smo ovde lista je prazna
    }

    T* pop_back()//vraca poslednji
    {
        Node* temp=head;

        T* ret_val=nullptr;
        if (!temp)return nullptr;//prazna lista
        else if (!temp->next)//1 element u listi
        {
            count--;
            head=nullptr;
            ret_val=temp->data;
            operator delete (temp);
            return ret_val;
        }
        else//2+ el
        {
            while (temp->next!=tail && temp->next!=nullptr)
            {
                temp=temp->next;
            }
            tail=temp;
            temp=temp->next;
            count--;
            tail->next=nullptr;
            ret_val=temp->data;
            operator delete(temp);
            return ret_val;
        }

    }





};



#endif //PROJECT_BASE_LIST_HPP
