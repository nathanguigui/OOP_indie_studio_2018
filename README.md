# Indie Studio
The goal of this project is to create a Bomberman Game in C++
This game is Window & Linux compatible

# Install on Linux
> Not difficulties (5 minutes max)
## Dependencies:
- CMake (>=3.10)
- g++ (C++11)

## How To:
```bash
git clone
cmake .
make
make install
cd ~/Bomberman
./bomberman
```


# Install on Windows
> Little bit more difficult
## Dependencies:
- CMake (>=3.10)
- msbuild

## How To:
```powershell
git clone
cmake -G "Visual Studio 15 (2017) Win64"
msbuild bomberman.vcxproj
.\bombermanInstaller.exe
cp -R Debug\ $DESKTOP\Bomberman
dir $DESKTOP\Bomberman
.\bomberman
```

# How to play:
- Add up to 4 players and chose her skins
- Start Game (there will always be 4 players in the game including bots)
- Keybindings are automatically defined as bellow:

|        |Foward              |Backward            |Left                |Right               |Put bomb                             |
|--------|--------------------|--------------------|--------------------|--------------------|-------------------------------------|
|Player 1|<center>`Z`</center>|<center>`S`</center>|<center>`Q`</center>|<center>`D`</center>|<center>`SPACE`</center>
|Player 2|<center>`UP`</center>|<center>`DOWN`</center>|<center>`LEFT`</center>|<center>`RIGHT`</center>|<center>`L_CTRL`</center>
|Player 3|<center>`O`</center>|<center>`L`</center>|<center>`K`</center>|<center>`M`</center>|<center>`P`</center>
|Player 4|<center>`T`</center>|<center>`G`</center>|<center>`F`</center>|<center>`H`</center>|<center>`Y`</center>

# Features:
- Procedural generation for map in launcher
- Change skin option
- Save launcher option every time the game launched

# Creators:
###### Haadi Ismael
```json
{
"firstname":"Haadi",
"name":"Ismael",
"email":"haadi.ismael@epitech.eu"
}
```
###### Rémi Cabandé
```json
{
"firstname":"Rémi",
"name":"Cabandé",
"email":"remi.cabande@epitech.eu"
}
```
###### Lucas Comte
```json
{
"firstname":"Lucas",
"name":"Comte",
"email":"lucas.comte@epitech.eu"
}
```
###### Nathan Guigui
```json
{
"firstname":"Nathan",
"name":"Guigui",
"email":"nathan.guigui@epitech.eu"
}
```
###### Costa Bushnaq
```json
{
"firstname":"Costa",
"name":"Bushnaq",
"email":"costa.bushnaq@epitech.eu"
}
```
###### Thomas Jaffry
```json
{
"firstname":"Thomas",
"name":"Jaffry",
"email":"thomas.jaffry@epitech.eu"
}
```