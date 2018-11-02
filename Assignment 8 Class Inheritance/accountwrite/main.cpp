/* File: accountwrite.cpp
   Shows how to derive classes*/

#include <iostream>
#include <string>
using namespace std;

class account {
protected:
    string owner;
    float balance;
    float withdrawfee;
   
public:
    account(string name, float fee);
    void write(ostream &out);
    void deposit(float amount); 
    bool withdraw(float amount);
    float getbalance(void);
    float getwithdrawfee(void);
};

class savingsaccount :public account {
private:
    float interestrate;  

public:
    savingsaccount(string name, float fee, float rate);
    void write(ostream &out);
    void addinterest(void);
};

class chequingaccount : public account {
private:
    int remainingfreewithdrawals;  

public:
    chequingaccount(string name, float fee, int numberfree);
    void write(ostream &out);
    bool withdraw(float amount);
};


int main(void)
{
    savingsaccount s("joe", 0.50, 0.02);
    chequingaccount c("bob", 0.50, 2);

    s.deposit(100.);
    c.deposit(100.);

    cout << "savings account: \n";
    s.write(cout);
    cout << "\nchequing account: \n";
    c.write(cout);
   
    s.withdraw(10.);
    s.withdraw(5.);
    s.withdraw(20.0);
    s.addinterest();

    cout << "\nsavings account: \n";
    s.write(cout);

    c.withdraw(10.);
    c.withdraw(5.);
    c.withdraw(20.0);

    cout << "\nchequing account: \n";
    c.write(cout);

   return 0;
}

///////////////////// implementation of account ///////////////////////
account::account(string name, float fee)
{
    owner = name;
    balance = 0;
    withdrawfee = fee;
}

void account::write(ostream &out)
{
    out << "owner: " << owner << "\n";
    out << "balance: " << balance << "\n";
    out << "withdrawfee " << withdrawfee << "\n"; 
}

void account::deposit(float amount)
{
    balance = balance + amount;
}

bool account::withdraw(float amount)
{
    bool result;
    if (amount > balance-withdrawfee) { 
        cout << "Insufficient funds"; 
        result = false;
    } else { 
        balance = balance - amount - withdrawfee;
        result = true;
    }

    return result;
}

float account::getbalance(void)
{
    return balance;
}

float account::getwithdrawfee(void)
{
    return withdrawfee;
}

///////////////////// implementation of savingsaccount ///////////////////////

savingsaccount::savingsaccount(string name, float fee, float rate):account(name, fee)
{
	interestrate = rate;
}
void savingsaccount::write(ostream &out)
{
	account::write(out);
	out << "interest rate: " << interestrate << endl;
}
void savingsaccount::addinterest(void)
{
	balance = (1 + interestrate) * balance;
}

///////////////////// implementation of chequingaccount ///////////////////////
chequingaccount::chequingaccount(string name, float fee, int numberfree):account(name, fee)
{
	remainingfreewithdrawals = numberfree;
}
void chequingaccount::write(ostream &out)
{
	account::write(out);
	out << "remaing free withdrawals: " << remainingfreewithdrawals << endl;
}
bool chequingaccount::withdraw(float amount)
{
	bool result;
	if(balance >= amount)
	{
		if(remainingfreewithdrawals > 0)
		{
			balance = balance - amount;
			remainingfreewithdrawals--;
			result = true;
		} else
		{
			balance = balance - amount - withdrawfee;
			result = true;
		}
	} else
	{
		result = false;
	}
	
	return result;
}


