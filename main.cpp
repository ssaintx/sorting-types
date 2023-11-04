#include <iostream>
#include <vector>
#include <chrono>

using namespace std::chrono;
using namespace std;

// Node for tree sort 
struct Node{ 
    int key; 
    struct Node *left, *right; 
}; 

struct Node *newNode(int item) { 
    struct Node *temp = new Node; 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 

void storeSorted(Node *root, int arr[], int &i){ 
    if (root != NULL) 
    { 
        storeSorted(root->left, arr, i); 
        arr[i++] = root->key; 
        storeSorted(root->right, arr, i); 
    } 
} 
  
Node* insert(Node* node, int key) { 
    if (node == NULL) return newNode(key); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
  
    return node; 
}


// quickSort
int partition(int arr[], int start, int end);
void quickSort(int arr[], int start, int end);
void quickSortOption();

// mergeSort
void merge(int array[], int const left, int const mid, int const right);
void mergeSort(int array[], int const begin, int const end);
void mergeSortOption();

// insertionSort 
void insertionSort(int arr[], int n);
void insertionSortOption();

// radixSort
int getMax(int arr[], int n);
void countSort(int arr[], int n, int exp);
void radixSort(int arr[], int n);
void radixSortOption();

// bubbleSort
void bubbleSort(int arr[], int size);
void bubbleSortOption();

// bogoSort
bool isSorted(int a[], int n);
void shuffle(int a[], int n);
void bogoSort(int a[], int n);
void bogoSortOption();

// heapSort
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);
void heapSortOption();

// treeSort
void storeSorted(Node *root, int arr[], int &i);
void treeSort(int arr[], int n);
void treeSortOption();

// selectionSort
void selectionSort(int arr[], int n);
void selectionSortOption();

// printOut Array
void printArr(int arr[], int size);


int main(){

    char option;
    int choice;
    
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
        
        cout<<"\nEnter a number to choose sort type: ";
        cin>>choice;
        
        switch(choice){
            case 1:
                quickSortOption();
                break;
            case 2:
                mergeSortOption();
                break;
            case 3:
                insertionSortOption();
                break;
            case 4:
                radixSortOption();
                break;
            case 5:
                bubbleSortOption();
                break;
            case 6:
                bogoSortOption();
                break;
            case 7:
                heapSortOption();
                break;
            case 8:
                treeSortOption();
                break;
            case 9:
                selectionSortOption();
                break;
            default:
                cout<<"There is no option as this. Please try again.\n";
        }

        cout<<"\n\nIf you want to continue press 'Y or 'y': ";
        cin>>option;

    }while(option == 'y' || option == 'Y'); 
    
    return 0;
}

// quickSort
int partition(int arr[], int start, int end){
 
    int pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

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

    if (start >= end)
        return;

    int p = partition(arr, start, end);

    quickSort(arr, start, p - 1);

    quickSort(arr, p + 1, end);
}

void quickSortOption(){
    int size;
            
    cout<<"Enter array size: ";
    cin>>size;
            
    int arr[size];
            
    for (int i = 0; i < size; i++){
        cout<<"Enter "<<size<<" numbers into array: ";
        cin>>arr[i];
    }
    
    auto start = high_resolution_clock::now();
    
    quickSort(arr, 0, size - 1);
    printArr(arr, size);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout<<"\nRuntime: "<<duration.count()<<" microseconds.";        
    cout<<"\n\nWorst-case complexity: n^2\nClass: Comparison sort\nAverage complexity: n*log(n)\nStable: No";
}

