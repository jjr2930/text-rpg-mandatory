#include "Object.h"
#include <iostream>

using namespace std;

Object::Object(int64_t id, const string& name) 
    : id(id), name(name)
{}

Object::Object(int64_t id, const string & name, shared_ptr<IConstructionParameter> params)
    : id(id), name(name)
{}

Object::~Object()
{
}

int64_t Object::GetId() const
{
    return id;
}

string Object::GetName() const
{
    return name;
}

void Object::SetName(const std::string& newName)
{
    name = newName;
}
