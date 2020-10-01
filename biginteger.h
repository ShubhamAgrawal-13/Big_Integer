#include<bits/stdc++.h>
using namespace std;

#define MAX 10000
#define ll long long

#define deb(x) cout << #x << "=" << x << endl

class BigInteger{
	string number;
	int size=0;
	int sign=0;

public:
	BigInteger(){
		// number="0";
		// size=1;
	}
	BigInteger(ll n){
		int j=0;

		if(n==0){
			number="0";
			size=1;
		}
		else{
			if(n<0){
				sign=1;
				n=-n;
			}

			while(n!=0){
				number.push_back((char)(n%10+48));
				n/=10;
			}

			size=number.size();
		}

	}

	BigInteger(string s){
		reverse(s.begin(),s.end());
		number=s;
		size=s.size();
		if(number=="")
		{
			number="0";
			size=1;
		}
	}


	void print(){
		if(sign==1 && number!="0")
			cout<<"-";
		int i=size-1;
		if(number=="")
			cout<<"0";
		for(;i>=0;i--)
			cout<<number[i];
		cout<<endl;
	}

	friend ostream &operator<<( ostream &output, const BigInteger &b ) { 
		if(b.sign==1 && b.number!="0")
			output<<"-";

		int i=b.size-1;

		if(b.number=="")
			output<<"0";

		for(;i>=0;i--)
			output<<b.number[i];

		output<<endl;
		
        return output;            
    }

    friend istream &operator>>( istream  &input, BigInteger &b ) { 
        input >> b.number;
        if(b.number[0]=='-'){
        	b.sign = 1;
        	b.number = b.number.substr(1, b.number.size()-1);
        }
        reverse(b.number.begin(), b.number.end());
        b.size = b.number.size();
        return input;            
    }

	BigInteger operator+(BigInteger);
	BigInteger operator-(BigInteger);
	BigInteger operator*(BigInteger);
	BigInteger operator/(BigInteger);
	BigInteger operator%(BigInteger);
	BigInteger operator=(BigInteger);
	BigInteger divideby2();

	friend int equalto(BigInteger, BigInteger);
	friend int lessthan(BigInteger, BigInteger);
	friend int greaterthan(BigInteger, BigInteger);
	friend int lessthanequalto(BigInteger, BigInteger);
	friend int greaterthanequalto(BigInteger, BigInteger);
	friend pair<BigInteger, BigInteger> divide(BigInteger, BigInteger);
	friend BigInteger fastpower(BigInteger, BigInteger);
	friend BigInteger gcd(BigInteger, BigInteger);
	friend BigInteger factorial(BigInteger);


};

BigInteger BigInteger::operator=(BigInteger num2){
	number.clear();
	number = num2.number;
	size = num2.size;
	sign = num2.sign;
	return *this;
}

BigInteger BigInteger::operator+(BigInteger num2)
{
	BigInteger num3;
	int sum=0,carry=0;
	int maxsize=(size>num2.size)?size:num2.size;
	
	if(size>num2.size)
	{
		int y = maxsize-num2.size;
		while(y--)
		{
			num2.number+='0';
		}
		num2.size=num2.number.size();
	}
	else
	{
		int y = maxsize-size;
		while(y--)
		{
			number+='0';
		}
		size=number.size();		
	}
	for(int i=0;i<maxsize;i++)
	{
		sum=number[i]-48+num2.number[i]-48+carry;
		carry=sum/10;
		num3.number+=sum%10+48;
	}
	
	if(carry==0)
		num3.size=maxsize;
	else
	{
		num3.number+=carry+48;
		num3.size=maxsize+1;
	}
	return num3;
}


BigInteger BigInteger::operator-(BigInteger num2)
{
	int maxsize=(size>num2.size)?size:num2.size;
	
	if(size>num2.size)
	{
		int y = maxsize-num2.size;
		while(y--)
		{
			num2.number+='0';
		}
		num2.size=num2.number.size();
	}
	else
	{
		int y = maxsize-size;
		while(y--)
		{
			number+='0';
		}
		size=number.size();		
	}
	//printnumber();
	for(int i=0;i<maxsize;i++)
	{
		num2.number[i]=48+9-num2.number[i]+48;
	}
	//num2.printnumber();
	BigInteger num3;
	int sum=0,carry=0;
	for(int i=0;i<maxsize;i++)
	{
		sum=number[i]-48+num2.number[i]-48+carry;
		carry=sum/10;
		num3.number+=sum%10+48;
	}
	//num3.printnumber();
	num3.size=maxsize;
	if(carry==1)
	{
		BigInteger num4("1");
		num3=num3+num4;	
	}
	else
	{
		for(int i=0;i<maxsize;i++)
		{
			num3.number[i]=48+9-num3.number[i]+48;
		}
		num3.sign=1;	
	}
	int z = num3.size-1;
	while(num3.number[z]=='0')
	{
		z--;
	}
	num3.size=z+1;
	num3.number=num3.number.substr(0,z+1);
	if(num3.number=="")
	{
		num3.number="0";
		num3.size=1;
	}
	return num3;	
}

