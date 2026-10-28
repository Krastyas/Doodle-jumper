#pragma once

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
	virtual const char* GetName() const = 0;

	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetWidth() const { return width; }
};

class BoostPlatform : public Platform
{
public:
	BoostPlatform(int startX, int startY)
		: Platform(startX, startY, 10) {}

	void ApplyEffect(Player* player) override;
	const char* GetName() const override { return "Boost"; }
};

class WeakPlatform : public Platform
{
public:
	WeakPlatform(int startX, int startY)
		: Platform(startX, startY, 10) {}

	void ApplyEffect(Player* player) override;
	const char* GetName() const override { return "Weak"; }
};

class SpringPlatform : public Platform
{
public:
	SpringPlatform(int startX, int startY)
		: Platform(startX, startY, 10) {}

	void ApplyEffect(Player* player) override;
	const char* GetName() const override { return "Spring"; }
};
