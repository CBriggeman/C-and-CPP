#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
/*This is a struct that is used to make a stack.*/
typedef struct
{
    char value;
    struct Node * next_node;
    
} Node ;
 
/* These next three function prototypes are used to work with the structure.
 * Linear structure, and values can only be read from top of the structure, 
 * and is therefore a stack. On TDM-gcc warnings are thrown for pop and 
 * push, but it works.
 */
Node * push(Node * stack_top, char value);
Node * pop(Node * stack_top);
char peek(Node * stack_top);
 
/*These do basic operations, and checks if string is a palindrome.*/
void is_palindrome(Node * stack_top, char * string);
Node* mem_to_stack(Node * stack_top, char * buffer);
void string_to_mem(char * buffer, char * string);
Node * stack_to_mem(Node * stack_top, char * buffer);
 
/*
 * 
 */
int main(int argc, char** argv) 
{
    char response;
    /*Couple palindromes  and one that is not.*/
    char string1[] = "Race car";
    char string2[] = "Never odd or even.";
    char string3[] = "Hello World!";    //No
    
    /*The ultimate test.*/
    char string4[] = "Do good? I? No! Evil anon I deliver \
                I maim nine more hero-men in Saginaw, sanitary \
                sword a-tuck, Carol, I -- lo! -- rack, cut a drowsy \
                rat in Aswan. I gas nine more hero-men in Miami. Reviled, \
                I (Nona) live on. I do, O God!";
    
    /*Stack pointer MUST be initialized.*/
    Node * a_stack = NULL;    
    
    is_palindrome(a_stack, string1);
    is_palindrome(a_stack, string2);
    is_palindrome(a_stack, string3);
    is_palindrome(a_stack, string4);
    
    scanf("\n");
    scanf("%c", &response);
 
    return (EXIT_SUCCESS);
}
 
/*      Function - is_palindrome
 * 
 * Purpose: 
 * To evaluate a string and determine if it is a palindrome.
 * 
 * Parameters:
 * stack_top - Stack pointer to be used by the function. Stack should
 *             be empty.
 * 
 * string - pointer to string that is to be evaluated.
 * 
 * Output:  
 * Does not return anything, is void.
 */
void is_palindrome(Node * stack_top, char * string)
{
    /*Intermediate strings that are used to process input string.*/
    char input_buffer[250];            
    char output_buffer[250];
    
    /*Calls processing function.*/
    string_to_mem(input_buffer,string);
    
    /* 
     * Because a stack is being used output_buffer will be 
     * the input_buffer backwards.
     */
    stack_top = mem_to_stack(stack_top, input_buffer);
    stack_top = stack_to_mem(stack_top, output_buffer);
    
    /*Finally, evaluates if string is a palindrome.*/
    if(!(strcmp(input_buffer,output_buffer)))
    {
        printf("String is a palindrome.\n");
    }
    else
    {
        printf("String is not a palindrome.\n");
    }
  
}
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
/*
 *      Function - mem_to_stack
 * 
 * Purpose:
 * Copies the contents of an entire buffer onto the stack.
 * 
 * Parameters:
 * stack_top - Points to stack to be used.
 * buffer - Buffer to be copied from.
 * 
 * Output:
 * Node that points to the top of filled stack.
 */
Node * mem_to_stack(Node * stack_top, char * buffer)
{
    char * current_ptr; //Pointer that is used to traverse buffer.
    
    /*Copy process.*/
    for(current_ptr = buffer; *current_ptr != '\0'; current_ptr++)
    {
        stack_top = push(stack_top, *current_ptr);
    }
    
    return stack_top;
}
 
/*
 *      Function - string_to_mem
 * 
 * Purpose:
 * To process string so it will be ready to be put onto the stack.
 * 
 * Parameters:
 * buffer - The buffer used to copy and process string.
 * string - String to be used.
 * 
 * Output:
 * Does not output anything, is void.
 */
void string_to_mem(char * buffer, char * string)
{
    char * char_ptr;  //Pointer used to traverse the string
    
    /*Copying and processing string.*/
    for(char_ptr = string; *char_ptr != '\0'; char_ptr++)
    {
        /*Throws out punctuation and whitespace.*/
        if(iswpunct(*char_ptr)||iswspace(*char_ptr))
        {
            continue;
        }
        
        /*All character are converted to lowercase.*/
        *buffer = tolower(*char_ptr);
        buffer++;
        
    }
     /*Don't forget to insert null character at the end.*/
    *buffer = '\0';
}
 
/*
 *      Function - stack_to_mem
 * 
 * Purpose:
 * Offloads contents of an entire stack onto a buffer.
 * 
 * Parameters:
 * stack_top - points to top of stack that is used.
 * buffer - Buffer that stack will be offloaded to.
 * 
 * Output:
 * Node that points to new top of the stack after offload. Stack should
 * be empty after process, and therefore null.
 */
Node * stack_to_mem(Node * stack_top, char * buffer)
{
    /*  Empties the stack. Meanwhile values on top of stack are copied
     *  to the buffer.
     */
    while(stack_top != NULL)
    {
        
        *buffer = peek(stack_top);
        stack_top = pop(stack_top);
        buffer++;    
    }
    
    /*Never forget.*/
    *buffer = '\0'; 
    
    return stack_top;
}