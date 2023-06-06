#include "Game.h"
using namespace std;

Game::Game() {
    window = nullptr;
    renderer = nullptr;
    paddleSpeed = PADDLE_SPEED;
    ballSpeedX = BALL_SPEED;
    ballSpeedY = BALL_SPEED;
    running = false;
}

Game::~Game() {
    cleanup();
}

void Game::run() {
    if (!initialize()) {
        cout << "Failed to initialize the game." << endl;
        return;
    }

    running = true;

    while (running) {
        processInput();
        update();
        draw();
    }

    cleanup();
}

bool Game::initialize() {
    //SDLを初期化
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to initialize SDL: " << SDL_GetError() << endl;
        return false;
    }

    //ゲームウィンドウを作成
    window = SDL_CreateWindow("Block Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        return false;
    }

    //レンダラ作成
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Failed to create renderer: " << SDL_GetError() << endl;
        return false;
    }

    // パドルとボールの初期位置を設定する
    paddle = { (SCREEN_WIDTH - PADDLE_WIDTH) / 2, SCREEN_HEIGHT - PADDLE_HEIGHT, PADDLE_WIDTH, PADDLE_HEIGHT };
    ball = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BALL_RADIUS, BALL_RADIUS };

    return true;
}

void Game::processInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    //キーボードの状態所得、パドルの移動処理
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT]) {
        paddle.x -= paddleSpeed;
    }
    else if (state[SDL_SCANCODE_RIGHT]) {
        paddle.x += paddleSpeed;
    }
}

void Game::update() {
    //ボールの座標更新
    ball.x += ballSpeedX;
    ball.y += ballSpeedY;

    // パドルの衝突判定
    if (ball.y + ball.h >= paddle.y && ball.y < paddle.y + paddle.h && ball.x + ball.w >= paddle.x && ball.x <= paddle.x + paddle.w) {
        ballSpeedY = -ballSpeedY;
    }

    // 壁とも衝突判定
    if (ball.x <= 0 || ball.x + ball.w >= SCREEN_WIDTH) {
        ballSpeedX = -ballSpeedX;
    }

    if (ball.y <= 0) {
        ballSpeedY = -ballSpeedY;
    }

    // ゲールオーバー判定
    if (ball.y + ball.h >= SCREEN_HEIGHT) {
        running = false;
    }
}

void Game::draw() {
    //画面を黒色でクリアする
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // パドルを白色に描画
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);

    // ボールを描画
    SDL_RenderFillRect(renderer, &ball);

    //描画内容画面に反映
    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    //レンダラを破棄
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    //ゲームウィンドウを破棄
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}



