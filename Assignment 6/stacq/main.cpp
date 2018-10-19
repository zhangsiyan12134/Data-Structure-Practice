// File: stacq.cpp
// This program implements a cross between a stack and a queue

#include <iostream>
#include <fstream>
using namespace std;

class node {
friend class stacq; 

private:
   int data;   // this is the data in a stacq element
   node *next; // pointer to the next node on the stack
   
public:
   node(int x) {data = x; next = NULL;}
   
};

class stacq {
private:
   int count;   // number of values stored
   node* top;   // pointer to the top of the stacq
 
public:
   stacq(void);                   // constructor of an empty stacq
   void store(int x);             // store the value x 
   int retrieve(void);            // retrieve a value
   bool empty(void) const;        // check for empty stack
   void write(ostream &out) const; // write stacq to out
};

/* A stacq  looks like

count = 
         +------+     +------+     +------+          +------+
         | data |     | data |     | data |          | data |
top ---> +------+     +------+     +------+          +------+
         | next |---->| next |---->| next |----> ... | next |---->NULL
         +------+     +------+     +------+          +------+     
*/

int main(void)
{
   stacq mine;
   ofstream fout ("stacqout.txt");
   char ch;
   int x;
   
   cout << "A dynamic stacq of integers\n";
   fout << "A dynamic stacq of integers\n";

   do {
      // print a little menu
      cout << "\n\ns = store \n";
      cout << "r = retrieve\n";
      cout << "p = print to screen\n";
      cout << "f = print to file\n";
      cout << "q = quit\n\n";
      
      cin >> ch;
      
      if (ch == 's') {
         cout <<"\ndata to store :";
         cin >> x;
         mine.store(x);
      }
      else if(ch == 'r') {
         if(mine.empty())
            cout << "empty\n";
         else
            cout << "\n\ndata retrieved :" << mine.retrieve();
      }
      else if(ch == 'p') mine.write(cout);
      else if(ch == 'f') mine.write(fout);

   }while(ch != 'q');
   
   fout.close();
   return 0;
}

stacq::stacq(void):top(0)
{
}
void stacq::store(int x)
{
	node *ptr;
	ptr = new node(x);
	ptr->next = top;
	top = ptr;
	count++;
}
int stacq::retrieve(void)	//something wrong here
{
	int temp;
	if(count % 2)
	{
		temp = top->data;
		node *ptr = top;
		top = ptr->next;
		delete ptr;
	} else
	{
		node *ptr = top;
		node *ptr2 = top;
		while(ptr->next != NULL)
		{
			ptr2 = ptr; 
			ptr = ptr->next;
		}
		temp = ptr->data;
		ptr2->next = NULL;
		if(ptr == top)
		{
			top = NULL;
		}
		delete ptr;
	}	
	count--;
	return temp;
}
bool stacq::empty(void) const
{
	if(top != NULL)
	{
		return 0;
	} else
	{
		return 1;
	}
}
void stacq::write(ostream &out) const
{
	node *ptr = top;
	while(ptr != NULL)
	{
		out << ptr->data << ",";
		ptr = ptr->next;
	}
	out << endl;
}