BigInteger BigInteger::operator*(BigInteger num2)
{
	vector<int> v(size+num2.size,0);
	int p=0,q=0;
	for(int i=0;i<size;i++)
	{
		int carry=0;
		int n1=number[i]-48;
		q=0;
		for(int j=0;j<num2.size;j++)
		{
			int n2=num2.number[j]-48;
			int sum = n1*n2 + v[p+q]+carry;
			carry=sum/10;
			v[p+q]=sum%10;
			q++;
		}
		if(carry>0)
			v[p+q]+=carry;
		p++;
	}
	
	int k=v.size()-1;
	while(k>=0 && v[k]==0)
	{
		k--;
		//cout<<k<<" ";
	}
	string s;
	while (k >= 0) 
        	s += std::to_string(v[k--]); 
	BigInteger num3(s);
	num3.size=s.size();
	return num3;
}

string trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

pair<BigInteger, BigInteger> divide(BigInteger num1, BigInteger num2){

	BigInteger zero("0");
	BigInteger one("1");
	BigInteger two("2");
	BigInteger three("3");
	BigInteger four("4");
	BigInteger five("5");
	BigInteger six("6");
	BigInteger seven("7");
	BigInteger eight("8");
	BigInteger nine("9");

	string q;
	reverse(num1.number.begin(), num1.number.end());

	BigInteger temp1;
	temp1.number = "";
	for(int i=0; i<num2.number.size() ; i++){
		temp1.number = num1.number[i] + temp1.number;
	}
	temp1.size = temp1.number.size();
	// cout<<"main";
	//deb(temp1);

	int i=num2.number.size() - 1;
	for(; i<num1.number.size(); ){
		
		if(temp1.size >= num2.size){
			BigInteger tt;
			int t=1;
			for(auto dc : {one, two, three, four, five, six, seven, eight, nine}){
				BigInteger tt2 = num2*dc;
				//deb(tt2);
				if(! greaterthanequalto(temp1, tt2)){
					break;
				}

				tt = temp1 - tt2;
				t++;
			}
			t--;
			if(t>=1){
				//deb(t);
				char ch = t + 48;
				q+=ch;
				temp1 = tt;
				//deb(ch);
				//deb(q);
				//deb(tt);
				i++;
				//deb(i);
				if(!equalto(temp1, zero)){
					temp1.number = num1.number[i] + temp1.number;
				}
				else{
					//cout<<"hii you got it";
					temp1.sign=0;
					temp1.number="";
					if(i<num1.number.size())
						temp1.number += num1.number[i];
					else
						temp1.number="0";
				}

				temp1.size = temp1.number.size();
				//deb(temp1);
			}else{
				q+='0';
				i++;
				//deb(i);
				if(i<num1.number.size()){
			   		temp1.number = num1.number[i] + temp1.number;
			   		temp1.size = temp1.number.size();
				}
				//deb(temp1);
			}
		}
		else{
			q+='0';
			i++;
			if(i<num1.number.size()){
		   		temp1.number = num1.number[i] + temp1.number;
		   		temp1.size = temp1.number.size();
			}
			//deb(temp1);
		}
		//deb(temp1);
	}	

	//deb(temp1);
	// deb(temp1.number.size());
	// const char *carr = temp1.number.c_str();
	// cout<<carr;
	// cout << strlen(carr);
	// deb(temp1.size);
	// deb(temp1.sign);

	int k=0;
	while (k<q.size() && q[k]=='0'){
		k++;
	}
	q = q.substr(k, q.size()-k);


	string r=temp1.number;
	string t="";
	k=r.size()-1;
	while (k>=0 && r[k]=='0'){
		k--;
	}

	//01112  21110
	for(int i=k; i>=0; i--){
		t+=r[i]; 
	}
	// q = trim(q);
	// t = trim(t);
	int len = t.size()-1;
	if(t[len] != '0' && t[len] != '1' && t[len] != '2' && t[len] != '3' && t[len] != '4' && t[len] != '5' && t[len] != '6' && t[len] != '7' && t[len] != '8' && t[len] != '9'){
		t = t.substr(0,t.size()-1);
	}
	
	BigInteger ques(q);
	BigInteger rem(t);
	return {ques, rem};
}

