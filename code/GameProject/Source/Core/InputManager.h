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

    bool IsButtonDown(Button pButton);
    bool WasButtonPressed(Button pButton);
    void GetCursorPosition(float& pX, float& pY);

private:
	void UpdateButtonStates();
	void UpdateCursorPosition();

    ButtonState mButtons[eTOTAL_SIZE];

    Vector2f mCursorPos;
};

#endif
