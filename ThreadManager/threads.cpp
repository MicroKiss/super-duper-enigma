#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

template<typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue () = default;

    ~ThreadSafeQueue () = default;

    T Pop ()
    {
        std::lock_guard<std::mutex> lock(mutex);
        T  retVal = queue.front ();
        queue.pop ();
        return retVal;
    }

    bool Empty () const
    {
        return queue.empty ();
    }
       
    template <typename TT>
    void Push (TT&& elem)
    {
        std::lock_guard<std::mutex> lock (mutex);
        queue.push (std::forward<TT> (elem));
    }

private:
    std::queue<T> queue;
    std::mutex mutex;
};



void WorkerFunction (std::atomic<bool>& shouldDie, std::condition_variable& cv, std::mutex& cvMutex, ThreadSafeQueue<std::function<void ()>>& jobs, std::string const& threadName)
{

    std::function<void ()> jobToDo;
    while (!shouldDie) {
        std::unique_lock<std::mutex> lock (cvMutex);
        cv.wait (lock, [&jobs, &shouldDie] {return !jobs.Empty () || shouldDie; });
        if (shouldDie)
            break;
        
        jobToDo = jobs.Pop ();
        lock.unlock ();

        std::cout << "work assigned to worker: " << threadName << "\n";
        jobToDo ();
        std::cout << "work finished\n";
        cv.notify_one ();
    }
    std::cout << "worker ended\n";
}

class ThreadManager
{
private:
    ThreadSafeQueue<std::function<void ()>> jobs;
    std::vector<std::thread> workers;
    std::mutex cvMutex;
    std::condition_variable cv;
    std::atomic<bool> forceQuit;
public:
    ThreadManager (size_t numOfWorkers) : forceQuit (false)
    {
        for (size_t i = 0; i < numOfWorkers; i++)
            workers.emplace_back (WorkerFunction, std::ref (forceQuit), std::ref (cv), std::ref(cvMutex), std::ref (jobs), std::to_string (i));
    }
    ~ThreadManager ()
    {
        forceQuit = true;
        cv.notify_all ();
        for (auto&& worker : workers)
            worker.join ();
        std::cout << "all workers are finished destroying threadManager\n";
    }

    void NewJob (std::function<void ()> func)
    {
        jobs.Push (func);
        cv.notify_one ();
    }

    void ForceStop ()
    {
        forceQuit = true;
    }

    void WaitAndStop ()
    {
        std::unique_lock<std::mutex> lock (cvMutex);
        cv.wait (lock, [this] {return jobs.Empty (); });
        lock.unlock ();
        forceQuit = true;
        cv.notify_all ();
    }
};



int main ()
{
    {
        auto exampleWork = [] {
            std::this_thread::sleep_for (1s);
        };
        ThreadManager threadManager (3);
        std::this_thread::sleep_for (1s);
        std::cout << "giving out 5 work initially and every secs 3 more for 3 seconds\n";
        for (size_t i = 0; i < 5; i++)
            threadManager.NewJob (exampleWork);        
        for (size_t i = 0; i < 3; i++) {
            std::this_thread::sleep_for (1s);
            threadManager.NewJob (exampleWork);
            threadManager.NewJob (exampleWork);
            threadManager.NewJob (exampleWork);
        }
           

        
        threadManager.WaitAndStop ();
    }
}

