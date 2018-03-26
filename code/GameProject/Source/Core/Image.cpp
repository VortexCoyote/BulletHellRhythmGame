#include "Image.h"
#include "Vector2f.h"

Image::Image(const char* path, int xOffset, int yOffset, int width, int height)
	: myName(path)
{
	CreateSprite(path, xOffset, yOffset, width, height);
}

Image::~Image()
{
}

bool Image::CreateSprite(const char* path, int xOffset, int yOffset, int width, int height)
{
	sf::IntRect rect;

	if (width > 0 && height > 0)
	{
		rect.left = xOffset;
		rect.top = yOffset;
		rect.width = width;
		rect.height = height;
	}

	bool success = myTexture.loadFromFile(path, rect);

	mySprite.setTexture(myTexture);

	return success;
}

sf::Sprite& Image::GetSprite()
{
	return mySprite;
}

void Image::SetPosition(const Vector2f& aPosition)
{
	mySprite.setPosition(sf::Vector2f(aPosition.x, aPosition.y));
}

void Image::SetPosition(float x, float y)
{
	mySprite.setPosition(sf::Vector2f(x, y));
}
