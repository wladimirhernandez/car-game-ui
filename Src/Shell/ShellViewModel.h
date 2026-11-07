#ifndef __CARGAMEUI_SHELLVIEWMODEL_H__
#define __CARGAMEUI_SHELLVIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/String.h>
#include <NsGui/InputEnums.h>
#include <NsApp/NotifyPropertyChangedBase.h>
#include <NsApp/DelegateCommand.h>

#include "MainMenu/MainMenuViewModel.h"
#include "VehicleSelect/VehicleSelectViewModel.h"


namespace CarGameUI
{

// Root ViewModel (window DataContext). Owns every screen, knows which one is active,
// and turns raw input (Left, Accept, Back...) into the right action for that screen.
// Screens never see keys: they expose intentions like MoveSelection.
class ShellViewModel final: public NoesisApp::NotifyPropertyChangedBase
{
public:
    ShellViewModel();

    // Called for every key press (keyboard or gamepad). On-screen hints follow
    // the device that was used last.
    void NotifyKeyPressed(Noesis::Key key);

    enum class Screen { MainMenu, VehicleSelect };
    void ShowScreen(Screen screen);

private:
    void OnLeft(Noesis::BaseComponent*);
    void OnRight(Noesis::BaseComponent*);
    void OnAccept(Noesis::BaseComponent*);
    void OnBack(Noesis::BaseComponent*);
    void OnPreviousTab(Noesis::BaseComponent*);
    void OnNextTab(Noesis::BaseComponent*);
    void OnMainMenu(Noesis::BaseComponent*);

private:
    Noesis::Ptr<MainMenuViewModel> _mainMenu;
    Noesis::Ptr<VehicleSelectViewModel> _vehicleSelect;

    Screen _screen = Screen::MainMenu;
    // Name of the active screen for XAML triggers: "MainMenu" or "VehicleSelect"
    Noesis::String _screenName;

    bool _usingGamepad = false;
    Noesis::String _playerName;
    int _playerLevel = 0;

    Noesis::Ptr<NoesisApp::DelegateCommand> _left;
    Noesis::Ptr<NoesisApp::DelegateCommand> _right;
    Noesis::Ptr<NoesisApp::DelegateCommand> _accept;
    Noesis::Ptr<NoesisApp::DelegateCommand> _back;
    Noesis::Ptr<NoesisApp::DelegateCommand> _previousTab;
    Noesis::Ptr<NoesisApp::DelegateCommand> _nextTab;
    Noesis::Ptr<NoesisApp::DelegateCommand> _goMainMenu;

    NS_DECLARE_REFLECTION(ShellViewModel, NotifyPropertyChangedBase)
};

}


#endif
