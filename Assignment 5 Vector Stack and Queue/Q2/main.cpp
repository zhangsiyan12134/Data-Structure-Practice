// File: circularqueue.cpp
// This program implements a circular queue of integers
//Name: Siyan Zhang         B00815329

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class queue{
private:
    int max;           // maximum size of the queue
    int count;         // number of items in the queue
    int start;         // data[start] is the first entry in the queue
    int end;           // data[end-1] is the last entry in the queue
    vector<int> data;  // vector holding the queue of items

public:
    queue(int sz);                   // constructor, max = sz

    void put(int item);              // put the integer item onto the queue
    int get(void);                   // get an item at the head of the queue
    void write(ostream &out) const;  // send the data stored to out
    bool empty(void) const;          // check for empty queue
    bool full(void) const;           // check for full queue
};

int main(void)
{
    queue myqueue(5);
    ofstream fout ("queueout.txt");
    char ch;
    int x;

    while(1) {
        // print a little menu
        cout << "\n\np = put \n";
        cout << "g = get\n";
        cout << "s = print to screen\n";
        cout << "f = print to file\n";
        cout << "q = quit\n\n";

        cin >> ch;

        if (ch == 'p') {
            cout <<"\ndata to put :";
            cin >> x;
            if(myqueue.full()) {
                cout << "queue is full" << endl;
            } else {
                myqueue.put(x);
            }
        } else if(ch == 'g') {
            if(myqueue.empty()) {
                cout << "queue is empty" << endl;
            } else {
                x = myqueue.get();
                cout << "\n\ndata gotten : " << x;
            }

        } else if(ch == 's') {
            myqueue.write(cout);
        }else if(ch == 'f') {
            myqueue.write(fout);
        }else if(ch == 'q') {
            break;
        }
    }

   fout.close();
   return 0;
}

queue::queue(int sz) : data(sz)
{
    max = sz;
    count = 0;           // the queue has no entries yet
    start = 0;
    end = 0;
}

void queue::put(int item)
{
	data[end] = item;
	count++;
	end++;
	if(end == max)
    {
        end = 0;
    }
}
int queue::get(void)
{
	int tmp = 0;
	tmp = data[start];
	start++;
	if(start == max)
	{
		start = 0;
	}
	count--;
	return tmp;
}
void queue::write(ostream &out) const
{
	for(int i = 0; i < count; i++)
	{
		if(start+i >= max)
		{
			out << data[i-max+start] << ' ';
		} else
		{
			out << data[i+start] << ' ';
		}
	}
	out << endl;
}

bool queue::empty(void) const
{
    return (count == 0);
}

bool queue::full(void) const
{
    return (count == max);
}
