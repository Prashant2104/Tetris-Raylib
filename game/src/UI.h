#pragma once
#include "raylib.h"

class UI {
public:
	UI();

	void Setup();
	void UpdateScoreText(int score);
	void DrawUI();
private:
	void DisplayScore();
	void NextBlockHolder();
	void HeldBlockHolder();
private:
	Font HeadingFont;
	Font DetailFont;
	char scoreText[10];
};