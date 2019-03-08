#include <stdio.h>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <omp.h>
#include "sorts.h"
#include "utils.h"
#define QUICK true
#define BUBBLE false
#define SELECTION false

using namespace std;

void calculate_distance(int distances[], vector<int> query, vector<int> refs[], int m, int d) {
	#pragma omp parallel for	
	for (int i=0; i<m;i++) {
		distances[i]=parallel_euclid_distance(query, refs[i], d);
	}
}

double* knn(vector<int> refs[], vector<int> query[], int m, int n, int d) {
	int distances[m];
	int dist_index[m];
	for (int i=0; i<m; i++) {
		dist_index[i] = i;
	}
	double start_dist, start_sort;
	double dist_time, sort_time;
	double *times;
	int i, j;
	times = new double[2];

	for (i=0; i<n; i=i+1) {
		for (j=0; j<m; j=j+1) {
			start_dist = omp_get_wtime();
			distances[j]=euclid_distance(query[i], refs[j], d);
			dist_time += (omp_get_wtime() - start_dist);

			if (j == m-1) {				
				start_sort = omp_get_wtime();				
				sort(distances, dist_index, m, false, QUICK, BUBBLE, SELECTION);
				sort_time += (omp_get_wtime() - start_sort);
				//writeSolutionToFile(dist_index, refs, m, d, false);
			}	
		}
	}
	times[0] = dist_time;
	times[1] = sort_time;
	return times;	
}

double* parallel_knn(vector<int> refs[], vector<int> query[], int m, int n, int d) {
	int distances[m];
	int dist_index[m];
	for (int i=0; i<m; i++) {
		dist_index[i] = i;
	}
	double start_dist, start_sort;
	double dist_time, sort_time;
	double *times;
	int i, j;
	times = new double[2];
	for (i=0; i<n; i=i+1) {
		start_dist = omp_get_wtime();
		calculate_distance(distances, query[i], refs, m, d);
		dist_time += (omp_get_wtime() - start_dist);
		start_sort = omp_get_wtime();				
		sort(distances, dist_index, m, true, QUICK, BUBBLE, SELECTION);
		sort_time += (omp_get_wtime() - start_sort);
		//writeSolutionToFile(dist_index, refs, m, d, true);
	}
	times[0] = dist_time;
	times[1] = sort_time;
	return times;	
}
