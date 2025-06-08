#pragma once
#include <time.h>
#include "entity.h"

/* ReturnStatus systemImpl(sysmanager, time, currentsystemstate or context, input?) */
typedef ReturnStatus (*ThreadFnPtr) (SystemManager, struct tm, enum Context, bool);
/* TODO: add handlers funcs for interactions between systems? */


typedef struct /* System modules treated as processes */
{
    enum 
    {
        /* General State (Note: `DELEGATE` - indicates intended handoff to another system) */
        SUCCESS, IDLE, RUNNING, PAUSED, TERMINATED, DELEGATE,

        /* Warnings and Errors */
        WARNING, ERR_RECOVER, ERR_RESET, FATALERR

    } CODE;

    const char* description;
    void* dataDump;

} ReturnStatus;

enum Context /* General Program Context to pass to system modules */
{
    /* Program Running Status */
    SUCCESS = (1 << 0),    IDLE = (1 << 1),        RUNNING = (1 << 2),    PAUSED = (1 << 3), 
    
    /* Program Enviroment */
    PRGM_START = (1 << 4), LOWMEM = (1 << 5),      LOWCPU = (1 << 6),     SHUTDOWN = (1 << 7),
    
    /* Errors */
    WARNING = (1 << 8),    ERR_RECOVER = (1 << 9), ERR_RESET = (1 << 10), FATALERR = (1 << 11)
};


/*
- [SystemManager] - Structure responsible for storing, registering, and updating components
                  - Also serves as interface for other modular systems that operate on data/entity
    - [entityIds]
                  - Unique Id List of Entities for systems to update and read data
    - [componentIds]
                  - Pool of all registered component ids
    - [componentData]
                  - Corresponding pool of component data 
*/

typedef struct { 
    UIdList          entityIds;     /* List of Entities */
    UIdList          componentIds;  /* List of all GlobalComponent Ids */
    GlobalComponent* componentData; /* All GlobalComponent Data used */
    /* To Add function ptr for tick for other systems, manage system perms */
} SystemManager;
/*



        
    int main() {
      time_t now; time(&now);
      struct tm *local = localtime(&now);
      printf("Local time: %d-%02d-%02d %02d:%02d:%02d\n",
             local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
             local->tm_hour, local->tm_min, local->tm_sec);
      return 0;
    }

        
        FnPtrList{}
        SystemInterface (serves as wrapper for systems)
        {
            id, fnptr, name, perms, storelastupdatetime, fatalerrorbool
            {
                SystemSpecificData
            }
        }

*/

/* todo add function declarations */
/* Defs */
void addEntity(SystemManager* manager, Entity* entity);

void update(SystemManager* manager);



