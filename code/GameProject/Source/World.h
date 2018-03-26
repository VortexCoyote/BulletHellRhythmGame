#ifndef HEADER_WORLD
#define HEADER_WORLD

class Image;
class Scene;

class World
{
public:
    
	void Create();
    void Destroy();
    void Update();
    void Draw();

private:
	
	Image* m_backGround;
	Image* m_bulletSprite;

	int m_player;
};

#endif