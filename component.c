#include "component.h"

GlobalComponent componentFromPosition(struct PositionComponent position) {
    return (GlobalComponent) {
        .position = position,
        .hasData = true,
        .id = getId()
    };
}

void printPositionComponent(struct PositionComponent position) 
{
    print("Positon Component @ { %p }\n", (void*) &(position));
    printVector(position.vector);
    print("Position as Angle: %f\n", position.rotationalAngle);
}

GlobalComponent componentFromSpeed(struct SpeedComponent speed) {
    return (GlobalComponent) {
        .speed = speed,
        .hasData = true,
        .id = getId()
    };
}

void printSpeedComponent(struct SpeedComponent speed) 
{
    print("Speed Component @ { %p }\n", (void*) &(speed)); 
    printVector(speed.velocityV3);
    print("Speed as Angle: %f\n", speed.rotationalVelocity);
}

GlobalComponent componentFromSensor(struct SensorComponent sensor) {
    return (GlobalComponent) {
        .sensor = sensor,
        .hasData = true,
        .id = getId()
    };
}

void printSensorComponent(struct SensorComponent sensor)
{
    print("Sensor Component @ { %p }\n", sensor.inputData); 
    switch (sensor.type)
    {
        case InfraredSensor: print("\t Type: INFRARED SENSOR \n");
            break;
        
        case ProximitySensor: print("\t Type: PROXIMITY SENSOR \n");
            break;

        case GyroscopeSensor: print("\t Type: GYROSCOPESENSOR\n");
            break;

        case PressureSensor: print("\t Type: PRESSURE SENSOR \n");
            break;

        default: print("Sensor type not Recognized.\n"); break;
    }
}

Vector3 newVec() {
    return (Vector3) { .x = 0, .y = 0, .z = 0 };
}

void printVector(Vector3 vector)
{
    double magnitude = sqrt((double) ((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z)));
    print("Vector Component @ { %p }\n", (void*) &(vector));
    print("\t Vector (Components): [ x: %d, y: %d, z: %d ]\n", vector.x, vector.y, vector.z);
    print("\t Vector (Magnitude): [%f]\n", magnitude);
}

GlobalComponent newComponent(enum ComponentType type)
{
    switch (type) 
    {
        case Position:
            return (GlobalComponent) { 
                .position = { .vector = newVec() },
                .hasData = true,
                .id = getId() 
            }; break;
        case Speed:
            return (GlobalComponent) {
                .speed = { .velocityV3 = newVec() },
                .hasData = true,
                .id = getId()
            }; break;
        case Sensor:
            return (GlobalComponent) {
                .sensor = { .type = ProximitySensor, .inputData = NULL },
                .hasData = true,
                .id = getId()
            }; break;
        default: panic("Invalid Component Type.");
    }
}

UIdList newIdList(size_t initSize) {
    return (UIdList) {
        .array = (unsigned int*) malloc(initSize * sizeof(unsigned int)),
        .allocated = initSize,
        .size = 0
    };
}

/* Returns index otherwise returns -1 if not found */
int hasId(UIdList* list, unsigned int id) 
{
    if(list == NULL) { return -1; }

    for (int i = 0; i < list->size; i++) {
        if (list->array[i] == id) { return i; }    
    }    

    return -1;
}

void printIdList(UIdList* list) 
{
    if (list == NULL) { print("[NULL UID List]\n"); }

    print("[Unique Id List] (Allocated Size: %zu, Elements Count: %zu) \n", list->allocated, list->size);
    
    /* \t -> <UID1: 202654, UID2: 500752, UID3: 585006> \n */ /* Intended Result Example */

    unsigned int currentIndex = 0;

    print("\t -> <");

    for (size_t i = 0; i < list->size; i++) /* Iterate through list (only array elements with assigned value (occupied)) */
    {
        if (list->array[i] == NIL_ID) { /* NULL IDs if-statement */
            print("UID%zu: NIL-ID", (i + 1));
        } else {
            print("UID%zu: %06u", (i + 1), list->array[i]); /* Prints UID with 6 decimal places (to account for 1M UIDs) */    
        }
        

        /* Limit to 5 UIDs per line for readability */
        if (((currentIndex % 5) == 0) && (currentIndex != 0)) { 
            print(">\n"); /* End line */
            if (currentIndex != list->size) { /* Start next line? */
                print("\t -> <");
            }
        } else { /* If not end of line then next item */
            print(", ");
        }

        currentIndex++;    
    }

    print("[End UID List]\n");
}

