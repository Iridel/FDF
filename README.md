What I have so far:

NOTE: mallocing isn't correct, neither is the freeing, mostly is just a mess at this point but technically we dont need
to handle error leaking in fdf. For now I'm leaving it until I can get the damn thing to work.

includes/fdf.h:
---------------
s_coord struct = x, y, z coords; is used for storing the coords and possibly color? Not sure if I will keep the color var.

s_initalize struct = variables used around the entire code including mlx(id) pointer, win pointer, fd, total width/height,
a flag, and a char **array for when I strsplit.

s_draw_var struct = variables I need for my bresenham's function, took from here: https://www.cs.umd.edu/class/fall2003/cmsc427/bresenham.html

srcs/main.c:
------------
malloc for *var, check for ac
all errors will be sent to error which puts the string + nl, and exits the program.
init for my mlx pointer (the id), make the window & name it the filename.
open the file & validate, then parse.
set hooks, 1 for key press, 1 for pressing the red x on the window.
key hook points to m_exit which checks if the key pressed was '53' aka esc and exits the program if so
the other hook points to close_window which destroys the window and exits the program if event 17 happens (the red x)
start loop that waits for input

srcs/validate.c:
----------------
in validate I check if the file extention is accurate
then open the file and begin validation.
here I use GNL until file is read and check the line that it produces for any alphabetical characters, tabs, or invalid '-'.
then I strsplit the line and set it to var->curr and double check the line is not just spaces.
Then I check if the width has been taken before and if not I get the width and save it in var->width & error check.
If it has, I get the width for the current line, set it to w2 and compare.
Then I free and increase the iterator that will count the 'height' (how many rows).
after the loop I save the height and do some error checking, and print out that the file is finished being read. (prob will change that later.)
the fd is then closed and reset

srcs/parse.c:
-------------
large comment at the top is mostly outdated.
I declare 2 new coord arrays, make sure the flag is 0, print out the height and width for double checking purposes, 
then open the fd again. Start with the GNL loop again, split, then send the split line to assign_pts_curr.
This function mallocs for the t_coord array, and sets the x, y, & z of each 'point', and then frees the var->curr array.
Then we take the data we just parsed and send it to draw the horizontal lines.
All data gotten is * 10 to show the space inbetween - this most likely will be changed to a variable to enable zooming.
then we check the flag, if 0, set the flag to 1 malloc the previous_data struct and set it to the current. Then it moves on.
if it isnt 0, we draw the vertical lines in between the previous row and the current one, free the previous one,
then set it to the current 'row'. Delete the line and loop through again. After, error checking is done.

printstruct is there for error checking so you can look to see if the parsing is accurate (it is so far as I know/tested).

the idea is essentially that GNL will get the line so if you have this:

0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0     This will be the first line it will get
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

the array that will be split will just be 0's for the first couple of lines but it will give the x, and y value based
on the iterators, which is done in the assign_pts_curr function, and the z value based on the atoi.
then it will go through that array of structs and look at 0,0,0 and draw a line from there to 1,0,0 all the way to the width
of the file, in this case, 19:

0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0

So the array of structs (c_data or p_data) will always have 19 structs of the points for the 
first line. then when it gets the second line and the current one is placed in the previous data struct, it will draw the
horizontal lines and then go through and draw the vertical by looking at the p_data, and drawing a line from p_data[i] to c_data[i] (0,0,0 to 0,1,0) down all the way till the end of the row.

0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0 -> 0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0
                                      -> | | | | | | | | | | | | | | | | | | |
0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0 -> 0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0

and repeat, though the logic on the drawing part isnt correct- if I do it all manually it is but if I use the draw_line function its not.

srcs/draw_line.c:
-----------------
in draw horizontal (2nd function, first one to be called in parse), it goes though and is supposed to use the 
draw_line function to draw a line from c_data[i] to c_data[i + 1], this however is not working that well.

in draw verical (1st function 2nd called), I manually pixel put the vertical lines; this was working when it got this far
when I was doing horizontal manually to, but I'd like it to work with the draw_line as well. 

The draw_line function is the 'normed' version of the algorithim that I posted next to the s_draw_var struct.
the initalize_var function is literally just that due to space constraint.

and thats everything so far
