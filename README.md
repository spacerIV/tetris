tetris
=========

## with C, OpenGL & GLUT

![tetris](https://github.com/vichou/tetris/raw/master/screenshots/tetris-1.png)

Written quickly as a student, and it shows!

### OSX Compile 
Something like: gcc -o tetris -framework glut -framework OpenGL tetris.c

### Linux Compile 
Something like: gcc -o tetris -lglut -lGLU -std=gnu99 -lm tetris.c

...and ignore the hundreds of deprecated api warnings.
