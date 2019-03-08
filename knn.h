#ifndef KNN_H
#define KNN_H
using namespace std;
double* knn(vector<int> refs[], vector<int> queries[], int m, int n, int d);
double* parallel_knn(vector<int> refs[], vector<int> queries[], int m, int n, int d);
#endif
