# Overview

This document shows how you can get started with contributing to this community project.
First we will setup our local repository with the project after which we
are going to set up your favourite IDE using the CMake project generator.

If you want to merge your code into the project, you should join our Discord server.
We continuously discuss ideas and things to do -- so just come up, ask
a (Team-Manager for help, and they will give you a task.

# Getting started

First, install Git on your computer. You can use the GitHub App installer, but
we wont use the GitHub App for our git stuff. The GitHub App Installer installs
some command line tools we need to use. Don't be alarmed about the complexity of these! 
Once you get the hang of it, things will make sense. Pinky promise!

As a second step: Fork the project. The development team has
decided to use forks to keep everything clean. You can fork the project by
clicking the fork button on the upper right side of the github page.

After that, clone the fork. Open the Git Shell and navigate to the folder you want
the project to be in. Copy the clone URL from the address bar of the fork,
or look it up on the GitHub UI. 

Next, enter this in the shell:

`git clone --recursive <fork-URL>`

Git should now download the fork. When finished downloading, change the the current
directory to the repository's root:

`cd Community-Game`

There is only a slight problem now: How can we update our fork if someone makes
a change to the main repository? 
The first step to this is to add another remote to our local repository. 

Enter this in the shell:

`git remote add upstream https://github.com/Hopson97/Community-Game`

Now the original repository where we forked from is now being added as another
remote. That means we can pull all the changes from that remote into our own
local repository to keep it up-to-date with the main development repository.

# Updating your code to the newest changes from the main repository

Whenever a Pull Request is merged into Main, you should update your local copy to include the changes.
Don't worry: if you stuck to this guide, your uncommited changes shouldn't be deleted.
Git merges the changes when it pulls, and looks for any conflicts. If you were to edit a file on Master that was 
edited by someone else, then Git will give you the opportunity to resolve this either automatically of manually. 
There are a ton of merge-conflict tutorials, so we won't be explaining that.
I suggest using Google and Git FAQ-pages if you're unable to find what you need.

`git pull upstream master`

The pull command downloads the changes from the main repository and merges the changes into your
currently active branch.

You can now make the changes you want to make, or compile the project and give it a test spin!

# Getting your code into the project

If you followed the tutorial, this will be an easy step. Make sure everything is in the right place and tested, so
we don't have to search for your bugs. If you have any issues here, feel free to inform yourself on our Discord server.

There might be one last problem before pushing your changes: The main repo could
have changed while you were editing your files. Don't forget to download the changes from the Main branch. 
If in any case there is a Merge Conflict, refer to the sheet above. (Line47)

As a reminder, this is how we pull changes from the Master branch:

`git pull upstream master`

After that, run this to add your changed file to the Branch:

`git add <file changed/added>`

If you wish to undo this, you can run this command:

`git rm <file changed/added>`

Finally, we can commit the changes using this:

`git commit -m '<message>'`

Replace the message placeholder with a short summary on what changes you made.

The last step is to push your changes. Do this with the following command:

`git push`

You now successfully pushed your local changes to your fork on Git! On the github page,
it might tell you: "You are ... commits ahead". This is fwhat we want.

THE PULL REQUEST!!!

Do the pull request, and give it a meaningful title. When completing the pull request, a manager will review your changes. 
If for any reason your changes won't be accepted, then check the pull request's page. 
We usually describe our request for changes clearly in the comments.

HAVE FUN CODING - Because thats what we want here!
