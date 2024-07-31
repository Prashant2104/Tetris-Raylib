#include "UI.h"
#include<iostream>

UI::UI()
{
	sprintf(scoreText, "%d", 0);
	canSwap = true;
	gameOver = false;
}

void UI::Setup()
{
	HeadingFont = LoadFontEx("resources/Fonts/Dosis-SemiBold.ttf", 246, NULL, 0);
	DetailFont = LoadFontEx("resources/Fonts/Dosis-Medium.ttf", 246, NULL, 0);

	LockedIcon = LoadTexture("resources/Icons/lock.png");
	UnlockedIcon = LoadTexture("resources/Icons/unlock.png");
}

void UI::UpdateScoreText(int score)
{
	sprintf(scoreText, "%d", score);
}

void UI::CanSwap(bool can)
{
	canSwap = can;
}

void UI::DrawGameOverScreen()
{
	DrawRectangleRounded({ 100, 250, 400, 200 }, 0.2f, 2, GRAY);
	DrawTextEx(HeadingFont, "Game Over", { 175, 260 }, 65, 5, BLACK);
	DrawTextEx(DetailFont, "Score: ", { 175, 325 }, 50, 5, BLACK);
	DrawTextEx(DetailFont, scoreText, { 305, 325 }, 50, 5, BLACK);
	DrawTextEx(DetailFont, "Press Any Key To Restart", { 175, 400 }, 30, 1, BLACK);
}

void UI::DrawUI()
{
	DisplayScore();
	NextBlockHolder();
	HeldBlockHolder();
	ShowControls();
}

void UI::DisplayScore()
{
	DrawRectangleRounded({ 390, 50, 200, 125 }, 0.2f, 2, LIGHTGRAY);
	DrawTextEx(HeadingFont, "Score", { 430, 55 }, 40, 10, BLACK);
	DrawTextEx(DetailFont, scoreText, { 440, 110 }, 40, 10, BLACK);
}

void UI::NextBlockHolder()
{
	DrawRectangleRounded({ 390, 200, 200, 125 }, 0.2f, 2, LIGHTGRAY);
	DrawTextEx(HeadingFont, "Next", { 440, 205 }, 40, 10, BLACK);
}

void UI::HeldBlockHolder()
{
	DrawRectangleRounded({ 390, 350, 200, 125 }, 0.2f, 2, LIGHTGRAY);
	DrawTextEx(HeadingFont, "Held", { 440, 355 }, 40, 10, BLACK);
	if (canSwap)
	{
		DrawTextureEx(UnlockedIcon, { 535, 355 }, 0, 0.08f, WHITE);
	}
	else
	{
		DrawTextureEx(LockedIcon, { 535, 355 }, 0, 0.08f, WHITE);
	}
}

void UI::ShowControls()
{
	DrawRectangleRounded({ 390, 500, 200, 155 }, 0.2f, 2, LIGHTGRAY);
	DrawTextEx(HeadingFont, "Controls", { 405, 505 }, 40, 10, BLACK);
	DrawTextEx(DetailFont, "Left/A - Move Left", { 405, 545 }, 25, 1, BLACK);
	DrawTextEx(DetailFont, "Right/D - Move Right", { 405, 570 }, 25, 1, BLACK);
	DrawTextEx(DetailFont, "Up/W - Rotate", { 405, 595 }, 25, 1, BLACK);
	DrawTextEx(DetailFont, "Shift - Swap", { 405, 620 }, 25, 1, BLACK);
}
