#ifndef __CARGAMEUI_GAMEMODE_H__
#define __CARGAMEUI_GAMEMODE_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/String.h>


namespace CarGameUI
{

// One card of the main menu carousel. Plain data: it never changes after creation,
// so it does not need property change notifications.
struct GameMode final: public Noesis::BaseComponent
{
    // Stable identifier used by XAML to pick the card artwork ("Career", "Arena"...)
    Noesis::String key;
    Noesis::String title;
    Noesis::String description;
    bool isLocked = false;

    // Reflection exposes the fields to XAML bindings under these names
    NS_IMPLEMENT_INLINE_REFLECTION(GameMode, BaseComponent)
    {
        NsProp("Key", &GameMode::key);
        NsProp("Title", &GameMode::title);
        NsProp("Description", &GameMode::description);
        NsProp("IsLocked", &GameMode::isLocked);
    }
};

}


#endif
