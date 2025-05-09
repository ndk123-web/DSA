import java.util.Arrays;

/**
 * This class implements the Bubble Sort algorithm.
 * It takes an array of integers as input and sorts it in ascending order.
 */
class bubbleSort {

    /**
     * The array of integers to be sorted.
     */
    int arr[];

    /**
     * Constructs a bubbleSort object with the given array of integers.
     */
    public bubbleSort(int[] myInput) {
        this.arr = myInput;
    }

    /**
     * Sorts the array of integers in ascending order using the Bubble Sort algorithm the sorted array of integers.
     */
    public int[] sort() {
        int n = arr.length;

        // Loop through the array n times
        for (int i = 0; i < n; i++) {
            // Loop through the array from the current index to the end
            for (int j = i + 1; j < n; j++) {
                // If the current element is greater than the element at the current index plus one
                if (this.arr[i] > this.arr[j]) {
                    // Swap the two elements
                    int temp = this.arr[i];
                    this.arr[i] = this.arr[j];
                    this.arr[j] = temp;
                }
            }
        }
        // Return the sorted array
        return this.arr;
    }

}

class bubbleSortJava {
    public static void main(String args[]) {

        int[] myInput = { 5,3,6,8,9,1,3,35 };
        System.out.println("Before Sorting: " + Arrays.toString(myInput));

        bubbleSort myBubbleSort = new bubbleSort(myInput);

        int[] sortedArray = myBubbleSort.sort();

        System.out.println("After Sorting: " + Arrays.toString(sortedArray));
    }
}
