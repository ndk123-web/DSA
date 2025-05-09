class BubbleSortJS {
  private arr: number[];

  constructor(arr: number[]) {
    this.arr = arr;
  }

  sort(): number[] {
    let a = [...this.arr]; // original array mutate na ho
    let n = a.length;
    for (let i = 0; i < n - 1; i++) {
      for (let j = 0; j < n - i - 1; j++) {
        if (a[j] > a[j + 1]) {
          [a[j], a[j + 1]] = [a[j + 1], a[j]]; // swap
        }
      }
    }
    return a;
  }
}

// Use the class
let myInput: number[] = [5, 3, 6, 8, 9, 1, 3, 35];
console.log("Original Array: ", myInput);

let myBubbleSort = new BubbleSortJS(myInput);  // 👈 correct class name and type
let sortedArray: number[] = myBubbleSort.sort();

console.log("Sorted Array: ", sortedArray);
