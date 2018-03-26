#ifndef HEADER_EVENTHANDLER
#define HEADER_EVENTHANDLER

class InputManager;

class EventHandler
{
public:
    
	void Init();
    void HandleEvents();

private:
	    
    void OnQuit();
};

#endif