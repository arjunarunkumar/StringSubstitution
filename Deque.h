#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include <deque>
using namespace std;
template<class T> class TrackingDeque : public deque<T>
{
public:
TrackingDeque();
~TrackingDeque();
void push_front(const T& var);
void push_back(const T& var);
private:
int max_size;
};

template<class T> TrackingDeque<T>::TrackingDeque() 
{
max_size=0;}
template<class T> TrackingDeque<T>::~TrackingDeque()
{
cout<<max_size << endl;
}

template<class T>void  TrackingDeque<T>::push_front(const T& var)
{
deque<T>::push_front(var);
if(deque<T>::size() > max_size)
max_size++;
}

template<class T>void  TrackingDeque<T>::push_back(const T& var)
{
deque<T>::push_back(var);
if(deque<T>::size() > max_size)
max_size++;
}


#endif
