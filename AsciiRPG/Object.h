#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

class IConstructionParameter;
class EventParameter;

class Object
{
public:
    static int64_t generatedCount;

    Object(int64_t id, const std::string& name);
    Object(int64_t id, const std::string& name, shared_ptr<IConstructionParameter> params);
    virtual ~Object();

    virtual void HandleEvent(shared_ptr<EventParameter> message) {}

    //getter
    int64_t GetId() const;
    std::string GetName() const;

    //setter
    void SetName(const std::string& newName);

protected:
    int64_t id;
    std::string name;
};

#endif // !OBJECT_H
