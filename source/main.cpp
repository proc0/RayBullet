#include "game.hpp"

int main(void){
    Game client;

#ifdef __EMSCRIPTEN__
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
#else
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
#endif

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, PROJECT_NAME);
    InitAudioDevice();
    
    client.Load();
    client.Run();
    client.Unload();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}