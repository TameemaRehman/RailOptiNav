#pragma once
#include <iostream>
#include <stdexcept>
#include "Graphs.h"

using namespace std;
class Pair {
public:
    int distance;
    int index;
};

class MinHeapPriorityQueue {
private:
    int MAX_SIZE;
    Pair* heap;
    int size{};

    void heapifyUp() {
        int index = size - 1;
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index].distance < heap[parentIndex].distance) {
                swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            }
            else {
                break;
            }
        }
    }

    void heapifyDown() {
        int index = 0;
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if (leftChild < size && heap[leftChild].distance < heap[smallest].distance) {
                smallest = leftChild;
            }

            if (rightChild < size && heap[rightChild].distance < heap[smallest].distance) {
                smallest = rightChild;
            }

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else {
                break;
            }
        }
    }

public:
    MinHeapPriorityQueue(int MAX_SIZE) : size(0) {
        this->MAX_SIZE = MAX_SIZE;
        heap = new Pair[MAX_SIZE];
    }

    // Insert an element into the priority queue
    void push(Pair element) {
        if (size >= MAX_SIZE) {
            //cout << "Priority Queue is Full" << endl; 
            //<<-- yahan pe continuously repeated times iss e ye print kia tha console pe 
            //tabhi i added just return statement
            return;
        }
        else {
            heap[size] = element;
            size++;
            heapifyUp();
        }
    }

    // Remove and return the smallest element from the priority queue
    Pair pop() {
        if (size == 0) {
            cout << "Priority Queue is Empty" << endl;
        }
        else {
            Pair top = heap[0];
            heap[0] = heap[size - 1];
            size--;
            heapifyDown();
            return top;
        }
    }

    // Get the size of the priority queue
    int getSize() const {
        return size;
    }
};