# fractal-generator
This is a simple OpenGL fractal generator/visualizer. Some fractals are defined which are then displayed using OpenGL with zooming capability.

## Fractals
Here, fractals are defined by set theory and limits. The equation used is below:

<img src="https://latex.codecogs.com/gif.latex?z_n\in\text{F}\text{iff}\limsup_{n\to\\d}|z_{n+1}|\leq5" /> 

Where <img src="https://latex.codecogs.com/gif.latex?d" /> is the maximum number of iterations performed on <img src="https://latex.codecogs.com/gif.latex?z_n" />. Each iteration is defined by an arithmetic expression describing the relationship between <img src="https://latex.codecogs.com/gif.latex?z_n" /> and <img src="https://latex.codecogs.com/gif.latex?z_{n+1}" />, which is defined in terms of complex number arithmetic. 

The superior limit of this iteration will consider points in fractal set if their iterations remain bounded within the set after the <img src="https://latex.codecogs.com/gif.latex?d" />th iteration. Points which pass this test are within the set, with all others some distance from the set (used for coloring).

Consider <img src="https://latex.codecogs.com/gif.latex?d=0" />: all points in the plane are within the set. With <img src="https://latex.codecogs.com/gif.latex?d=1" />, less are within the set, and so on until the shape of the set is realized. A very large <img src="https://latex.codecogs.com/gif.latex?d" /> will render the fractal set with higher precision but may be difficult to see as points become "infinitely" thin; contrastingly, a very small <img src="https://latex.codecogs.com/gif.latex?d" /> will render the fractal set with very little granularity and is overall an inaccurate render. 

Suggested use case scenario is <img src="https://latex.codecogs.com/gif.latex?d\in[64,512]" /> as it's a good balance between clarity, visual pleasure, and of course execution time.

## Supported Fractals
Included are ten fractals, the first three have canonical names and the other seven are found through experimentation. The canonically named fractals alongside their iterative arithmetic is below:

<b>Mandelbrot Set</b>
- <img src="https://latex.codecogs.com/gif.latex?z_{n+1}=z_n^2+c" /> 

<b>Julia Set</b>
- <img src="https://latex.codecogs.com/gif.latex?z_{n+1}=z_n^2+k" /> 
- <img src="https://latex.codecogs.com/gif.latex?k" /> is some constant, here defined as <img src="https://latex.codecogs.com/gif.latex?(-0.835-0.232i)" />

<b>Burning Ship Set</b>
- <img src="https://latex.codecogs.com/gif.latex?z_{n+1}=|z_n|^2+c" /> 

You can experiment with other fractals by editing `Set.cpp`: within `Set::iterate()` you can define the arithmetic expression which determines the set. Using a subset of complex number arithmetic, you can define new fractals. Available arithmetic operations are:

- `neg()` on a complex number <img src="https://latex.codecogs.com/gif.latex?(a+bi)" /> returns <img src="https://latex.codecogs.com/gif.latex?(-a-bi)" />
- `inv()` on a complex number <img src="https://latex.codecogs.com/gif.latex?(a+bi)" /> returns <img src="https://latex.codecogs.com/gif.latex?(b+ai)" />
- `abso()` on a complex number <img src="https://latex.codecogs.com/gif.latex?(a+bi)" /> returns <img src="https://latex.codecogs.com/gif.latex?(|a|+|b|i)" />
- standard operators `+`, `-`, `*` and `^` will function as expected
- `^` only works with integer as second operand

For example, to get <img src="https://latex.codecogs.com/gif.latex?z_{n+1}=-z_n^3+z_n^2+c" />, you would hardcode in `(z^3).neg() + z^2 + c`, etc.

## Dependencies
- Freeglut
- Freeimage
- C++03 or later
- gcc
- X11 or other window manager

## Execution
    # Using included script:
    $ ./fractal-generator.sh <arg>
    # Or alternatively, manually compile and run:
    $ g++ src/main.cpp -O2 -lGL -lGLU -lglut -lfreeimage -lX11 -std=c++0x
    $ /a.out <arg>
  
`<arg>` is the maximum depth (number of iterations) used to define fractal within the range `[32, 4096]`. Higher is slower but shows higher fidelity of the fractal set. This is the <img src="https://latex.codecogs.com/gif.latex?d" /> from before. Default is <img src="https://latex.codecogs.com/gif.latex?d=128" />.

CLI will appear on execution detailing controls. `1` through `0` will cycle between fractals, `r` to reset, `s` to save screen capture to parent directory. Use mouse buttons to zoom in and out.

## Example Outputs
<img src="https://github.com/stratzilla/fractal-generator/blob/master/img/ShurikenZoom.png" width="20%"/> <img src="https://github.com/stratzilla/fractal-generator/blob/master/img/MandelbrotDefault.png" width="20%"/> <img src="https://github.com/stratzilla/fractal-generator/blob/master/img/VeinDefault.png" width="20%"/> <img src="https://github.com/stratzilla/fractal-generator/blob/master/img/JuliaZoom.png" width="20%"/>

L-to-R: `(z^2 - z^3) + (-0.372 + 0.519i)`, `z^2 + c`, `z.inv().neg()^2 + z`, `z^2 + (-0.835 - 0.232i)`. More examples in `img/`. These images found using <img src="https://latex.codecogs.com/gif.latex?d=64" />.

## Future
It is painfully trivial to add more fractals to the system, but this requires hardcoding. A truly generalized fractal visualizer should parse user input (eg. a string) into an arithmetic expression which defines the iteration for the fractal set. Perhaps in the future I can implement this. Lambda expressions are a possibility but I constrained myself to C++03.
