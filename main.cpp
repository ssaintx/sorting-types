#include <iostream>
#include <vector>

using namespace std;

int partition(int arr[], int start, int end){
 
    int pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}

void quickSort(int arr[], int start, int end){
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);
}

void merge(int array[], int const left, int const mid,
           int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;
 
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
 
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
 
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}
 
// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(int array[], int const begin, int const end){
    if (begin >= end)
        return;
 
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void insertionSort(int arr[], int n){
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1],
        // that are greater than key, 
        // to one position ahead of their
        // current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void bubbleSort(int arr[], int size){
    int i, j; 
    for (i = 0; i < size - 1; i++) 
        for (j = 0; j < size - i - 1; j++) 
            if (arr[j] > arr[j + 1]) 
                swap(arr[j], arr[j + 1]); 
}

int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSort(int arr[], int n, int exp)
{
 
    // Output array
    int output[n];
    int i, count[10] = { 0 };
 
    // Store count of occurrences
    // in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    // Change count[i] so that count[i]
    // now contains actual position
    // of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
// The main function to that sorts arr[]
// of size n using Radix Sort
void radixSort(int arr[], int n)
{
 
    // Find the maximum number to
    // know number of digits
    int m = getMax(arr, n);
 
    // Do counting sort for every digit.
    // Note that instead of passing digit
    // number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

bool isSorted(int a[], int n)
{
    while (--n > 0)
        if (a[n] < a[n - 1])
            return false;
    return true;
}
 
// To generate permutation of the array
void shuffle(int a[], int n)
{
    for (int i = 0; i < n; i++)
        swap(a[i], a[rand() % n]);
}
 
// Sorts array a[0..n-1] using Bogo sort
void bogoSort(int a[], int n)
{
    // if array is not sorted then shuffle
    // the array again
    while (!isSorted(a, n))
        shuffle(a, n);
}

void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root Since we are using 0 based indexing
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
 
// main function to do heap sort
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

struct Node 
{ 
    int key; 
    struct Node *left, *right; 
}; 
  
// A utility function to create a new BST Node 
struct Node *newNode(int item) 
{ 
    struct Node *temp = new Node; 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
  
// Stores inorder traversal of the BST 
// in arr[] 
void storeSorted(Node *root, int arr[], int &i) 
{ 
    if (root != NULL) 
    { 
        storeSorted(root->left, arr, i); 
        arr[i++] = root->key; 
        storeSorted(root->right, arr, i); 
    } 
} 
  
/* A utility function to insert a new 
   Node with given key in BST */
Node* insert(Node* node, int key) 
{ 
    /* If the tree is empty, return a new Node */
    if (node == NULL) return newNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
  
    /* return the (unchanged) Node pointer */
    return node; 
} 
  
// This function sorts arr[0..n-1] using Tree Sort 
void treeSort(int arr[], int n) 
{ 
    struct Node *root = NULL; 
  
    // Construct the BST 
    root = insert(root, arr[0]); 
    for (int i=1; i<n; i++) 
        root = insert(root, arr[i]); 
  
    // Store inorder traversal of the BST 
    // in arr[] 
    int i = 0; 
    storeSorted(root, arr, i); 
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < n - 1; i++) {
 
        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
 
        // Swap the found minimum element
        // with the first element
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}

void printArr(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout<<arr[i]<<" ";
    }
}

int main() {

    int option;
    
    do{
        cout<<"1. Qiuck sort\n";
        cout<<"2. Merge sort\n";
        cout<<"3. Insertion sort\n";
        cout<<"4. Radix sort \n";
        cout<<"5. Bubble sort\n";
        cout<<"6. Bogo sort\n";
        cout<<"7. Heap sort\n";
        cout<<"8. Tree sort\n";
        cout<<"9. Selection sort\n";
        cin>>option;
    
        if(option == 1){
            int size;
            
            cout<<"Enter array size: ";
            cin>>size;
            
            int arr[size];
            
            for (int i = 0; i < size; i++){
               cout<<"Enter "<<size<<" numbers into array: ";
               cin>>arr[i];
            }
            
            quickSort(arr, 0, size - 1);
            printArr(arr, size);
            
            cout<<"\n\nWorst-case complexity: n^2\nClass: Comparison sort\nAverage complexity: n*log(n)\nStable: No";
            
        }else if(option == 2){
            int size;
            
            cout<<"Enter array size: ";
            cin>>size;
            
            int arr[size];
            
            for (int i = 0; i < size; i++){
               cout<<"Enter "<<size<<" numbers into array: ";
               cin>>arr[i];
            }
            
            mergeSort(arr, 0, size - 1);
            printArr(arr, size);
            
            cout<<"\n\nTime complexity: O(nLogn)";
            
        }else if(option == 3){
            int size;
            
            cout<<"Enter array size: ";
            cin>>size;
            
            int arr[size];
            
            for (int i = 0; i < size; i++){
               cout<<"Enter "<<size<<" numbers into array: ";
               cin>>arr[i];
            }
            
            insertionSort(arr, size);
            printArr(arr, size);
            
            cout<<"\n\nWorst-case complexity: n^2\nBest complexity: n\nAverage complexity: n^2\nClass: Comparison sort\nAverage performance: comparisons and swaps\nData structure: Array";
  
        }else if(option == 4){
            int size;
            
            cout<<"Enter array size: ";
            cin>>size;
            
            int arr[size];
            
            for (int i = 0; i < size; i++){
               cout<<"Enter "<<size<<" numbers into array: ";
               cin>>arr[i];
            }
            
            radixSort(arr, size);
            printArr(arr, size);
            
            cout<<"\n\nWorst-case complexity: n*k/d\nClass: Non-comparison sort";
            
        }else if(option == 5){
            int size;
            
            cout<<"Enter array size: ";
            cin>>size;
            
            int arr[size];
            
            for (int i = 0; i < size; i++){
               cout<<"Enter "<<size<<" numbers into array: ";
               cin>>arr[i];
            }
            
            bubbleSort(arr, size);
            printArr(arr, size);
            
            cout<<"Class: Comparison sort\nData structure: Array";
            
        }else if(option == 6){
            int size;
            
            cout<<"Enter array size: ";
            cin>>size;
            
            int arr[size];
            
            for (int i = 0; i < size; i++){
               cout<<"Enter "<<size<<" numbers into array: ";
               cin>>arr[i];
            }
            
            bogoSort(arr, size);
            printArr(arr, size);
            
            cout<<"\n\nWorst-case complexity: Infinite\nAverage complexity: n*n!\nClass: Sorting\nData structure: Array\nWorst-case performance: Unbounded (randomized version), (deterministic version)";
            
        }else if(option == 7){
            int size;
            
            cout<<"Enter array size: ";
            cin>>size;
            
            int arr[size];
            
            for (int i = 0; i < size; i++){
               cout<<"Enter "<<size<<" numbers into array: ";
               cin>>arr[i];
            }
            
            heapSort(arr, size);
            printArr(arr, size);
            
            cout<<"\n\nWorst-case complexity: n*log(n)\nAverage complexity: n*log(n)";
            
        }else if(option == 8){
            int size;
            
            cout<<"Enter array size: ";
            cin>>size;
            
            int arr[size];
            
            for (int i = 0; i < size; i++){
               cout<<"Enter "<<size<<" numbers into array: ";
               cin>>arr[i];
            }
            
            treeSort(arr, size);
            printArr(arr, size);
            
            cout<<"\n\nWorst-case space complexity: Θ(n)\nWorst-case complexity: n*log(n) (balanced)\nAverage complexity: n*log(n)\nClass: Comparison sort\nAverage performance: O(n log n)\nData structure: Array\n";
            
        }else if(option == 9){
            int size;
            
            cout<<"Enter array size: ";
            cin>>size;
            
            int arr[size];
            
            for (int i = 0; i < size; i++){
               cout<<"Enter "<<size<<" numbers into array: ";
               cin>>arr[i];
            }
            
            selectionSort(arr, size);
            printArr(arr, size);
            
            cout<<"\n\nWorst-case space complexity: auxiliary\nWorst-case complexity: n^2\nClass: Comparison sort\nData structure: Array\n";
        }

    }while(option == 'q'); 
    
    return 0;
}
