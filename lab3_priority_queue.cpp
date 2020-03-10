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
	for (int i = 1; i <= size; i++) {
		delete heap[i];
		heap[i] = NULL;
	}
	delete [] heap;
	heap = NULL;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return 0;
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
void PriorityQueue::print() const {
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
	if (full()) {
		return false;
	}
	else {
		++size;
		**(heap + size) = val;
	}

	int cur = (int)(size);

	while (cur > 1 && (**(heap + cur / 2)).priority < val.priority) {
		TaskItem temp = **(heap + cur / 2);
		(**(heap + cur / 2)) = **(heap + cur);
		**(heap + cur) = temp;
		cur = (cur / 2);
	}
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	return false;
}
