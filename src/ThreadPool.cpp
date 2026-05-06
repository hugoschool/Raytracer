#include "ThreadPool.hpp"

Raytracer::ThreadPool::ThreadPool() : _threads()
{
}

void Raytracer::ThreadPool::add(std::thread &&thread)
{
    _threads.push_back(std::move(thread));
}

void Raytracer::ThreadPool::execute()
{
    for (std::thread &thread : _threads) {
        thread.join();
    }
}
