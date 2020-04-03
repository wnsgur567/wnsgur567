#pragma once

#include<string>
using namespace std;

class Player {
private:
	string name = "";
	int score = 0;
public:
	void setName(string n) { name = n; }
	void win() { score++; }
};