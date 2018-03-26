#ifndef HEADER_INPUTMANAGER
#define HEADER_INPUTMANAGER

#include "Vector2f.h"

class InputManager
{
public:
    struct ButtonState
    {
        bool isDown;
        bool wasDown;
    };


    enum Button
    {
        eMoveUp,
        eMoveDown,
        eMoveLeft,
        eMoveRight,
        eFire,

        eTOTAL_SIZE
    };

    void Init();

    void Update();

    bool IsButtonDown(Button button);
    bool WasButtonPressed(Button button);
    void GetCursorPosition(float& X, float& Y);

private:
	void UpdateButtonStates();
	void UpdateCursorPosition();

    ButtonState myButtons[eTOTAL_SIZE];

    Vector2f myCursorPos;
};

#endif
