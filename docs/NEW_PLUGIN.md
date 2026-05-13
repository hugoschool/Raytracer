# Adding a new plugin to the Raytracer

If you wish to create a new plugin (whether it is a primitive, a material, a transform) for the Raytracer, here's how to proceed.

> [!NOTE]
> This guide will be talking about mostly primitives, however it can apply to any other category.

## Includes

You must use the interfaces included within the Raytracer.

For example, if you wish to create a plugin for the primitives, named the `AwesomePrimitive`, you must use the IPrimitive interface and derive from it.

Creating your own header file, can be done as such:

```cpp
#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"

namespace Raytracer {
    class AwesomePrimitive : public APrimitive {
        public:
            AwesomePrimitive(PrimitiveOptions options);
            ~AwesomePrimitive() = default;

            HitInfo hits(Ray &ray) override;
            Math::Vector3D getNormal(const Math::Point3D) const override;
    };
}
```

## Entrypoint

Once done, you need to create an entrypoint for your plugin. Use the appropriate one that is matching the `Utils.hpp` variables.

For a primitive, your entrypoint must be named `primitiveEntrypoint`.

Example:

```cpp
extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::AwesomePrimitive(options);
}
```

## Overriding the appropriate functions

Override all functions such as `hits`, `getNormal` with proper values for your new primitive.

> This is different for each interface, make sure to use the right one. See your related interface definition: for primitives, it is `IPrimitive`.

## Compiling it

Make sure to compile it to a shared library.

You must use the `-fPIC` flag for object files and `-shared` for shared object.

Once done, to use your plugin, you must name it as such:

`raytracer_category_name.so`

In our case, the plugin name is `raytracer_primitive_awesome.so`.

> Do not include any underscores inside your name or inclusion of your plugin will fail.

> Please consult the already existing plugins and try to match them.

## Usage

Inside the `.cfg` file, just add your primitive at the right spot:

Example for our primitive:

```cfg
primitives:
{
    awesome = (
        { x = 0; y = 0; z = -200; r = 120; color = { r = 255; g = 0; b = 0; }; },
    );
};
```
