#include "game.hpp"

const int Game::Update(){
    physics.Update();
    float rotDeg = -135*DEG2RAD*GetMouseDelta().x*0.003f;
    CameraYaw(&camera, rotDeg, true);

    const std::pair<Vector3, Vector3> ballResult = ball.Update(physics, camera.position);

    camera.target = ballResult.first;
    camera.position += ballResult.second;
    camera.position.y = 10.0f;
}

#if __EMSCRIPTEN__
EM_JS(int, getBrowserWidth, (), {
    return window.innerWidth;
});

EM_JS(int, getBrowserHeight, (), {
    return window.innerHeight;
});
#endif

void Game::Render() const {

#if __EMSCRIPTEN__
    static int PADDING = 30; // set padding to avoid scrollbar and browser edge overlap
    SetWindowSize(getBrowserWidth() - PADDING, getBrowserHeight() - PADDING);
#endif
    BeginDrawing();

    BeginMode3D(camera);

    DrawMesh(meshPlane, materialPlane, MatrixIdentity());
    ball.Render();

    EndMode3D();

    DrawFPS(10, 10);
    EndDrawing();
}

void Game::Load() {
    physics.Load();
    ball.Load(physics);

    physics.CreateGround();
    meshPlane = GenMeshPlane(300, 300, 1, 1);
    materialPlane = LoadMaterialDefault();

    // Camera setup
    camera = (Camera3D) {
        .position = (Vector3) { 0, 12, 24 },
        .target = (Vector3) { 0, 0, 0 },
        .up = (Vector3) { 0, 1, 0 },
        .fovy = 60,
        .projection = CAMERA_PERSPECTIVE,
    };

    UpdateCamera(&camera, CAMERA_THIRD_PERSON);
}

void Game::Unload(){
    ball.Unload();
    physics.Unload();
    UnloadMesh(meshPlane);
    UnloadMaterial(materialPlane);
}

void Game::Loop(void *self) {
    Game *client = static_cast<Game *>(self);

    client->Update();
    client->Render();
}

void Game::Run() {
    // no target FPS for web (performance)
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop_arg(Loop, this, 0, 1);
    #else
        SetTargetFPS(60);
        while (!WindowShouldClose()) {
            Loop(this);
        }
    #endif
}
