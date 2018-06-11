#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <limits.h>
#include <time.h>

using namespace std;

struct City {
	int id;
	int x;
	int y;
	bool marked;
	int* dist;
};

int findDistance(City n, City m) {
	return round(sqrt(pow(n.x - m.x, 2) + pow(n.y - m.y, 2)));
}

int findTotalDistance(City* cities, int cityIndex) {
	int sum = 0;
	for (int i = 0; i < cityIndex - 1; i++)
		sum += findDistance(cities[i], cities[i + 1]);
	return sum;
}

void fillDistArr(City* cities, int cityIndex) {
	for (int i = 0; i < cityIndex; i++) {
		cities[i].dist = new int[cityIndex];
		for (int j = 0; j < cityIndex; j++) {
			cities[i].dist[j] = findDistance(cities[i], cities[j]);
		}
	}
}

void copyTour(City* oldTour, City* newTour, int cityIndex) {
	for (int i = 0; i < cityIndex; i++)
		newTour[i] = oldTour[i];
}

void greedyNeighbor(City* cities, int cityIndex) {
	int currentCity = 0;
	int nextCity;
	int visitedCities = 0;
	City* tour = new City[cityIndex];

	for (int i = 0; i < cityIndex; i++)
		cities[i].marked = false;

	tour[0] = cities[0];
	visitedCities++;

	while (visitedCities < cityIndex) {
		cities[currentCity].marked = true;
		int minDistance = INT_MAX;
		for (int i = 0; i < cityIndex; i++) {
			if (cities[i].marked == false) {
				if (cities[currentCity].dist[i] < minDistance) {
					minDistance = cities[currentCity].dist[i];
					nextCity = i;
				}
			}
		}
		tour[visitedCities] = cities[nextCity];
		visitedCities++;
		currentCity = nextCity;
	}
	copyTour(tour, cities, cityIndex);
	delete[] tour;
}

void twoOptSwap(int i, int j, int cityIndex, City* tour, City* tempTour) {
	int count = 0;

	for (int a = 0; a <= i - 1; ++a)
		tempTour[a] = tour[a];
	for (int a = i; a <= j; ++a) {
		tempTour[a] = tour[j - count];
		count++;
	}
	for (int a = j + 1; a < cityIndex; ++a)
		tempTour[a] = tour[a];
}

int twoOpt(City* cities, int cityIndex) {
	int optomize = 0;
	int bestDistance;
	time_t end;
	end = time(NULL) + 180;

	bestDistance = findTotalDistance(cities, cityIndex);

	for (int i = 0; i < cityIndex - 1; i++) {
		if (time(NULL) > end)
			break;
		for (int j = i + 1; j < cityIndex; j++) {
			if (time(NULL) > end)
				break;
			City* tempTour = new City[cityIndex];
			twoOptSwap(i, j, cityIndex, cities, tempTour);

			int tempDistance = findTotalDistance(tempTour, cityIndex);

			if (tempDistance < bestDistance) {
				optomize = 0;
				bestDistance = tempDistance;
				copyTour(tempTour, cities, cityIndex);
			}
			delete[] tempTour;
		}
	}

	return bestDistance;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "usage: " << argv[0] << "<filename>\n";
		return 1;
	}
	ifstream inputFile(argv[1]);
	ofstream outputFile;
	string line;
	int cityIndex = 0;
	int minDist = 0;

	if (inputFile) {
		while (getline(inputFile, line))
			cityIndex++;

		inputFile.clear();
		inputFile.seekg(0, ios::beg);

		City* cities = new City[cityIndex];

		cityIndex = 0;
		while (getline(inputFile, line)) {
			istringstream ss(line);
			ss >> cities[cityIndex].id;
			ss >> cities[cityIndex].x;
			ss >> cities[cityIndex].y;
			cityIndex++;
		}


		fillDistArr(cities, cityIndex);
		greedyNeighbor(cities, cityIndex);
		int minDist = twoOpt(cities, cityIndex);

		string name = ".tour";
		string filename = argv[1] + name;

		outputFile.open(filename.c_str());
		outputFile << minDist << endl;
		for (int i = 0; i < cityIndex; i++)
			outputFile << cities[i].id << endl;
		delete[] cities;
	}
	else {
		cout << "Cannot read file.\n";
		return 1;
	}
}