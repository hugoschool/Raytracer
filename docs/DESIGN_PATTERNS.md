# Design Patterns used in Raytracer

## Factory

The factory allows us to construct primitives, lights and transforms.

It calls the `registerAllPlugins` function in its constructor which goes through the entire `pluginsDir` folder (hardcoded to `./plugins/` from the `./raytracer` path in `Utils.hpp`) and opens all the plugins and adds all of their functions in the factory.

> The `registerAllPlugins` function determines categories based on the plugins name:
>
> `raytracer_primitive_sphere.so`
>
> Primitive is the category and sphere is the object associated.

It then exposes `create...` function based on the category (primitives, lights...).

Available in: `Factory.hpp`

Learn more about factories here: https://refactoring.guru/design-patterns/factory-method

## Decorator

The decorator allows to imbracate object one into another.

> See the image of the `Real-World analogy` here: https://refactoring.guru/design-patterns/decorator

It is useful to order the transformations in the Raytracer.

Transformation order is very important as it can completely change the shape of the object.

How it works:

Each transformation object contains the object of the next one.
If we're seeing it as russian nesting dolls, the top one contains a pointer to the one directly underneath. The last one contains a null pointer.
Each one except the last one calls the pointer's same method first then proceeds with the transformation .

Example:

A rotation and a scale doesn't do the same as a scale and a rotation.

Available and used in: `{ITransform,ATransform,Default,Scale}.hpp`

Learn more about decorator patterns: https://refactoring.guru/design-patterns/decorator
