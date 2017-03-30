# Overwiew

This document shows how you can get started with contributing to this community project.
First we will setup our local repository with the project.
Then we are going to set up your favourite IDE usign the CMake project generator.

# Getting the project

It is recommended to fork this project if you are actually going to contribute to this project.
For that case, please refer this link to learn how to maintain a fork.
https://gist.github.com/Chaser324/ce0505fbed06b947d962
But watch out! When you are cloning you have to add `--recursive` to the clone.
This is because we use Submodules and it assures that SFML will be also cloned into the repository.

If you just want to look at the source code and compile it, then a simple
`git clone --recursive https://github.com/Hopson97/Community-Game` can be enough.

# Compiling the project

First, you have to have CMake. CMake is a tool to generate project files for
Visual Studio, CodeBlocks, GNU Makefile and many more. It is really useful for
a team of people where everyone wants to use his/her preferred IDE and operating
system. Download it from their website or from your favorite package manager if
you are on a Linux distribution.

If you look at the repository, you will see a CMakeLists.txt file. It will tell
CMake on how it should generate the project files for your favorite IDE.

Go on and open the CMake GUI. Set the source path to the path where the CMakeLists.txt
is inside(the repository root) and select any new folder to be the build folder.
Its a good idea to make a new folder called `build` inside the root of the repository
and set that to the build folder in the CMake GUI.

Click on the Configure Button. Here you can select your IDE of choice.
(Side reminder: VS 2017 is VC 15 in CMake). Also you have to select a compiler
that you actually have installed and CMake should be able to find it.
After that, items will appear in that list and they will go red,
but don't worry it's normal. Then click on the generate button.
It will generate the project for your chosen toolchain/IDE and you should be
set to go! Click on `Open Project` and your project should be opened.

If any error did occur, please look if you have done everything that was being said
here correctly. Also double-check if your IDE is really installed if CMake tells
you the compiler could not be found.

If there are still error, go to our Discord and ask `kaizi99` for help, there
could be still bugs in our CMakeLists.txt so just tell him.

# Contributing to the project

*To do*
