
#ifndef ObjectPool_RingBuffer_H
#define ObjectPool_RingBuffer_H
 
#include <atomic>
#include <cstddef>

using namespace std;
 
template <typename T> class RingBuffer {
	T *m_buffer;
	atomic<size_t> m_head;
	atomic<size_t> m_tail;
	const size_t m_size;
 
	size_t next(size_t current) {
		return (current + 1) % m_size;
	}
 
public:
 
	RingBuffer(const size_t size) : m_size(size), m_head(0), m_tail(0) {
		m_buffer = new T[size];
	}
 
	virtual ~RingBuffer() {
		delete [] m_buffer;
	}
 
	bool push(const T &object) {
		size_t head = m_head.load(memory_order_relaxed);
		size_t nextHead = next(head);
		if (nextHead == m_tail.load(memory_order_acquire)) {
			return false;
		}
		m_buffer[head] = object;
		m_head.store(nextHead, memory_order_release);
 
		return true;
	}
 
	bool pop(T &object) {
		size_t tail = m_tail.load(memory_order_relaxed);
		if (tail == m_head.load(memory_order_acquire)) {
			return false;
		}
 
		object = m_buffer[tail];
		m_tail.store(next(tail), memory_order_release);
		return true;
	}

	float rollingAverage() {
		float total = 0.0;
		for (int i = 0; i < m_size; i++) {
			total += m_buffer.load(memory_order_relaxed);
		}

		return (total / m_size);
	}
};
 
 
#endif