BigInteger BigInteger::operator/(BigInteger num2){

	// BigInteger n_one("-1");
	BigInteger zero("0");
	BigInteger one("1");
	BigInteger num1=*this;

	if(equalto(num1,zero)){
		if(!equalto(num2,zero))
			return zero;
		else
			throw "Not defined\n";
	}

	if(equalto(num2,zero))
		throw "Can't divide by zero\n";
	if(equalto(num2,one))
		return num1;

	if(equalto(num1,num2))
		return one;

	if(greaterthanequalto(num1,num2)){
		pair<BigInteger, BigInteger> pdm = divide(num1, num2);
		return pdm.first;
	}
	return zero;
}

BigInteger BigInteger::operator%(BigInteger num2){
	// BigInteger n_one("-1");
	BigInteger zero("0");
	BigInteger one("1");
	BigInteger num1=*this;

	if(equalto(num1,zero)){
		if(!equalto(num2,zero))
			return zero;
		else
			throw "Not defined\n";
	}

	if(equalto(num2,zero))
		throw "Can't take modulo by zero\n";

	if(equalto(num2,one))
		return zero;

	if(equalto(num1,num2))
		return zero;

	if(greaterthanequalto(num1,num2)){
		pair<BigInteger, BigInteger> pdm = divide(num1, num2);
		return pdm.second;
	}

	return num1;
}

int equalto(BigInteger num1,BigInteger num2)
{
	
	int maxsize=(num1.size>num2.size)?num1.size:num2.size;
	
	if(num1.size>num2.size)
	{
		int y = maxsize-num2.size;
		while(y--)
		{
			num2.number+='0';
		}
		num2.size=num2.number.size();
	}
	else
	{
		int y = maxsize-num1.size;
		while(y--)
		{
			num1.number+='0';
		}
		num1.size=num1.number.size();		
	}
	for(int i=0;i<maxsize;i++)
	{
		    if (num1.number[i]!=num2.number[i])
		    {
			    return 0;
		    }
	}
	return 1;
}


int greaterthan(BigInteger num1,BigInteger num2)
{
	
	int maxsize=(num1.size>num2.size)?num1.size:num2.size;
	
	if(num1.size>num2.size)
	{
		int y = maxsize-num2.size;
		while(y--)
		{
			num2.number+='0';
		}
		num2.size=num2.number.size();
	}
	else
	{
		int y = maxsize-num1.size;
		while(y--)
		{
			num1.number+='0';
		}
		num1.size=num1.number.size();		
	}
	for(int i=maxsize-1;i>=0;i--)
	{
		    if (num1.number[i]>num2.number[i])
		    {
			    return 1;
		    }
		    if (num1.number[i]<num2.number[i])
		    {
			    return 0;
		    }
	}
	return 0;
}

int greaterthanequalto(BigInteger num1,BigInteger num2)
{
	
	int maxsize=(num1.size>num2.size)?num1.size:num2.size;
	
	if(num1.size>num2.size)
	{
		int y = maxsize-num2.size;
		while(y--)
		{
			num2.number+='0';
		}
		num2.size=num2.number.size();
	}
	else
	{
		int y = maxsize-num1.size;
		while(y--)
		{
			num1.number+='0';
		}
		num1.size=num1.number.size();		
	}
	for(int i=maxsize-1;i>=0;i--)
	{
		    if (num1.number[i]>num2.number[i])
		    {
			    return 1;
		    }
		    if (num1.number[i]<num2.number[i])
		    {
			    return 0;
		    }
	}
	return 1;
}