/* I tire of adding in numerous null checks in my code, I yearn for memory allocations and blissfully assuming it worked. */

int addId(UIdList* list, unsigned int id) 
{
    if (id == NIL_ID) {
        print("[WARN]: Can't add NIL UID to list (UIdList unchanged) \n");
        return 1;
    }
    
    if (list != NULL) {
        if ((list->allocated - list->size) > 2) { /* Still has room in list? */
            if (hasId(list, id) != -1){
                print("[ERROR]: Can't add duplicate UID(%u) to list\n", id);
            }
            
            list->array[list->size] = id;
            list->size++;
        } else { /* Reallocate & add */
            print("[WARN]: Allocating additional memory to UID List with space (%u/%u)", list->size, list->allocated);
            
            unsigned int* temp = (unsigned int*) realloc(list->array, sizeof(unsigned int) * (list->allocated + INIT_SIZE));
            if (temp == NULL) {
                panic("Failed to reallocate `UIdList` to add new UID Entry"); /* FIXME: dont forget to free */
                return -1;
            }
            
            list->array = temp;
            list->array[list->size] = id; /* TODO: delete and reorganize repetative code */
            list->size++;
        }
        
    } else { /* Allocate, then add to list */
        if(allocateIdList(list, INIT_SIZE) < EXIT_SUCCESS) {
            panic("Failed to allocate `UIdList` to add new UID Entry");
            return -1;
        }

        list->array[list->size] = id;
        list->size++;
    }

    return EXIT_SUCCESS;
}

int removeId(UIdList* list, unsigned int id) /* Because of how UIDs are removed don't refer to components via the index */
{
    if(list != NULL) 
    {
        for (size_t i = 0; i < list->size; i++) { /* Search for Id */ 

            /* Method of removal? (assign null id? make new updated array and assign? way to physically move?) */
            if (list->array[i] == id) 
            {   
                /* Opted for shifting elements left method */
                for (int j = i; j < (list->size - 1); j++) { 
                    /* Iterate starting from `id` to "overwrite" target element. Move all elements down to fill in gap */
                    /* Stop iteration before last element as nothing left to shift down, thus => `j < (list->size - 1)` */
                    list->array[j] = list->array[j + 1];
                }

                list->size--;

                /* Now reduce size to "forget" element, check if new size exceeds allocation threshold */
                if((list->allocated - list->size) > (INIT_SIZE + 5)) {
                    unsigned int* tmpPtr = (unsigned int*) realloc(list->array, sizeof(unsigned int) * list->size);
                    if (tmpPtr == NULL) {
                        print("[WARN]: Unable to resize `UIdList` array.\n");
                        return EXIT_FAILURE;
                    }
                    list->array = tmpPtr;
                }

                return EXIT_SUCCESS;
            }
        }
        
        print("UID(%u) not found in list. Unable to remove.", id);
        return -1; /* Id not found in list */
    } else {
        print("[ERROR]: Unable to remove <UID: %u> from NULL List.\n", id);
        return -1;
    }
}

int deAllocateIdList(UIdList* list) 
{
    if (list != NULL) {
        free(list->array);
    } else {
        print("[ERROR]: Unable to deallocate NULL List.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;    
}


void componentUnitTests()
{
    print("[UID List Unit Tests]\n");
    
    UIdList myList = newIdList(INIT_SIZE);
    printIdList(&myList);
    addId(&myList, 65651); addId(&myList, 8663); addId(&myList, 60); addId(&myList, 97556);
    printIdList(&myList);
    removeId(&myList, 97556);
    printIdList(&myList);
    int result = deAllocateIdList(&myList);

    print("[UID Unit Test Exit with code (%d)]\n", result);


    print("[Component Unit Tests]\n");
    GlobalComponent position = newComponent(Position);
    GlobalComponent speed = newComponent(Speed);
    GlobalComponent sensor = newComponent(Sensor);

    printPositionComponent(position.position);
    printSpeedComponent(speed.speed);
    printSensorComponent(sensor.sensor);

    position = (GlobalComponent) { /* Repurpose `PositionComponent` as `SpeedComponent` via union */
        .speed = (struct SpeedComponent) {
            .velocityV3 = (Vector3) { .x = 16, .y = 56, .z = 169 }
        },
        .id = getId(),
        .hasData = true
    };

    printSpeedComponent(position.speed); /* Should work */
    
    print("[Intended Undefined Behavior] (TestCase: Improper Union access) \n");
    printPositionComponent(position.position); /* Still configured as SpeedComponent */

    print("[End Unit Tests].\n");
}

