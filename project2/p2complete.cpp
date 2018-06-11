#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

void clearArray(int inArray[], int length) {
	for (int i = 0; i < length; i++)
		inArray[i] = 0;
}

int vecSum(vector<int> vect) {
	int count = 0;
	for (int i = 0; i < vect.size(); i++)
		count += vect[i];
	return count;
}
void changeslow(vector<int> inVec, vector<int> &outVec, int target) {
	int totalCoins = target;
	int numSum = 0;
	for (int i = 0; i < inVec.size(); i++) {
		if (inVec[i] == target) {
			outVec[i] = 1;
			return;
		}
	}

	for (int i = 1; i <= target / 2; i++) {
		vector<int> subVec(outVec.size(), 0);
		vector<int> subVec2(outVec.size(), 0);
		changeslow(inVec, subVec, target - i);
		changeslow(inVec, subVec2, i);

		for (int j = 0; j < subVec.size(); j++) {
			subVec[j] += subVec2[j];
		}
		numSum = vecSum(subVec);
		if (numSum <= totalCoins) {
			totalCoins = numSum;
			outVec = subVec;
		}
		subVec.clear();
		subVec2.clear();
	}
}

int changegreedy(int inArray[], int outArray[], int &target, int &length) {
	clearArray(outArray, length);
	int i = length - 1;
	int numCoin;
	int totalCoins = 0;

	while (i >= 0) {
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

int changedp(int inArray[], int outArray[], int target, int length) {
	clearArray(outArray, length);
	int min = 0;
	int **tempArr = (int**)malloc(sizeof(int*)*length);

	for (int i = 0; i < length; i++) {
		tempArr[i] = (int*)malloc(sizeof(int)*(target + 1));
		for (int j = 0; j <= target; j++) {
			if (i == 0)
				tempArr[i][j] = j;
			else if (inArray[i] > j)
				tempArr[i][j] = tempArr[i - 1][j];
			else if (tempArr[i - 1][j] < tempArr[i][j - inArray[i]] + 1)
				tempArr[i][j] = tempArr[i - 1][j];
			else
				tempArr[i][j] = tempArr[i][j - inArray[i]] + 1;
		}
	}
	int i = length - 1;
	int j = target;
	while (i >= 0) {
		if (i == 0) {
			outArray[i] = target;
			min += target;
			i--;
		}
		else if (tempArr[i][j] == tempArr[i - 1][j])
			i--;
		else {
			target -= inArray[i];
			min++;
			j -= inArray[i];
			outArray[i]++;
		}
	}

	for (int i = 0; i < length; i++) {
		delete tempArr[i];
	}

	delete tempArr;
	return min;
}

void printArr(int inArray[], int outArray[], int numCoins, int length, ofstream *outFile) {
	for (int i = 0; i < length; i++)
		*outFile << inArray[i] << " ";
	*outFile << endl;
	for (int i = 0; i < length; i++)
		*outFile << outArray[i] << " ";
	*outFile << endl << numCoins << endl << endl;
}
void printVec(vector<int> inVec, vector<int> outVec, int length, ofstream *outFile)
{
	for (int i = 0; i < length; i++)
		*outFile << inVec[i] << " ";
	*outFile << endl;
	for (int i = 0; i < length; i++)
		*outFile << outVec[i] << " ";
	*outFile << endl << vecSum(outVec) << endl << endl;

}

int main() {
	string line, strAmt;
	int count, count2, num, intAmt, intAmt2;
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
			count2 = 0;

			while (ss >> num) {
				inArr[count] = num;
				inVec.push_back(num);
				count++;
				count2++;
			}
			vector<int> outVec(inVec.size(), 0);
			getline(inFile, strAmt);
			intAmt = atoi(strAmt.c_str());
			intAmt2 = intAmt;

			changeslow(inVec, outVec, intAmt);
			outFile << "Algorithm changeslow:" << endl;
			printVec(inVec, outVec, count, &outFile);

			int numCoins = changegreedy(inArr, outArr, intAmt, count);
			outFile << "Algorithm changegreedy:" << endl;
			printArr(inArr, outArr, numCoins, count, &outFile);

			int numCoins2 = changedp(inArr, outArr, intAmt2, count);
			outFile << "Algorithm changedp:" << endl;
			printArr(inArr, outArr, numCoins2, count, &outFile);
		}
	}
	inFile.close();
	outFile.close();
}