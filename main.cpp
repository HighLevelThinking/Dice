#include "raylib.h"
#include "dice.hpp"
#include "raymath.h"
#include <iostream>
#include <cmath>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Raylib 2D Demo");

    SetTargetFPS(60);

    std::vector<Die> dice(5, standardDie);
    int score = 0;

    std::vector<int> upgrades = {GetRandomValue(1,5),GetRandomValue(1,5),GetRandomValue(1,5)};

    int selectedDiceIndex = -1;

    std::string mode = "playing";//modes are: playing shopping dice
    int upgradePlacing = -1;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_E)){
            mode = mode != "shopping" ? "shopping" : "playing";
        } if (IsKeyPressed(KEY_Q)){
            mode = mode != "dice" ? "dice" : "playing";
            if (mode == "dice"){
                selectedDiceIndex = -1;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (mode == "playing"){
            int posMod = std::ceil(std::log(dice.size())/std::log(3));
            int rowCount = (posMod - 1) * 2 + 1;
            for (int i = 0; i < dice.size(); i++){
                Die die = dice[i];
                DrawRectangle(375-(posMod-i%rowCount)*55+rowCount/2*55,200-(posMod-i/rowCount)*55+rowCount/2*55,50,50,RAYWHITE);
                DrawText(std::to_string(die.getLastRoll()).c_str(),
                        400 - MeasureText(std::to_string(die.getLastRoll()).c_str(),40)/2-(posMod-i%rowCount)*55+rowCount/2*55,
                        205-(posMod-i/rowCount)*55+rowCount/2*55,40,BLACK);
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                for (auto &die: dice){
                    die.roll();
                    score += die.getLastRoll();
                }
            }
            DrawText(std::to_string(score).c_str(),5,5,80,WHITE);
        } else if (mode == "shopping"){
            DrawRectangle(80,355,90,90,WHITE);
            DrawText(("+"+std::to_string(upgrades[0])).c_str(),85,400,40,BLACK);
            DrawRectangle(180,355,90,90,WHITE);
            DrawText(("+"+std::to_string(upgrades[1])).c_str(),185,400,40,BLACK);
            DrawRectangle(280,355,90,90,WHITE);
            DrawText(("+"+std::to_string(upgrades[2])).c_str(),285,400,40,BLACK);
            DrawText(std::to_string(score).c_str(),5,5,80,WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if (CheckCollisionPointRec(GetMousePosition(),{80,355,90,90}) && score >= upgrades[0]*2){
                    upgradePlacing = upgrades[0];
                    score -= upgrades[0]*2;
                    mode = dice
                } else if (CheckCollisionPointRec(GetMousePosition(),{180,355,90,90}) && score >= upgrades[1]*2){
                    upgradePlacing = upgrades[1];
                    score -= upgrades[1]*2;
                    mode = dice
                } else if (CheckCollisionPointRec(GetMousePosition(),{280,355,90,90}) && score >= upgrades[2]*2){
                    upgradePlacing = upgrades[2];
                    score -= upgrades[2]*2;
                    mode = dice
                }
            }
        } else if (mode == "dice"){
            if (selectedDiceIndex == -1){
                int posMod = std::ceil(std::log(dice.size())/std::log(3));
                int rowCount = (posMod - 1) * 2 + 1;
                for (int i = 0; i < dice.size(); i++){
                    Die die = dice[i];
                    DrawRectangleRounded({375 - (posMod - i % rowCount) * 55 + rowCount / 2 * 55, 
                    200 - (posMod - i / rowCount) * 55 + rowCount / 2 * 55, 50, 50}, 90, 90, RAYWHITE);
                    DrawText(std::to_string(die.getLastRoll()).c_str(),
                            400 - MeasureText(std::to_string(die.getLastRoll()).c_str(), 40) / 2 - (posMod - i % rowCount) * 55 + rowCount / 2 * 55,
                            205 - (posMod - i / rowCount) * 55 + rowCount / 2 * 55, 40, BLACK);
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(),
                        {375 - (posMod - i % rowCount) * 55 + rowCount / 2 * 55, 
                        200 - (posMod - i / rowCount) * 55 + rowCount / 2 * 55, 50, 50})){
                        selectedDiceIndex = i;
                    }
                }
            } else {
                DrawRectangleRounded({350,10,100,100})
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
