#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"


#include "IConstructionParameter.h"

using namespace std;

class Entity;

class Component : public Object
{
public:
    class ConstructionParamterBase : public IConstructionParameter
    {
    public:
        ConstructionParamterBase(shared_ptr<Entity> entity);
    public:
        weak_ptr<Entity> entity;
    };

public:
    using Object::Object;
    Component(int64_t id, const std::string& name, shared_ptr<IConstructionParameter> params);
    virtual ~Component();

    virtual void Start() {};
    virtual void Update() {};
    virtual void OnDestroy() {};

    //getter
    bool GetIsStarted() const;

    //setter
    void SetIsStarted(bool value);

    shared_ptr<Entity> GetEntity() const;

protected:
    void DestroyEntity();

protected:
    bool isStarted = false;
    weak_ptr<Entity> entity;
};

#endif // !COMPONENT_H

