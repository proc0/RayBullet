#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <raylib.h>
#include <rcamera.h>

#include "config.h"
#include "physics.hpp"
#include "ball.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game {
    Physics physics;
    Ball ball;
    
    Camera camera;
    Mesh meshPlane;
    Material materialPlane;
    
    public:
        ~Game(){}
        void Load();
        static void Loop(void *self);
        void Render() const;
        void Run();
        void Update();
        void Unload();
};
