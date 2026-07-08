#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "SingletonMacro.h"

#include <unordered_map>
#include <random>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

#include "Object.h"
#include "Random.h"

using namespace std;

class IConstructionParameter;
class Entity;

class ObjectManager
{
    SINGLETON(ObjectManager)

public:

    template <typename T,
        typename = enable_if_t<is_base_of<Object, T>::value>>
    shared_ptr<T> CreateOne()
    {
        int64_t randomNumber = Random::GetInstance().RandomRange(INT64_MIN, INT64_MAX);
        shared_ptr<T> newOne = make_shared<T>(randomNumber, string());
        createdObjects.insert({ randomNumber, newOne });

        return newOne;
    }

    template <typename T,
        typename = enable_if_t<is_base_of<Object, T>::value>>
    shared_ptr<T> CreateOne(shared_ptr<IConstructionParameter> params)
    {
        int64_t randomNumber = Random::GetInstance().RandomRange(INT64_MIN, INT64_MAX);
        shared_ptr<T> newOne = make_shared<T>(randomNumber, string(), params);
        createdObjects.insert({ randomNumber, newOne });

        return newOne;
    }
    shared_ptr<Entity> CreateEntity();
    template <typename T,
        typename = enable_if_t<is_base_of<Object, T>::value>>
    vector<shared_ptr<T>> GetObjectsByType() 
    {
        vector<shared_ptr<T>> result;

        for (const auto& pair : createdObjects)
        {
            if (auto castedObject = dynamic_pointer_cast<T>(pair.second))
            {
                result.push_back(castedObject);
            }
        }

        return result;
    }

    void DestroyObject(shared_ptr<Object> object);
    void DestroyEntity(shared_ptr<Entity> entity);

private:
    void Init();
private:
    unordered_map<int64_t, shared_ptr<Object>> createdObjects;
    unordered_set<shared_ptr<Entity>> createdEntities;
};

#endif // !OBJECTMANAGER_H