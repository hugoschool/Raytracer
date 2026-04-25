#pragma once

#include "Exception.hpp"
#include <dlfcn.h>
#include <functional>
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
            std::function<T *(O)> getSymbol(const std::string functionName) const
            {
                if (_handle == nullptr)
                    throw Raytracer::Exception("Impossible to find handle");

                return reinterpret_cast<T *(*)(O)>(dlsym(_handle, functionName.c_str()));
            }

            template <typename T, typename O>
            static std::shared_ptr<T> turnFunctionIntoInstance(std::function<T *(O)> function, O options)
            {
                T *instance = function(options);
                if (instance == nullptr)
                    throw Raytracer::Exception("Impossible to create instance");

                return std::shared_ptr<T>(instance);
            }

            template <typename T, typename O>
            std::shared_ptr<T> getInstance(const std::string functionName, O options) const
            {
                if (_handle == nullptr)
                    throw Raytracer::Exception("Impossible to find handle");

                std::function<T *(O)> function = getSymbol<T, O>(functionName);
                if (!function)
                    throw Raytracer::Exception(dlerror());

                return turnFunctionIntoInstance(function, options);
            };

            void closeHandle();

        private:
            const std::string _libraryName;
            void *_handle;
    };
}
