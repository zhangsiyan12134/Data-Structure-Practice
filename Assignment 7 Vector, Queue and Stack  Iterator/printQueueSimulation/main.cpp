/* File: printQueueSimulation.cpp Simulation of a printer queue
Print jobs arrive at a printer for processing. The jobs require varying 
amounts of processing time and only one job can be processed at a given 
time. When a job is being processed arriving jobs must wait in a queue.
				-----+--+--+--+
 					 |  |  |  | 
arriving jobs --->   |  |  |  | --> finished jobs depart 
					 |  |  |  | 
				-----+--+--+--+ 
				queue of jobs
We can think of the job at the front of the queue as the one currenly being
processed.

Print jobs have an arrival time and a finish time (integers)

Time is discrete, t = 1, 2, 3, ..., n

There is a queue of jobs called waiting_jobs 
There is a vector of completed jobs called completed_jobs 
There is a vector integers called queue_length which records the length of 
the queue at each time t

At each time t:

step 1: a job arrives with probability p 
		the job’s start time is set to t and 
		the job is pushed into the queue waiting_jobs
		
step 2: if waiting_jobs is not empty a job is popped with probability q 
		the popped job’s finish time is set to t and 
		the popped job is appended to the vector completed_jobs.
		
step 3: the queue size is appended to the vector queue_length

After n time steps: 
		the vector of completed_jobs is printed 
		the average queue length is printed. 
*/

#include <iostream> 
#include <iomanip> 
#include <queue> 
#include <vector> 
#include <cstdlib> 

using namespace std;

class job 
{ 
	private: 
		int arrive; // arrival time 
		int finish; // finish time
	public: 
		void set_arrive(int a); // set arrival time
		void set_finish(int f); // set finish time 
		void write(ostream& out); // write to out
};
/* returns true if a randomly chosen floating point number between 0 and 1 
	is less than prob. The probability of this is exactly prob */ 
	
bool bernoulli(float prob);

int main(void) 
{ 
	int t; // time 
	int n = 50; // number of time steps to simulate 
	float p = 0.4; // probability of the arrival of a job 
	float q = 0.5; // probability that a job being processed is finished
	srand(777666); // seed the random number generator
	job* ptr; // jobs are created dynamically when they arrive
	// declare the queue and vectors
	queue<job> waiting_jobs;
	vector<job> completed_jobs;
	vector<int> queue_length;
	
	for(t = 1; t <= n; t++) 
	{
	// step 1: job arrives with probability p
		if(bernoulli(p))
		{
			ptr = new job;
			ptr->set_arrive(t);
			waiting_jobs.push(*ptr);
		}
	// step 2: job being processed finishes with probability q
		if(!waiting_jobs.empty())
		{
			if(bernoulli(q))
			{
				job temp;
				temp = waiting_jobs.front();
				temp.set_finish(t);
				waiting_jobs.pop();
				completed_jobs.push_back(temp);
			}
		}
	//step 3: record queue size
		queue_length.push_back(waiting_jobs.size());
	}
	// print the entries in completed_jobs
	for(int i = 0; i < completed_jobs.size(); i++)
	{
		completed_jobs[i].write(cout);
	}
	
	cout << endl << endl;
	// compute and print the average queue length
	float average = 0.0; 
	for(int i = 0; i < queue_length.size(); i++)
	{
		average += queue_length[i];
	}
	cout << "Average queue size is: " << (average/queue_length.size());
	
	return 0;
}

void job::set_arrive(int a) 
{
	arrive = a;
}
void job::set_finish(int f) 
{ 
	finish = f; 
}
void job::write(ostream& out) 
{ 
	out << "arrive "<< setw(4) << arrive << " finish "<< setw(4); 
	out << finish << endl; 
}
/* returns true if a randomly chosen floating point number between 0 and 1
 is less than prob. The probability of this is exactly prob */ 
bool bernoulli(float prob) 
{ 
	float x = (float) rand() / (float) RAND_MAX; 
	return (x < prob); 
}

