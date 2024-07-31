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
}

void UI::DisplayScore()
{
	//DrawRectangleRounded({ 390, 40, 200, 100 }, 0.2, 2, BLUE);
	DrawTextEx(HeadingFont, "Score", { 400, 50 }, 40, 10, BLACK);
	DrawTextEx(DetailFont, scoreText, { 400, 100 }, 30, 10, BLACK);
}
