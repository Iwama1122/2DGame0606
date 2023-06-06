#pragma once
#include <SDL.h>

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    bool initialize();
    void processInput();
    void update();
    void draw();
    void cleanup();

    SDL_Window* window;//ゲームウィンドウへのポインタ
    SDL_Renderer* renderer;//レンダラへのポインタ

    //ゲームウィンドウのサイズ
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    const int PADDLE_WIDTH = 100;//パドルの幅
    const int PADDLE_HEIGHT = 20;//パドルの高さ
    const int PADDLE_SPEED = 5;//パドルの速度

    const int BALL_RADIUS = 10;//ボールの半径
    const int BALL_SPEED = 5;//ボールの速度

    SDL_Rect paddle;//パドルの矩形を表すSDL_Rect構造体
    int paddleSpeed;//パドルの移動速度

    SDL_Rect ball;//ボールの矩形
    int ballSpeedX;//ボールのX軸
    int ballSpeedY;//ボールのY軸

    bool running;//ゲーム実行状況
};