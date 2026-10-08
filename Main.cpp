#include <iostream>

#include "raylib-cpp.hpp"
#include "Square.hpp"
#include "Blockade.hpp"
#include "AStar.hpp"
#include "GridGraph.hpp"

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

static Vector3 divideVector3(const Vector3& value, const float scalar)
{
    return {value.x / scalar, value.y / scalar, value.z / scalar};
}

int main() {
    int screenWidth = 1000;
    int screenHeight = 800;

    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    // SetWindowPosition(0, 0);
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
    Vector3 movement_position = cube_position;
    Vector3 position_highlight = {0.0f, 0.0f, 0.0f};
    
    Vector3 blockade_size = {0.5f, 0.5f, 0.5f};
    std::vector<Blockade> blockades;

    std::vector<Point> moves;
    int active_move = 0;
    GridGraph<Point> graph;
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
        
        if (!moving && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            moves.clear();
            new_cube_position = {position_highlight.x, cube_size.y * 0.5f, position_highlight.z};
            std::cout << "{ " << cube_position.x << ", " << cube_position.y << " }, { " << new_cube_position.x << ", " << new_cube_position.y << " }\n";
            moves = aStar<Point, GridGraph<Point>, std::vector<Point>>(
                graph,
                {cube_position.x, cube_position.z},
                {new_cube_position.x, new_cube_position.z});
            if (moves.size() > 0) {    
                // for(int i = 0; i < moves.size(); ++i) {
                //     std::cout << "( "<<moves.at(i).x << ", " << moves.at(i).z << ") ";
                // }
                active_move = 1;
                Point first_move = moves.at(active_move);
                movement_position = {first_move.x, cube_position.y, first_move.z};
                
                move_angle = atan2f(movement_position.z - cube_position.z, movement_position.x - cube_position.x);
                moving = true;
            }
            else
            {
                moving = false;
                
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            const Vector3 blockade_position = {position_highlight.x, blockade_size.y * 0.5f, position_highlight.z};
            bool temp = false;
            for (const Blockade& b : blockades) {
                if(b.PositionIntersects(blockade_position, blockade_size))
                {
                    temp = true;
                    break;
                }
            }
            if (!temp) 
            {
                blockades.emplace_back(blockade_position, blockade_size, raylib::Color::DarkGray());
                graph.addBlockade({blockade_position.x, blockade_position.z}, blockade_size.x, blockade_size.z);
            }
        }
        

        if (moving) 
        {
            // bool blocked = false;
            // for(const Blockade& b : blockades)
            // {
            //     if(b.PositionIntersects(cube_position, divideVector3(cube_size, 2.0f)))
            //     {
            //         blocked = true;
            //     }
            // }
            const float frame_time = GetFrameTime();
            float x = movement_position.x - cube_position.x;
            float z = movement_position.z - cube_position.z;
            float distance = sqrtf(x * x + z * z);


            if ((/*fabs(distance) <= 0.001f &&*/ distance <= speed * frame_time) /*|| blocked*/) 
            {
                cube_position = {movement_position.x, movement_position.y, movement_position.z};
                if (active_move >= (moves.size() - 1)) {
                    moving = false;
                }
                else 
                {
                    active_move++;
                    Point next_move = moves.at(active_move);
                    movement_position = {next_move.x, cube_position.y, next_move.z};
                    move_angle = atan2f(movement_position.z - cube_position.z, movement_position.x - cube_position.x); 
                }
            }
            if (moving)
            {
                moveCube(cube_position, speed, move_angle, frame_time);
            }
        }
        BeginDrawing();

        window.ClearBackground(raylib::Color::RayWhite());

            BeginMode3D(camera);
                DrawCubeV(cube_position, cube_size, raylib::Color::Red());
                DrawCubeWiresV(cube_position, cube_size, raylib::Color::Maroon());
                for(const Blockade& b : blockades)
                {
                    b.Draw();
                }

                DrawRay(ray, raylib::Color::Green());
                DrawGrid(100, 0.5f);

                highlightSquare.Draw(position_highlight, raylib::Color::Yellow());
                DrawLine3D({0.0f, 0.0f, 0.0f}, {2.0f, 0.0f, 0.0f}, raylib::Color::Red());
                DrawLine3D({0.0f, 0.0f, 0.0f}, {0.0f, 2.0f, 0.0f}, raylib::Color::Green());
                DrawLine3D({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 2.0f}, raylib::Color::Blue());
                

            EndMode3D();

            raylib::DrawText(TextFormat("Active move: %i; moves size: %i", active_move, moves.size()), 10, 70, 20, raylib::Color::Black());
            raylib::DrawText(TextFormat("Movement position: %f, %f", movement_position.x, movement_position.z), 10, 90, 20, raylib::Color::Black());
            raylib::DrawText("Moves: ", 10, 110, 20, raylib::Color::Black());

            
            DrawFPS(10, 40);
        EndDrawing();
    }
    return 0;
}