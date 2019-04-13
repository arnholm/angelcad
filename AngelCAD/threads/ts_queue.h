#ifndef TS_QUEUE_H
#define TS_QUEUE_H

// this code obtained from
// http://stackoverflow.com/questions/15278343/c11-thread-safe-queue

// The ts_queue offers a thread safe way of communicating information packets
// between threads. Typical use is a thread reading data from some data source
// and forwarding to another thread via the queue.
// One thread calls q.enqueue(t) to put data on the back of the queue,
// another thread removes data from the front of the queue using t=q.dequeue()

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class ts_queue
{
public:
  ts_queue(void)
    : q()
    , m()
    , c()
  {}

  ~ts_queue(void)
  {}

  void enqueue(T t)
  {
     // Unlock before notifying to avoid waking up
     // the waiting thread only to block it again.
     // Therefore this extra code block.
     {
       std::lock_guard<std::mutex> lock(m);
       q.push(t);
     }
     c.notify_one();
  }

  // return false if queue is empty
  bool try_dequeue(T& val)
  {
    std::unique_lock<std::mutex> lock(m);
    if(q.empty())return false;

    val = q.front();
    q.pop();
    return true;
  }

  // wait for new data if queue empty
  T dequeue(void)
  {
    std::unique_lock<std::mutex> lock(m);
    while(q.empty())
    {
      c.wait(lock);
    }
    T val = q.front();
    q.pop();
    return val;
  }

  size_t size() const
  {
     std::lock_guard<std::mutex> lock(m);
     return q.size();
  }

private:
  std::queue<T> q;
  mutable std::mutex m;
  std::condition_variable c;
};

#endif // TS_QUEUE_H
