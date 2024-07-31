#include "UI.h"
#include<iostream>


UI::UI()
{
	sprintf(scoreText, "%d", 0);
}

void UI::Setup()
{
	HeadingFont = LoadFontEx("resources/Fonts/Dosis-SemiBold.ttf", 246, NULL, 0);
	DetailFont = LoadFontEx("resources/Fonts/Dosis-Medium.ttf", 246, NULL, 0);
}

void UI::UpdateScoreText(int score)
{
	sprintf(scoreText, "%d", score);
}

void UI::DrawUI()
{
	DisplayScore();
	NextBlockHolder();
	HeldBlockHolder();
}

void UI::DisplayScore()
{
	DrawRectangleRounded({ 390, 40, 200, 100 }, 0.2, 2, LIGHTGRAY);
	DrawTextEx(HeadingFont, "Score", { 430, 45 }, 40, 10, BLACK);
	DrawTextEx(DetailFont, scoreText, { 450, 100 }, 30, 10, BLACK);
}

void UI::NextBlockHolder()
{
	DrawRectangleRounded({ 390, 250, 200, 125 }, 0.2, 2, LIGHTGRAY);
	DrawTextEx(HeadingFont, "Next", { 440, 255 }, 40, 10, BLACK);
}

void UI::HeldBlockHolder()
{
	DrawRectangleRounded({ 390, 450, 200, 125 }, 0.2, 2, LIGHTGRAY);
	DrawTextEx(HeadingFont, "Held", { 440, 455 }, 40, 10, BLACK);
}