// mergeSort
void merge(int array[], int const left, int const mid,
           int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

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

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
 

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end){
    if (begin >= end)
        return;
 
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void mergeSortOption(){
    int size;
            
    cout<<"Enter array size: ";
    cin>>size;
            
    int arr[size];
            
    for (int i = 0; i < size; i++){
        cout<<"Enter "<<size<<" numbers into array: ";
        cin>>arr[i];
    }
    
    auto start = high_resolution_clock::now();
            
    mergeSort(arr, 0, size - 1);
    printArr(arr, size);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout<<"\nRuntime: "<<duration.count()<<" microseconds.";               
    cout<<"\n\nTime complexity: O(nLogn)";
}

// insertionSort
void insertionSort(int arr[], int n){
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertionSortOption(){
    int size;
            
    cout<<"Enter array size: ";
    cin>>size;
            
    int arr[size];
            
    for (int i = 0; i < size; i++){
        cout<<"Enter "<<size<<" numbers into array: ";
        cin>>arr[i];
    }
    
    auto start = high_resolution_clock::now();
            
    insertionSort(arr, size);
    printArr(arr, size);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout<<"\nRuntime: "<<duration.count()<<" microseconds.";   
    cout<<"\n\nWorst-case complexity: n^2\nBest complexity: n\nAverage complexity: n^2\nClass: Comparison sort\nAverage performance: comparisons and swaps\nData structure: Array";    
}

// radixSort
int getMax(int arr[], int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(int arr[], int n, int exp){

    int output[n];
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n){

    int m = getMax(arr, n);
 
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void radixSortOption(){
    int size;
            
    cout<<"Enter array size: ";
    cin>>size;
            
    int arr[size];
            
    for (int i = 0; i < size; i++){
        cout<<"Enter "<<size<<" numbers into array: ";
        cin>>arr[i];
    }
            
    auto start = high_resolution_clock::now();
    
    radixSort(arr, size);
    printArr(arr, size);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout<<"\nRuntime: "<<duration.count()<<" microseconds.";               
    cout<<"\n\nWorst-case complexity: n*k/d\nClass: Non-comparison sort";     
}

// bubbleSort
void bubbleSort(int arr[], int size){
    int i, j; 
    for (i = 0; i < size - 1; i++) 
        for (j = 0; j < size - i - 1; j++) 
            if (arr[j] > arr[j + 1]) 
                swap(arr[j], arr[j + 1]); 
}

void bubbleSortOption(){
    int size;
            
    cout<<"Enter array size: ";
    cin>>size;
            
    int arr[size];
            
    for (int i = 0; i < size; i++){
        cout<<"Enter "<<size<<" numbers into array: ";
        cin>>arr[i];
    }
    
    auto start = high_resolution_clock::now();
            
    bubbleSort(arr, size);
    printArr(arr, size);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout<<"\nRuntime: "<<duration.count()<<" microseconds.";   
    cout<<"\n\nClass: Comparison sort\nData structure: Array";   
}

// bogoSort
bool isSorted(int a[], int n){
    while (--n > 0)
        if (a[n] < a[n - 1])
            return false;
    return true;
}

void shuffle(int a[], int n){
    for (int i = 0; i < n; i++)
        swap(a[i], a[rand() % n]);
}
 
void bogoSort(int a[], int n){
    while (!isSorted(a, n))
        shuffle(a, n);
}

void bogoSortOption(){
    int size;
            
    cout<<"Enter array size: ";
    cin>>size;
            
    int arr[size];
            
    for (int i = 0; i < size; i++){
        cout<<"Enter "<<size<<" numbers into array: ";
        cin>>arr[i];
    }
    
    auto start = high_resolution_clock::now();
            
    bogoSort(arr, size);
    printArr(arr, size);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout<<"\nRuntime: "<<duration.count()<<" microseconds.";               
    cout<<"\n\nWorst-case complexity: Infinite\nAverage complexity: n*n!\nClass: Sorting\nData structure: Array\nWorst-case performance: Unbounded (randomized version), (deterministic version)";
}

// heapSort
void heapify(int arr[], int n, int i){
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        heapify(arr, n, largest);
    }
}
 
void heapSort(int arr[], int n){

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void heapSortOption(){
    int size;
            
    cout<<"Enter array size: ";
    cin>>size;
            
    int arr[size];
            
    for (int i = 0; i < size; i++){
        cout<<"Enter "<<size<<" numbers into array: ";
        cin>>arr[i];
    }
    
    auto start = high_resolution_clock::now();
            
    heapSort(arr, size);
    printArr(arr, size);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout<<"\nRuntime: "<<duration.count()<<" microseconds.";               
    cout<<"\n\nWorst-case complexity: n*log(n)\nAverage complexity: n*log(n)";    
}

// treeSort, you may also use Classes instead of structs
void treeSort(int arr[], int n){ 
    struct Node *root = NULL; 
   
    root = insert(root, arr[0]); 
    for (int i=1; i<n; i++) 
        root = insert(root, arr[i]); 
  
    int i = 0; 
    storeSorted(root, arr, i); 
}
void treeSortOption(){
    int size;
            
    cout<<"Enter array size: ";
    cin>>size;
            
    int arr[size];
            
    for (int i = 0; i < size; i++){
        cout<<"Enter "<<size<<" numbers into array: ";
        cin>>arr[i];
    }
    
    auto start = high_resolution_clock::now();
            
    treeSort(arr, size);
    printArr(arr, size);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout<<"\nRuntime: "<<duration.count()<<" microseconds.";               
    cout<<"\n\nWorst-case space complexity: Θ(n)\nWorst-case complexity: n*log(n) (balanced)\nAverage complexity: n*log(n)\nClass: Comparison sort\nAverage performance: O(n log n)\nData structure: Array\n";
}

// selectionSort
void selectionSort(int arr[], int n){
    int i, j, min_idx;
 
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}

void selectionSortOption(){
    int size;
            
    cout<<"Enter array size: ";
    cin>>size;
            
    int arr[size];
            
    for (int i = 0; i < size; i++){
        cout<<"Enter "<<size<<" numbers into array: ";
        cin>>arr[i];
    }
    
    auto start = high_resolution_clock::now();
            
    selectionSort(arr, size);
    printArr(arr, size);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout<<"\nRuntime: "<<duration.count()<<" microseconds.";               
    cout<<"\n\nWorst-case space complexity: auxiliary\nWorst-case complexity: n^2\nClass: Comparison sort\nData structure: Array\n";    
}

// array printOut
void printArr(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout<<arr[i]<<" ";
    }
}
