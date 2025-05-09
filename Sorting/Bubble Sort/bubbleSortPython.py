# We are doing Bubble Sort
# It Takes O(n^2)


class BubbleSort:
    def __init__(self,myInput):
        print("Bubble Sort")
        
    # Logic of Bubble Sort 
    def sort(self):
        
        i = 0 
        j = 0
        
        for i in range(len(myInput)):
            for j in range(i+1):
                if myInput[i] < myInput[j]:
                    myInput[i] , myInput[j] = myInput[j], myInput[i] 
        
        return myInput  


myInput = [5,3,6,8,9,1,3,35]

# create an instance of the BubbleSort class
bubblSort = BubbleSort(myInput)

sortedArray = bubblSort.sort()

print("Before Sorting: ", myInput)
print("After Sorting: ", sortedArray)