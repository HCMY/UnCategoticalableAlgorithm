#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int arr[10][10];
}rand_arr;

rand_arr retArr(){

    rand_arr result;
    srand((unsigned)time(NULL));
    int row, col;
    for(row=0;row<10;row++){
    	for(col=0;col<10;col++){
    		int number = rand()%100;
    		result.arr[row][col]=number;
    	}
    }

    return result;
}

int main(int argc, const char* argv[]) {
    rand_arr result = retArr();
    int row, col;
    for(row=0; row<10; row++){
        for(col=0;col<10;col++)
            printf("%d ",result.arr[row][col]);
        printf("\n");
    }
    return 0;
}
