#include "points_segments.h"

int **segs;
int plen;

int *sorted;

typedef struct Point{
    int pos;
    int index;
}Point;

int comparator(const void *p, const void *q){
    Point x = *(const Point *)p;
    Point y = *(const Point *)q;

    int countx = 0;
    int county = 0;

    for(int i = 0; i < plen; i++){
        if(segs[i][0] < x.pos && x.pos < segs[i][1]){
            countx++;
        }
    }

    for(int i = 0; i < plen; i++){
        if(segs[i][0] < y.pos && y.pos < segs[i][1]){
            county++;
        }
    }

    sorted[x.index] = countx;
    sorted[y.index] = county;

    if(county < countx){
        return -1;
    }
    else if(county > countx){
        return 1;
    }
    else{
        return 0;
    }
}


// I was still a bit sick while writing this. Pardon the use of globals.
// points_segments_divide - runs in O(n log n) time, worst case O(n^2).
// The actual value of the sort doesn't matter, just how many times it runs.
// No memory is leaked due to use of globals.
int *points_segments_divide(int **segments, int *points, int s, int p){
    segs = segments;
    plen = s;
    Point *sortee = malloc(sizeof(Point)*p);
    for(int i = 0; i < p; i++){
        sortee[i].index = i;
        sortee[i].pos = points[i];
        //printf("[%d] ", sortee[i]);
    }
    sorted = malloc(sizeof(int)*p);
    qsort(sortee, p, sizeof(Point), comparator);
    free(sortee);
    return sorted;
}

/*int main(){
    int val[] = {1, 3, 3, 4, 5};

    int *z = points_segments_divide(val, 5);
    printf("\n");
    for(int i = 0; i < 5; i++){
        printf("[%d] ", z[i]);
    }

    return 0;
}*/