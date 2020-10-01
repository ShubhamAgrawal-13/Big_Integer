#include<bits/stdc++.h>
using namespace std;
#include "biginteger.h"

#define MAX 10000
#define ll long long

int main(int argc, char *argv[]){
	string n1, n2;
	if(argc<3){
		cout<<"Pass Two Numbers in command line arguments\n";
		return 0;
	}
	n1 = string(argv[1]);
	n2 = string(argv[2]);
	BigInteger b1(n1);
	BigInteger b2(n2);
	cout<<"Number 1 : "<<b1;
	cout<<"Number 2 : "<<b2;
	cout<<"\n\n";
	cout<<"Addition : "<<b1 + b2 ;
	cout<<"Subtraction : "<<b1 - b2;
	cout<<"Multiplication : "<<b1 * b2;
	try{
		cout<<"Division : ";
		cout << b1 / b2;
	}
	catch(const char *msg){
		cout<<msg<<endl;
	}

	// string str;
	// cout<<"Division by inbuilt function : ";
	// str = "echo ";
	// str += n1;
	// str += '/';
	// str+= n2;
	// str += " | bc";
	// cout<<str<<" : \n";
	// const char *command = str.c_str();
	// system(command);

	try{
		cout<<"Modulo : ";
		cout << b1 % b2;
	}
	catch(const char *msg){
		cout<<msg<<endl;
	}
	// cout<<"Modulo by inbuilt function : ";
	// str = "echo ";
	// str += n1;
	// str += '%';
	// str+= n2;
	// str += " | bc";
	// cout<<str<<" : \n";
	// const char *command1 = str.c_str();
	// system(command1);
	cout<<"\n";
	cout<<"GCD: " << gcd(b1, b2);
	cout<<"Factorial : "<< factorial(b1);
	cout<<"Power : "<< fastpower(b1, b2);
	// cout<<"GCD by : ";
	string str;
	str = "python3 verify.py ";
	str += n1;
	str += ' ';
	str+= n2;
	// cout<<str<<" : \n";
	const char *command2 = str.c_str();
	system(command2);
	// cout<<b1;
	// b1.print();
	// b2.print();
	return 0;
}