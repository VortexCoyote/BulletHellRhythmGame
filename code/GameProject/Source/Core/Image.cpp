#include "Image.h"
#include "Vector2f.h"

Image::Image(const char* pPath, int pXOffset, int pYOffset, int pWidth, int pHeight)
	: mName(pPath)
{
	CreateSprite(pPath, pXOffset, pYOffset, pWidth, pHeight);
}

Image::~Image()
{
}

bool Image::CreateSprite(const char* pPath, int pXOffset, int pYOffset, int pWidth, int pHeight)
{
	sf::IntRect rect;

	if (pWidth > 0 && pHeight > 0)
	{
		rect.left = pXOffset;
		rect.top = pYOffset;
		rect.width = pWidth;
		rect.height = pHeight;
	}

	bool success = mTexture.loadFromFile(pPath, rect);

	mSprite.setTexture(mTexture);

	return success;
}

sf::Sprite& Image::GetSprite()
{
	return mSprite;
}

void Image::SetPosition(const Vector2f& pPosition)
{
	mSprite.setPosition(sf::Vector2f(pPosition.x, pPosition.y));
}

void Image::SetPosition(float pX, float pY)
{
	mSprite.setPosition(sf::Vector2f(pX, pY));
}
