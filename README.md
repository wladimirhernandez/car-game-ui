# Car Game UI

A racing game menu built with the **NoesisGUI 4.0 native C++ SDK**: XAML for the visuals, C++ ViewModels for the state and logic. It recreates the layout of the Dribbble shot [Racing game interface concept](https://dribbble.com/shots/24405015-Racing-game-interface-concept) with free (CC0) images and a custom logo.

## Screens

- **Main menu**: section tabs, an animated game mode carousel, profile badge and input hints.
- **Vehicle select**: full-screen car, stats panel with bars and a thumbnail strip.

## Controls

| Key | Main menu | Vehicle select |
|---|---|---|
| Left / Right | Move the carousel | Change car |
| Enter | Open vehicle select (unlocked modes) | Confirm and go back |
| Esc | Quit | Back |
| Q / E | Previous / next tab | — |
| M | — | Main menu |

Input hints switch between keyboard keys and gamepad buttons depending on the last device used. Gamepads must be in XInput mode.

## Requirements

- Windows 10/11, Visual Studio 2022 or later with the **Desktop development with C++** workload.
- [NoesisGUI SDK 4.0](https://www.noesisengine.com/) extracted to `C:\NoesisSDK`. Use another location by passing `/p:NoesisSDK=<path>` to MSBuild.
- `NoesisApp` built from the SDK sources: open `C:\NoesisSDK\Src\Projects\NoesisApp\windows_x86_64\NoesisApp-vs2022.vcxproj` and build Debug x64. It produces `NoesisApp.dll` and `NoesisApp.lib`.

## Build and run

Open `CarGameUI.vcxproj` in Visual Studio, select **Debug | x64** and press **F5**. The post-build step copies the Noesis DLLs next to the executable, and the app runs from the project folder, where it reads `Data/`.

From a terminal:

```
MSBuild CarGameUI.vcxproj -p:Configuration=Debug -p:Platform=x64
Bin\Debug\CarGameUI.exe
```

`CarGameUI.exe --vehicle-select` opens straight on the vehicle select screen.

## Project layout

```
Src/
  Main.cpp                     App launcher: asset providers, root DataContext, key tracking
  Shell/ShellViewModel         Active screen and input routing
  MainMenu/                    Game modes, section tabs
  VehicleSelect/               Vehicles and stats
Data/
  MainWindow.xaml              Both screens and the input map
  Resources.xaml               Colors, typography, icons, templates and animations
  Fonts/                       Titillium Web (SIL Open Font License)
  Images/                      CC0 photos (see Images/CREDITS.md) and logo.svg
```

## Credits

- Layout reference: Dribbble shot linked above. All UI copy, the logo and the code are original.
- Photos: CC0, listed with authors and sources in `Data/Images/CREDITS.md`.
- Font: Titillium Web, SIL Open Font License (`Data/Fonts/OFL.txt`).
- NoesisGUI is a commercial SDK by Noesis Technologies and is not included in this repository.
