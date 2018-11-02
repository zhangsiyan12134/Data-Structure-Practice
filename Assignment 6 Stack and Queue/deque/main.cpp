/* File: deque.cpp
   This program implements a double ended queue of integers as a
   doubly linked list */

#include <iostream>
#include <fstream>
using namespace std;

class node {
friend class deque;

private:
    int data;   // this is the data in a list element
    node *next; // pointer to the next node in the list
    node *prev; // pointer to the previous node in the list

public:
    node(int x); // data = x, prev=next = NULL
};

class deque
{
   private:
      node* front;      // pointer to the front of the list
      node* back;       // pointer to the back of the list

   public:
      deque(void);             // constructor of an empty queue
      void put_front(int x);   // put x at the front of the list
      void put_back(int x);    // put x at the back of the list
      int get_front(void);     // get the node at the front of the list
      int get_back(void);      // get the node at the back of the list
      bool empty(void) const;        // check for empty deque
      void write(ostream &out) const; // write data stored to out
};

/* A deque  looks like

         +------+     +------+     +------+          +------+
         | data |     | data |     | data |          | data |
         +------+     +------+     +------+          +------+
         | next |---->| next |---->| next |----> ... | next |---->NULL
NULL<----| prev |<----| prev |<----| prev |... <---- | prev |
         +------+     +------+     +------+          +------+
            ^                                            ^
            |                                            |
            |                                            |
           back                                        front
*/


int main(void)
{
    deque mydeque;
    ofstream fout ("dequeout.txt");
    char ch;
    int x;

    cout << "A dynamic deque of integers\n";
    fout << "A dynamic deque of integers\n";

    do {
        // print a little menu
        cout << "\n\n1 = put front \n";
        cout << "2 = put back \n";
        cout << "3 = get front\n";
        cout << "4 = get back\n";
        cout << "s = print to screen\n";
        cout << "f = print to file\n";
        cout << "q = quit\n\n";

        cin >> ch;

        if (ch == '1') {
            cout <<"\ndata to put front:";
            cin >> x;
            mydeque.put_front(x);
        }
        else if (ch == '2') {
            cout <<"\ndata to put back:";
            cin >> x;
            mydeque.put_back(x);
        }
        else if(ch == '3') {
            if(mydeque.empty()) {
                cout << "deque is empty\n";
            } else {
                cout << "\n\ndata gotten : " << mydeque.get_front();
            }
        }
        else if(ch == '4') {
            if(mydeque.empty()) {
                cout << "deque is empty\n";
            } else {
                cout << "\n\ndata gotten : " << mydeque.get_back();
            }
        }
        else if(ch == 's') mydeque.write(cout);
        else if(ch == 'f') mydeque.write(fout);

    }while(ch != 'q');

    fout.close();
    return 0;
}

node::node(int x)
{
    data = x;
    next = NULL;
    prev = NULL;
}

/*  the put_back function takes an existing deque

            +------+     +------+          +------+
            | last |     | data |          | 1st  |
            +------+     +------+          +------+
            | next |---->| next |----> ... | next |---->NULL
NULL<----   | prev |<----| prev |<---- ... | prev |
            +------+     +------+          +------+
               ^                               ^
               |                               |
               |                               |
              back                           front

ptr points to a new node

         +------+
         |   x  |
ptr ---->+------+
         | next |
         | prev |
         +------+

then connect this  new node into the list

         +------+     +------+     +------+          +------+
         |  x   |     | last |     | data |          | 1st  |
         +------+     +------+     +------+          +------+
         | next |---->| next |---->| next |----> ... | next |---->NULL
NULL<----| prev |<----| prev |<----| prev |<---- ... | prev |
         +------+     +------+     +------+          +------+
            ^                                            ^
            |                                            |
            |                                            |
           back                                        front
*/

