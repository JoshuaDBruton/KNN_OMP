#include <stdio.h>
#include <vector>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "sorts.h"
#define KNN 3

using namespace std;

double mean (double arr[], int n) {
	double sum;
	for (int i=0; i<n; i++) {
		sum += arr[i];
	}
	return (sum/(double)n);
}

void writeResultsToFile (bool parallel, int m, int n, int d, double total_time, double dist_time, double sort_time) {
	ofstream file;
	if (parallel) {
		file.open("parallel_times.csv", std::fstream::app);
		file << m << "," << n << "," << d << "," << total_time << "," << dist_time << "," << sort_time << "\n";
	}	else {
		file.open("serial_times.csv", std::fstream::app);
		file << m << "," << n << "," << d << "," << total_time << "," << dist_time << "," << sort_time << "\n";
	}
	file.close();
}

void writeSolutionToFile (int indices[], vector<int> refs[], int m, int d, bool parallel) {
	ofstream file;	
	if (parallel) {
		file.open("parallel_sol.txt", std::fstream::app);
		for (int i=0; i<KNN; i++) {
			file << "(";
			for (int j=0; j<d; j++) {
				file << refs[indices[i]].at(j);
				if (j == d-1) {
					file << ")";
				} else {
					file << ",";
				}
			}
		}
		file << "\n";
	} else {
		file.open("serial_sol.txt", std::fstream::app);
		for (int i=0; i<KNN; i++) {
			file << "(";
			for (int j=0; j<d; j++) {
				file << refs[indices[i]].at(j);
				if (j == d-1) {
					file << ")";
				} else {
					file << ",";
				}
			}
		}
		file << "\n";
	}
	file.close();
}

void printArray(int arr[], int m) {
	for (int i=0; i<m; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\n\n");
}

int man_distance(vector<int> a, vector<int> b, int d) {
	int sum = 0;
	for (int i=0; i<d; i++) {
		sum += abs(a.at(i)-b.at(i));
	}
	return sum;
}

int parallel_man_distance(vector<int> a, vector<int> b, int d) {
	int sum = 0;
	#pragma omp parallel for reduction(+:sum)
	for (int i=0; i<d; i++) {
		sum += abs(a.at(i)-b.at(i));
	}
	return sum;
}

double euclid_distance(vector<int> a, vector<int> b, int d) {
	double sum=0.0; 
	for (int i=0; i<d; i++) {
		sum += (a.at(i) -  b.at(i))*(a.at(i) -  b.at(i));
	}
	return sqrt(sum);
}
// Parallelisation of distance formula's is only worth it with large dimensional vector space
double parallel_euclid_distance(vector<int> a, vector<int> b, int d) {
	double sum=0.0; 
	int i;
	for (i=0; i<d; i++) {
		sum += (a.at(i) -  b.at(i))*(a.at(i) -  b.at(i));
	}
	return sqrt(sum);
}
