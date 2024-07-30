#include<assert.h>
#include"raylib.h"
#include "Game.h"
#include<iostream>
#include "ResourceLoader.h"

Game::Game(int width, int height, int fps, char* title)
{
	assert(width > 0 && height > 0 && fps > 0);
	InitWindow(width, height, title);
	SetTargetFPS(fps);
	ResourceLoader r;
	UI tempui = UI(r.LoadFontRes());
	ui = tempui;

	fallCounter = 0;
	fallMultiplier = Settings::fallSpeed;
	fallDifficultyMultiplier = 1;
	fallTime = Settings::fallTime;

	board = Board();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();

	gameOver = false;
	score = 0;
}

Game::~Game() noexcept
{
	CloseWindow();
}

bool Game::GameShouldClose() const
{
	assert(GetWindowHandle()); //If assertion triggers: Window is already closed
	return WindowShouldClose();
}

void Game::Tick()
{
	Inputs();
	Draw();
	Update();
}

void Game::Reset()
{
	gameOver = false;
	score = 0;
	board.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock()
{
	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}
	int randomIndex = GetRandomValue(0, blocks.size() - 1);
	Block block = blocks[randomIndex];
	//blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}


void Game::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);
	board.Draw();
	currentBlock.Draw(Settings::boardOffsetX, Settings::boardOffsetY);

	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(255, 290);
		break;
	case 4:
		nextBlock.Draw(255, 290);
		break;
	default:
		nextBlock.Draw(270, 270);
		break;
	}

	ui.DrawUI();

	EndDrawing();
}

void Game::Update()
{
	fallCounter += GetFrameTime() * fallMultiplier * fallDifficultyMultiplier;
	if (fallCounter >= fallTime) {
		fallCounter = 0;
		MoveBlockDown();
	}
}

void Game::Inputs()
{
	int keyPressed = GetKeyPressed();

	if (gameOver && keyPressed != 0) {
		Reset();
	}
	if (!gameOver) {
		switch (keyPressed)
		{
		case KEY_LEFT:
		case KEY_A:
			MoveBlockLeft();
			break;

		case KEY_RIGHT:
		case KEY_D:
			MoveBlockRight();
			break;

		case KEY_DOWN:
		case KEY_S:
			fallMultiplier *= 5;
			break;

		case KEY_UP:
		case KEY_W:
			RotateBlock();
			break;

		default:
			break;
		}
	}
	if (IsKeyReleased(KEY_S) || IsKeyReleased(KEY_DOWN)) {
		fallMultiplier = Settings::fallSpeed;
	}
}

void Game::MoveBlockDown()
{
	currentBlock.Move(1, 0);
	if (IsBlockOutside() || !BlockFits()) {
		currentBlock.Move(-1, 0);
		LockBlock();
	}
}

void Game::MoveBlockLeft()
{
	currentBlock.Move(0, -1);
	IsBlockOutside();
	if (!BlockFits()) {
		currentBlock.Move(0, 1);
	}
}

void Game::MoveBlockRight()
{
	currentBlock.Move(0, 1);
	IsBlockOutside();
	if (!BlockFits()) {
		currentBlock.Move(0, -1);
	}
}

void Game::RotateBlock()
{
	currentBlock.Rotate();
	IsBlockOutside();
	if (!BlockFits()) {
		currentBlock.UndoRotate();
	}
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (board.IsCellOutside(item.row, item.column)) {
			std::cout << item.row << " " << item.column << std::endl;
			if (item.row < 20 && item.row > 0) {
				if (item.column < 0) {
					MoveBlockRight();
				}
				else
				{
					MoveBlockLeft();
				}
			}
			return true;
		}
	}
	return false;
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (!board.IsCellEmpty(item.row, item.column))
			return false;
	}
	return true;
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		board.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (!BlockFits()) {
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	int rowsCleared = board.ClearFullRows();
	UpdateScore(rowsCleared);
	fallDifficultyMultiplier += 0.25;
}

void Game::UpdateScore(int lines)
{
	score += lines * 100;
	std::cout << score << std::endl;
	//ui.UpdateScoreText(score);
}