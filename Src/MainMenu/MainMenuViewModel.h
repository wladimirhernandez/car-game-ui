#ifndef __CARGAMEUI_MAINMENUVIEWMODEL_H__
#define __CARGAMEUI_MAINMENUVIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsGui/ObservableCollection.h>
#include <NsApp/NotifyPropertyChangedBase.h>

#include "MainMenu/GameMode.h"
#include "MainMenu/SectionTab.h"


namespace CarGameUI
{

// State of the main menu screen: section tabs and the game mode carousel.
// Input arrives already translated into intentions (move, switch tab) by the ShellViewModel.
class MainMenuViewModel final: public NoesisApp::NotifyPropertyChangedBase
{
public:
    MainMenuViewModel();

    // Moves the carousel selection one card left (-1) or right (+1), clamped to the ends
    void MoveSelection(int step);

    // Switches section tab left (-1) or right (+1), clamped to the ends
    void MoveTab(int step);

    GameMode* GetSelectedMode() const;

    // True while the SINGLE PLAYER tab (the one with game modes) is active
    bool GetShowGameModes() const;

private:
    void AddMode(const char* key, const char* title, const char* description, bool isLocked);
    void AddTab(const char* title);

    void SetSelectedMode(GameMode* value);
    int GetSelectedIndex() const;

    SectionTab* GetSelectedTab() const;
    void SetSelectedTab(SectionTab* value);

private:
    Noesis::Ptr<Noesis::ObservableCollection<GameMode>> _modes;
    GameMode* _selectedMode = nullptr;

    Noesis::Ptr<Noesis::ObservableCollection<SectionTab>> _tabs;
    SectionTab* _selectedTab = nullptr;

    NS_DECLARE_REFLECTION(MainMenuViewModel, NotifyPropertyChangedBase)
};

}


#endif
