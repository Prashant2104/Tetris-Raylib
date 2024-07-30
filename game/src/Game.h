#pragma once
#include "Tetrominoes.h"
#include <vector>
class Game {
public:
    Game(int width, int height, int fps, char* title); //Creating a constructor to set window
    Game(const Game& other) = delete;	//Deleting copy constructor
    Game& operator=(const Game& other) = delete; //Deleting copy operator
    ~Game() noexcept; //Destructor

    bool GameShouldClose() const;

    void Tick();
    void SpawnTetromino(int index);
private:
    void Draw();
    void Update();
    void Inputs();
    void ShowControls();

    Straight tetromino;
};