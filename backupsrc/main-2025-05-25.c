#include "entity.h"

int main()
{
    /* TODO: Redo main file; Currently unusable program */
    // SystemManager* system = newSystem();   
    
    entityUnitTest();

    // deleteSystem(system); 

    return EXIT_SUCCESS;
}


int old_main()
{
/*
    struct Entity motors = {
        .name = "Motor Group 1 (Wheel)",
        .implementations = Moveable | Rotatable,
        .uniqueID = getId()
    };

    struct PositionComponent position = { .rotationalAngle = 0.0, .entityId = motors.uniqueID };

    struct SpeedComponent velocity = {
        .rotationalVelocity = 10.568763, // Initial Velocity // 
        .entityID = motors.uniqueID
    };

    struct Entity gyroSensor = {
        .name = "GyroScope Sensor",
        .implementations = SendsData,
        .uniqueID = getId()
    };

    struct SensorComponent sensor = { .type = GyroscopeSensor, .entityId = gyroSensor.uniqueID };

    SystemManagerPtr system = {
        .entity = NULL,
        .next = NULL
    };
*/

/* anon enum varible in structs */
/* bit flags corresponding to size (unsigned char == 1 << 3) */
    return EXIT_SUCCESS;
}