int lessthan(BigInteger num1,BigInteger num2)
{
	
	int maxsize=(num1.size>num2.size)?num1.size:num2.size;
	
	if(num1.size>num2.size)
	{
		int y = maxsize-num2.size;
		while(y--)
		{
			num2.number+='0';
		}
		num2.size=num2.number.size();
	}
	else
	{
		int y = maxsize-num1.size;
		while(y--)
		{
			num1.number+='0';
		}
		num1.size=num1.number.size();		
	}
	for(int i=maxsize-1;i>=0;i--)
	{
		    if (num1.number[i]<num2.number[i])
		    {
			    return 1;
		    }
		    if (num1.number[i]>num2.number[i])
		    {
			    return 0;
		    }
	}
	return 0;
}




int lessthanequalto(BigInteger num1,BigInteger num2)
{
	
	int maxsize=(num1.size>num2.size)?num1.size:num2.size;
	
	if(num1.size>num2.size)
	{
		int y = maxsize-num2.size;
		while(y--)
		{
			num2.number+='0';
		}
		num2.size=num2.number.size();
	}
	else
	{
		int y = maxsize-num1.size;
		while(y--)
		{
			num1.number+='0';
		}
		num1.size=num1.number.size();		
	}
	for(int i=maxsize-1;i>=0;i--)
	{
		    if (num1.number[i]<num2.number[i])
		    {
			    return 1;
		    }
		    if (num1.number[i]>num2.number[i])
		    {
			    return 0;
		    }
	}
	return 1;
}


BigInteger BigInteger::divideby2()
{	
	int sum=number[size-1]-48;
	int i=size-1;
	
	string s;
	while(sum<2)
	{	
		i--;
		sum=sum*10+number[i]-48;
	}
	for(;i>=0;)
	{
		s+=(sum/2)+48;
		//cout<<sum/2<<endl;
		sum=(sum%2)*10+number[--i]-48;
	}
	BigInteger x(s);
	return x;
}


BigInteger fastpower(BigInteger b,BigInteger e)
{
	BigInteger zero("0");
	BigInteger one("1");
	if(equalto(zero,e))
		return one;
	if(equalto(one,e))
		return b;
	BigInteger temp = fastpower(b,e.divideby2());
	temp=temp*temp;
	if(e.number[0]%2==0)
		return temp;
	else
	{
		return (temp*b);
	}
}


BigInteger gcd(BigInteger a, BigInteger b){
	BigInteger zero("0");
	BigInteger one("1");

	// if(equalto(a,one))
	// 	return one;
	// if(equalto(b,one))
	// 	return one;
	// if(equalto(a,b))
	// 	return a;
	
	// while(!equalto(a,b))
	// {
	// 	if(greaterthan(a,b))
	// 		a=a-b;
	// 	else
	// 		b=b-a;
	// }
	// return a;

	// deb(a);
	// deb(b);
	// cout<<" -----------" <<endl;

	int cnt=0;
	BigInteger temp;
	while(!equalto(b, zero)){
		// cout<<"a:\n";
		// cout<<a.number<<endl;
		// cout<<a.sign<<endl;
		// cout<<a.size<<endl;
		// cout<<"b:\n";
		// cout<<b.number<<endl;
		// cout<<b.sign<<endl;
		// cout<<b.size<<endl;
	    temp = a % b;
	 //    cout<<"temp:\n";
	 //    cout<<temp;
	 //    for(int i=0;i <temp.number.size();i++ ){
	 //    	cout<<temp.number[i]<<" ---- "<<endl;
	 //    }
		// cout<<temp.number.size()<<endl;
		// cout<<temp.sign<<endl;
		// cout<<temp.size<<endl;
		a = b;
		b = temp;
		// cout<<a;
		// cout<<b;
		// cnt++;
		// if(cnt==5)
		// 	break;
	}

	return a;
	// if(equalto(b, zero))
	// 	return a;

	// BigInteger temp = a % b;
	// deb(temp);
	// deb(b);
	// return temp;
	// return gcd(b, temp);
	
}

BigInteger factorial(BigInteger num)
{
	BigInteger fact("1");
	BigInteger one("1");
	BigInteger zero("0");
	if(equalto(num,zero))
		return one;
	while(!equalto(num,one))
	{
		fact=fact*num;
		//fact.printnumber();
		num=num-one;
		//num.printnumber();
	}
	return fact;
}


/*

10000100001000010000100001000010000100001000010000100001000
10000100001000010000100001000010000100001000010000100001000

non zero one 
0    0    0
0    0    1
0    1    0
0    1    1

1    0    0
1    0    1
1    1    0
1    1    1


num1 num2
0     0     -> throw not defined
0     1     -> zero
1     0     -> throw 
1     1	    -> one

*/