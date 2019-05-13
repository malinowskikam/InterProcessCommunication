#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

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

matrix* laplace_element_async(matrix* m,int x,int y);
double laplace_determinant_async(matrix *m);
double determinant_async(matrix *m);
void* thread_laplace(t_laplace_args *args);


double determinant_async(matrix *m)
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
        return laplace_determinant_async(m);
    }
    else
    {
        printf("Invalid matrix of size %d", m->size);
        exit(1);
    }
}

double laplace_determinant_async(matrix *m)
{
    double* results = (double*)malloc(sizeof(double)*m->size);
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t)*m->size);
    
    double sum = 0;

    for(int i=0;i<m->size;i++)
    {
        t_laplace_args* args = (t_laplace_args*)malloc(sizeof(struct args1));
        args->m=m;
        args->results=results;
        args->i=i;
        pthread_create(&(threads[i]),NULL,(void*)thread_laplace,args);
    }

    for(int i=0;i<m->size;i++)
    {
        pthread_join(threads[i],NULL);
    }

    for(int i=0;i<m->size;i++)
    {
        sum+=results[i];
    }
    
    return sum;
}

matrix* laplace_element_async(matrix* m,int x,int y)
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

void* thread_laplace(t_laplace_args *args) //wątek
{   
    matrix* m = args->m;

    double value = m->data[0][args->i]*determinant_async(laplace_element_async(m,0,args->i));
    if(args->i%2==1)
        value *=-1.0;

    args->results[args->i]=value;
    
}