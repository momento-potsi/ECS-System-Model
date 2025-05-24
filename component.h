#pragma once
#include "utility.h"

typedef struct  { int x, y, z; } Vector3;

Vector3 newVec();

void printVector(Vector3 vector);

enum ComponentType { Position, Speed, Sensor };

/* Each component type has their own associated data (different types) */

struct PositionComponent
{
    union {
        Vector3 vector;
        double  rotationalAngle;
    };
};

void printPositionComponent(struct PositionComponent position);

struct SpeedComponent
{
    union {
        Vector3 velocityV3;
        double  rotationalVelocity;
    };
};

void printSpeedComponent(struct SpeedComponent speed);

struct SensorComponent
{
    enum {
        InfraredSensor, ProximitySensor,
        GyroscopeSensor, PressureSensor
    } type;

    void* inputData; /* Nothing here just for fun */
};

void printSensorComponent(struct SensorComponent sensor);

/* General Wrapper type for Components */
typedef struct 
{
    /* Enum variant, WARNING: use as correct variant only to avoid UB */
    bool hasData;
    union { 
        struct PositionComponent position;
        struct SpeedComponent    speed;
        struct SensorComponent   sensor;
    };

    unsigned int id; /* By default is `0` to indicate if `id` isn't set */
} GlobalComponent;

GlobalComponent newComponent(enum ComponentType type);
GlobalComponent componentFromPosition(struct PositionComponent position);
GlobalComponent componentFromSpeed(struct SpeedComponent speed);
GlobalComponent componentFromSensor(struct SensorComponent sensor);

typedef struct 
{
    /* Unique IDs Array[] */
    unsigned int* array;
    /* Size = current # of elements */
    size_t        size; 
    /* Memory currently Allocated for Array */    
    size_t        allocated;
    /* Realloc at set threshold */ 
} UIdList;

UIdList newIdList(size_t initSize);
int     hasId(UIdList* list, unsigned int id);
void    printIdList(UIdList* list);
int     addId(UIdList* list, unsigned int id);
int     removeId(UIdList* list, unsigned int id);
int     deAllocateIdList(UIdList* list);

void componentUnitTests(); 