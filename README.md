# Community-Game
Made by my subscribers :) - Matthew Hopson

This project is a project maintained by Matt Hopson's subscriber community/server
and is an attempt at making a brand-spanking-new collaborative game together.

# How to join us

Just join our public discord, where all of the development happens.

`https://discord.gg/JKVBze6`

# Building and Contributing

If you want to know how to contribute to this project,
look at `CONTRIBUTING.md`. The document will tell you how you can get the project
files with git, and how to contribute your code back into this
main repository.

Also take a look at the `CODESTYLE.md` file. It tells you how you should program
when you want your Pull Request mergerd into the project.

Don't know what to add? Check out the Trello here: https://trello.com/b/Kc93SBo2/hopson-community-project

# Compiling the project

First, get the repsoitory downloaded to your computer. If you just want to look at
the code, clone the repository with

`git clone --recursive https://github.com/Hopson97/Community-Game`

Otherwise look at the Contributing file to get a fork and your local repository
configured right.

## Compiling in console
### Preperation
#### Windows
Make sure you have MINGW with a c++ compiler, make installed in your path.
Install CMake from their official website and add it to the PATH.

#### Mac
Install CMake from their site. Make sure you add the CMake executable to the
PATH.
Also make sure you have a working C++ compiler with C++ 14 capabilities.

#### Linux
Get a working C++ compiler, make and CMake from your distribution's package manager.

#### Compiling
Go into the cloned repository and make a folder called `build`

`mkdir build`

Then, run CMake inside that build folder pointing the root folder.

`cd build`
`cmake ..`

CMake creates the Makefile in the build directory. Now you can just run

`make`

and your files will be compiled.

## Compiling in CLion
Compiling in CLion is simple, CLion uses CMake for building, so you only to download the main repository and open CLion.

Go to ``FILE > Import Project`` and open the path when the project is, click done.

Then appears an info popup, click the button ``Open Project``.
Then CLion prepares all the IDE so you have to wait for a seconds.

Then in the right top you have a couple of buttons like that:

<img src="http://i.imgur.com/gwbZoA5.png" />

Press in the play green like button and then another popup appears, in the executable config select the only available and click run.

Then the IDE reads the CMake and builds the project.

## Compiling in Visual Studio

Download CMake. Also make sure when installing Visual Studio you install the
C++ compiler too.

Go on and open the CMake GUI. Set the source path to the path where the CMakeLists.txt
is inside(the repository root) and select any new folder to be the build folder.
Its a good idea to make a new folder called `build` inside the root of the repository
and set that to the build folder in the CMake GUI.

Click on the Configure Button. Here you can select your IDE of choice.
(Side reminder: VS 2017 is VC 15 in CMake, VS 2015 is VC 14, and so on). It is really important to select a compiler
that you actually have installed onto your system.
After that, items will appear in the list and they will go red,
but don't worry it's normal. Then click on the generate button.
It will generate the project for your chosen toolchain/IDE and you should be
set to go! Click on `Open Project` and your project should be opened.

Right click on the project `Community Project` and then click `Set as startup project`
Click on that green Run Button and the project should compile.

## Program crashes when launching?

Most likely it will happen because you wont have the res/ folder where the
execute relies. Just copy the folder to your build/ folder and you should be most
likely good to go.

If there are still error, go to our Discord and ask `kaizi99` for help, there
could be still bugs in our `CMakeLists.txt` so just tell him.

HAVE FUN CODING!
