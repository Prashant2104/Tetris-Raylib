#pragma once
#include "Board.h"
#include "Blocks.cpp"
#include "UI.h"

class Game {
public:
	Game(int width, int height, int fps, char* title); //Creating a constructor to set window
	Game(const Game& other) = delete;	//Deleting copy constructor
	Game& operator=(const Game& other) = delete; //Deleting copy operator
	~Game() noexcept; //Destructor

	bool GameShouldClose() const;

	void Tick();
	void Reset();

public:
	bool gameOver;
	int score;

private:
	void Draw();
	void Update();
	void Inputs();

	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	
	void MoveBlockDown();
	void MoveBlockLeft();
	void MoveBlockRight();
	void RotateBlock();

	bool IsBlockOutside();
	bool BlockFits();
	void LockBlock();
	void UpdateScore(int lines);

private:
	float fallTime;
	float fallCounter;
	float fallMultiplier;
	float fallDifficultyMultiplier;

	std::vector<Block> blocks;
	Board board;
	Block currentBlock, nextBlock;

	UI ui;
};