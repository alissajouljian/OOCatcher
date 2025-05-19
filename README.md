# Stickman Walking Animation

This project animates a walking stickman using OpenGL and GLFW, ported from a Turbo C++ graphics implementation. The stickman cycles through 5 walking poses while moving smoothly across the window.

## How to Run

1. Make sure you have GLFW and OpenGL installed on your system.
2. Compile the program with:

```bash
g++ -o stickman stickman.cpp -lglfw -framework OpenGL -DGL_SILENCE_DEPRECATION
````

3. Run the executable:

```bash
./stickman
```

## Credits

This code was created with help from ChatGPT and inspired by the original Turbo C++ walking stickman animation tutorial:
[https://see-programming.blogspot.com/2013/09/walking-stickman-animation-using-c.html](https://see-programming.blogspot.com/2013/09/walking-stickman-animation-using-c.html)

