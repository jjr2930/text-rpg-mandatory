#include "Object.h"
#include "Logger.h"

#include <format>
#include <iostream>

using namespace std;

int64_t Object::generatedCount = 0;

Object::Object(int64_t id, const string& name) 
    : id(id), name(name)
{
    generatedCount++;

    //Logger::LogInfo(std::format("Construction! createdCount: {}, name {}, id {}", generatedCount, name, id));
}

Object::Object(int64_t id, const string & name, shared_ptr<IConstructionParameter> params)
    : id(id), name(name)
{
    generatedCount++;

    //Logger::LogInfo(std::format("Construction! createdCount: {}, name {}, id {}", generatedCount, name ,id));
}

Object::~Object()
{
    generatedCount--;
    //Logger::LogInfo(std::format("Destruction! createdCount: {}, name {}, id {}", generatedCount, name ,id));  
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
