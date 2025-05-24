#include "entity.h"

/* Attributes seperate from components owned */
typedef enum { /* Defines what can be done with data */
    Moveable  = (1 << 0),
    Rotatable = (1 << 1),
    SendsData = (1 << 2)
} SystemImplements;

typedef struct {
    const char*      name;
    unsigned int     id;
    unsigned int*    components;      /* Array of components */
    size_t           size;            /* Number of components in list */
    SystemImplements implementations;
} Entity;

/* Creates new Entity, If `components` is NULL then initialized with no list, If no implements then set `impls` to 0 */
Entity newEntity(const char* name, unsigned int* components, SystemImplements impls) /* Use bitwise for multiple implementations */
{
    if (components != NULL) {
        return (Entity) {
            .name = name, .id = getId(),
            .components = components,
            .implementations = impls 
        };
    }
    
    return (Entity) {
        .name = name, .id = getId(),
        .implementations = impls
    };
}

void printEntity(Entity* entity, bool recursive)
{
    unsigned int count = 0;

    if (entity == NULL) {
        print("Error: Entity Undefined.\n");
        return; 
    }

    print("ENTITY [%s | id: %d]\n", entity->name, entity->id);
    print("\t |> implements => [");
    if (entity->implementations & Moveable) {
        if (count != 0) { print(", MOVEABLE"); } else { print("MOVEABLE"); }
        count++;
    }
    if (entity->implementations & Rotatable) {
        if (count != 0) { print(", ROTATION"); } else { print("ROTATION"); }
        count++;
    }
    if (entity->implementations & SendsData) {
        if(count != 0) { print(", SENDSDATA"); } else { print("SENDSDATA"); }
    }
    print("].");

    if(recursive) {
        /* find components else -1, use to printComponent */ /* TODO: */
    }
}

void addComponent(unsigned int componentId, Entity* entity) {
    /* aww man have to do malloc stuff */ /* TODO: */
}

void removeComponent();


