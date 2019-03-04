#include "points_segments.h"

// Points_Segments_Naive - runs in O(N^2) seconds. Iterates over the
// array and places each one into its proper position.
int *points_segments_naive(int **segments, int *points, int s, int p){
    int *seg = malloc(sizeof(int) * p);
    for(int i = 0; i < p; i++){
        int x = 0;
        for(int j = 0; j < s; j++){
            if(segments[j][0] < points[i] && points[i] < segments[j][1]){
                x++;
            }
        }
       seg[i] = x;
    }
    return seg;
}