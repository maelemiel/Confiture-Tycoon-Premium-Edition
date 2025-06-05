#include "raylib-cpp.hpp"

int main() {
    raylib::Window window(800, 600, "Ultra Dual Death Run 2 Deluxe Edition Remastered");
    raylib::Vector2 player(400, 300);

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        if (IsKeyDown(KEY_W)) player.y -= 2;
        if (IsKeyDown(KEY_S)) player.y += 2;
        if (IsKeyDown(KEY_A)) player.x -= 2;
        if (IsKeyDown(KEY_D)) player.x += 2;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        ::DrawCircle(player.x, player.y, 20, RED);
        DrawText("Ultra Death Run!", 10, 10, 20, BLACK);
        EndDrawing();
    }

    return 0;
}
