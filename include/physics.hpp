#pragma once

#include <btBulletDynamicsCommon.h>

class Physics {
    btDefaultCollisionConfiguration* configuration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlaps;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;
    btAlignedObjectArray<btCollisionShape*> collisions;

    
    public:
        btRigidBody* sphere;
        ~Physics(){}
        void Load();
        btRigidBody* CreateSphere();
        void CreateGround();
        void Update();
        void Unload();
};

