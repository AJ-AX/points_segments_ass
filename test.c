#include "points_segments.h"

void print_array(int *arr, int size){
	for (int i=0; i<size; i++){
		printf("%d ",arr[i]);	
	}
	printf("\n");
}

void print_array_2D(int **arr, int rows, int cols){
	for (int i=0; i<rows; i++){
		printf("[");
		for (int j=0; j<cols; j++)
			printf("%d ",arr[i][j]);
		printf("] ");
	}
	printf("\n");
}


/*

While these tests show the naive algorithmn having better times, it's important to
note that A) The divide algorithmn has more steps, so it will take more time in smaller amounts
(+B) at first.

and

B) All the samples tested here are relatively small (for a computer). If we tested with a much
larger database (millions of points, etc.) - you would see a marked difference in the runtimes
of the Algorithmns.

*/
int main() {	

	clock_t t;
	double naive_time_used;
	double divide_time_used;
	int count_tests;
	double average_naive = 0;
	double average_divide = 0;

	const char * files[] = {"input1.txt", "input2.txt", "input3.txt"};   

	for (int f=0; f < 3; f++){
		FILE *pfile = fopen(files[f], "r");
		if(pfile == NULL)  {
			printf("Error opening file %s\n", files[f]);
			return 1;
		}
		
		int s, p;
		while(fscanf(pfile, "%d %d", &s, &p)!=EOF){		
		
			//allocate 2D array to hold s segments
			int ** segments = malloc(s*sizeof(int *));
			for (int i=0; i < s; i++){
				segments[i] = malloc(2*sizeof(int));
			}
		
			//scan all segment lines and populate the segments
			for (int i=0; i < s; i++){
				fscanf(pfile, "%d %d", &segments[i][0], &segments[i][1]);
			}		
		
			//allocate a single array to hold p points
			int * points = malloc(p*sizeof(int));
		
			//scan all point coordinates into points array
			for (int i=0; i < p; i++){
				fscanf(pfile, "%d", &points[i]);
			}
			
			printf("There are total %d segments, and %d points\n", s, p);
			
			print_array_2D(segments, s, 2);
			print_array(points, p);
			//TODO: pass s, p, segments, and points to your two algorithms
			//the output should be an array of size p containing 
			//-for each point- the number of covering segments 
			
			//TODO: implement - compare these outputs from 2 algorithms

			t = clock();
			int *z = malloc(sizeof(int) * p);
			z = points_segments_naive(segments, points, s, p);
			print_array(z, p);
			free(z);
			t = clock()-t;
			naive_time_used = ((double)t)/CLOCKS_PER_SEC;
			average_naive += naive_time_used;

			t = clock();
			int *r = points_segments_divide(segments, points, s, p);
			print_array(r, p);
			free(r);
			t = clock()-t;
			divide_time_used = ((double)t)/CLOCKS_PER_SEC;
			average_divide += divide_time_used;

			count_tests++;

			printf("Time Taken by Naive Alg: [%lf]", naive_time_used);
			printf("\nTime Taken by Divide Alg: [%lf]\n\n", divide_time_used);
			
		}
		fclose(pfile);
	}
	printf("\n\nAverage Time Taken by Naive Alg: [%lf]", average_naive/count_tests);
	printf("\nAverage Time Taken by Divide Alg: [%lf]", average_divide/count_tests);
	return 0;
}