#pragma once

class Player
{
private:
	float x;
	float y;
	float velocityY;
	float jumpPower;
	bool isJumping;
	int height;

public:
	Player(float startX, float startY)
		: x(startX), y(startY), velocityY(0), jumpPower(2.6f), isJumping(false), height(2)
	{
	}

	void Jump()
	{
		if (!isJumping)
		{
			velocityY = -jumpPower;
			isJumping = true;
		}
	}

	void Update(float gravity)
	{
		if (!isJumping)
			return;

		velocityY += gravity;
		y += velocityY;
	}

	void Land(float landingY)
	{
		y = landingY;
		isJumping = false;
		velocityY = 0;
	}

	void SetX(float newX)
	{
		x = newX;
	}

	void AddJumpPower(float amount)
	{
		jumpPower += amount;
		if (jumpPower > 3.2f) jumpPower = 3.2f;
	}

	void RemoveJumpPower(float amount)
	{
		jumpPower -= amount;
		if (jumpPower < 1.5f) jumpPower = 1.5f;
	}

	void SetMaxPower()
	{
		jumpPower = 3.2f;
	}

	float GetX() const
	{
		return x;
	}

	float GetY() const
	{
		return y;
	}

	int GetHeight() const
	{
		return height;
	}

	float GetJumpPower() const
	{
		return jumpPower;
	}

	bool IsJumping() const
	{
		return isJumping;
	}

	float GetVelocity() const
	{
		return velocityY;
	}
};
