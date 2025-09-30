#include "physics.hpp"

void Physics::Load() {
    // collision configuration contains default setup for memory, collision setup
	configuration = new btDefaultCollisionConfiguration();
	// default collision dispatcher
	dispatcher = new btCollisionDispatcher(configuration);
	// btDbvtBroadphase is a good general purpose broadphase
	overlaps = new btDbvtBroadphase();
	// default constraint solver
	solver = new btSequentialImpulseConstraintSolver;
	// initialize world
	world = new btDiscreteDynamicsWorld(dispatcher, overlaps, solver, configuration);
	// world settings
	world->setGravity(btVector3(0, -10, 0));

	CreateGround();
}

void Physics::CreateGround() {
	// the ground is a cube of side 300 at position y = -10
	btCollisionShape* shape = new btBoxShape(btVector3(btScalar(150.), btScalar(10.), btScalar(150.)));
	collisions.push_back(shape);

	// intial transform and shape settings
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(0, -10, 0));
	btScalar mass(0.);
	btVector3 intertia(0, 0, 0);

	// default motion state
	btDefaultMotionState* state = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo properties(mass, state, shape, intertia);
	btRigidBody* ground = new btRigidBody(properties);

	// add rigid body to dynamic world
	world->addRigidBody(ground);
}

btRigidBody* Physics::CreateSphere() {
	// create a dynamic rigid body
	btCollisionShape* shape = new btSphereShape(btScalar(1.));
	collisions.push_back(shape);

	// intial transform and shape settings
	btTransform transform;
	transform.setIdentity();
	btScalar mass(0.8f);
	btVector3 intertia(0, 0, 0);
	shape->calculateLocalInertia(mass, intertia);
	transform.setOrigin(btVector3(2, 10, 0));

	// default motion state
	btDefaultMotionState* state = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo properties(mass, state, shape, intertia);
	btRigidBody* body = new btRigidBody(properties);
	sphere = body;
	// rigid body settings
	body->setFriction(1000);
	// add rigid body to dynamic world
	world->addRigidBody(body);

	return body;
}

void Physics::Update(){
	world->stepSimulation(1.f / 60.f, 10);
}

void Physics::Unload() {
	//remove the rigidbodies from the dynamics world and delete them
	for (int i = world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = world->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		world->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisions.size(); j++)
	{
		btCollisionShape* shape = collisions[j];
		collisions[j] = 0;
		delete shape;
	}

	// delete dynamics world
	delete world;
	// delete solver
	delete solver;
	// delete broadphase
	delete overlaps;
	// delete dispatcher
	delete dispatcher;
	// delete configuration
	delete configuration;
}
