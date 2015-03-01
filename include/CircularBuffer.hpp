
#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

// This is a fixed-size, circular buffer of integer.
// The class is not thread-safe,
class CircularBuffer {
public:

  // Creates a buffer with 'slots' slots.
  explicit CircularBuffer(int slots);
  // Destructor.
  ~CircularBuffer();
  // Writes 'value' to the next available slot. It may overwrite
  // values that were not yet read out of the buffer.
  void write(int value);
  // Returns the next value available for reading, in the order they
  // were written, and marks slot as read. If the buffer is empty returns -1.
  int read();
  // Removes all the elements from the buffer.
  void clear();
  // Computes the average
  float rollingAverage();
  // Computes the derivative
  float findDerivative();

private:
  //array of integers
  int* data_;
  // the size of the buffer
  int  num_of_slots_;
  //index to read the next integer from buffer
  int  read_index_;
  //index to write a new integer to buffer
  int  write_index_;

  // Non-copyable, non-assignable.
  CircularBuffer(CircularBuffer&);
  CircularBuffer& operator=(const CircularBuffer&);
};

#endif  // _CIRCULAR_BUFFER_H_
