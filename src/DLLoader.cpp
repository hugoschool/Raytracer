#include "DLLoader.hpp"
#include "Exception.hpp"
#include <dlfcn.h>
#include <memory>
#include <string>

Raytracer::DLLoader::DLLoader(const std::string libraryName) : _libraryName(libraryName), _handle(nullptr)
{
    openHandle();
};

Raytracer::DLLoader::~DLLoader()
{
    closeHandle();
};

void *Raytracer::DLLoader::openHandle()
{
    _handle = dlopen(_libraryName.c_str(), RTLD_NOW);
    if (_handle == nullptr)
        throw Raytracer::Exception(dlerror());
    return _handle;
}

bool Raytracer::DLLoader::symbolExists(const std::string symbol) const
{
    if (_handle == nullptr)
        return false;

    return dlsym(_handle, symbol.c_str()) != nullptr;
}

void Raytracer::DLLoader::closeHandle()
{
    if (_handle == nullptr)
        return;
    if (dlclose(_handle) != 0)
        throw Raytracer::Exception(dlerror());

    _handle = nullptr;
}
