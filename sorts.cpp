#include <stdio.h>
#define NUM_THREADS 8
#define STOP_C 9999

using namespace std;

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int distances[], int dist_index[], int low, int high) {
	int piv = distances[high];
	int i = low-1;
	for (int j = low; j <= high-1; j++) {
		if (distances[j]<=piv) {
			i++;
			swap(&distances[i], &distances[j]);
			swap(&dist_index[i], &dist_index[j]);
		}
	}
	swap(&distances[i+1], &distances[high]);
	swap(&dist_index[i+1], &dist_index[high]);
	return i+1;
}

void q_sort (int distances[], int dist_index[], int low, int high) {
	if (low < high) {
		int piv = partition(distances, dist_index	, low, high);
		q_sort(distances, dist_index, low, piv-1);
		q_sort(distances, dist_index, piv+1, high);
	}
}

void parallel_q_sort (int distances[], int dist_index[], int low, int high) {
	int piv;	
	if (low < high) {	
		piv = partition(distances, dist_index, low, high);				
		#pragma omp parallel sections
		{
			#pragma omp section						
			q_sort(distances, dist_index, low, piv-1);
			#pragma omp section
			q_sort(distances, dist_index, piv+1, high);		
		}
	}
}

void bubble_sort(int distances[], int m) 
{
	int i, j; 
	for (i = 0; i < m-1; i++) {          
		for (j = 0; j < m-i-1; j++) {  
			if (distances[j+1] < distances[j]) { 
				swap(&distances[j], &distances[j+1]);
			} 
		}
	} 
}

void parallel_bubble_sort(int distances[], int m) 
{ 
	int i, j; 
	for (i = 0; i < m-1; i++) {          
		for (j = 0; j < m-i-1; j++) { 
			if (distances[j+1] < distances[j]) { 
				swap(&distances[j], &distances[j+1]);
			} 
		}
	}
}

void selection_sort(int distances[], int m) 
{ 
	int i, j, min; 
	for (i = 0; i < m-1; i++) 
	{  
		min=i;
		for (j = i+1; j < m; j++) { 
			if (distances[j] < distances[min]) { 
				min = j;  
			}
		}
		swap(&distances[i], &distances[min]); 
	} 
}

void parallel_selection_sort(int distances[], int m) 
{
	int i, j, min; 
	for (i = 0; i < m-1; i++) 
	{  
		min=i;
		for (j = i+1; j < m; j++) { 
			if (distances[j] < distances[min]) { 
				min = j;  
			}
		}
		swap(&distances[i], &distances[min]); 
	}
}

void sort(int distances[], int dist_index[], int m, bool parallel, bool quick, bool bubble, bool selection) {
	if (parallel) {
		if (quick) {
			parallel_q_sort(distances, dist_index, 0, m-1);
			return;
		}
		if (bubble) {
			parallel_bubble_sort(distances, m);
			return;
		}
		if (selection) {
			parallel_selection_sort(distances, m);
			return;
		}
	} else {
		if (quick) {
			q_sort(distances, dist_index, 0, m-1);
			return;
		}
		if (bubble) {
			bubble_sort(distances, m);
			return;
		}
		if (selection) {
			selection_sort(distances, m);
			return;
		}
	}
}
