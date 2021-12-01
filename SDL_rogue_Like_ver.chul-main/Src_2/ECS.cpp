#include "ECS/ECS.h"


//Group 은 최대 32인 user_defined datatype이네~

//Grouping
void Entity::addGroup(std::size_t mGroup)
{
    groupBitset[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}
