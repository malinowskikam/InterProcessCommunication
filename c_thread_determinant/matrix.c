#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct matrix_data
{
    int size;
    double** data;
} matrix;

typedef struct args1
{
    double* results;
    matrix* m;
    int i;
} t_laplace_args;

double determinant(matrix *m);
matrix* laplace_element(matrix* m,int x,int y);
double laplace_determinant(matrix *m);

double determinant(matrix *m)
{
    if(m->size==1)
    {
        return m->data[0][0];
    }
    else if(m->size==2)
    {
        return m->data[0][0]*m->data[1][1] - m->data[1][0]*m->data[0][1];
    }
    else if(m->size==3)
    {
        return m->data[0][0] * m->data[1][1] * m->data[2][2] +
            m->data[0][1] * m->data[1][2] * m->data[2][0] +
            m->data[0][2] * m->data[1][0] * m->data[2][1] -
            m->data[0][2] * m->data[1][1] * m->data[2][0] -
            m->data[0][0] * m->data[1][2] * m->data[2][1] -
            m->data[0][1] * m->data[1][0] * m->data[2][2]; // metoda sarrusa
    }
    else if(m->size>3)
    {
        return laplace_determinant(m);
    }
    else
    {
        printf("Invalid matrix of size %d", m->size);
        exit(1);
    }
}

matrix* laplace_element(matrix* m,int x,int y)
{
    int new_matrix_size = m->size-1;
    matrix* result = (matrix*)malloc(sizeof(struct matrix_data));
    double** data = (double**)malloc(sizeof(double*)*new_matrix_size);
    for(int i=0;i<new_matrix_size;i++)
    {
        data[i] = (double*)malloc(sizeof(double)*new_matrix_size);
    }

    result->size=new_matrix_size;
    result->data=data;

    for(int i=0;i<m->size;i++)
        for(int j=0;j<m->size;j++)
            if(i!=x && j!= y) 
            {
                int new_i,new_j;
                if(i<x)
                    new_i=i;
                else
                    new_i=i-1;

                if(j<y)
                    new_j=j;
                else
                    new_j=j-1;

                result->data[new_i][new_j] = m->data[i][j];
            }

    return result;
}

double laplace_determinant(matrix *m)
{
    double sum = 0;
    for(int i=0;i<m->size;i++)
    {
        double value = m->data[0][i]*determinant(laplace_element(m,0,i));
        if(i%2==1)
            value *=-1.0;

        sum += value;
    }

    return sum;
}