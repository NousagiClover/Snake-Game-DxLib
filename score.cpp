#include "score.h"

Score::Score(int _key)
{
	key = _key;
	score = 0;
	hiScore = 0;
	scoreCheckCode = encode(score);
	hiScoreCheckCode = encode(hiScore);
}

int Score::encode(int _data)
{
	return ((_data + key) ^ key);
}

int Score::decode(int _data)
{
	return ((_data ^ key) - key);
}

void Score::addScore(int _score)
{
	score += _score;
	scoreCheckCode = encode(score);
	return;
}

void Score::addHiScore(int _score)
{
	hiScore += _score;
	hiScoreCheckCode = encode(hiScore);
	return;
}

void Score::zeroScore()
{
	score = 0;
	scoreCheckCode = encode(0);
	return;
}

void Score::zeroHiScore()
{
	hiScore = 0;
	hiScoreCheckCode = encode(0);
	return;
}

bool Score::check()
{
	if (decode(scoreCheckCode) != score) return false;
	if (decode(hiScoreCheckCode) != hiScore) return false;
	return true;
}

void Score::hiScoreUpdate()
{
	if (score > hiScore)
	{
		hiScore = score;
		hiScoreCheckCode = encode(hiScore);
	}
	return;
}

int Score::getScore() { return score; }
int Score::getHiScore() { return hiScore; }
