#include "VehicleSelect/VehicleSelectViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/StringUtils.h>
#include <NsGui/BitmapImage.h>
#include <NsGui/Uri.h>


using namespace CarGameUI;
using namespace Noesis;


namespace
{

// Formats a 0..10 stat with one decimal: 7.2f -> "7.2"
String FormatStat(float value)
{
    return String(String::VarArgs(), "%.1f", value);
}

}


VehicleSelectViewModel::VehicleSelectViewModel()
    : _vehicles(*new ObservableCollection<Vehicle>())
{
    // Images: Data/Images/car_<key>.jpg (full screen) and thumb_<key>.jpg (strip)
    AddVehicle("gtr_egoist", "Nissan", "GT-R Egoist", "2012", 7.6f, 7.9f, 6.8f);
    AddVehicle("gtr_tspec", "Nissan", "GT-R T-spec", "2024", 8.4f, 8.6f, 7.4f);
    AddVehicle("carrera4s", "Porsche", "911 Carrera 4S", "2015", 7.2f, 5.0f, 3.5f);
    AddVehicle("dakar", "Porsche", "911 Dakar", "2022", 6.1f, 6.4f, 5.2f);
    AddVehicle("gtr_track", "Nissan", "GT-R Track Edition", "2016", 8.9f, 9.1f, 8.3f);

    // The middle car starts highlighted, as in the reference design
    _selectedVehicle = _vehicles->Get(2);
}

void VehicleSelectViewModel::AddVehicle(const char* key, const char* brand, const char* model,
    const char* year, float topSpeed, float acceleration, float braking)
{
    Ptr<Vehicle> vehicle = *new Vehicle();
    vehicle->brand = brand;
    vehicle->model = model;
    vehicle->year = year;
    vehicle->shortName = String(String::VarArgs(), "%s '%s", model, year + 2);

    vehicle->topSpeed = topSpeed / 10.0f;
    vehicle->acceleration = acceleration / 10.0f;
    vehicle->braking = braking / 10.0f;
    vehicle->topSpeedText = FormatStat(topSpeed);
    vehicle->accelerationText = FormatStat(acceleration);
    vehicle->brakingText = FormatStat(braking);

    vehicle->hero = *new BitmapImage(Uri(String(String::VarArgs(), "Images/car_%s.jpg", key).Str()));
    vehicle->thumbnail = *new BitmapImage(Uri(String(String::VarArgs(), "Images/thumb_%s.jpg", key).Str()));

    _vehicles->Add(vehicle);
}

void VehicleSelectViewModel::MoveSelection(int step)
{
    int count = _vehicles->Count();
    if (count == 0) return;

    int target = GetSelectedIndex() + step;
    if (target < 0) target = 0;
    if (target > count - 1) target = count - 1;
    SetSelectedVehicle(_vehicles->Get(target));
}

Vehicle* VehicleSelectViewModel::GetSelectedVehicle() const
{
    return _selectedVehicle;
}

void VehicleSelectViewModel::SetSelectedVehicle(Vehicle* value)
{
    if (_selectedVehicle != value)
    {
        _selectedVehicle = value;
        OnPropertyChanged("SelectedVehicle");
        OnPropertyChanged("SelectedIndex");
    }
}

int VehicleSelectViewModel::GetSelectedIndex() const
{
    return _selectedVehicle != nullptr ? _vehicles->IndexOf(_selectedVehicle) : 0;
}


NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(VehicleSelectViewModel)
{
    NsProp("Vehicles", &VehicleSelectViewModel::_vehicles);
    NsProp("SelectedVehicle", &VehicleSelectViewModel::GetSelectedVehicle,
        &VehicleSelectViewModel::SetSelectedVehicle);
    NsProp("SelectedIndex", &VehicleSelectViewModel::GetSelectedIndex);
}

NS_END_COLD_REGION
