# Selection Sort algorithm in Python

# Selection Sort is an in-place comparison-based algorithm in which the list is divided into two parts, the sorted part at the left end and the unsorted part at the right end. Initially, the sorted part is empty and the unsorted part is the entire list. The smallest element is selected from the unsorted array and swapped with the leftmost element, and that element becomes a part of the sorted array. This process continues moving unsorted array boundary by one element to the right. This algorithm is not suitable for large data sets as its average and worst case complexity are of Ο(n^2) where n is the number of items.

# The SelectionSort class encapsulates the selection sort algorithm
class SelectionSort:
    def __init__(self, arr):
        # The constructor takes an array as input
        self.arr = arr

    def sort(self):
        # The outer loop iterates through the array
        for i in range(len(self.arr)):
            # The variable minIndex keeps track of the index of the smallest element
            minIndex = i
            
            # The inner loop iterates through the array from the current index to the end
            for j in range(i+1, len(self.arr)):
                # If the element at the current index is greater than the element at the inner loop index
                if self.arr[j] < self.arr[minIndex]:
                    # Update the minIndex
                    minIndex = j

            # Swap the element at the current index with the element at the minIndex
            self.arr[i], self.arr[minIndex] = self.arr[minIndex], self.arr[i]

        # Return the sorted array
        return self.arr

# Create an array
arr = [64, 25, 12, 22, 11]

# Create an instance of the SelectionSort class
SelectionSort = SelectionSort(arr)

# Call the sort method
sortedArray = SelectionSort.sort()

# Print the sorted array
print("Sorted array:", sortedArray)
