#include <stdio.h>

void findMinMax(int arr[], int start, int end, int *min, int *max) {
    if (start == end) {
        *min = *max = arr[start];
        return;
    }

    int mid = (start + end) / 2;

    int leftMin, leftMax, rightMin, rightMax;
    findMinMax(arr, start, mid, &leftMin, &leftMax);
    findMinMax(arr, mid + 1, end, &rightMin, &rightMax);

    *min = (leftMin < rightMin) ? leftMin : rightMin;
    *max = (leftMax > rightMax) ? leftMax : rightMax;
}

int main() {
    int arr[] = {3, 8, 1, 5, 12, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    int min, max;
    findMinMax(arr, 0, n - 1, &min, &max);

    printf("Minimum element: %d\n", min);
    printf("Maximum element: %d\n", max);

    return 0;
}

