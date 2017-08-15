# A Circle and a Square
My solution to the HackerRank "A Circle and a Square" competition:
https://www.hackerrank.com/contests/w29/challenges/a-circle-and-a-square

## Problem description
From the site:
> In this challenge, you must implement part of a raster graphics editor that takes the coordinates of a circle and a square as input and draws them as filled-in shapes on a rectangular canvas.

## My implementation

### Data respresentation

The representation of the canvas was relatively straightforward, just a two dimensional vector of booleans to describe whether
a "pixel" is shaded or not.

### The circle
The circle was easy to tell if a given "pixel" is shaded, just take the center and radius of the circle and use the pythagorean
theorem to tell if a given point is within the circle.

### The square
The square was more difficult. My solution ended up telling whether a given pixel was in the square or not by making a 
(mathematical) vector from one of the corners given of the square to the other, generating a vector from the starting corner
to the given point, then using the dot product and cosine formula to tell if both the angle they made was less than 45 degrees,
and the length of the vector to the "pixel" was less than or equal to the length of the sides of the square. It's kind of like
if you take a string the length of a side of the square, pin one end to a corner, and sweep the other end across the square. 
It ends up marking some of the pixels in the middle twice, but it's not really an issue. 

### A note on rounding
Since the comparisons for points are done with floating point numbers, I had to add an epsilon to the numbers to prevent
rounding errors from messing up the comparisons.
