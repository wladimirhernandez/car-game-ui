#ifndef __CARGAMEUI_VEHICLESELECTVIEWMODEL_H__
#define __CARGAMEUI_VEHICLESELECTVIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsGui/ObservableCollection.h>
#include <NsApp/NotifyPropertyChangedBase.h>

#include "VehicleSelect/Vehicle.h"


namespace CarGameUI
{

// State of the vehicle select screen: the garage and the highlighted car.
class VehicleSelectViewModel final: public NoesisApp::NotifyPropertyChangedBase
{
public:
    VehicleSelectViewModel();

    // Moves the highlighted car left (-1) or right (+1), clamped to the ends
    void MoveSelection(int step);

    Vehicle* GetSelectedVehicle() const;

private:
    void AddVehicle(const char* key, const char* brand, const char* model, const char* year,
        float topSpeed, float acceleration, float braking);

    void SetSelectedVehicle(Vehicle* value);
    int GetSelectedIndex() const;

private:
    Noesis::Ptr<Noesis::ObservableCollection<Vehicle>> _vehicles;
    Vehicle* _selectedVehicle = nullptr;

    NS_DECLARE_REFLECTION(VehicleSelectViewModel, NotifyPropertyChangedBase)
};

}


#endif
