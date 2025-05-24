


/* Systems */
typedef struct { /* Use ID as index */
    struct Entity*     entityData;   /* List of Entities */
    unsigned int*    positionData;   /* List of Position IDs */
    unsigned int*       speedData;   /* List of Speeds IDs */
    unsigned int*      sensorData;   /* List of Sensors IDs */
    GlobalComponent* componentData;  /* All Component Data used */
} SystemManager;
/* todo add function declarations */
/* Defs */
void addEntity(struct SystemManager* manager, Entity* entity);

void update(struct SystemManager* manager);



