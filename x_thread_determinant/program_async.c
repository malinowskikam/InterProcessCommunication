#define _REENTRANT

#include<stdio.h>
#include<pthread.h>
#include<string.h>

#include"matrix_async.c"

int main(int argc, char** argv)
{
    int matrix_size;

    printf("Enter matrix size: ");
    scanf("%d", &matrix_size);

    printf("Enter %d elements separated with spaces:\n",matrix_size*matrix_size);
    double** data = (double**)malloc(sizeof(double*)*matrix_size);
    for(int i=0;i<matrix_size;i++)
    {
        data[i] = (double*)malloc(sizeof(double)*matrix_size);
    }
    
    fflush(stdin);
    for(int i=0;i<matrix_size;i++)
        for(int j=0;j<matrix_size;j++)
            scanf("%lf", *(data +i) + j);
    
    matrix m;
    m.data = data;
    m.size = matrix_size;

    printf("Matrix:\n");
    for(int i=0;i<m.size;i++)
    {
        for(int j=0;j<m.size;j++)
            printf("%lf  ",m.data[i][j]);
        printf("\n");
    }

    printf("determinant: %lf\n",determinant_async(&m));

    return 0;
}