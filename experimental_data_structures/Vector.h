#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>

/*
This is an experimental vector class that I would like to use in embedded programs. 
I pretty much conjured this up in a couple hours, so formatting and functionality is 
rather subpar at the moment. Will work on this in the near future.
*/

template<typename T>
class Node
{
    public:
        
        T value;
        Node<T> * next;
        bool has_next;
        Node(){has_next = false;};
        ~Node(){};
};

template<typename T>
class Vector
{
    public:
        
        Vector();
        void push_back(T data);
        Node<T> * iterator();
        Node<T> * end();
    private:
       
        Node<T> * beginning;
        Node<T> * current;
        
            
};

template<typename T>
Vector<T>::Vector()
{
    Node<T> * vect_ptr = (Node<T>*)malloc(sizeof(Node<T>));
    vect_ptr->value = NULL;
    beginning = vect_ptr;
    current = beginning;
}

template<typename T>
void Vector<T>::push_back(T data)
{
    current->next = (Node<T>*)malloc(sizeof(Node<T>));
    current->has_next = true;
    current = current->next;
    current->value = data;
}

template<typename T>
Node<T> * Vector<T>::iterator()
{
	return beginning->next;
}

template<typename T>
Node<T> * Vector<T>::end()
{
    current->next = NULL;
    return current->next;
}
#endif