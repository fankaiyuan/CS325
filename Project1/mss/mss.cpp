#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
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
    int a[1024], subA[100], maxSubA[100];
    int count;
    int subArrCount = 0;
    int num;
    string line;
    ifstream inFile;
    ofstream outFile;
    subArr ret,ret2,ret4;

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
            //int start_s=clock();
            ret = enumeration(a, count, subA, maxSubA);
            //int stop_s=clock();
            //cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
            //int start_s=clock();
            ret2 = Better_enumeration(a,count, subA, maxSubA);
            //int stop_s=clock();
            //cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
            //int start_s=clock();
            ret4 = Linear_time(a, count, subA, maxSubA);
            //int stop_s=clock();
            //cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
            outFile << "Results of Algorithm 1: Enumeration:"<<endl;
            for (int i = 0; i < count; i++)
                outFile << a[i] << " ";
            outFile << endl;
            for (int i = 0; i < ret.len; i++)
                outFile << ret.subA[i] << " ";
            outFile << endl;
            outFile << ret.sum << endl << endl;

            outFile << "Results of Algorithm 2: Better Enumeration:"<<endl;
            for (int i = 0; i < count; i++)
                outFile << a[i] << " ";
            outFile << endl;
            for (int i = 0; i < ret2.len; i++)
                outFile << ret2.subA[i] << " ";
            outFile << endl;
            outFile << ret2.sum << endl << endl;

            outFile << "Results of Algorithm 4: Linear_time:"<<endl;
            for (int i = 0; i < count; i++)
                outFile << a[i] << " ";
            outFile << endl;
            for (int i = 0; i < ret4.len; i++)
                outFile << ret4.subA[i] << " ";
            outFile << endl;
            outFile << ret4.sum << endl << endl;

        }
    }
    inFile.close();
    outFile.close();
}
