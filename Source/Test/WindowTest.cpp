#include <memory>
#include <iostream>

#include "SGF/Window/WindowManager.h"

int main()
{
    auto windowManager = std::unique_ptr<SGF::WindowManager>(SGF::CreateWindowManager());
    auto window = std::unique_ptr<SGF::Window>(windowManager->CreateAndRegisterWindow("Test", 800, 600));

    bool run = true;

    while (run)
    {
        while (auto windowEvent = std::unique_ptr<SGF::WindowEvent>(windowManager->PollEvent()))
        {
            SGF::Window* eventWindow = windowEvent->GetWindow();

            switch (windowEvent->GetType())
            {
            case SGF::WindowEvent::Type::Quit:
                run = false;

                std::cout << "Got SDL2 quit event!" << std::endl;

                break;

            case SGF::WindowEvent::Type::Closed:
                windowManager->UnregisterWindow(eventWindow);

                std::cout << "Got window close event! (" 
                          << eventWindow << ")"
                          << std::endl;

                break;

            case SGF::WindowEvent::Type::Resized:
                std::cout << "Got window resize event! (" 
                          << windowEvent->GetNewWidth() << ", " 
                          << windowEvent->GetNewHeight() << ")" 
                          << std::endl;

                break;

            case SGF::WindowEvent::Type::Keyboard:
                std::cout << "Got keyboard event! (" 
                          << windowEvent->GetKeyCode() << ", "
                          << windowEvent->GetKeyMod() << ", " 
                          << windowEvent->GetKeyState() << ")" 
                          << std::endl;
                
                break;

            case SGF::WindowEvent::Type::MouseButton:
                std::cout << "Got mouse button event! (" 
                          << (int)windowEvent->GetButton() << ", " 
                          << windowEvent->GetButtonState() << ")" 
                          << std::endl;

                break;

            case SGF::WindowEvent::Type::MouseMotion:
                std::cout << "Got mouse motion event! (" 
                          << windowEvent->GetAbsoluteX() << ", " 
                          << windowEvent->GetAbsoluteY() << ", " 
                          << windowEvent->GetRelativeX() << ", " 
                          << windowEvent->GetRelativeY() << ")" 
                          << std::endl;

                break;

            case SGF::WindowEvent::Type::MouseWheel:
                std::cout << "Got mouse wheel event! (" 
                          << windowEvent->GetWheelX() << ", " 
                          << windowEvent->GetWheelY() << ")" 
                          << std::endl;

                break;

            default:
                // std::cout << "Got an unknown event!" << std::endl;

                break;
            }
        }
    }

    return 0;
}