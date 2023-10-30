// Max-heap for 10^6 random values
#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
using namespace std;

const int SIZE = 1000000;
int arr[SIZE];


// Function to generate 10^6 random integers and store it in a file
void generateRandom(void)
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(0,SIZE); // distribution in range [0,1000000]

    ofstream file;
    file.open("random.txt");

    for (int i = 0; i < SIZE; i++)
        file << dist(rng) << endl; // Saving to file

    file.close();
}

// Function to heapify a subtree with root at ith position
void maxHeapify(int N, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < N && arr[l] > arr[largest])
        largest = l;

    if (r < N && arr[r] > arr[largest])
        largest = r;

    // If largest is not the root
    if (largest != i)
    {
        // Swap with largest
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the new subtree
        maxHeapify(N, largest);
    }
}


// Function to build max-heap from given array
void buildHeap(int N)
{
    int startIndex = ceil(N/2 - 1); // Start index of the first non-leaf node

    for (int i = startIndex; i >= 0; i--)
        maxHeapify(N, i);
}


int main(void)
{
    cout << "Generating random numbers..." << endl;
    generateRandom();

    ifstream file1;
    file1.open("random.txt");
    int x;
    for (int i = 0; i < SIZE; i++)
    {
        file1 >> x;
        arr[i] = x;
    }
    file1.close();

    cout << "Building heap..." << endl;
    buildHeap(SIZE);

    // Printing the max-heap array in a file
    ofstream file2;
    file2.open("maxheap.txt");

    for (int i = 0; i < SIZE; i++)
        file2 << arr[i] << endl; // Saving to file

    file2.close();


    // Deleting the root and storing values in a file
    cout << "Deleting root elements (heap sort)..." << endl;
    ofstream file3;
    file3.open("maxheapsort.txt");

    for (int i = SIZE-1; i >= 0; i--)
    {
        file3 << arr[0] << endl; // Saving root to file
        arr[0] = arr[i];
        maxHeapify(i, 0);
    }
}
