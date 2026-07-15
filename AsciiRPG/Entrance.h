#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Component.h"
#include <memory>

using namespace std;

class Position;

/*
* TODO: Entrance와 Exit를 하나로 합칠 수 있다.
* 연결된 층을 적어주면 Entrance와 Exit를 하나로 합칠 수 있다.
*/
class Entrance : public Component
{
public:
    using Component::Component;
    Entrance(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    void Update() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;

private:
 
    shared_ptr<Position> myPosition;
    bool previousOverlap = false;
    bool playerEntered = false;
    bool active = false;
};


#endif // !ENTRANCE_H