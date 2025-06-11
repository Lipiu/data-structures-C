# Teorie pentru examen

## Declarations and types
**Type specifiers:**
* void 
* char 
* short 
* int 
* long 
* float 
* double 
* signed/unsigned
* struct/union 
* enum

**Type qualifiers:**
* const
* volatile

**Storage-class specifier:**
* auto 
* register 
* static 
* extern 
* typedef
* __declspec

**User defined types**
* Article
    * Groups different types of primitive variables 
    * Aggregated type which uses compact memory

* Bit structure
    * A particular type of article which allows users access at bit level

* Union
    * Allows that the same memory region be defined as two or multiple different types of variables

* Enumeration
    * Is a list of constant integer variables with given names

Synonyms 
    * Are defined by using the typedef specifier
#
**Bitwise operators:**
* & - AND
* | - OR
* ^ - OR exclusive - XOR
* ~ - One complement (flips bit value)
* .>> - Right shifting
* << - Left shifting

#

## Simple linked lists
* Linear structures, heap allocated, managed by a pointer to the first element of the lsit called head.
* Main operations:
    * Insertion
    * Deletion
    * Parsing
* Resembles the unidimensional arrays
* Contains two types of fields:
    * pointer to the next element (link data)
    * a field for the useful data
* if we write head = head->next we change the head of the list
* if we write head->next = head->next->next we change where the LINK from the head points to

![example](images/image.png)
![example2](images/image-1.png)

#

## Stacks
* Definition:
    * It is a linear structure in which the two basic operations, insertion and deletion are made on a LIFO (Last In First Out) rule. These operations are made in a single part of the structure called the head of the stack, or the top.
![alt text](images/stack.png)

* Operations
    * PUSH -> adding an element
    * POP -> deleting an element
    * PEEK -> looking at the top element

#

## Infix - Postfix - Prefix notations
* **Notations:**
    * **Polish notation** - prefix notation
    * **Reverse Polish notation** - postfix notation

* **Characteristics:**
    * **Polish notation** (prefix): the operators are written `before` the operands.
    * **Reverse Polish notation** (postfix) - the operators are placed `after` the operands.
* **Hierarchy**
![hierarchy](images/hierarchy%20polish%20notation.png)
![alt text](images/table%20hierarchy.png)
#
**Dijkstra-Shunting yard algorithm**
* **1st step:** Scan the entire infix expression from left to right and look for `tokens` (operators, operands and paranthesis)
* **2nd step:** For each token test:
    * if token is an `operator`
        * Remove all operators at the top of the stack that have
          higher or equal precedence compared to the incoming
          operator, and add them to the postfix expression following
          this step, place the new operator onto the stack
    * if token is an `operand`
        * append it to the postfix expression
    * if token is a `left paranthesis`
        * push it on the stack
    * if token is a `right paranthesis`
        * Remove all operators from the stack and add them to the postfix
          expression until a matching left parenthesis is encountered. Do not add this left parenthesis to the result, simply discard it.

`Example:`
* Infix->Postfix: 2*(4+3)+9/3
* We iterate through each token and use the table and theory from above
    * First iteration:
        * Output: 2
        * Stack: nothing
    * Second iteration:
        * Output: 2
        * Stack: *
    * Third iteration:
        * Output: 2
        * Stack: *(
    * Fourth iteration:
        * Output: 24
        * Stack: *(
    * Sixth iteration:
        * Output: 24
        * Stack: *(+
    * Seventh iteration:
        * Output: 243
        * Stack: *(+
    * Eigth iteration:
        * Output: 243+
        * Stack: *
    * Ninth iteration:
        * Output: 243+*
        * Stack: +
    * Tenth iteration:
        * Output: 243+*9 
        * Stack: +
    * Eleventh iteration:
        * Output: 243+*9
        * Stack: +/
    * Twelfth iteration:
        * Output: 243+*93
        * Stack: +/
    * Last iteration (congrats if you made it!!!)
        * Output: 243+*93/+
        * Stack: nothing
#
**Postfix evaluation algorithm**
* **1st step:** Scan the entire postfix expression from left to right and look for `tokens` (operators, operands and paranthesis)
* For each `token` test wheter:
    * If token is an `operand` is pushed on the stack
    * If token is an `operator`:
        * Pop the `left element` from the stack into a `y` variable;
        * Pop the `right element` from the stack into a `x` variable;
        * The operation between `x` operator `y` is computed;
        * The result is `pushed` on the stack;
* The last value standing on the stack is the result of the expression

#

## Queues
* **Definition:**
    * It is a linear structure in which the two basic operations, insertion and deletion are made on a `FIFO`(First In First Out) based model. The `insertion` is made on the `tail section` and the `deletion` is made on the `front section` of the queue.
#

## Hash Tables

