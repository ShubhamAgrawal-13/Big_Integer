#include<iostream>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;

#define MAX 10000
#define ll long long

class bigInteger
{
	string number;
	int size=0;
	int sign=0;
	public:
		bigInteger()
		{
		}
		bigInteger(ll n)
		{
			int j=0;
			if(n<0)
			{
				sign=1;
				n=-n;
			}
			while(n!=0)
			{
				number+=n%10+48;
				n/=10;
			}
			if(n==0)
			{
				number="0";
			}
			size=number.size();
		}
		bigInteger(string s)
		{
			reverse(s.begin(),s.end());
			number=s;
			size=s.size();
			if(number=="")
			{
				number="0";
				size=1;
			}
		}
		void printnumber()
		{
			if(sign==1 && number!="0")
				cout<<"-";
			int i=size-1;
			if(number=="")
				cout<<"0";
			for(;i>=0;i--)
				cout<<number[i];
			cout<<endl;
		}
		bigInteger operator+(bigInteger);
		bigInteger operator-(bigInteger);
		bigInteger operator*(bigInteger);
		bigInteger operator/(bigInteger);
		bigInteger operator%(bigInteger);
		bigInteger divideby2();
		friend int equalto(bigInteger,bigInteger);
		friend int lessthan(bigInteger,bigInteger);
		friend int greaterthan(bigInteger,bigInteger);
		friend int lessthanequalto(bigInteger,bigInteger);
		friend int greaterthanequalto(bigInteger,bigInteger);
		friend bigInteger fastpower(bigInteger,bigInteger);
		friend bigInteger gcd(bigInteger,bigInteger);
		friend bigInteger factorial(bigInteger);
};

bigInteger bigInteger::operator+(bigInteger num2)
{
	bigInteger num3;
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

bigInteger bigInteger::operator-(bigInteger num2)
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
	bigInteger num3;
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
		bigInteger num4("1");
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

bigInteger bigInteger::operator*(bigInteger num2)
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
	bigInteger num3(s);
	num3.size=s.size();
	return num3;
}


bigInteger bigInteger::operator/(bigInteger num2)
{
	bigInteger zero("0");
	bigInteger one("1");
	bigInteger n_one("-1");
	bigInteger num1=*this;
	if(equalto(num2,zero))
		throw "Can't divide by zero";
	if(equalto(num2,one))
		return num1;
	if(equalto(num1,one) && !equalto(num2,one))
		return zero;
	if(equalto(num1,zero))
		return zero;
	if(equalto(num1,num2))
		return one;
	if(lessthan(num1,num2))
		return zero;
	
	//cout<<"hello\n";
	string q="";
	bigInteger tempd(num1.number.substr(num2.size-1,num2.size));
	int i=1;
	tempd.printnumber();
	if(lessthan(tempd,num2))
	{
		tempd.number=num1.number[i]+tempd.number;		
		i++;
		//cout<<"hello";
	}
	tempd.printnumber();
	while(greaterthanequalto(tempd,num2) && i<=(num1.size-num2.size))
	{
		tempd.printnumber();
		bigInteger temp("0");
		int j=1;
		while(lessthanequalto(temp,tempd))
		{
			bigInteger nn(j);
			temp=temp*nn;
			j++;
		}
		j--;
		q+=j+48;
		tempd=tempd-temp;
		tempd.number=num1.number[i+num1.size-num2.size]+tempd.number;
		i++;
		tempd.printnumber();	
	}
	bigInteger quo(q);
	quo.size=q.size();
	return quo;
}

int equalto(bigInteger num1,bigInteger num2)
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


int greaterthan(bigInteger num1,bigInteger num2)
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

int greaterthanequalto(bigInteger num1,bigInteger num2)
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


int lessthan(bigInteger num1,bigInteger num2)
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




int lessthanequalto(bigInteger num1,bigInteger num2)
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


bigInteger bigInteger::divideby2()
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
	bigInteger x(s);
	return x;
}


bigInteger fastpower(bigInteger b,bigInteger e)
{
	bigInteger zero("0");
	bigInteger one("1");
	if(equalto(zero,e))
		return one;
	if(equalto(one,e))
		return b;
	bigInteger temp = fastpower(b,e.divideby2());
	temp=temp*temp;
	if(e.number[0]%2==0)
		return temp;
	else
	{
		return (temp*b);
	}
}


bigInteger gcd(bigInteger a,bigInteger b)
{
	bigInteger one("1");
	if(equalto(a,one))
		return one;
	if(equalto(b,one))
		return one;
	if(equalto(a,b))
		return a;
	
	while(!equalto(a,b))
	{
		if(greaterthan(a,b))
			a=a-b;
		else
			b=b-a;
	}
	
	return a;
}

bigInteger factorial(bigInteger num)
{
	bigInteger fact("1");
	bigInteger one("1");
	bigInteger zero("0");
	if(equalto(num,zero))
		return zero;
	while(!equalto(num,one))
	{
		fact=fact*num;
		//fact.printnumber();
		num=num-one;
		//num.printnumber();
	}
	return fact;
}
