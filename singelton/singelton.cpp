#include <iostream>
#include <cstring> //std::strerror
#include <pthread.h>


template<class T>
class Singelton
{
public:
	Singelton();
	~Singelton();
	
	T& getInstance();
	T& setInstance(const T t);
private:
	T * m_instance;
};

Singelton<int> g_sp;

#define NUM_THREADS 8

pthread_t tid[NUM_THREADS];
pthread_mutex_t lock;

void* testSingelton(void *arg)
{
	
	g_sp.setInstance( *((int*)(&arg)) );
	
	return 0;
}

int main()
{
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        std::cout << "mutex init failed" << std::endl;
        return 1;
    }
	
	int err;
    for (int i=0;i < NUM_THREADS; ++i)
    {
        err = pthread_create(&(tid[i]), NULL, &testSingelton, (void *)(i + 2));
        if (err != 0)
            std::cout << "can't create thread :[" << std::strerror(err) << "]" << std::endl;
    }
    
	std::cout << g_sp.getInstance() << std::endl;
	
	for (int i=0; i<NUM_THREADS; ++i)
    	pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
	


//===========  implements of Singelton class   ======================//
template <class T>
Singelton<T>::Singelton()
{
	m_instance = NULL;
}

template <class T>
Singelton<T>::~Singelton()
{
	delete m_instance;
}

template <class T>
T& Singelton<T>::setInstance(const T t)
{
	pthread_mutex_lock(&lock);
	
	getInstance() = t;
	
	pthread_mutex_unlock(&lock);
		
	return *m_instance;
}

template <class T>
T& Singelton<T>::getInstance()
{
    if (m_instance != NULL)
        return *m_instance;
    pthread_mutex_lock(&lock);
    if (m_instance == NULL)
    {
        try
        {
            m_instance = new T();
        }
        catch (std::bad_alloc & e)
        {
            pthread_mutex_unlock(&lock);
            throw;
        }
        pthread_mutex_unlock(&lock);
    }
    return *m_instance;
}
