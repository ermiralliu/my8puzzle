You can create a function that executes lambdas from a queue without busy-waiting by using a combination of a thread-safe queue and a condition variable. This approach allows the worker thread to efficiently wait for new tasks to arrive in the queue without consuming unnecessary CPU cycles.

Here's a complete example demonstrating this:

```c++
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <atomic>

class TaskQueue {
private:
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
        std::atomic<bool> done{false};

public:
    void enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.push(std::move(task));
        }
        cv.notify_one(); // Notify the worker thread
    }

    void worker_thread() {
        while (!done) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this]{ return !tasks.empty() || done; }); // Wait for a task or done signal
                if(done && tasks.empty()){
                    break;
                }
                task = std::move(tasks.front());
                tasks.pop();
            }
            if(task){
                task(); // Execute the task (outside the lock)
            }
        }
    }
        void stop(){
                {
                        std::unique_lock<std::mutex> lock(mtx);
                        done = true;
                }
                cv.notify_one();
        }
};

int main() {
    TaskQueue task_queue;

    std::thread worker([&task_queue]() {
        task_queue.worker_thread();
    });

    // Enqueue some tasks:
    task_queue.enqueue([]() { std::cout << "Task 1 executed\n"; });
    task_queue.enqueue([]() { std::cout << "Task 2 executed\n"; });
    task_queue.enqueue([]() { std::cout << "Task 3 executed\n"; });

    std::this_thread::sleep_for(std::chrono::seconds(1));
        task_queue.stop();
    worker.join();

    std::cout << "Main thread finished\n";

    return 0;
}
```

**Explanation and Key Improvements:**

1.  **Thread-Safe Queue:** The `TaskQueue` class encapsulates the queue and the necessary synchronization mechanisms.

2.  **Mutex and Condition Variable:**
    *   `std::mutex mtx`: Protects the queue from concurrent access.
    *   `std::condition_variable cv`: Allows the worker thread to wait efficiently for new tasks.

3.  **`enqueue()`:**
    *   Acquires the mutex to safely add a task to the queue.
    *   Calls `cv.notify_one()` to wake up the waiting worker thread.

4.  **`worker_thread()`:**
    *   Uses a `while (!done)` loop to keep processing tasks.
    *   Acquires the mutex.
    *   Uses `cv.wait(lock, [this]{ return !tasks.empty() || done; });` to wait for a task to be available *or* for the `done` flag to be set. This is the crucial part that avoids busy-waiting. The lambda expression is the predicate that determines when the wait should stop.
    *   If a task is available, it's moved from the queue and the mutex is released *before* the task is executed. This is very important to avoid holding the mutex for potentially long-running tasks.
    * The while loop also checks the done flag, so that the thread can be stopped.

5. **Stopping the worker thread:**
    * The stop function sets the done flag and also notifies the condition variable, so that the worker thread can be woken up from its waiting state and stop.
    * It is very important to notify the condition variable, because otherwise the thread might be waiting indefinitely.

**Why This Is Better Than Busy-Waiting:**

*   **No CPU Waste:** The worker thread is blocked by the operating system when the queue is empty, so it doesn't consume CPU cycles.
*   **Efficient Notification:** The condition variable provides an efficient way to signal the worker thread when a new task is available.
*   **Correct Synchronization:** The mutex ensures that access to the queue is properly synchronized, preventing race conditions.

**Key Improvements over a Simple `while (true)` Loop:**

*   **Efficiency:** Avoids busy-waiting, saving CPU resources.
*   **Correctness:** Ensures proper synchronization, preventing data races and other concurrency issues.
*   **Stop mechanism:** Provides a way to stop the worker thread.

This approach using a thread-safe queue and a condition variable is the standard and most efficient way to implement a task queue in C++. It provides correct synchronization and avoids the performance problems of busy-waiting.

-------------------------------------------------------------------------------------------------------------------------------

Unfortunately, the C++ standard library does *not* provide a single, ready-to-use class that combines a queue with the necessary synchronization (mutex and condition variable) for this exact task queue pattern. You generally have to implement the synchronization yourself, as shown in the previous example.

Here's why and what alternatives or related components exist:

**Why No Single Class:**

The C++ standard library focuses on providing general-purpose data structures and synchronization primitives, rather than highly specialized combinations. The task queue pattern is a common but specific use case that can be implemented efficiently using the existing components.

**Related Components and Alternatives:**

1.  **`std::queue` (Requires External Synchronization):** `std::queue` itself is *not* thread-safe. You *must* use external synchronization (like a mutex) when accessing it from multiple threads. This is what was demonstrated in the previous examples.

2.  **`std::condition_variable`:** This is the key component for avoiding busy-waiting. It allows threads to efficiently wait for a condition to become true (in this case, the queue becoming non-empty).

3.  **`std::packaged_task` and `std::future` (For Individual Tasks):** While not a direct replacement for a task queue, `std::packaged_task` and `std::future` are useful for managing individual asynchronous tasks and retrieving their results. If you have a fixed set of tasks, you could potentially use them, but for a dynamic queue of tasks, the previous example is more appropriate.

4.  **Third-Party Libraries (e.g., Boost.Asio, Intel TBB):** Libraries like Boost.Asio and Intel Threading Building Blocks (TBB) provide more advanced asynchronous programming facilities, including thread pools and task schedulers, which can be used to implement task queues more easily. They often offer higher-level abstractions that handle the synchronization details for you.

    *   **Boost.Asio:** Provides asynchronous I/O and networking, but also includes general-purpose asynchronous programming tools that can be used for task queues.
    *   **Intel TBB:** Provides high-level abstractions for parallel programming, including task scheduling, parallel algorithms, and concurrent data structures.

5. **Executors (C++20):** C++20 introduces executors, which are a more standardized way to manage asynchronous operations. Executors can be used to submit tasks to a thread pool, which can effectively act as a task queue. However, executors are a more general concept and might require more setup than a simple task queue implementation.

**Example using a thread pool (C++20):**

```c++
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <atomic>
#include <future>
#include <execution>

int main() {
    std::vector<std::future<void>> futures;
    for(int i = 0; i<10; ++i){
        futures.push_back(std::async(std::launch::async, [i](){std::cout<<"Task "<<i<<" executed on thread "<<std::this_thread::get_id()<<"\n";}));
    }
    for(auto& f : futures){
        f.get();
    }
    std::cout << "Main thread finished\n";

    return 0;
}
```

**Recommendation:**

*   For simple task queue implementations where you need basic thread safety and efficient waiting, implementing your own `TaskQueue` class using `std::queue`, `std::mutex`, and `std::condition_variable` (as shown in the previous example) is often the most straightforward and efficient approach.
*   If you need more advanced features like thread pools, task scheduling, or more complex concurrency patterns, consider using a third-party library like Boost.Asio or Intel TBB, or C++20 executors.

In many cases, the overhead of implementing the synchronization yourself is minimal, and it gives you more control over the behavior of your task queue. Therefore, it is often preferred over using a third party library.
