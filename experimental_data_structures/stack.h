/* 
 * File:   stack.h
 * Author: Chris
 *
 * Created on November 8, 2012, 4:39 PM
 */

#ifndef STACK_H
#define	STACK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    /*This is a struct that is used to make a stack.*/
typedef struct
{
    char value;
  struct Node * next_node;
} Node ;

/* Theses next three function prototypes are used to work with the structure.
 * Linear structure, and values can only be read from top of the structure, 
 * and is therefore a stack. On TDM-gcc warnings are thrown for pop and 
 * push, but it works.
 */
Node * push(Node * stack_top, char value);
Node * pop(Node * stack_top);
char peek(Node * stack_top);

/*
 *      Function - push
 * 
 * Purpose:
 * To add a value to the stack.
 * 
 * Parameters:
 * stack_top - Points to top of stack used to add value.
 * value - Value to add.
 * 
 * Output: 
 * Node that is the new top of stack.
 */
Node * push(Node * stack_top, char value)
{
    /*Creates new node.*/
    Node * new = (Node *) malloc(sizeof(Node));
    
    /* Adds value to new node. Then refers the old top of stack
     * as the next node. This is why the stack pointer needs to be
     * initialized to null, so the program knows where the bottom is.
     */
    new->value = value;
    new->next_node = stack_top;
    
    return new;
}
/*
 *      Function - pop
 * 
 * Purpose:
 * To remove a value from the stack. Can be used in a while loop
 * to empty the stack.
 * 
 * Parameters:
 * stack_top - Points to top of stack to be used.
 * 
 * Output:
 * Node that points to new top of stack.
 */
Node * pop(Node * stack_top)
{
    
    Node * temp = stack_top->next_node;
    free(stack_top);
    
    return temp;
    
}

/*
 *      Function - peek
 * 
 * Purpose:
 * Gives value of the top of stack without removing it.
 * 
 * Parameters:
 * stack_top - Points to top of stack to be used.
 * 
 * Output:
 * Value of the top of stack.
 */
char peek(Node *stack_top)
{
    return stack_top->value;
}




#ifdef	__cplusplus
}
#endif

#endif	/* STACK_H */

