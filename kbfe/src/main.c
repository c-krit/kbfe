/*
    Copyright (c) 2021 jdeokkim

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "raylib.h"

#define TARGET_FPS 60

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/* UTF-8 형식으로 인코딩된 한글 문자열 2개 */
#define EXAMPLE_TEXT_ONE "\xEC\x95\x88\xEB\x85\x95\xED\x95\x98\xEC\x84\xB8\xEC\x9A\x94\x21"
#define EXAMPLE_TEXT_TWO_1 "\xEC\x9D\xB4\x20\xED\x94\x84\xEB\xA1\x9C\xEA\xB7\xB8\xEB\x9E\xA8" \
                           "\xEC\x9D\x80\x20\x72\x61\x79\x6C\x69\x62\xEC\x97\x90\xEC\x84\x9C" \
                           "\x20\xED\x95\x9C\xEA\xB8\x80\x20\xEB\xB9\x84\xED\x8A\xB8\xEB\xA7" \
                           "\xB5\x20\xEA\xB8\x80\xEA\xBC\xB4\xEC\x9D\x84"
#define EXAMPLE_TEXT_TWO_2 "\x20\xEC\x82\xAC\xEC\x9A\xA9\xED\x95\x98\xEB\x8A\x94\x20\xEB\xB0" \
                           "\xA9\xEB\xB2\x95\xEC\x9D\x84\x20\xEB\xB3\xB4\xEC\x97\xAC\xEC\xA3" \
                           "\xBC\xEA\xB8\xB0\x20\xEC\x9C\x84\xED\x95\xB4\x20\xEB\xA7\x8C\xEB" \
                           "\x93\xA0\x20\xEA\xB0\x84\xEB\x8B\xA8\xED\x95\x9C\x20\xEC\x98\x88" \
                           "\xEC\xA0\x9C\xEC\x9E\x85\xEB\x8B\x88\xEB\x8B\xA4\x2E"
    
static Font font_neodgm_one, font_neodgm_two;

/* 자간이 `spacing`인 글꼴 `font`를 기준으로, 위치가 `position`인 문자열 `text`를 가운데 정렬한다. */
static Vector2 CenterText(Font font, const char *text, Vector2 position, float spacing);

/* 게임 리소스를 메모리로 불러온다. */
static void LoadResources(void);

/* 게임 리소스에 할당된 메모리를 해제한다. */
static void UnloadResources(void);

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(TARGET_FPS);
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "c-krit/kbfe | main.c");
    
    LoadResources();

    while (!WindowShouldClose()) {
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        DrawTextEx(
            font_neodgm_one,
            EXAMPLE_TEXT_ONE,
            CenterText(
                font_neodgm_one, 
                EXAMPLE_TEXT_ONE, 
                (Vector2) { 0.0f, SCREEN_HEIGHT * 0.35f },
                2
            ),
            font_neodgm_one.baseSize,
            2,
            WHITE
        );
        
        DrawTextEx(
            font_neodgm_two,
            EXAMPLE_TEXT_TWO_1,
            CenterText(
                font_neodgm_two, 
                EXAMPLE_TEXT_TWO_1, 
                (Vector2) { 0.0f, SCREEN_HEIGHT * 0.5f },
                2
            ),
            font_neodgm_two.baseSize,
            2,
            WHITE
        );
        
        DrawTextEx(
            font_neodgm_two,
            EXAMPLE_TEXT_TWO_2,
            CenterText(
                font_neodgm_two, 
                EXAMPLE_TEXT_TWO_2, 
                (Vector2) { 0.0f, SCREEN_HEIGHT * 0.55f },
                2
            ),
            font_neodgm_two.baseSize,
            2,
            WHITE
        );
        
        DrawFPS(8, 8);

        EndDrawing();
    }
    
    UnloadResources();
    
    CloseWindow();

    return 0;
}

/* 게임 리소스를 메모리로 불러온다. */
static void LoadResources(void) {
    font_neodgm_one = LoadFont("../res/fonts/neodgm/neodgm-24pt.fnt");
    font_neodgm_two = LoadFont("../res/fonts/neodgm/neodgm-18pt.fnt");
}

/* 게임 리소스의 메모리를 해제한다. */
static void UnloadResources(void) {
    UnloadFont(font_neodgm_one);
    UnloadFont(font_neodgm_two);
}

/* 자간이 `spacing`인 글꼴 `font`를 기준으로, 위치가 `position`인 문자열 `text`를 가운데 정렬한다. */
static Vector2 CenterText(Font font, const char *text, Vector2 position, float spacing) {
    Vector2 v = MeasureTextEx(font, text, font.baseSize, spacing);
    
    return (Vector2) { (SCREEN_WIDTH - v.x) / 2, position.y };
}