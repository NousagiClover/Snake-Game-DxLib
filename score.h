#pragma once

class Score
{
private:
	int score;
	int hiScore;
	int scoreCheckCode;
	int hiScoreCheckCode;
	int key;
	int encode(int _data);
	int decode(int _data);
public:
	Score(int _key);
	void addScore(int _score);
	void addHiScore(int _score);
	void zeroScore();
	void zeroHiScore();
	bool check();
	void hiScoreUpdate();
	int getScore();
	int getHiScore();
};
