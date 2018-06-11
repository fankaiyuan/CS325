#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include <time.h>
//#include <chrono>
//#include <thread>
//#include <climits>
//#include <ctime>


using namespace std;

struct subArr
{
	int* subA;
	int sum;
	int len;
};

void clearArr(int* subA, int n)
{
	fill(subA, subA + n, 0);
}

void copyArr(int* subA, int* maxSubA, int n)
{
	clearArr(maxSubA, n);
	for (int i = 0; i < n; i++)
		maxSubA[i] = subA[i];
}

struct subArr recombineSubArrs(struct subArr leftSubArr, struct subArr rightSubArr,int rhsBegIndex,int lhsEndIndex,int sumRhsArr,int sumLhsArr)
{
	subArr combinedArr;
	combinedArr.subA = leftSubArr.subA;
	combinedArr.len = (lhsEndIndex - rhsBegIndex) + 1;
	combinedArr.sum = sumRhsArr + sumLhsArr;
	return combinedArr;
}

struct subArr maxSum(struct subArr a, struct subArr b)
{
	if (a.sum >= b.sum) { return a; }
	else { return b; }
}

struct subArr enumeration(int* a, int n, int* subA, int* maxSubA)
{
	subArr sub;
	int sum;
	int maxSum = 0;
	int aLength;
	int maxLength;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			sum = 0;
			aLength = 0;
			clearArr(subA, n);
			for (int k = i; k <= j; k++)
			{
				subA[aLength] = a[k];
				sum += a[k];
				aLength++;
			}
			if (sum > maxSum)
			{
				maxSum = sum;
				maxLength = aLength;
				copyArr(subA, maxSubA, maxLength);
			}
		}
	}
	sub.sum = maxSum;
	sub.subA = maxSubA;
	sub.len = maxLength;
	return sub;
}

struct subArr Better_enumeration(int* a, int n, int* subA, int* maxSubA)
{
	subArr sub;
	int sum;
	int maxSum = 0;
	int aLength;
	int maxLength;
	for (int i = 0; i < n; i++)
	{
		sum = 0;
		aLength = 0;
		clearArr(subA, n);
		for (int j = i; j < n; j++)
		{
			subA[aLength] = a[j];
			sum += a[j];
			aLength++;
			if (sum > maxSum)
			{
				maxSum = sum;
				maxLength = aLength;
				copyArr(subA, maxSubA, maxLength);
			}
		}
	}
	sub.sum = maxSum;
	sub.subA = maxSubA;
	sub.len = maxLength;
	return sub;
}

struct subArr Linear_time(int* a, int n, int* subA, int* maxSubA)
{
 subArr sub;
 int sum;
 int maxSum = a[0];
 int aLength;
 int maxLength;
 int first = 0;
 int last;
 clearArr(subA, n);
 copyArr(a, subA, n);//subA is a clone of array a
 for (int i = 1; i < n; i++) {
 if (subA[i - 1]>0) {
 subA[i] = subA[i - 1] + a[i];
 }//now the max value in SubA is the maxSum
 else {
 first = i;
 }
 }
 for (int j = 0; j < n; j++) {
 if (subA[j]>maxSum) {
 maxSum = subA[j];
 last = j + 1;
 }
 }
 if (last <= first){
 first = 0;
 }
 maxLength = last - first;
 for (int k = 0; k<maxLength; k++) {
 maxSubA[k] = a[k + first];
 }
 sub.sum = maxSum;
 sub.subA = maxSubA;
 sub.len = maxLength;
 return sub;
}


struct subArr divideAndConquer(int* a, int n)
{
	subArr sub;
	sub.subA = a;
	sub.len = n;
	if (n == 1)
	{
		sub.sum = *(sub.subA);
		return sub;
	}
	//base case
	subArr lhs_subArr = divideAndConquer(sub.subA, sub.len / 2);
	subArr rhs_subArr = divideAndConquer((sub.subA) + (sub.len / 2), sub.len - (sub.len / 2));
	//divides the array into lhsArr[0...n/2] and rhsArr[(n/2 + 1...n] recursively
	int lhs_sumTemp = -2147483648;
	int rhs_sumTemp = -2147483648;
	//set temp sums to most negative integer so we can evalue an all negative integer array (not required for assignment)
	int lhs_lenTemp, rhs_lenTemp;
	//set temp length to keep track of how long each max subarray is, so we dont have to change the original subarray length 
	int lhs_begIndex, rhs_endIndex,sumToRhsEnd,sumToLhsBeg;
	//set up temp index and sums for rhs and lhs subarrays so we can combine them later and test to see if the
	//combination of lhs and rhs subarrays is the maximum subarray

