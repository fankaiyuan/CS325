#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;
int vecSum(vector<int> vect){
	int count = 0;
	for (int i = 0; i < vect.size(); i++)
		count += vect[i];
	return count;
}
void changeslow(vector<int> inVec, vector<int> &outVec,int target){
	int totalCoins = target;
	int numSum = 0;
	for (int i = 0; i < inVec.size(); i++){
		if (inVec[i] == target){
			outVec[i]=1;
			return;
		}
	}

	for (int i = 1; i <= target/2; i++){
		vector<int> subVec(outVec.size(), 0);
		vector<int> subVec2(outVec.size(), 0);
		changeslow(inVec, subVec, target - i);
		changeslow(inVec, subVec2, i);

		for (int j = 0; j < subVec.size(); j++){
			subVec[j] += subVec2[j];
		}
		numSum = vecSum(subVec);
		if (numSum <= totalCoins){
			totalCoins = numSum;
			outVec = subVec;
		}
		subVec.clear();
		subVec2.clear();
	}
}

int changegreedy(int inArray[], int outArray[], int &target, int &length) {
   int i = length - 1;
   int numCoin;
   int totalCoins = 0;

   while(i >= 0) {
      if (inArray[i] <= target) {
         numCoin = (target / inArray[i]);
         outArray[i] = numCoin;
         target -= (numCoin * inArray[i]);
         totalCoins += numCoin;
      }
      else
         outArray[i] = 0;
      i--;
   }
   return totalCoins;
}

void printArr(int inArray[], int outArray[], int numCoins, int length, ofstream *outFile) {
   *outFile << "Algorithm changegreedy:"<<endl;
   for (int i = 0; i < length; i++)
      *outFile << inArray[i] << " ";
   *outFile << endl;
   for (int i = 0; i < length; i++)
      *outFile << outArray[i] << " ";
   *outFile << endl << numCoins << endl << endl;
}
void printVec(vector<int> inVec,vector<int> outVec, int length, ofstream *outFile)
{
    *outFile << "Algorithm changeslow:" << endl;
	for (int i = 0; i < length; i++)
		*outFile << inVec[i]<< " ";
    *outFile<<endl;
    for (int i = 0; i < length; i++)
        *outFile << outVec[i]<< " ";
    *outFile<<endl;
    *outFile<<vecSum(outVec)<<endl;

}

int main() {
   string line, strAmt;
   int count, num, intAmt;
   int inArr[100], outArr[100];
   vector<int> inVec;
   ifstream inFile;
   ofstream outFile;
   inFile.open("coins.txt");
   outFile.open("coinschange.txt");
   while (!inFile.eof()) {
      while (getline(inFile, line)) {
         istringstream ss(line);
         count = 0;

         while (ss >> num) {
            inArr[count] = num;
            inVec.push_back(num);
            count++;
         }
         vector<int> outVec(inVec.size(), 0);
         getline(inFile, strAmt);
         intAmt = atoi(strAmt.c_str());

         changeslow(inVec,outVec,intAmt);
         printVec(inVec,outVec,count,&outFile);

         int numCoins = changegreedy(inArr, outArr, intAmt, count);
         printArr(inArr,outArr,numCoins,count,&outFile);
      }
   }
   inFile.close();
   outFile.close();
}
