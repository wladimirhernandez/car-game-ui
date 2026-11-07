#include "Shell/ShellViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsApp/Application.h>


using namespace CarGameUI;
using namespace Noesis;
using namespace NoesisApp;


ShellViewModel::ShellViewModel()
    : _mainMenu(*new MainMenuViewModel()), _vehicleSelect(*new VehicleSelectViewModel()),
    _screenName("MainMenu"), _playerName("Giakky90"), _playerLevel(17)
{
    _left = *new DelegateCommand(MakeDelegate(this, &ShellViewModel::OnLeft));
    _right = *new DelegateCommand(MakeDelegate(this, &ShellViewModel::OnRight));
    _accept = *new DelegateCommand(MakeDelegate(this, &ShellViewModel::OnAccept));
    _back = *new DelegateCommand(MakeDelegate(this, &ShellViewModel::OnBack));
    _previousTab = *new DelegateCommand(MakeDelegate(this, &ShellViewModel::OnPreviousTab));
    _nextTab = *new DelegateCommand(MakeDelegate(this, &ShellViewModel::OnNextTab));
    _goMainMenu = *new DelegateCommand(MakeDelegate(this, &ShellViewModel::OnMainMenu));
}

void ShellViewModel::NotifyKeyPressed(Key key)
{
    // The display layer reports gamepad buttons as a contiguous range of keys
    bool fromGamepad = key >= Key_GamepadLeft && key <= Key_GamepadContext4;

    if (_usingGamepad != fromGamepad)
    {
        _usingGamepad = fromGamepad;
        OnPropertyChanged("UsingGamepad");
    }
}

void ShellViewModel::ShowScreen(Screen screen)
{
    if (_screen == screen) return;

    _screen = screen;
    _screenName = screen == Screen::MainMenu ? "MainMenu" : "VehicleSelect";
    OnPropertyChanged("CurrentScreen");
}

void ShellViewModel::OnLeft(BaseComponent*)
{
    if (_screen == Screen::MainMenu) _mainMenu->MoveSelection(-1);
    else _vehicleSelect->MoveSelection(-1);
}

void ShellViewModel::OnRight(BaseComponent*)
{
    if (_screen == Screen::MainMenu) _mainMenu->MoveSelection(+1);
    else _vehicleSelect->MoveSelection(+1);
}

void ShellViewModel::OnAccept(BaseComponent*)
{
    if (_screen == Screen::MainMenu)
    {
        // Only playable modes open the garage; locked ones (Arena) do nothing
        GameMode* mode = _mainMenu->GetSelectedMode();
        if (_mainMenu->GetShowGameModes() && mode != nullptr && !mode->isLocked)
        {
            ShowScreen(Screen::VehicleSelect);
        }
    }
    else
    {
        // Confirming a car returns to the menu (there is no race screen in this demo)
        ShowScreen(Screen::MainMenu);
    }
}

void ShellViewModel::OnBack(BaseComponent*)
{
    if (_screen == Screen::MainMenu)
    {
        // "Quit game" on the main menu
        Application::Current()->Shutdown();
    }
    else
    {
        ShowScreen(Screen::MainMenu);
    }
}

void ShellViewModel::OnPreviousTab(BaseComponent*)
{
    if (_screen == Screen::MainMenu) _mainMenu->MoveTab(-1);
}

void ShellViewModel::OnNextTab(BaseComponent*)
{
    if (_screen == Screen::MainMenu) _mainMenu->MoveTab(+1);
}

void ShellViewModel::OnMainMenu(BaseComponent*)
{
    ShowScreen(Screen::MainMenu);
}


NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(ShellViewModel)
{
    NsProp("MainMenu", &ShellViewModel::_mainMenu);
    NsProp("VehicleSelect", &ShellViewModel::_vehicleSelect);
    NsProp("CurrentScreen", &ShellViewModel::_screenName);
    NsProp("UsingGamepad", &ShellViewModel::_usingGamepad);
    NsProp("PlayerName", &ShellViewModel::_playerName);
    NsProp("PlayerLevel", &ShellViewModel::_playerLevel);

    NsProp("LeftCommand", &ShellViewModel::_left);
    NsProp("RightCommand", &ShellViewModel::_right);
    NsProp("AcceptCommand", &ShellViewModel::_accept);
    NsProp("BackCommand", &ShellViewModel::_back);
    NsProp("PreviousTabCommand", &ShellViewModel::_previousTab);
    NsProp("NextTabCommand", &ShellViewModel::_nextTab);
    NsProp("MainMenuCommand", &ShellViewModel::_goMainMenu);
}

NS_END_COLD_REGION
