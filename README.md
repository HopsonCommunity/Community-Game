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

# Compiling the code

# Compiling the project

First, get the repsoitory downloaded to your computer. If you just want to look at
the code, clone the repository with

`git clone --recursive https://github.com/Hopson97/Community-Game`

Otherwise look at the Contributing file to get a fork and your local repository
configured right.

## Compiling without IDE
Simply run:

### Windows
Only can run on an IDE

### Mac
You have to install SFML library package:
* With <a href="//brew.sh">Homebrew</a>
  ```
  $ brew install sfml
  ```


  And then build with CMake:
  ```
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
  ```
### Ubuntu
You have to install SFML library package:
  ```
  $ sudo apt-get install libsfml-dev
  ```

  And then build with CMake:
  ```
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
  ```


## Compiling in CLion
Compiling in CLion is simple, CLion uses CMake for building, so you only to download the main repository and open CLion.

Go to ``FILE > Import Project`` and open the path when the project is, click done.

Then appears an info popup, click the button ``Open Project``.
Then CLion prepares all the IDE so you have to wait for a seconds.

Then in the right top you have a couple of buttons like that: 

<img src="http://i.imgur.com/gwbZoA5.png" />

Press in the play green like button and then another popup appears, in the executable config select the only available and click run.

Then the IDE compiles CMake and builds the project.

## Compiling in every other toolchain/IDE

First, you have to have CMake. CMake is a tool to generate project files for
Visual Studio, CodeBlocks, GNU Makefile and many more toolchains. It is really useful for
a team of people where everyone wants to use his/her preferred IDE and operating
system. Download it from their website or from your favorite package manager if
you are on a Linux distribution.

If you look at the repository, you will see a CMakeLists.txt file. It will tell
CMake on how it should generate the project files for your IDE.

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

If any error did occur, please look if you have done everything that was being said
here correctly. Also double-check if your IDE is really installed if CMake tells
you the compiler could not be found.

If there are still error, go to our Discord and ask `kaizi99` for help, there
could be still bugs in our `CMakeLists.txt` so just tell him.

HAVE FUN CODING!
