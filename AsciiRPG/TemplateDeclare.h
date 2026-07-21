#ifndef TEMPLATE_DECLARE_H
#define TEMPLATE_DECLARE_H

#include <concepts>

class Component;
class Object;

template<class T>
concept ComponentType = std::derived_from<T, Component>;

template<class T>
concept ObjectType = std::derived_from<T, Object>;

#endif // !TEMPLATE_DECLARE_H
