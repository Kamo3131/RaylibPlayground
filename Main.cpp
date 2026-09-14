#include <iostream>

#include "raylib-cpp.hpp"
#include "Square.hpp"

float roundToSecond(const float& number) {
    float rounded = round(number * 10);
    float result = 0.0f;
    if (number < 0) {
        int remainder = static_cast<int>(-rounded)%10;
        result = static_cast<float>(static_cast<int>(rounded)/10);
        if (remainder > 3 && remainder < 7) 
        {
            result -= 0.5f;
        } 
        else if (remainder >= 7) 
        {
            result -= 1.0f;
        }
    }
    else if (number > 0) {
        int remainder = static_cast<int>(rounded)%10;
        result = static_cast<float>(static_cast<int>(rounded)/10);
        if (remainder > 3 && remainder < 7) 
        {
            result += 0.5f;
        } 
        else if (remainder >= 7) 
        {
            result += 1.0f;
        }
    }
    return result;
}

void moveCube(Vector3 &current_position, const float speed, const float angle, const float frame_time) 
{
    current_position.z += speed * frame_time * sin(angle);
    current_position.x += speed * frame_time * cos(angle);
}

int main() {
    int screenWidth = 1920;
    int screenHeight = 1080;

    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    Camera3D camera = {};
    camera.position = {0.0f, 10.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float speed = 5.0f;
    float move_angle = 0.0f;
    bool moving = false;

    Vector3 cube_size = {1.0f, 1.0f, 1.0f};
    Vector3 cube_position = {0.0f, cube_size.y * 0.5f, 0.0f};
    Vector3 new_cube_position = cube_position;
    Vector3 position_highlight = {0.0f, 0.0f, 0.0f};

    Square highlightSquare(cube_size.x/2, 0.05f);

    Ray ray = {0.0f, 0.0f, 0.0f};
    // RayCollision collision = {0.0f, 0.0f, 0.0f};
    // collision.hit = true;
     
    SetTargetFPS(240);
    EnableCursor();
    while (!window.ShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        ray = GetScreenToWorldRay(GetMousePosition(), camera);
        position_highlight = {roundToSecond((-ray.position.y * ray.direction.x / ray.direction.y)+ray.position.x), 0.0f, roundToSecond((-ray.position.y * ray.direction.z / ray.direction.y)+ray.position.z)};
        
        if(IsKeyPressed(KEY_Z)) camera.target = {0.0f, 0.0f, 0.0f};
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            new_cube_position = {position_highlight.x, cube_size.y * 0.5f, position_highlight.z};
            move_angle = atan2f(new_cube_position.z - cube_position.z, new_cube_position.x - cube_position.x);
            moving = true;
        }
        if (moving) 
        {
            const float frame_time = GetFrameTime();
            float x = new_cube_position.x - cube_position.x;
            float z = new_cube_position.z - cube_position.z;
            float distance = sqrtf(x * x + z * z);
            if (fabs(distance) <= 0.5f && distance <= speed * frame_time) 
            {
                moving = false;
                cube_position = {roundToSecond(cube_position.x), cube_position.y, roundToSecond(cube_position.z)};
            }
            else
            {
                moveCube(cube_position, speed, move_angle, frame_time);
            }
            // std::cout << "Current pos: " << cube_position.x << ", " << cube_position.z << std::endl;
            // std::cout << "New pos: " << new_cube_position.x << ", " << new_cube_position.z << std::endl;
        }
        BeginDrawing();

        window.ClearBackground(raylib::Color::RayWhite());

            BeginMode3D(camera);
                DrawCubeV(cube_position, cube_size, raylib::Color::Red());
                DrawCubeWiresV(cube_position, cube_size, raylib::Color::Maroon());
                DrawRay(ray, raylib::Color::Green());
                DrawGrid(100, 0.5f);

                highlightSquare.DrawSquare(position_highlight, raylib::Color::Yellow());
                DrawLine3D({0.0f, 0.0f, 0.0f}, {2.0f, 0.0f, 0.0f}, raylib::Color::Red());
                DrawLine3D({0.0f, 0.0f, 0.0f}, {0.0f, 2.0f, 0.0f}, raylib::Color::Green());
                DrawLine3D({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 2.0f}, raylib::Color::Blue());

            EndMode3D();

            raylib::DrawText(TextFormat("%f, %f, %f", ray.position.x, ray.position.y, ray.position.z), 10, 60, 10, raylib::Color::Black());
            raylib::DrawText(TextFormat("%f, %f, %f", ray.direction.x, ray.direction.y, ray.direction.z), 10, 80, 10, raylib::Color::Black());
            DrawFPS(10, 40);
        EndDrawing();
    }
    return 0;
}