#ifndef __CARGAMEUI_VEHICLE_H__
#define __CARGAMEUI_VEHICLE_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/String.h>
#include <NsCore/Ptr.h>
#include <NsGui/ImageSource.h>


namespace CarGameUI
{

// One car of the vehicle select screen. Stats go from 0 to 10: the text shows the
// value ("7.2") and the bars use the matching 0..1 ratio as a horizontal scale.
struct Vehicle final: public Noesis::BaseComponent
{
    Noesis::String brand;
    Noesis::String model;
    Noesis::String year;
    Noesis::String shortName;   // label under the thumbnail: "911 Carrera 4S '15"

    Noesis::String topSpeedText;
    Noesis::String accelerationText;
    Noesis::String brakingText;
    float topSpeed = 0.0f;
    float acceleration = 0.0f;
    float braking = 0.0f;

    Noesis::Ptr<Noesis::ImageSource> hero;
    Noesis::Ptr<Noesis::ImageSource> thumbnail;

    NS_IMPLEMENT_INLINE_REFLECTION(Vehicle, BaseComponent)
    {
        NsProp("Brand", &Vehicle::brand);
        NsProp("Model", &Vehicle::model);
        NsProp("Year", &Vehicle::year);
        NsProp("ShortName", &Vehicle::shortName);
        NsProp("TopSpeedText", &Vehicle::topSpeedText);
        NsProp("AccelerationText", &Vehicle::accelerationText);
        NsProp("BrakingText", &Vehicle::brakingText);
        NsProp("TopSpeed", &Vehicle::topSpeed);
        NsProp("Acceleration", &Vehicle::acceleration);
        NsProp("Braking", &Vehicle::braking);
        NsProp("Hero", &Vehicle::hero);
        NsProp("Thumbnail", &Vehicle::thumbnail);
    }
};

}


#endif
