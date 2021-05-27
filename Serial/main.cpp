// C++ program to demonstrate working of Guassian Elimination
// method
#include<bits/stdc++.h>
#include <time.h>
using namespace std;

#define N 500

void backSub(double mat[N][N+1]);
int forwardElim(double mat[N][N+1]);
    time_t start, finish;
    double duration;

void gaussianElimination(double mat[N][N+1])
{
    /* reduction into r.e.f. */
    int singular_flag = forwardElim(mat);

    /* if matrix is singular */
    if (singular_flag != -1)
    {
        printf("Singular Matrix.\n");

        /* if the RHS of equation corresponding to
           zero row  is 0, * system has infinitely
           many solutions, else inconsistent*/
        if (mat[singular_flag][N])
            printf("Inconsistent System.");
        else
            printf("May have infinitely many "
                   "solutions.");

        return;
    }
        // The execution of Gauss algorithm
    start = clock();
    backSub(mat);
    finish = clock();
    duration = (finish-start)/double(CLOCKS_PER_SEC);
    // Printing the execution time of Gauss method
    printf("\n Time of execution: %f\n", duration);

}

void swap_row(double mat[N][N+1], int i, int j)
{
    for (int k=0; k<=N; k++)
    {
        double temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

// function to reduce matrix to r.e.f.
int forwardElim(double mat[N][N+1])
{
    for (int k=0; k<N; k++)
    {
        // Initialize maximum value and index for pivot
        int i_max = k;
        int v_max = mat[i_max][k];

        /* find greater amplitude for pivot if any */
        for (int i = k+1; i < N; i++)
            if (abs(mat[i][k]) > v_max)
                v_max = mat[i][k], i_max = i;

        /* if a prinicipal diagonal element  is zero,
         * it denotes that matrix is singular, and
         * will lead to a division-by-zero later. */
        if (!mat[k][i_max])
            return k; // Matrix is singular

        /* Swap the greatest value row with current row */
        if (i_max != k)
            swap_row(mat, k, i_max);


        for (int i=k+1; i<N; i++)
        {
            /* factor f to set current row kth element to 0,
             * and subsequently remaining kth column to 0 */
            double f = mat[i][k]/mat[k][k];

            /* subtract fth multiple of corresponding kth
               row element*/
            for (int j=k+1; j<=N; j++)
                mat[i][j] -= mat[k][j]*f;

            /* filling lower triangular matrix with zeros*/
            mat[i][k] = 0;
        }

        //print(mat);        //for matrix state
    }
    //print(mat);            //for matrix state
    return -1;
}

void print(double mat[N][N+1])
{
    for (int i=0; i<N; i++, printf("\n"))
        for (int j=0; j<=N; j++)
            printf("%lf ", mat[i][j]);

    printf("\n");
}

void backSub(double mat[N][N+1])
{
    double x[N];
    for (int i = N-1; i >= 0; i--)
    {
        x[i] = mat[i][N];
        for (int j=i+1; j<N; j++)
        {
            x[i] -= mat[i][j]*x[j];
        }
        x[i] = x[i]/mat[i][i];
    }

    for (int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    printf("\nSolution for the system:\n");
    for (int i=0; i<N; i++)
        printf("%lf\n", x[i]);
}

int main()
{
    /* input matrix */

    /*
    double mat[N][N+1] = {{1.0, -1.0,0.0, 0.0, 160.0},
                          {0.0, 1.0,-1.0, 0.0, -40.0},
                          {0.0, 0.0,1.0, -1.0, 210.0},
                          {1.0, 0.0,0.0, 1.0, -330.0}
                         };*/


    double mat[N][N+1];
    for (int i=0; i<N; i++){
        for(int j=0; j<N+1; j++){
            mat[i][j] = rand()/double(1000);
        }
    }

    print(mat);
    gaussianElimination(mat);
    cout << endl;
    return 0;
}
