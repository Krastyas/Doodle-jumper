#pragma once
#include <string>

class Player;

class Platform
{
protected:
	int x;
	int y;
	int width;

public:
	Platform(int startX, int startY, int platformWidth)
		: x(startX), y(startY), width(platformWidth) {}

	virtual ~Platform() = default;

	virtual void ApplyEffect(Player* player) = 0;
	virtual std::string GetName() = 0;

	int GetX() { return x; }
	int GetY() { return y; }
	int GetWidth() { return width; }
};

class BoostPlatform : public Platform
{
public:
	BoostPlatform(int startX, int startY)
		: Platform(startX, startY, 10) {}

	void ApplyEffect(Player* player);
	std::string GetName() { return "Boost"; }
};

class WeakPlatform : public Platform
{
public:
	WeakPlatform(int startX, int startY)
		: Platform(startX, startY, 10) {}

	void ApplyEffect(Player* player);
	std::string GetName() { return "Weak"; }
};

class SpringPlatform : public Platform
{
public:
	SpringPlatform(int startX, int startY)
		: Platform(startX, startY, 10) {}

	void ApplyEffect(Player* player);
	std::string GetName() { return "Spring"; }
};
