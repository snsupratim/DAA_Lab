#include <stdio.h>
#include <limits.h>

// Function to print the optimal parenthesization
void printOptimalParens(int i, int j, int n, int *s)
{
    if (i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        printOptimalParens(i, *((s + i * n) + j), n, s);
        printOptimalParens(*((s + i * n) + j) + 1, j, n, s);
        printf(")");
    }
}

// Function to find the minimum number of scalar multiplications needed
void MatrixChainOrder(int p[], int n)
{
    int m[n][n]; // m[i][j] will store the minimum number of multiplications needed to compute the matrix A[i]A[i+1]...A[j] = A[i..j]
    int s[n][n]; // s[i][j] will store the index of the optimal split point
    int i, j, k, L, q;

    // Cost is zero when multiplying one matrix
    for (i = 1; i < n; i++)
    {
        m[i][i] = 0;
    }

    // L is chain length
    for (L = 2; L < n; L++)
    {
        for (i = 1; i < n - L + 1; i++)
        {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of multiplications is %d\n", m[1][n - 1]);
    printf("Optimal Parenthesization is: ");
    printOptimalParens(1, n - 1, n, (int *)s);
    printf("\n");
}

int main()
{
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int arr[n + 1];
    printf("Enter the dimensions of the matrices:\n");
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }

    MatrixChainOrder(arr, n + 1);

    return 0;
}
