#pragma once

#include "Exception.hpp"
#include <dlfcn.h>
#include <memory>
#include <string>

namespace Raytracer {
    class DLLoader {
        public:
            DLLoader() = delete;

            DLLoader(const std::string libraryName);

            ~DLLoader();

            void *openHandle();

            bool symbolExists(const std::string symbol) const;

            template <typename T, typename O>
            std::shared_ptr<T> getInstance(const std::string functionName, O options) const
            {
                if (_handle == nullptr)
                    throw Raytracer::Exception("Impossible to find handle");

                T *(*function)(O) = reinterpret_cast<T *(*)(O)>(dlsym(_handle, functionName.c_str()));
                if (function == nullptr)
                    throw Raytracer::Exception(dlerror());

                T *instance = (*function)(options);
                if (instance == nullptr)
                    throw Raytracer::Exception("Impossible to find instance");

                return std::shared_ptr<T>(instance);
            };

            void closeHandle();

        private:
            const std::string _libraryName;
            void *_handle;
    };
}
