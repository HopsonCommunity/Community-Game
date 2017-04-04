# Overview

This document shows how you can get started with contributing to this community project.
First we will setup our local repository with the project.
Then we are going to set up your favourite IDE usign the CMake project generator.

If you want to get your code into the project, you should join our Discord server.
We are constantly talking about ideas and things to do, so just come up, ask
a Developer/Artist/Music team manager what to do and he will give you a task.

# Getting started

First, install Git on your computer. You can use the GitHub App installer, but
we wont use the GitHub App for our git stuff. The GitHub App Installer installs
some command line tools we need to use. But please DONT BE AFRAID!!! Once you
get the hang of it everything will make sense, I(kaizi99) promise!

Fork the project. The development team has
decided to use forks to keep everything clean. You can fork the project by
clicking the fork button on the upper right side of the github page.

Then clone the fork. Open the Git Shell and navigate to the folder you want
your project to be in. Then copy the clone URL from the address bar of the fork
or look it up on the GitHub UI. In your shell, enter

`git clone --recursive <fork-URL>`

Git should now download the fork. After it downloaded, change the the current
directory to the repository's root:

`cd Community-Game`

There is only a slight problem now: How can we update our fork if someone makes
a change to the main repository?

First we want to add another remote to our local repository. In the shell,
type

`git remote add upstream https://github.com/Hopson97/Community-Game`

Now the original repository, where we forked from, is now being added as another
remote. That means we can pull all the changes from that remote into our own
local repository, to keep it up-.to-date with the main development repository.

# Updating your code to the newest changes from the main repository

Everytime when there is a Pull Request merged you shoul update your local copy to include the changes.
Don't worry, if you sticked to this guide before your uncommited changes shouldn't be deleted.
Git merges the changes when it pulls, and if it fails to merge because you and the commit affect for
example the same line of on file, the repository is in a merge conflict state that you can resolve by
editing the files. There are a ton of merge-conflict tutorials, so just google a little bit if git says
that it cannot merge some files.

`git pull upstream master`

The pull command downloads the changes from the main repo and merges stuff into your
currently active branch.

Now you can do the changes you want to do, or go to compiling (explained on the
  readme) and do have fun with the code!

# Getting your code into the project

So you did your stuff? Make sure everything is in the right place and tested, so
we don't have to search for your bugs, or at least call bugs you know in the
Discord.

There might be one last problem before pushing your changes: The main repo could
have changed while you were editing your files. Just make sure you update your repo agian
and if a merge conflict happens resolve it with the help of google, it shouldnt be a really big
problem.

`git pull upstream master`

Now run

`git add <file changed/added>`

or if you want to untrack a file

`git rm <file changed/added>`

Now finally make a commit:

`git commit -m '<message>'`

Replace the message placeholder with a
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
