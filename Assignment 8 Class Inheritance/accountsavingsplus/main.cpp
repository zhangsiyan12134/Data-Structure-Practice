/* File: accountsavingsplus.cpp
   Shows how to derive classes */

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


class savingsaccountplus :public savingsaccount {
private:
    float minimumbalance;  

public:
    savingsaccountplus(string name, float fee, float rate, float minbal);
    bool withdraw(float amount);
    void write(ostream &out);
};


int main(void)
{
    savingsaccount s("joe", 0.50, 0.02);
    chequingaccount c("bob", 0.50, 2);
    savingsaccountplus t("jill", 0.50, 0.02, 1000.00);
    s.deposit(1200.00);
    c.deposit(1200.00);
    t.deposit(1200.00);

    cout << "savings account: \n";
    s.write(cout);
    cout << "\nchequing account: \n";
    c.write(cout);
    cout << "\nsavings account plus: \n";
    t.write(cout);
   
    s.withdraw(100.00);
    s.withdraw(200.00);
    s.withdraw(100.00);
    s.addinterest();

    cout << "\nsavings account: \n";
    s.write(cout);

    c.withdraw(100.00);
    c.withdraw(200.00);
    c.withdraw(100.00);

    cout << "\nchequing account: \n";
    c.write(cout);

    t.withdraw(100.00);
    t.withdraw(200.00);
    t.withdraw(100.00);
    t.addinterest();

    cout << "\nsavings account plus: \n";
    t.write(cout);

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

///////////////// implementation of savingsaccountplus ///////////////////////
savingsaccountplus::savingsaccountplus(string name, float fee, float rate, float minbal):savingsaccount(name, fee, rate)
{
	minimumbalance = minbal;
}
bool savingsaccountplus::withdraw(float amount)
{
	bool result;
	if(balance >= amount)
	{
		if(balance > minimumbalance)
		{
			balance = balance - amount;
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
void savingsaccountplus::write(ostream &out)
{
	savingsaccount::write(out);
	out << "minimum balance: " << minimumbalance << endl;
}

