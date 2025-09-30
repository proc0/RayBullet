#pragma once

#include <btBulletDynamicsCommon.h>

class Physics {
    btDefaultCollisionConfiguration* configuration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlaps;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;
    btAlignedObjectArray<btCollisionShape*> collisions;

    btRigidBody* sphere;
    
    public:
        ~Physics(){}
        void Load();
        btRigidBody* CreateSphere();
        void CreateGround();
        void Update();
        void Unload();
};

