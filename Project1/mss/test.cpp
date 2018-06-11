#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <time.h>
#include <cstdlib>
#define SIZE_OF_TEST_ARRAY 172000
using namespace std;

struct subArr
{
    int* subA;
    int sum;
    int len;
};

void clearArr(int* subA, int n)
{
    fill(subA, subA+n, 0);
}

void copyArr(int* subA, int* maxSubA, int n)
{
    clearArr(maxSubA, n);
    for (int i = 0; i < n; i++)
        maxSubA[i] = subA[i];
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

struct subArr  Linear_time(int* a, int n, int* subA, int* maxSubA)
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
    for (int i = 1; i < n; i++){
        if(subA[i-1]>0){
            subA[i]=subA[i-1]+a[i];
        }//now the max value in SubA is the maxSum
        else{
            first=i;
        }
    }
    for(int j = 0;j < n; j++){
        if(subA[j]>maxSum){
            maxSum=subA[j];
            last=j+1;
        }
    }

    maxLength=last-first;
    for (int k =0; k<maxLength;k++){
        maxSubA[k]=a[k+first];
    }
    sub.sum = maxSum;
    sub.subA = maxSubA;
    sub.len = maxLength;
    return sub;
}

int main(int argc, char** argv)
{
    int a[SIZE_OF_TEST_ARRAY], subA[SIZE_OF_TEST_ARRAY], maxSubA[SIZE_OF_TEST_ARRAY];
    subArr ret1,ret2,ret4;
	srand(time(NULL));
    for (int i = 0; i < SIZE_OF_TEST_ARRAY; i++){
            int randRange = rand() % (2000)-1000;
			a[i] = randRange;
    }
    //ret = enumeration(a, count, subA, maxSubA);
    clock_t begin = clock();
    //ret2 = Better_enumeration(a,SIZE_OF_TEST_ARRAY, subA, maxSubA);SIZE_OF_TEST_ARRAY
    ret4 = Linear_time(a,SIZE_OF_TEST_ARRAY , subA, maxSubA);
    clock_t end = clock();
    double elapsed_secs = double(end - begin);
    printf("elapsed time:%f\n",elapsed_secs );
    //ret4 = Linear_time(a, count, subA, maxSubA);

}
