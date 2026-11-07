#ifndef __CARGAMEUI_SECTIONTAB_H__
#define __CARGAMEUI_SECTIONTAB_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/String.h>


namespace CarGameUI
{

// One entry of the top navigation (SINGLE PLAYER, MULTIPLAYER...)
struct SectionTab final: public Noesis::BaseComponent
{
    Noesis::String title;

    NS_IMPLEMENT_INLINE_REFLECTION(SectionTab, BaseComponent)
    {
        NsProp("Title", &SectionTab::title);
    }
};

}


#endif
