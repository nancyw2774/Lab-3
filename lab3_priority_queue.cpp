#include "lab3_priority_queue.hpp"

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	size = 0;
	capacity = n_capacity;
	heap = new TaskItem* [n_capacity+1];
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size; 
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	return size == 0 && heap[1] == NULL;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	for(int i = 1; i < size; i++){
        cout << "Item Priority: " << heap[i]->priority << endl;
        cout << "Item Description: " << heap[i]->description << endl; 
    }//we can use the for loop because the size of the heap is not being changed while we iterate
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	int maxNum = 0;
	if (size == 0) 
		return TaskItem(-1, "N/A");

	for (int i = 1; i <= size; i++) {
		if (heap[i]->priority > maxNum)
			maxNum = heap[i]->priority;
	}
	return *(heap[1]);
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	return false;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
  //setting a pointer to a dynamically alloacted object
    
    if(empty())
        return false;
    else if(size == 1){
        TaskItem* temp = heap[1];
        heap[1] = NULL;
        delete temp;//yes, the TaskItems are dynamically allocated
    }
    else {
        TaskItem* temp = heap[size];
        heap[size] = heap[1];
        heap[1] = temp; //this swaps the bottom level with the top level
        delete heap[size]; //deletes what was the highest level node
        
        TaskItem* cur = heap[1];
        
        for (int i = 2; i <= size && (cur->priority > heap[i*2]->priority||cur->priority > heap[i*2+1]->priority); i++) {
            if(heap[i*2]->priority > heap[i*2+1]->priority) {
                TaskItem* temp2 = heap[i*2];
                heap[i*2] = cur;
                cur = temp2;
            }
            else {
                TaskItem* temp2 = heap[i*2+1];
                heap[i*2+1] = cur;
                cur = temp2;
            }
        }
    }//we can use the for loop because the size of the heap is not being changed while we iterate
    size--;
    return true;
}
