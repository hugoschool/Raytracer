#pragma once

#include "Exception.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <dlfcn.h>
#include <memory>
#include <string>

namespace Raytracer {
    template <typename T>
    class DLLoader {
        public:
            DLLoader() = delete;

            DLLoader(const std::string libraryName) : _libraryName(libraryName), _handle(nullptr)
            {
                openHandle();
            };

            ~DLLoader()
            {
                closeHandle();
            };

            void *openHandle()
            {
                _handle = dlopen(_libraryName.c_str(), RTLD_NOW | RTLD_GLOBAL | RTLD_NODELETE);
                if (_handle == nullptr)
                    throw Raytracer::Exception(dlerror());
                return _handle;
            }

            bool symbolExists(const std::string symbol) const
            {
                if (_handle == nullptr)
                    return false;

                return dlsym(_handle, symbol.c_str()) != nullptr;
            }

            std::shared_ptr<T> getInstance(const std::string functionName, Raytracer::PrimitiveOptions options) const
            {
                if (_handle == nullptr)
                    throw Raytracer::Exception("Impossible to find handle");

                T *(*function)(PrimitiveOptions) = reinterpret_cast<T *(*)(PrimitiveOptions)>(dlsym(_handle, functionName.c_str()));
                if (function == nullptr)
                    throw Raytracer::Exception(dlerror());

                T *instance = (*function)(options);
                if (instance == nullptr)
                    throw Raytracer::Exception("Impossible to find instance");

                return std::shared_ptr<T>(instance);
            };

            void closeHandle()
            {
                if (_handle == nullptr)
                    return;
                if (dlclose(_handle) != 0)
                    throw Raytracer::Exception(dlerror());

                _handle = nullptr;
            }

        private:
            const std::string _libraryName;
            void *_handle;
    };
}
