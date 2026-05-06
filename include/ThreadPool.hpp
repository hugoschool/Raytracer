#pragma once

#include <thread>
#include <vector>

namespace Raytracer {
    class ThreadPool {
        public:
            ThreadPool();
            ~ThreadPool() = default;

            void add(std::thread &&);
            void execute();

        private:
            std::vector<std::thread> _threads;
    };
}
