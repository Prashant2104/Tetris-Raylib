#include "UI.h"
#include<iostream>


UI::UI()
{
	sprintf(scoreText, "%d", 0);
}

UI::UI(Font headline):
	HeadingFont(headline)
{
	//HeadingFont = LoadFontEx("resources/Fonts/blocks.ttf", 128, NULL, 0);
	sprintf(scoreText, "%d", 0);
}

UI::~UI() noexcept
{
	//UnloadFont(HeadingFont);
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
	//if(IsFontReady(HeadingFont))
		DrawTextEx(HeadingFont, "Score", { 400, 50 }, 40, 10, BLACK);
	DrawText(scoreText, 400, 100, 30, BLACK);
}
