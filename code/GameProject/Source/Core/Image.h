#ifndef HEADER_IMAGE
#define HEADER_IMAGE

#include <string>

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Texture.hpp"

struct Vector2f;

class Image
{
public:
	Image(const char* pPath, int pXOffset = 0, int pYOffset = 0, int pWidth = 0, int pHeight = 0);
    ~Image();

	sf::Sprite& GetSprite();
	void SetPosition(const Vector2f& pPosition);
	void SetPosition(float pX, float pY);

private:
	bool CreateSprite(const char* pPath, int pXOffset, int pYOffset, int pWidth, int pHeight);

	sf::Texture mTexture;
	sf::Sprite mSprite;
    
    //debug
    std::string mName;
};

#endif
