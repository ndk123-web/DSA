# This is a sorting algorithm which uses the "3-way partition" approach.
# It divides the array into three parts: elements less than the pivot, equal to the pivot, and greater than the pivot.
# The pivot is chosen as the middle value of the array.
# The algorithm then recursively sorts the left and right partitions.

# Time Complexity: O(n log n) 
# Space Complexity: O(n log n)

class mySort:
    def __init__(self, arr):
        # The constructor takes an array as input
        self.arr = arr

    def sort(self):
        # Base case: if the array has one or zero elements, it is already sorted
        if len(self.arr) <= 1:
            return self.arr

        # Find the minimum, maximum, and middle values of the array
        minVal = min(self.arr)
        maxVal = max(self.arr)
        midVal = (minVal + maxVal) // 2

        # Create three lists: one for elements less than the pivot, one for elements equal to the pivot, and one for elements greater than the pivot
        left = []
        mid = []
        right = []

        # Iterate through the array and add each element to the appropriate list
        for val in self.arr:
            if val < midVal:
                left.append(val)
            elif val > midVal:
                right.append(val)
            else:
                mid.append(val)

        # Recursively sort the left and right partitions
        leftSorted = mySort(left).sort()
        rightSorted = mySort(right).sort()

        # Combine the sorted left partition, the middle partition, and the sorted right partition
        return leftSorted + mid + rightSorted

arr = [7,12,9,11,13]

# Create an instance of the sorting algorithm
mySortInstance = mySort(arr)

# Call the sort method
sortedArray = mySortInstance.sort()

# Print the sorted array
print("Sorted array:", sortedArray)
