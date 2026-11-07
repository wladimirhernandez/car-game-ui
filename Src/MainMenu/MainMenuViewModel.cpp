#include "MainMenu/MainMenuViewModel.h"

#include <NsCore/ReflectionImplement.h>


using namespace CarGameUI;
using namespace Noesis;


namespace
{

// Returns index + step clamped to [0, count - 1]
int ClampStep(int index, int step, int count)
{
    int target = index + step;
    if (target < 0) return 0;
    if (target > count - 1) return count - 1;
    return target;
}

}


MainMenuViewModel::MainMenuViewModel()
    : _modes(*new ObservableCollection<GameMode>()), _tabs(*new ObservableCollection<SectionTab>())
{
    AddMode("TimeTrial", "Time Trial",
        "Race against the clock and beat your best lap on every track", false);
    AddMode("Arena", "Arena",
        "Face other drivers in short, aggressive events. Unlocks at level 20", true);
    AddMode("Career", "Career",
        "Step into the shoes of a rookie, race to win contracts and sponsors, "
        "and get ready to climb to the top of world motorsport", false);
    AddMode("QuickRace", "Quick Race",
        "Pick a car and a track and jump straight into a single race", false);
    AddMode("Championship", "Championships",
        "Compete in a full season and fight for the title, race after race", false);

    AddTab("SINGLE PLAYER");
    AddTab("MULTIPLAYER");
    AddTab("SETTINGS");
    AddTab("LIVERY EDITOR");

    // Career and SINGLE PLAYER start selected, as in the reference design
    _selectedMode = _modes->Get(2);
    _selectedTab = _tabs->Get(0);
}

void MainMenuViewModel::AddMode(const char* key, const char* title, const char* description,
    bool isLocked)
{
    Ptr<GameMode> mode = *new GameMode();
    mode->key = key;
    mode->title = title;
    mode->description = description;
    mode->isLocked = isLocked;
    _modes->Add(mode);
}

void MainMenuViewModel::AddTab(const char* title)
{
    Ptr<SectionTab> tab = *new SectionTab();
    tab->title = title;
    _tabs->Add(tab);
}

void MainMenuViewModel::MoveSelection(int step)
{
    if (_modes->Count() == 0) return;
    SetSelectedMode(_modes->Get(ClampStep(GetSelectedIndex(), step, _modes->Count())));
}

void MainMenuViewModel::MoveTab(int step)
{
    if (_tabs->Count() == 0) return;
    int index = _selectedTab != nullptr ? _tabs->IndexOf(_selectedTab) : 0;
    SetSelectedTab(_tabs->Get(ClampStep(index, step, _tabs->Count())));
}

GameMode* MainMenuViewModel::GetSelectedMode() const
{
    return _selectedMode;
}

void MainMenuViewModel::SetSelectedMode(GameMode* value)
{
    if (_selectedMode != value)
    {
        _selectedMode = value;
        // Tells every binding on these properties to read the new value
        OnPropertyChanged("SelectedMode");
        OnPropertyChanged("SelectedIndex");
    }
}

int MainMenuViewModel::GetSelectedIndex() const
{
    return _selectedMode != nullptr ? _modes->IndexOf(_selectedMode) : 0;
}

SectionTab* MainMenuViewModel::GetSelectedTab() const
{
    return _selectedTab;
}

void MainMenuViewModel::SetSelectedTab(SectionTab* value)
{
    if (_selectedTab != value)
    {
        _selectedTab = value;
        OnPropertyChanged("SelectedTab");
        OnPropertyChanged("ShowGameModes");
    }
}

bool MainMenuViewModel::GetShowGameModes() const
{
    return _selectedTab == _tabs->Get(0);
}


NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(MainMenuViewModel)
{
    NsProp("GameModes", &MainMenuViewModel::_modes);
    NsProp("SelectedMode", &MainMenuViewModel::GetSelectedMode, &MainMenuViewModel::SetSelectedMode);
    NsProp("SelectedIndex", &MainMenuViewModel::GetSelectedIndex);
    NsProp("Tabs", &MainMenuViewModel::_tabs);
    NsProp("SelectedTab", &MainMenuViewModel::GetSelectedTab, &MainMenuViewModel::SetSelectedTab);
    NsProp("ShowGameModes", &MainMenuViewModel::GetShowGameModes);
}

NS_END_COLD_REGION