/*  the put_front function takes an existing deque

            +------+     +------+          +------+
            | last |     | data |          | 1st  |
            +------+     +------+          +------+
            | next |---->| next |----> ... | next |---->NULL
NULL<----   | prev |<----| prev |... < ----| prev |
            +------+     +------+          +------+
               ^                               ^
               |                               |
               |                               |
              back                           front

ptr points to a new node

         +------+
         |   x  |
ptr ---->+------+
         | next |
         | prev |
         +------+

then connect this  new node into the list
         +------+     +------+         +------+      +------+
         | last |     | data |         | 1st  |      |  x   |
         +------+     +------+         +------+      +------+
         | next |---->| next |---->... | next |----> | next |---->NULL
NULL<----| prev |<----| prev |... <----| prev |<---- | prev |
         +------+     +------+         +------+      +------+
            ^                                           ^
            |                                           |
            |                                           |
           back                                       front
*/

/* The get_front function takes an existing deque

         +------+     +------+         +------+      +------+
         | last |     | data |         | 2nd  |      | 1st  |
         +------+     +------+         +------+      +------+
         | next |---->| next |---->... | next |----> | next |---->NULL
NULL<----| prev |<----| prev |... <----| prev |<---- | prev |
         +------+     +------+         +------+      +------+
            ^                                            ^
            |                                            |
            |                                            |
           back                                        front

and picks off the first data node to be returned

          +------+
          |  1st |
 ptr ---->+------+
          | next |
          | prev |
          +------+

then reassigns the front pointer

            +------+     +------+          +------+
            | last |     | data |          | 2nd  |
            +------+     +------+          +------+
            | next |---->| next |----> ... | next |---->NULL
NULL<----   | prev |<----| prev |... <---- | prev |
            +------+     +------+          +------+
               ^                               ^
               |                               |
               |                               |
              back                           front
*/

/* The get_back function takes an existing deque

         +------+     +------+     +------+          +------+
         | last |     | 2nd  |     | data |          | 1st  |
         +------+     +------+     +------+          +------+
         | next |---->| next |---->| next |----> ... | next |---->NULL
NULL<----| prev |<----| prev |<----| prev |<---- ... | prev |
         +------+     +------+     +------+          +------+
            ^                                            ^
            |                                            |
            |                                            |
           back                                        front

and picks off the last data node to be returned

          +------+
          | last |
 ptr ---->+------+
          | next |
          | prev |
          +------+

then reassigns the back pointer

            +------+     +------+          +------+
            | 2nd  |     | data |          | 1st  |
            +------+     +------+          +------+
            | next |---->| next |----> ... | next |---->NULL
NULL<----   | prev |<----| prev |<---- ... | prev |
            +------+     +------+          +------+
               ^                               ^
               |                               |
               |                               |
              back                           front
*/

deque::deque(void)
{
    front = NULL;
    back = NULL;
}
void deque::put_front(int x)
{
    node *ptr = new node(x);
    if(front == NULL)
    {
        back = front = ptr; //special case for very first node
    } else
    {
        front->next = ptr;  //make old front point to the new node
        ptr->prev = front;  //make new node point back to old front
        front = ptr;    //point front pointer to new node
    }
}

void deque::put_back(int x)
{
    node *ptr = new node(x);
    if(back == NULL)
    {
        back = front = ptr; //special case for very first node
    } else
    {
        back->prev = ptr;   //make old back point to the new node
        ptr->next = back;   //make new node point back to old back
        back = ptr;     //point back pointer to new node
    }
}

int deque::get_front(void)
{
    int temp = front->data;
    if(front == back)
    {
        delete front;   //special case for very last node
        front = back = NULL;    //set stack as empty
    } else
    {
        node *ptr = front;  //create a new pointer to store current front node
        front = ptr->prev;  //let front pointer point to second last node
        front->next = NULL; //let second last node point to NULL
        delete ptr; //delete last node
    }
    return temp;
}

int deque::get_back(void)
{
    int temp = back->data;
    if(front == back)
    {
        delete back;    //special case for very last node
        front = back = NULL;    //set stack as empty
    } else
    {
        node *ptr = back;	//create a new pointer to store current back node
        back = ptr->next;	//let back pointer point to second last node
        back->prev = NULL;	//let second last node point to NULL
        delete ptr; //delete last node
    }

    return temp;
}

bool deque::empty(void) const
{
    return(front == NULL);
}
void deque::write(ostream &out) const
{
	node *ptr = back;
	while(ptr != NULL)
	{
		out << ptr->data << " ";
		ptr = ptr->next;
	}
	out << endl;
}
