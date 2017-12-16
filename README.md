FDF
----
Premise is to create a wireframe using the mlx library and data from the provided maps. This is the entry point to the graphics branch at 42.

### includes folder:
fdf.h, libft library, mlx library
### srcs folder:
main.c, validate.c, parse.c, draw_line.c
### maps folder:
all avalible maps for testing

## How to use
make the program and choose a map for it to show with the command ./fdf maps/42.fdf

## Explanation
### main.c
includes 5 functions, the main, initalize to initialize certain variables, error for error checks, m_exit and close window to exit the program.
```
we start by mallocing the variable struct, then we initialize and validate the file,
then we parse the data, draw it, and then wait for our hooks.
```
### validate.c
starts with validate, validation does the main validation, check looks at a single string for alphabet and  - signs, checkw looks for the width/length of the line)
```
First of all, we double check the .fdf exention--
(using strstr isn't most complete way of doing this but it handles most cases).
Secondly, after opening the file we double check the result.
If both of those pass, we will continue with the validation.
From here, we use get_next_line to read each line of the file,
then we strsplit that line and double check it wasn't NULL.

Then, it checks the line for alphabet and - signs without numbers after them,
if either of these are there it will error. Next we set up the width checking.
What this does is save the width of the first line and compare it against all other lines.
If it finds a discrepancy, it will error out. While doing this it saves the width and height of the map.
```
### parse.c
only 2 functions, parse, and assign_pts
```
Much like validate, parse uses GNL && strsplit to go through the file and get the data.
There is next to no error checking because it should have all been taken care of in validate.
Then it assigned the current split line and gets the data values of the map and puts them into
the t_coord double array. (The array is supposed to match the map with each point like data[0][0]
would be the virst value of the first point in the map.
```
### draw_line.c 
starts with draw, then draw_line, and then initalize_vb
```
draw takes the data and goes through each point and
passes into draw_line the first point, and the second point
draw_line initalizes its variables and
then uses a generalized bresenham's algorithm to draw a line from point a to point b
using their respective x, y, z values.
draw repeats this until the entire 'map' of data has been drawn.
```

And that is the entire program, there are many maps in the maps folder to try out and the angle it is displayed at can be changed in the header by modifying A_X & A_Z.
