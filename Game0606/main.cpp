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
    //SDL��������
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to initialize SDL: " << SDL_GetError() << endl;
        return false;
    }

    //�Q�[���E�B���h�E���쐬
    window = SDL_CreateWindow("Block Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        return false;
    }

    //�����_���쐬
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Failed to create renderer: " << SDL_GetError() << endl;
        return false;
    }

    // �p�h���ƃ{�[���̏����ʒu��ݒ肷��
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

    //�L�[�{�[�h�̏�ԏ����A�p�h���̈ړ�����
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT]) {
        paddle.x -= paddleSpeed;
    }
    else if (state[SDL_SCANCODE_RIGHT]) {
        paddle.x += paddleSpeed;
    }
}

void Game::update() {
    //�{�[���̍��W�X�V
    ball.x += ballSpeedX;
    ball.y += ballSpeedY;

    // �p�h���̏Փ˔���
    if (ball.y + ball.h >= paddle.y && ball.y < paddle.y + paddle.h && ball.x + ball.w >= paddle.x && ball.x <= paddle.x + paddle.w) {
        ballSpeedY = -ballSpeedY;
    }

    // �ǂƂ��Փ˔���
    if (ball.x <= 0 || ball.x + ball.w >= SCREEN_WIDTH) {
        ballSpeedX = -ballSpeedX;
    }

    if (ball.y <= 0) {
        ballSpeedY = -ballSpeedY;
    }

    // �Q�[���I�[�o�[����
    if (ball.y + ball.h >= SCREEN_HEIGHT) {
        running = false;
    }
}

void Game::draw() {
    //��ʂ����F�ŃN���A����
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // �p�h���𔒐F�ɕ`��
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);

    // �{�[����`��
    SDL_RenderFillRect(renderer, &ball);

    //�`����e��ʂɔ��f
    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    //�����_����j��
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    //�Q�[���E�B���h�E��j��
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}



