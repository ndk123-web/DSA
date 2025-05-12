class QuickSort:
    """
    This class implements the Quick Sort algorithm.
    """

    def __init__(self, arr):
        """
        The constructor takes an array as input and stores it in the instance variable self.arr.
        """
        self.arr = arr

    def sort(self):
        """
        This method sorts the array in ascending order using the Quick Sort algorithm and returns the sorted array.
        """
        self._quick_sort(0, len(self.arr) - 1)
        return self.arr

    def _quick_sort(self, low, high):
        """
        This is a recursive helper method that takes two indices, low and high, as input.
        It sorts the subarray from index low to high using the Quick Sort algorithm.
        """
        if low < high:
            # Find the pivot index using the partition method
            pi = self._partition(low, high)

            # Recursively sort the left and right partitions
            self._quick_sort(low, pi - 1)
            self._quick_sort(pi + 1, high)

    def _partition(self, low, high):
        """
        This method takes two indices, low and high, as input and partitions the subarray from index low to high around a pivot element.
        It returns the index of the pivot element.
        """
        pivot = self.arr[low]
        i = low + 1
        j = high

        while True:
            # Find the first element from the left that is greater than the pivot
            while i <= j and self.arr[i] <= pivot:
                i += 1

            # Find the first element from the right that is less than the pivot
            while i <= j and self.arr[j] >= pivot:
                j -= 1

            # If i is less than or equal to j, swap the elements at indices i and j
            if i <= j:
                self.arr[i], self.arr[j] = self.arr[j], self.arr[i]
            else:
                break

        # Swap the pivot element with the element at index j
        self.arr[low], self.arr[j] = self.arr[j], self.arr[low]
        return j
    

# Create an array
arr = [64, 25, 12, 22, 11]
print("Original array:", arr)

# Create an instance of the QuickSort class
quickSort = QuickSort(arr)

# Call the sort method
sortedArray = quickSort.sort()
print("Sorted array:", sortedArray)
