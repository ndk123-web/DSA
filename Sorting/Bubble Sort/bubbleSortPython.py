# We are doing Bubble Sort
# It Takes O(n^2)

# This is a class for Bubble Sort
class BubbleSort:
    def __init__(self, myInput):
        print("Bubble Sort")
        
    # This function implements the Bubble Sort algorithm
    # It takes an array as an argument
    # It returns the sorted array
    def sort(self, myInput):
        # We loop through the array
        for i in range(len(myInput)):
            # We loop through the array again
            for j in range(i+1):
                # "<" means ascending order  ( means first bigger number will be at the end of the array )
                # ">" means descending order ( means first smaller number will be at the end of the array )  
                if myInput[i] < myInput[j]:  
                    # Swap the elements
                    myInput[i] , myInput[j] = myInput[j], myInput[i] 
        # We return the sorted array
        return myInput  

# We create an array
myInput = [5,3,6,8,9,1,3,35]

# We print the array before sorting
print("Before Sorting: ", myInput)

# We create an instance of the BubbleSort class
# We pass the array to the instance
bubblSort = BubbleSort(myInput)

# We call the sort method
# It returns the sorted array
sortedArray = bubblSort.sort(myInput)

# We print the sorted array
print("After Sorting: ", sortedArray)
