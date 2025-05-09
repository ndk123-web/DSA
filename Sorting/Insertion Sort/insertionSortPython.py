class InsertionSort:
    def __init__(self, arr):
        # Initialize the class with the array to be sorted
        self.arr = arr
    
    def sort(self):
        # Iterate over the array starting from the second element
        for i in range(1, len(self.arr)):
            # Store the current element as key
            key = self.arr[i]
            # Initialize j to the index before i
            j = i - 1

            # Move elements of arr[0..i-1], that are greater than key,
            # to one position ahead of their current position
            while j >= 0 and self.arr[j] > key:
                # Shift element to the right
                self.arr[j + 1] = self.arr[j]
                j -= 1
            
            # Place the key at the correct position
            self.arr[j + 1] = key
        
        # Return the sorted array
        return self.arr

# Create an array to be sorted
arr = [5, 3, 6, 8, 9, 1, 3, 35]

# Create an instance of the InsertionSort class
InsertionSort = InsertionSort(arr)

# Call the sort method to sort the array
sortedArray = InsertionSort.sort()

# Print the sorted array
print("Sorted array:", sortedArray)
