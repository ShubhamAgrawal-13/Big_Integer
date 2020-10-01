#!/bin/usr/python3

from sys import argv

def gcd(a, b):
	# print(a, b)
	if(b==0):
		return a
	return gcd(b, a%b)


def fastpower(a, b):
	res=1
	while(b>0):
		if(b&1):
			res = res*a
		a = a*a
		b>>=1
	return res

def factorial(a):
	if(a==0 or a==1):
		return 1
	return a*factorial(a-1)

n1 = int(argv[1])
n2 = int(argv[2])

print()
print("Verifying Results using python : ")
print()
print("Addition : ", n1+n2)
print("Subtraction : ", n1-n2)
print("Multiplication : ", n1*n2)
print("Division : ", n1//n2)
print("Modulo : ", n1%n2)
print()
print("GCD: ", gcd(n1, n2))
print("Factorial: ", factorial(n1))
print("Power: ", fastpower(n1, n2))