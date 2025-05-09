
class bubbleSortJS{
    // This is the constructor for the Bubble Sort class
    constructor(arr){
        // The constructor takes an array as input
        this.arr = arr;
    }

    // The sort method sorts the array in ascending order using the Bubble Sort algorithm
    sort = () => {
        // The outer loop iterates through the array
        let n = this.arr.length; 
        
        for(let i = 0 ; i < n ; i++){
            // The inner loop iterates through the array from the current index to the end
            for(let j = i + 1 ; j < n ; j++){
                // If the current element is greater than the element at the current index plus one
                if(this.arr[i] > this.arr[j]){
                    // Swap the two elements
                    let temp = this.arr[i];
                    this.arr[i] = this.arr[j];
                    this.arr[j] = temp;
                }
            }
        }
        // Return the sorted array
        return this.arr;
    }
}

let myInput = [5,3,6,8,9,1,3,35]
console.log("Sorted Array: ", myInput);


let myBubbleSort = new bubbleSortJS(myInput);

let sortedArray = myBubbleSort.sort();

console.log("Sorted Array: ", sortedArray);
