#pragma once

#include <raylib.h>
#include <raymath.h>
#include <btBulletDynamicsCommon.h>
#include <string>

#include "physics.hpp"
#include "config.h"

#define URI_SOUND_SPLAT "splat1.wav"

#define BALL_MAX_SPEED 50.0f
#define BALL_ACCELERATION 8.0f
#define BALL_BREAK_FORCE 20.0f

class Ball {
    Model sphere = { 0 };
    Texture2D texture;
    btRigidBody* collision;
    Sound sound;
    Vector3 position = { 0 };
    Matrix transform = { 0 };
    Color color = RED;
    
    public:
        ~Ball(){}
        void Load(Physics& bullet);
        void Render() const;
        const std::pair<Vector3, Vector3> Update(Physics& bullet, Vector3 cameraPos);
        void Unload();
};
