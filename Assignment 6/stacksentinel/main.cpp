// File: stacksentinal.cpp
// This program implements a simple stack of integers using a linked list
// with a sentinel

#include <iostream>
#include <fstream>
using namespace std;

class node {

friend class stack;  // stack needs access to node's members
   
private:
    int data;   // this is the data in a stack node
    node *next; // pointer to the next stack node

public:
    node(int x); // data = x, next = NULL
};

class stack {
private:
    node sentinel; // sentinel for the stack

public:
    stack(void);                        // constructor
    void push(int x);                    
    int pop(void);                       
    bool empty(void) const;             // check for empty stack
    void write(ostream &out) const;     // write the stack to out
};
/* A stack looks like a chain of nodes

     +------+     +------+     +------+          +------+
     |  0   |     | data |     | data |          | data |
     +------+     +------+     +------+          +------+
     | next |---->| next |---->| next |----> ... | next |---->NULL
     +------+     +------+     +------+          +------+     
     sentinel      top of                        bottom of
                   stack                         stack

sentinel is an object which acts as a marker for the top of the stack. 
sentinel.next points to the top of the stack which will be NULL if the stack
is empty. The value stored in sentinel.data is not part of the stack so we
can put any value there.  The value at the top of the stack is
sentinel.next->data. */

int main(void)
{
    stack mystack; 
    ofstream fout ("stacksentinelout.txt");
    char ch;
    int x;
   
    cout << "A dynamic stack of integers\n";
    fout << "A dynamic stack of integers\n";

    do {
        // print a little menu
        cout << "\n\np = push \n";
        cout << "o = pop\n";
        cout << "s = print to screen\n";
        cout << "f = print to file\n";
        cout << "q = quit\n\n";
      
        cin >> ch;
      
        if (ch == 'p') {
            cout <<"\ndata to push :";
            cin >> x;
            mystack.push(x);
        }
        else if(ch == 'o') {
            if(mystack.empty()) {
                cout << "Stack is empty\n";
            } else {
                cout << "\n\ndata popped : " << mystack.pop();
            }
        }
        else if(ch == 's') mystack.write(cout);
        else if(ch == 'f') mystack.write(fout);

    }while(ch != 'q');

    fout.close();   
    return 0;
}

node::node(int x)
{
    data = x;
    next = NULL;
}
    
/*  the push function takes an existing stack 

     +------+     +------+     +------+          +------+
     |  0   |     | data |     | data |          | data |
     +------+     +------+     +------+          +------+
     | next |---->| next |---->| next |----> ... | next |---->NULL
     +------+     +------+     +------+          +------+     
     sentinel      top of                        bottom of
                   stack                         stack




ptr points to a new node object
     
         +------+
         |   x  |
ptr ---->+------+
         | next |
         +------+

then connect this new node into the list

     +------+     +------+     +------+          +------+
     |  0   |     |   x  |     | data |          | data |
     +------+     +------+     +------+          +------+
     | next |---->| next |---->| next |----> ... | next |---->NULL
     +------+     +------+     +------+          +------+     
     sentinel      new top      old top            bottom
*/

/* The pop function takes an existing stack

     +------+     +------+     +------+          +------+
     |  0   |     | data |     | data |          | data |
     +------+     +------+     +------+          +------+
     | next |---->| next |---->| next |----> ... | next |---->NULL
     +------+     +------+     +------+          +------+     
     sentinel      top of                        bottom of
                   stack                         stack

and picks off the first node object to return it's data

          +------+
          | 1st  |
 ptr ---->+------+
          | next |
          +------+

then reassigns the next pointer to the second node

     +------+     +------+          +------+
     |  0   |     | 2nd  |          | data |
     +------+     +------+          +------+
     | next |---->| next |----> ... | next |---->NULL
     +------+     +------+          +------+     
     sentinel      new top            bottom

*/

stack::stack(void):sentinel(0)
{
}
void stack::push(int x)
{
	node *ptr;
	ptr = new node(x);
	ptr->next = sentinel.next;
	sentinel.next = ptr;
}                    
int stack::pop(void)
{
	int temp = 0;
	temp = sentinel.next->data;
	node *ptr = sentinel.next;
	sentinel.next = ptr->next;
	delete ptr;
	
	return temp;
}                      
bool stack::empty(void) const
{
	if(sentinel.next == NULL)
	{
		return 1;
	} else
	{
		return 0;
	}
}
void stack::write(ostream &out) const
{
	node *ptr = sentinel.next;
	while(ptr != NULL)
	{
		out << ptr->data << ",";
		ptr = ptr->next;
	}
	out << endl;
}
