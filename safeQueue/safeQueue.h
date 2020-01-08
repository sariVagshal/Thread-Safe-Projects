#ifndef __SAFEQUEUE_H__
#define __SAFEQUEUE_H__
#include <queue> // std::queue
#include<pthread.h>
#include <semaphore.h>
#include <stdexcept>

#define CAPACITY 10

template<typename T>
class SafeQueue
{
public:
	SafeQueue();
	~SafeQueue();
	
	void push(const T&);
	T pop();
private:
	std::queue<T> m_queue;
	
	pthread_mutex_t m_mutex;
	sem_t m_empty, m_full;
};

template<typename T>
SafeQueue<T>::SafeQueue()
{
	sem_init(&m_empty, 0, CAPACITY);
	sem_init(&m_full, 0, 0);
	int status = pthread_mutex_init(&m_mutex, NULL);
	
	if (status != 0)
	{
		sem_destroy(&m_empty);
		sem_destroy(&m_full);
		
		throw std::invalid_argument("failed to init mutex");
	}
}

template<typename T>
SafeQueue<T>::~SafeQueue()
{
	pthread_mutex_destroy(&m_mutex);
	
	sem_destroy(&m_empty);
	sem_destroy(&m_full);
}

template<typename T>
void SafeQueue<T>::push(const T& t)
{
	sem_wait(&m_empty);
	pthread_mutex_lock(&m_mutex);
	
	m_queue.push(t);
	
	pthread_mutex_unlock(&m_mutex);
	sem_post(&m_full);
}

template<typename T>
T SafeQueue<T>::pop()
{
	sem_wait(&m_full);
	pthread_mutex_lock(&m_mutex);
	
	T temp = m_queue.front();
	m_queue.pop();
	
	pthread_mutex_unlock(&m_mutex);
	sem_post(&m_full);
	
	return temp;
}


#endif //__SAFEQUEUE_H__









