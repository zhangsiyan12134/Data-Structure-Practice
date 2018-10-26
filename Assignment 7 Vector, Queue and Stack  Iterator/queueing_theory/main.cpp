#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

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
	int n = 1000000; // number of time steps to simulate 
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
	/*for(int i = 0; i < completed_jobs.size(); i++)
	{
		completed_jobs[i].write(cout);
	}
	
	cout << endl << endl;
	*/
	// compute and print the average queue length
	float average = 0.0; 
	for(int i = 0; i < queue_length.size(); i++)
	{
		average += queue_length[i];
	}
	
	float r = (p/q)*((1-q)/(1-p));
	
	cout << "Theoretical average queue size is: " << (r/(1-r)) << endl;
	cout << "Simulated average queue size is: " << (average/queue_length.size());
	
	
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
