#pragma once

#include "Platform/SDL2/SDL2WindowManager.h"

namespace SGF
{
    SDLWindow::SDLWindow(SDLWindowManager* manager, const char* title, 
                         unsigned int width, unsigned int height)
    {
        m_Manager = manager;
        m_Handle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                    width, height, SDL_WINDOW_RESIZABLE);
    }

    SDLWindow::~SDLWindow()
    {
        SDL_DestroyWindow(m_Handle);
    }

    SDL_Window* SDLWindow::GetHandle()
    {
        return m_Handle;
    }

    Uint32 SDLWindow::GetID()
    {
        return SDL_GetWindowID(m_Handle);
    }

    void SDLWindow::SetTitle(const char* title)
    {
        SDL_SetWindowTitle(m_Handle, title);
    }

    const char* SDLWindow::GetTitle()
    {
        return SDL_GetWindowTitle(m_Handle);
    }

    void SDLWindow::GetExtent(unsigned int& width, unsigned int& height)
    {
        SDL_GetWindowSize(m_Handle, 
                          reinterpret_cast<int*>(&width), 
                          reinterpret_cast<int*>(&height));
    }

    void SDLWindow::SetExtent(unsigned int width, unsigned int height)
    {
        SDL_SetWindowSize(m_Handle, width, height);
    }

    void SDLWindow::Close()
    {
        SDL_Event closeEvent;

        closeEvent.type = SDL_WINDOWEVENT;

        closeEvent.window.windowID = GetID();
        closeEvent.window.event = SDL_WINDOWEVENT_CLOSE;

        SDL_PushEvent(&closeEvent);
    }

    Window* SDLWindowEvent::GetWindow()
    {
        return m_Window;
    }

    WindowEvent::Type SDLWindowEvent::GetType()
    {
        switch (m_Event.type)
        {
        case SDL_QUIT:
            return Type::Quit;

        case SDL_WINDOWEVENT:
            switch (m_Event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                return Type::Closed;

            case SDL_WINDOWEVENT_RESIZED:
                return Type::Resized;
            }

            break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
            return Type::Keyboard;

        case SDL_MOUSEMOTION:
            return Type::MouseMotion;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            return Type::MouseButton;

        case SDL_MOUSEWHEEL:
            return Type::MouseWheel;
        }

        return Type::Unknown;
    }

    unsigned int SDLWindowEvent::GetNewWidth()
    {
        return (unsigned int)m_Event.window.data1;
    }

    unsigned int SDLWindowEvent::GetNewHeight()
    {
        return (unsigned int)m_Event.window.data2;
    }

    bool SDLWindowEvent::GetKeyState()
    {
        return (bool)m_Event.key.state;
    }

    unsigned int SDLWindowEvent::GetKeyCode()
    {
        return (unsigned int)m_Event.key.keysym.sym;
    }

    unsigned int SDLWindowEvent::GetKeyMod()
    {
        return (unsigned int)m_Event.key.keysym.mod;
    }

    int SDLWindowEvent::GetAbsoluteX()
    {
        return m_Event.motion.x;
    }

    int SDLWindowEvent::GetAbsoluteY()
    {
        return m_Event.motion.y;
    }

    int SDLWindowEvent::GetRelativeX()
    {
        return m_Event.motion.xrel;
    }

    int SDLWindowEvent::GetRelativeY()
    {
        return m_Event.motion.yrel;
    }

    WindowEvent::Button SDLWindowEvent::GetButton()
    {
        switch (m_Event.button.button)
        {
        case SDL_BUTTON_LEFT:
            return Button::Left;

        case SDL_BUTTON_MIDDLE:
            return Button::Middle;

        case SDL_BUTTON_RIGHT:
            return Button::Right;
        }

        return Button::Unknown;
    }

    bool SDLWindowEvent::GetButtonState()
    {
        return (bool)m_Event.button.state;
    }

    int SDLWindowEvent::GetWheelX()
    {
        return m_Event.wheel.x;
    }

    int SDLWindowEvent::GetWheelY()
    {
        return m_Event.wheel.y;
    }

    SDLWindowManager::SDLWindowManager()
    {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    }

    SDLWindowManager::~SDLWindowManager()
    {
        SDL_Quit();
    }

    Window* SDLWindowManager::CreateAndRegisterWindow(const char* title, 
                                                      unsigned int width, 
                                                      unsigned int height)
    {
        SDLWindow* newWindow = new SDLWindow(this, title, width, height);

        m_WindowMap.emplace(newWindow->GetID(), newWindow);

        return newWindow;
    }

    void SDLWindowManager::UnregisterWindow(Window* window)
    {
        SDLWindow* sdlWindow = dynamic_cast<SDLWindow*>(window);

        for (auto windowMap : m_WindowMap)
        {
            if (windowMap.second == sdlWindow)
            {
                m_WindowMap.erase(windowMap.first);

                return;
            }
        }
    }

    WindowEvent* SDLWindowManager::PollEvent()
    {
        SDL_Event evt;

        if (!SDL_PollEvent(&evt))
            return nullptr;

        Uint32 windowID = 0;

        switch (evt.type)
        {
        case SDL_QUIT:
            break;

        case SDL_MOUSEWHEEL:
            windowID = evt.wheel.windowID;

            break;

        case SDL_MOUSEMOTION:
            windowID = evt.motion.windowID;

            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            windowID = evt.button.windowID;

            break;

        case SDL_KEYUP:
        case SDL_KEYDOWN:
            windowID = evt.key.windowID;

            break;

        case SDL_WINDOWEVENT:
            windowID = evt.window.windowID;

            break;
        }

        SDLWindow* window = nullptr;

        if (m_WindowMap.find(windowID) != m_WindowMap.end())
            window = m_WindowMap[windowID];

        return new SDLWindowEvent(evt, window);
    }

    WindowManager* CreateWindowManager()
    {
        return new SDLWindowManager();
    }
}