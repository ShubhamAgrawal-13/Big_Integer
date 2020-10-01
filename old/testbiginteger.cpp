#include<iostream>
#include "bigInteger.h"
using namespace std;
int main()
{
	cout<<"Task 1 : Implementation of BigInteger\n";
	string s1,s2;
	cin>>s1>>s2;
	bigInteger bn1(s1);
	bigInteger bn2(s2);
	bigInteger bn3;


	cout<<"Equality : ";
	if(equalto(bn1,bn2))
		cout<<"Equal\n";
	else
		cout<<"Not Equal\n";


	cout<<"Addition : ";
	bn3=bn1+bn2;
	bn3.printnumber();

	cout<<"Subtraction : ";
	bn3=bn1-bn2;
	bn3.printnumber();

	cout<<"Multiplication : ";
	bn3=bn1*bn2;
	bn3.printnumber();

	cout<<"Division by 2 : ";
	bn3 = bn1.divideby2();
	bn3.printnumber();

	cout<<"factorial of first number : ";
	bn3 = factorial(bn1);
	bn3.printnumber();

	cout<<"GCD of first and second : ";
	bn3 = gcd(bn1,bn2);
	bn3.printnumber();

	cout<<"Power first to the power second : ";
	bn3 = fastpower(bn1,bn2);
	bn3.printnumber();

	// try{
	// bn3=bn1/bn2;
	// bn3.printnumber();
	// }
	// catch(const char* msg)
	// {
	// 	cout<<msg<<endl;
	// }
	return 0;
}


