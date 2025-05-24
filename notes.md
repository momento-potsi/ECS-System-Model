# ECS - ENTITY COMPONENT SYSTEM 

    General functions: new, from, get, set/update, add, remove, memory management, print, unit tests


## Entity    
    Consists of Entity ID and `componentIDList[]` 
    Entities that are passed around don't contain their associated data ...
    Rather instead have it contain (inexpensive) unique ids to components to reduce CPU load
    In high performance makes huge difference by only pulling ids, thus you can choose to load its associated data
    Note: For sake of simplicity `Entities` pull ids from the same pool of components

    Functions: newEntity, printEntity, 

## Component 
    Has actual Data ` struct { ... } `
    Functions: newVec, componentFrom.., newComponent, print..Component, printVec, UnitTest

## System
    Trait/Implementations [ functions, enums, etc. ]



Done List: components,
Todo: make sure every allocation/reallocation made isn't null, set freed ptrs to null?, ask for code review, try to steer away from oop
Todo: make sure completely memory safe, todo check for all printfs, check for newlines in prints
Todo: alarming lack of frees/memory cleanup in laying out programm template, make consistent convention for printing stuff,
Todo: double check allocations to make sure im not leaving out sizeof
Todo: git terminal