	int sum_subArr = 0;
	for (int i = (sub.len / 2); i < sub.len; i++)
	{
		sum_subArr += *(sub.subA + i);
		if (sum_subArr > rhs_sumTemp)
		{
			rhs_sumTemp = sum_subArr;
			rhs_lenTemp = (i + 1) - (sub.len / 2);
			rhs_endIndex = i;
			sumToRhsEnd = sum_subArr;
		}

	}
	//the rhs subarray is now the maximum subarray
	if (rhs_subArr.sum < rhs_sumTemp)
	{
		rhs_subArr.sum = rhs_sumTemp;
		rhs_subArr.len = rhs_lenTemp;
	}
	//set the len and sum of the rhs subarray to the len and sum of the max subarray that we found.  

	
	sum_subArr = 0;
	for (int i = (sub.len / 2) - 1; i >= 0; i--)
	{
		sum_subArr += *(sub.subA + i);
		if (sum_subArr > lhs_sumTemp)
		{
			lhs_sumTemp = sum_subArr;
			lhs_lenTemp = (sub.len / 2) - i;
			lhs_begIndex = i;
			sumToLhsBeg = sum_subArr;

		}
	}
	//the lhs subarray is now the max subarray
	if (lhs_subArr.sum < lhs_sumTemp)
	{
		lhs_subArr.sum = lhs_sumTemp;
		lhs_subArr.len = lhs_lenTemp;
	}
	//set the len and sum of the lhs subarray to the len and sum of the max subarray that we found
	return maxSum(maxSum(lhs_subArr, rhs_subArr), recombineSubArrs(lhs_subArr, rhs_subArr,lhs_begIndex,rhs_endIndex,sumToRhsEnd,sumToLhsBeg));
	//the maximum subarray is chosen from the list: lhs subarray, rhs subarray, the subarray starting with beg index of the max lhs subarray 
	//and the end index of the max rhs subarray
}

int main(int argc, char** argv)
{
int a[1024], subA[100], maxSubA[100];
int count;
int subArrCount = 0;
int num;
string line;
ifstream inFile;
ofstream outFile;
subArr ret, ret2,ret3, ret4;

inFile.open("MSS_Problems.txt");
outFile.open("MSS_Results.txt");
while (!inFile.eof())
{
	
	while (getline(inFile, line))
	{
		istringstream ss(line);
		count = 0;
		while (ss >> num)
		{
			a[count] = num;
			count++;
		}
		ret = enumeration(a, count, subA, maxSubA);
		ret2 = Better_enumeration(a, count, subA, maxSubA);
		ret3 = divideAndConquer(a, count);
		ret4 = Linear_time(a, count, subA, maxSubA);
		outFile << "Results of Algorithm 1: Enumeration:" << endl;
		for (int i = 0; i < count; i++)
		{
			outFile << a[i] << " ";
		}
		outFile << endl;
		for (int i = 0; i < ret.len; i++)
		{
			outFile << ret.subA[i] << " ";
		}
		outFile << endl;
		outFile << ret.sum << endl << endl;
		
		outFile << "Results of Algorithm 2: Better Enumeration:" << endl;
		for (int i = 0; i < count; i++)
		{
			outFile << a[i] << " ";
		}
		outFile << endl;
		for (int i = 0; i < ret2.len; i++)
		{
			outFile << ret2.subA[i] << " ";
		}
		outFile << endl;
		outFile << ret2.sum << endl << endl;

		outFile << "Results of Algorithm 3: Divide and Conquer:" << endl;
		for (int i = 0; i < count; i++)
		{
			outFile << a[i] << " ";
		}
		outFile << endl;
		for (int i = 0; i < ret2.len; i++)
		{
			outFile << ret3.subA[i] << " ";
		}
		outFile << endl;
		outFile << ret3.sum << endl << endl;
		
		outFile << "Results of Algorithm 4: Linear_time:" << endl;
		for (int i = 0; i < count; i++)
		{
			outFile << a[i] << " ";
		}
		outFile << endl;
		for (int i = 0; i < ret4.len; i++)
		{
			outFile << ret4.subA[i] << " ";
		}
		outFile << endl;
		outFile << ret4.sum << endl << endl;
	}
}
	inFile.close();
	outFile.close();
}

