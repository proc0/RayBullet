#include "ball.hpp"

void Ball::Load(Physics& bullet){
    std::string pathResource = DIR_RESOURCE;
    const char* pathSoundSplat = pathResource.append("/").append(URI_SOUND_SPLAT).c_str();

    sound = LoadSound(pathSoundSplat);

    collision = bullet.CreateSphere();

    if (collision->getMotionState()) {
        btTransform trans;
        collision->getMotionState()->getWorldTransform(trans);
        float x = float(trans.getOrigin().getX());
        float y = float(trans.getOrigin().getY());
        float z = float(trans.getOrigin().getZ());

        transform = MatrixTranslate(x, y, z);
    }

    // Create scene objects
    sphere = LoadModel("resource/soccerball.glb");
    sphere.transform = transform;
    texture = LoadTexture("resource/soccertext.jpg");
    sphere.materials[0].maps[0].texture = texture; 
}

void Ball::Render() const {
    DrawModel(sphere, position, 1.0f, WHITE);
}

std::pair<Vector3, Vector3> Ball::Update(Physics& bullet, Vector3 cameraPos) {
    
    Vector3 forwardZ = Vector3Subtract(position, cameraPos);
    forwardZ.y = position.y;
    Vector3 forwardX = Vector3RotateByAxisAngle(forwardZ, {0, 1, 0}, -90.0f);
    Vector3 fwdZ = Vector3Normalize(forwardZ);
    Vector3 fwdX = Vector3Normalize(forwardX);

    if(IsKeyPressed(KEY_SPACE)){
        PlaySound(sound);
        collision->applyForce(btVector3(0, 300.0f, 0), btVector3(0, 0, 0));
    }

    if (IsKeyDown(KEY_W)) {
        collision->applyForce(btVector3(fwdZ.x*BALL_ACCELERATION, 0, fwdZ.z*BALL_ACCELERATION), btVector3(0, 0, 0));
    }

    if (IsKeyDown(KEY_S)) {
        collision->applyForce(btVector3(fwdZ.x*-BALL_ACCELERATION, 0, fwdZ.z*-BALL_ACCELERATION), btVector3(0, 0, 0));
    }

    if (IsKeyDown(KEY_A)) {
        collision->applyForce(btVector3(fwdX.x*-BALL_ACCELERATION, 0, fwdX.z*-BALL_ACCELERATION), btVector3(0, 0, 0));
    }

    if (IsKeyDown(KEY_D)) {
        collision->applyForce(btVector3(fwdX.x*BALL_ACCELERATION, 0, fwdX.z*BALL_ACCELERATION), btVector3(0, 0, 0));
    }

    btTransform trans;
    collision->getMotionState()->getWorldTransform(trans);
    float x = float(trans.getOrigin().getX());
    float y = float(trans.getOrigin().getY());
    float z = float(trans.getOrigin().getZ());

    btQuaternion quatRot = trans.getRotation();
    Quaternion quatRot2 = (Quaternion){
        x: quatRot.getX(),
        y: quatRot.getY(),
        z: quatRot.getZ(),
        w: quatRot.getW(),
    };

    transform = MatrixMultiply(QuaternionToMatrix(quatRot2), MatrixTranslate(x, y, z));
    Vector3 ballDelta = (Vector3){ x: x - transform.m12, y: y - transform.m13, z: z - transform.m14 };
    sphere.transform = transform;
    Vector3 ballPos = (Vector3){ x: transform.m12, y: transform.m13, z: transform.m14 };
    position = ballPos;

    return std::make_pair(ballPos, ballDelta);
}

void Ball::Unload(){
    delete collision;
    UnloadSound(sound);
    UnloadTexture(texture);
    UnloadModel(sphere);
}