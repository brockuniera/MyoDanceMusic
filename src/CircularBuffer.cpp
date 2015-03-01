
#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer(int slots) {
  if (slots <= 0) {
    num_of_slots_ = 10; /*pre-assigned value */
  } else {
      num_of_slots_ = slots;
  }
  clear();
}

CircularBuffer::~CircularBuffer() {
  delete[] data_;
}

void CircularBuffer::write(int value) {
  data_[write_index_] = value;
  if (read_index_ == -1) {
    //if buffer is empty, set the read index to the 
 //current write index. because that will be the first 
 //slot to be read later.
    read_index_ = write_index_; 
  }
  write_index_ = (write_index_ + 1) % num_of_slots_; 
}

int CircularBuffer::read() {
  if (read_index_ == -1) {
    // buffer empty
    return -1;
  }
  int ret_val = data_[read_index_];
  read_index_ = (read_index_ + 1) % num_of_slots_;
  if (read_index_ == write_index_) {
    /*all available data is read, now buffer is empty*/
    read_index_ = -1;
  }

  return ret_val;  
}

void CircularBuffer::clear() {
  read_index_ = -1; /* buffer empty */
  write_index_ = 0; /* first time writing to that buffer*/
  delete [] data_;
  data_ = new int[num_of_slots_]; /* allocate space for buffer */
}

float CircularBuffer::rollingAverage() {
	float total = 0.0;
	for (int i = 0; i < num_of_slots_; i++) {
		total += read();
	}

	return (total / num_of_slots_);
}

