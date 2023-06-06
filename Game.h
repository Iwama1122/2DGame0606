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

    SDL_Window* window;//�Q�[���E�B���h�E�ւ̃|�C���^
    SDL_Renderer* renderer;//�����_���ւ̃|�C���^

    //�Q�[���E�B���h�E�̃T�C�Y
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    const int PADDLE_WIDTH = 100;//�p�h���̕�
    const int PADDLE_HEIGHT = 20;//�p�h���̍���
    const int PADDLE_SPEED = 5;//�p�h���̑��x

    const int BALL_RADIUS = 10;//�{�[���̔��a
    const int BALL_SPEED = 5;//�{�[���̑��x

    SDL_Rect paddle;//�p�h���̋�`��\��SDL_Rect�\����
    int paddleSpeed;//�p�h���̈ړ����x

    SDL_Rect ball;//�{�[���̋�`
    int ballSpeedX;//�{�[����X��
    int ballSpeedY;//�{�[����Y��

    bool running;//�Q�[�����s��
};