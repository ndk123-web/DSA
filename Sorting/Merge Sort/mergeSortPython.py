class MergeSort:
    """
    This class implements the Merge Sort algorithm.
    """

    def __init__(self, arr):
        """
        The constructor takes an array as input and stores it in the instance variable self.arr.
        """
        self.arr = arr

    def sort(self):
        """
        This method sorts the array in ascending order using the Merge Sort algorithm and returns the sorted array.
        """
        # Call the merge method to sort the array
        return self._merge(0, len(self.arr) - 1)

    def _merge(self, low, high):
        """
        This is a recursive helper method that takes two indices, low and high, as input.
        It sorts the subarray from index low to high using the Merge Sort algorithm.
        """
        # Base case: if the subarray has one or zero elements, it is already sorted
        if low >= high:
            return [self.arr[low]]

        # Find the middle index of the subarray
        mid = (low + high) // 2

        # Recursively sort the left and right partitions
        leftArr = self._merge(low, mid)
        rightArr = self._merge(mid + 1, high)

        # Merge the sorted left and right partitions
        return self._mergeSort(leftArr, rightArr)

    def _mergeSort(self, leftArr, rightArr):
        """
        This method takes two sorted arrays as input and merges them into one sorted array.
        """
        sortedArr = []
        i = j = 0

        # Compare elements from the two arrays and add the smaller one to the sorted array
        while i < len(leftArr) and j < len(rightArr):
            if leftArr[i] < rightArr[j]:
                sortedArr.append(leftArr[i])
                i += 1
            else:
                sortedArr.append(rightArr[j])
                j += 1

        # Add any remaining elements from the left array
        while i < len(leftArr):
            sortedArr.append(leftArr[i])
            i += 1

        # Add any remaining elements from the right array
        while j < len(rightArr):
            sortedArr.append(rightArr[j])
            j += 1

        return sortedArr


# Create an array
arr = [5, 3, 6, 8, 9, 1, 3, 35] 
print("Original array:", arr)

# Create an instance of the MergeSort class
mergeSort = MergeSort(arr) 

# Call the sort method to sort the array
sortedArray = mergeSort.sort()
print("Sorted array:", sortedArray) 
