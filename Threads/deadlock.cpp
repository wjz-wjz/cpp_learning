#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "worker: waiting...\n";
    cv.wait(lock, [] { return ready; });
    std::cout << "worker: starts working\n";
}

int main() {
    std::thread t(worker);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "main: ready = true\n";
    }

    cv.notify_one();

    t.join();
}