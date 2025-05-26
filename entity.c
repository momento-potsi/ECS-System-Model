#include "entity.h"

/* Creates new Entity, If `components` is NULL then initialized with no list, If no implements then set `impls` to 0 */
Entity newEntity(const char* name, UIdList* components, SystemImplements impls) /* Use bitwise for multiple implementations */
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
    print("].\n");

    if(recursive && (entity->components != NULL)) {
        printIdList(entity->components);
    }
}



void entityUnitTest()
{
    print("[Entity Unit Test]\n");
    
    UIdList myList = newIdList(INIT_SIZE);
    Entity entity = newEntity("A Ball", &myList, Moveable | Rotatable);
    
    addId(&myList, 65651); addId(&myList, 8663); addId(&myList, 60); addId(&myList, 97556);
    printEntity(&entity, true);

    int result = deAllocateIdList(&myList);
    
    print("[UID Unit Test Exit with code (%d)]\n", result);
}
