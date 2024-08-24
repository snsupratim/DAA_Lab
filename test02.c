#include <stdio.h>
#include <limits.h>

void parenthesis(int i, int j, int n, int *s)
{
    if (i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        parenthesis(i, ((s + i * n) + j), n, s);
        parenthesis(((s + i * n) + j) + 1, j, n, s);
        printf(")");
    }
}

void matrixchain(int p[], int n)
{
    int m[n][n];
    int s[n][n];

    for (int i = 1; i < n; i++)
    {
        m[i][i] = 0;
    }

    for (int L = 2; L < n; L++)
    {
        for (int i = 1; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[j] * p[k];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("sca;ar multipliaction:%d", m[1][n - 1]);
    parenthesis(1, n - 1, n, (int *)s);
    printf("\n");
}

int main()
{
    int n;
    printf("enter number of matrice:");
    scanf("%d", &n);

    int arr[n + 1];
    for (int i = 0; i < n; i++)
    {
        printf("%d", &arr[i]);
    }

    matrixchain(arr, n + 1);
    return 0;
}