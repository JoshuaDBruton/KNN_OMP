#include <stdio.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include "knn.h"
#include "utils.h"
#define TARGET 1500
#define STEP_SIZE 100
#define MAX 10000
#define TEST_NUM 1

using namespace std;

void generate_refs(vector<int> refs[], int m, int d) {
	for (int i=0; i < m; i=i+1) {
		for (int j=0; j < d; j=j+1) {
			refs[i].push_back(rand()%(MAX+1));
		}
	}
}

void generate_queries(vector<int> queries[], int n, int d) {
	for (int i=0; i < n; i=i+1) {
		for (int j=0; j < d; j=j+1) {
			queries[i].push_back(rand()%(MAX+1));
		}
	}
}

int main(int argc, char *argv[]) {
	double times[TEST_NUM], dists[TEST_NUM], sorts[TEST_NUM];
	double start;

	for (int m=100000, n=1300, d=8; n<=TARGET; n+=STEP_SIZE) {
		// Generating data set
		vector<int> refs[m], queries[n];
		generate_refs(refs, m, d);	
		generate_queries(queries, n, d);
		
		printf("%d/%d\n", n, TARGET);
		/*
		for (int i=0; i<TEST_NUM; i++) {
			double *serial_times;		
			start=omp_get_wtime();
			serial_times = knn(refs, queries, m, n, d);		
			dists[i]=serial_times[0];
			sorts[i]=serial_times[1];
			times[i]=omp_get_wtime()-start;
			delete serial_times;
		}
		writeResultsToFile(false, m, n, d, mean(times, TEST_NUM), mean(dists, TEST_NUM), mean(sorts, TEST_NUM));
		*/
		for (int i=0; i<TEST_NUM; i++) {
			double *par_times;		
			start=omp_get_wtime();
			par_times = parallel_knn(refs, queries, m, n, d);		
			dists[i]=par_times[0];
			sorts[i]=par_times[1];
			times[i]=omp_get_wtime()-start;
			delete par_times;
		}
		writeResultsToFile(true, m, n, d, mean(times, TEST_NUM), mean(dists, TEST_NUM), mean(sorts, TEST_NUM));
	}
}
