#include <stdio.h>

// Function to perform binary search
int binarySearch(int arr[], int low, int high, int target) {
    if (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if the target is present at the middle
        if (arr[mid] == target)
            return mid;

        // If target is smaller than the middle element, search in the left subarray
        if (arr[mid] > target)
            return binarySearch(arr, low, mid - 1, target);

        // If target is larger than the middle element, search in the right subarray
        return binarySearch(arr, mid + 1, high, target);
    }

    // If the target is not present in the array
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    int result = binarySearch(arr, 0, n - 1, target);

    if (result == -1)
        printf("Element %d is not present in the array.\n", target);
    else
        printf("Element %d is present at index %d.\n", target, result);

    return 0;
}

