#pragma once

#include "SGF/Defines.h"

namespace SGF
{
    class SGF_EXPORT Window
    {
    public:
        Window() = default;
        virtual ~Window() = default;

        virtual void SetTitle(const char* title) = 0;
        virtual const char* GetTitle() = 0;

        virtual void GetExtent(unsigned int& widthOut, unsigned int& heightOut) = 0;
        virtual void SetExtent(unsigned int width, unsigned int height) = 0;

        virtual void Close() = 0;
    };

    class SGF_EXPORT WindowEvent
    {
    public:
        WindowEvent() = default;
        virtual ~WindowEvent() = default;

        enum class Type
        {
            Unknown,
            Quit,
            Closed,
            Resized,
            Keyboard,
            MouseMotion,
            MouseButton,
            MouseWheel
        };

        virtual Window* GetWindow() = 0;
        virtual Type GetType() = 0;

        virtual unsigned int GetNewWidth() = 0;
        virtual unsigned int GetNewHeight() = 0;

        virtual bool GetKeyState() = 0;
        virtual unsigned int GetKeyCode() = 0;
        virtual unsigned int GetKeyMod() = 0;

        virtual int GetAbsoluteX() = 0;
        virtual int GetAbsoluteY() = 0;
        virtual int GetRelativeX() = 0;
        virtual int GetRelativeY() = 0;

        virtual int GetWheelX() = 0;
        virtual int GetWheelY() = 0;

        enum class Button
        {
            Unknown,
            Left,
            Middle,
            Right
        };

        virtual Button GetButton() = 0;
        virtual bool GetButtonState() = 0;
    };

    class SGF_EXPORT WindowManager
    {
    public:
        WindowManager() = default;
        virtual ~WindowManager() = default;

        virtual Window* CreateAndRegisterWindow(const char* title, 
                                                unsigned int width, 
                                                unsigned int height) = 0;

        virtual void UnregisterWindow(Window* window) = 0;

        virtual WindowEvent* PollEvent() = 0;
    };

    // For now, since we use a single implementation (SDL2),
    // this is just defined in the respective implementation files.

    SGF_EXPORT WindowManager* CreateWindowManager();
}