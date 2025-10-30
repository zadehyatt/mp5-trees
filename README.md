# mp5
Binary Search Trees

See the mp5.pdf found on canvas for details about the assignment requirements.

You must first clone the template code.  

To clone and then later submit, review the Quiz1 details on Canvas about how 
to use gh and git.

You may need to login if you find you get errors about permissions:

    gh auth login 

To check if you are loggged in use 

    gh auth status

To clone

On the github classroom page with the code look for the green "<> Code"
button.  Select the "GitHub CLI" tab.  Use the copy icon to get the line that
starts with (this is incomplete):

   gh repo clone clemson-ece-2230/mp5-more details

In a terminal on your Ubuntu machine, navigate to a mp5 folder and paste 
the clone command.  Now you will have template files for the assignment.

To submit

In the directory with your code do (change file names as needed):

    git add lab5.c tree.c tree.h makefile
    git add mytestplan myperformance
    git commit -m "final mp5 code"
    git push

Notice you are not adding any of my testing scripts or testing files.  Just
the code needed to compile and run your program.

If additioanl files are added to the project, you may need to complete
a pull request.

To get them, first complete the Pull requests found on your github classroom 
page.  You need to merge the new files into your respository.  Then in your 
local terminal do:

    git pull

(Completing the Pull requests is not needed if you clone your repository from
the template repository after the files have been added to the template 
repository.)

