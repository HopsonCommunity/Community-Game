# Overview

This document shows how you can get started with contributing to this community project.
First we will setup our local repository with the project.
Then we are going to set up your favourite IDE usign the CMake project generator.

If you want to get your code into the project, you should join our Discord server.
We are constantly talking about ideas and things to do, so just come up, ask
a Developer/Artist/Music team manager what to do and he will give you a task.

# Getting the project

First, install Git on your computer. You can use the GitHub App installer, but
we wont use the GitHub App for our git stuff. The GitHub App Installer installs
some command line tools we need to use. But please DONT BE AFRAID!!! Once you
get the hang of it everything will make sense, I(kaizi99) promise!

If you just want to look at the source code and compile it, then a simple
`git clone --recursive https://github.com/Hopson97/Community-Game` can be enough.

However, if you want to contribute, first fork the project. The development team has
decided to use forks to keep everything clean. You can fork the project by
clicking the fork button on the upper right side of the github page.

Then clone the fork. Open the Git Shell and navigate to the folder you want
your project to be in. Then copy the clone URL from the address bar of the fork
or look it up on the GitHub UI. In your shell, enter

`git clone --recursive <fork-URL>`

Git should now download the fork.

There is only a slight problem now: How can we update our fork if someone makes
a change to the main repository?

First we want to add another remote to our local repository. In the shell,
type

`git remote add upstream https://github.com/Hopson97/Community-Game`

Now the original repository, where we forked from, is now being added as another
remote. That means we can pull all the changes from that remote into our own
local repository, to keep it up-.to-date with the main development repository.

So everytime you want to edit some files, e.g. make a contribution, make your
local repository up-to-date with the following commands:

`git fetch upstream`
`git checkout master`
`git merge upstream/master`

The fetch command downloads the changes from the main repo, the checkout command
makes sure you are on your master branch, and at last the merge command will merge
the changes from the main development repo into your current local repository.

Now you can do the changes you want to do, or go to the compiling step and develop.

# Compiling the project

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

# Getting your code into the project

So you did your stuff? Make sure everything is in the right place and tested, so
we don't have to search for your bugs, or at least call bugs you know in the
Discord.

There might be one last problem before pushing your changes: The main repo could
have changed while you were editing your files. Just make sure you run these 3 agian:

`git fetch upstream`
`git checkout master`
`git merge upstream/master`

There could be a merge conflict, and if there is one, god may help you(jk, Look up
on how to solve merge conflicts in git, there is lots of resources on the internet).
If not, then you have luck!

Now run

`git commit -m '<message>'`

Replace the message placeholder with a really
short summary on what changes you made.

After that run

`git push`

It pushes the changes you made to your GitHub fork! Now you can go to the GitHub
website again and right beneath the message "You are ... commits ahead" there is
out destiny:

THE PULL REQUEST!!!

Do the pull request, and give it a meaningful title. Thats it. Send it off and
hope that a manager accepts it. If a manager didnt accept it, then ask them why,
and they will give you an answer.

HAVE FUN CODING - Because thats what we want here!
