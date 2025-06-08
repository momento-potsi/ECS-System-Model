#pragma once
#include <string.h>
#include "component.h"

/* Attributes seperate from components owned (Defines what can be done with data) */
typedef enum {
    Moveable  = (1 << 0),
    Rotatable = (1 << 1),
    SendsData = (1 << 2)
} SystemImplements;

/* Entity struct only holds data relevant to its specifc instance, and system permissions on entity */
typedef struct {
    const char*      name;
    unsigned int     id;
    UIdList*         components;      /* Array of components' UIDs */
    SystemImplements implementations;
} Entity;

/*
    Entity Struct Relation with UIdList:
        - The `UIdList`, `components`, is actually a pointer to the data and should be allocated/managed seperately from any given entity.
            - UIdList (unsigned int *, ...) -> IdArray[] -> Group of any `GlobalComponent` ids (serves as map to physical data)
            - Done like this to optimize cache grouping, Also shifts burden of responsibility to system
            - Electing to uid lists group based on the Component Type both undermines `GlobalComponent` 
              and makes it inefficent for recalling entities spanning across different component types
            - Additionally can manage group of components seperate from entity and transform into different entities by mutating list
            - `Entity` instances are generally maintained independently of system so they aren't "registered" to any structure 
            - (Where as `GlobalComponent*` is a aggregate pool of components -> ComponentsArray[] that needs to be tracked => Registered to system)
    End Documentation 
*/

Entity newEntity(const char* name, UIdList* components, SystemImplements impls);

void printEntity(Entity* entity, bool recursive);

void entityUnitTest();

/* Because UIdList struct already implements much of component manangement/allocation behavior we don't need many functions for entities */
