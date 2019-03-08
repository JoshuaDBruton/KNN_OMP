#ifndef UTILS_H
#define UTILS_H
using namespace std;
void printArray(int arr[], int m);
double mean (double arr[], int n);
void writeSolutionToFile (int arr[], vector<int> refs[], int m, int d, bool parallel);
void writeResultsToFile (bool parallel, int m, int n, int d, double total_time, double dist_time, double sort_time);
bool validate();
int man_distance(vector<int> a, vector<int> b, int d);
int parallel_man_distance(vector<int> a, vector<int> b, int d);
double euclid_distance(vector<int> a, vector<int> b, int d);
double parallel_euclid_distance(vector<int> a, vector<int> b, int d);
#endif
