#pragma once

#include <map>
#include "SGF/Window/WindowManager.h"
#include "SDL.h"

struct SDL_Window;
typedef unsigned int Uint32;

namespace SGF
{
    class SDLWindowManager;

    class SDLWindow : public Window
    {
    private:
        SDLWindowManager* m_Manager;
        SDL_Window* m_Handle;

    public:
        SDLWindow(SDLWindowManager* manager, const char* title,
                  unsigned int width, unsigned int height);

        ~SDLWindow();

        SDLWindow(const SDLWindow&) = delete;
        void operator=(const SDLWindow&) = delete;

        SDL_Window* GetHandle();
        Uint32 GetID();

        virtual void SetTitle(const char* title) override;
        virtual const char* GetTitle() override;

        virtual void GetExtent(unsigned int& width, unsigned int& height) override;
        virtual void SetExtent(unsigned int width, unsigned int height) override;

        virtual void Close() override;
    };

    class SDLWindowEvent : public WindowEvent
    {
    private:
        SDL_Event m_Event;
        SDLWindow* m_Window;

    public:
        SDLWindowEvent(SDL_Event& event, SDLWindow* window)
                      : m_Event(event), m_Window(window) { }

        ~SDLWindowEvent() = default;

        SDLWindowEvent(const SDLWindowEvent&) = delete;
        void operator=(const SDLWindowEvent&) = delete;

        virtual Window* GetWindow() override;
        virtual Type GetType() override;

        virtual unsigned int GetNewWidth() override;
        virtual unsigned int GetNewHeight() override;

        virtual bool GetKeyState() override;
        virtual unsigned int GetKeyCode() override;
        virtual unsigned int GetKeyMod() override;

        virtual int GetAbsoluteX() override;
        virtual int GetAbsoluteY() override;
        virtual int GetRelativeX() override;
        virtual int GetRelativeY() override;

        virtual Button GetButton() override;
        virtual bool GetButtonState() override;

        virtual int GetWheelX() override;
        virtual int GetWheelY() override;
    };

    class SDLWindowManager : public WindowManager
    {
    private:
        std::map<Uint32, SDLWindow*> m_WindowMap;

    public:
        SDLWindowManager();
        ~SDLWindowManager();

        SDLWindowManager(const SDLWindowManager& other) = delete;
        void operator=(const SDLWindowManager& other) = delete;

        virtual Window* CreateAndRegisterWindow(const char* title, 
                                                unsigned int width, 
                                                unsigned int height) override;

        virtual void UnregisterWindow(Window* window) override;

        virtual WindowEvent* PollEvent() override;
    };
}