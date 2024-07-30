#pragma once
#include "raylib.h"

class UI {
public:
	UI();
	UI(Font headline);
	//UI(const UI& other) = delete;	//Deleting copy constructor
	//UI& operator=(const UI& other) = delete; //Deleting copy operator
	~UI() noexcept; //Destructor

	void UpdateScoreText(int score);
	void DrawUI();
private:
	void DisplayScore();

private:
	Font HeadingFont;
	//Font DetailFont;
	char scoreText[10];
};