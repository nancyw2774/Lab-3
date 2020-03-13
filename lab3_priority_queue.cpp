#include "lab3_priority_queue.hpp"
#include <iostream>

//TODO: fix print, dequeue, and probably more stuff but thats as far as i got

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	size = 0;
	capacity = n_capacity;
	heap = new TaskItem * [n_capacity + 1];
	for (int i = 0; i < capacity; i++) 
		heap[i] = NULL;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for (int i = 1; i <= (int)size; i++) {
		delete heap[i];
		heap[i] = NULL;
	}
	delete[] heap;
	heap = NULL;
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
	if (size == capacity) {
		return true;
	}
	return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
//this doesnt print properly (maybe print out each row as a new line?
void PriorityQueue::print() const {/*
	for (int i = 1; i < (int)size; i++) {
		cout << "Item Priority: " << heap[i]->priority << endl;
		cout << "Item Description: " << heap[i]->description << endl;
	*///we can use the for loop because the size of the heap is not being changed while we iterate
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	int maxNum = 0;
	if (size == 0)
		return TaskItem(-1, "N/A");

	for (int i = 1; i <= (int)size; i++) {
		if (heap[i]->priority > maxNum)
			maxNum = heap[i]->priority;
	}
	return *(heap[1]);
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue(TaskItem val) {
	TaskItem* newVal = new TaskItem(val);
	if (full()) {
		return false;
	}
	else {
		++size;
		heap[size] = newVal;
	}

	int cur = (int)size;
	
	while (cur > 1 && (heap[cur / 2]->priority < newVal->priority)) {
		TaskItem temp = *heap[cur / 2];
		*heap[cur / 2] = *heap[cur];
		*heap[cur] = temp;
		cur = (cur / 2);
	}
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {/*
	//setting a pointer to a dynamically allocated object
	
	if (empty())
		return false;
	else if (size == 1) {
		TaskItem* temp = heap[1];
		heap[1] = NULL;
		delete temp;//yes, the TaskItems are dynamically allocated
	}
	else {
		TaskItem* temp = heap[size];
		heap[size] = heap[1];
		heap[1] = temp; //this swaps the bottom level with the top level
		delete heap[size]; //deletes what was the highest level node
		heap[size] = NULL;

		TaskItem* cur = heap[1];
		int index = 2;

		//TODO: account for if 2 > size || 2i > size || 2i+1 > size
		while (heap[i * 2] != NULL && heap[i * 2 + 1] != NULL || (cur->priority < heap[i * 2]->priority || cur->priority < heap[i * 2 + 1]->priority)) {
		//i feel like a while loop makes more sense? cuz we dont know how many times we're iterating
		//for (int i = 2; i <= (int)size && (cur->priority < heap[i * 2]->priority || cur->priority < heap[i * 2 + 1]->priority); i++) {
			if (heap[i * 2] != NULL){
				else if (heap[i * 2 + 1] == NULL || heap[i * 2]->priority > heap[i * 2 + 1]->priority) {
					TaskItem* temp2 = heap[i * 2];
					heap[i * 2] = cur;
					heap[i] = temp2;
				}
				else {
					TaskItem* temp2 = heap[i * 2 + 1];
					heap[i * 2 + 1] = cur;
					heap[i] = temp2;
				}
			}
			++i;
		}
	}
	--size;*/
	return true;
}
