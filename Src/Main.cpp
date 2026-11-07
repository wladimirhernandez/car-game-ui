#include <NsCore/Noesis.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/LocalXamlProvider.h>
#include <NsApp/LocalFontProvider.h>
#include <NsApp/LocalTextureProvider.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Window.h>
#include <NsGui/UIElementEvents.h>
#include <NsCore/StringUtils.h>

#include "Shell/ShellViewModel.h"


using namespace Noesis;
using namespace NoesisApp;


// Root folder for every asset (XAML, fonts, images), relative to the working directory
static constexpr const char* AssetsRoot = "Data";

// Development flag: "--vehicle-select" opens straight onto the vehicle select screen
static bool StartOnVehicleSelect = false;


class AppLauncher final: public ApplicationLauncher
{
private:
    // Global ResourceDictionary (colors, brushes, styles) shared by every screen
    Uri GetResources(bool /*darkTheme*/) const override
    {
        return Uri("Resources.xaml");
    }

    // Asset providers: tell Noesis where to read files from when XAML references them
    Ptr<XamlProvider> GetXamlProvider() const override
    {
        return *new LocalXamlProvider(AssetsRoot);
    }

    Ptr<FontProvider> GetFontProvider() const override
    {
        return *new LocalFontProvider(AssetsRoot);
    }

    Ptr<TextureProvider> GetTextureProvider() const override
    {
        return *new LocalTextureProvider(AssetsRoot);
    }

    // Runs once the main window exists: plug in the root ViewModel every binding reads from
    void OnAppStartUp() override
    {
        Window* window = GetMainWindow();
        mViewModel = MakePtr<CarGameUI::ShellViewModel>();
        window->SetDataContext(mViewModel);

        if (StartOnVehicleSelect)
        {
            mViewModel->ShowScreen(CarGameUI::ShellViewModel::Screen::VehicleSelect);
        }

        // Preview runs on the way down, before any control can mark the key as handled,
        // so every press (keyboard or gamepad) reaches the device tracker
        window->PreviewKeyDown() += MakeDelegate(this, &AppLauncher::OnPreviewKeyDown);

        // Key and gamepad events start at the focused element and bubble up.
        // With nothing focused they reach nobody, so the window itself takes the
        // focus and its InputBindings receive every press.
        window->SetFocusable(true);
        window->Focus();
    }

    void OnPreviewKeyDown(BaseComponent*, const KeyEventArgs& e)
    {
        mViewModel->NotifyKeyPressed(e.key);
    }

private:
    Ptr<CarGameUI::ShellViewModel> mViewModel;
};


int NsMain(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (StrEquals(argv[i], "--vehicle-select")) StartOnVehicleSelect = true;
    }

    AppLauncher launcher;
    launcher.SetArguments(argc, argv);
    launcher.SetStartupUri("MainWindow.xaml");
    return launcher.Run();
}
