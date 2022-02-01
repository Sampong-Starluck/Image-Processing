# Image Processing (Year 5 ITC)

## Requirement for running the code
---
### Text editor or IDE
- Visual Studio Code (Python) or other IDE (Pycharm, ...)
- Visual Studio 2022, 2019, ... (c++)
### Library
- OpenCV (The time of writing opencv version 4.5.5)
- numpy for python
---

## Code explain and image formulas
---
### Grayscale
The formula for this function is <!-- $$ Luminance = (0.299 \times blue) + (0.587 \times green) + (0.114 \times red) $$ --> 

<div align="center"><img style="background: white;" src="svg\p7hbVXdigE.svg"></div> <br>
where red have color channel: 2, green color channel: 1 and blue color channel: 0

---
### Invert_Color
The formulas for changing the color of image from original color to invert color is:
<!-- $$ Invert = 255 - color $$ --> 

<div align="center"><img style="background: white;" src="svg\ub3CvnqMaE.svg"></div>
where the color is the image color in each pixels and the invert function must do it in all color channels (3 color channels).

---
### Mirror_image
To get the reflextion of the current image, there are two ways to do: <br>
- Shift position from up to down: by running the outer loop (i): 
<!-- $$mirror_{up} = rows - i - 1$$ --> 

<div align="center"><img style="background: white;" src="svg\Hj4S4LDUhH.svg"></div> 
- Shift position from right to left: by running the inner loop (j): 
<!-- $$ mirror_{side} = cols - j - 1 $$ --> 

<div align="center"><img style="background: white;" src="svg\is6hcUGDqA.svg"></div> 

---
### Sobel_filter
The formula for this function has two parts:
- Convolutional: Smoothing [1 2 1] and Derivative [1 0 -1]
<!-- $$ 
\frac{dI}{dx} = 
\left(\begin{array}{cc} 
1 & 0 & -1\\
2 & 0 & -2\\
1 & 0 & -1\\
\end{array}\right) / 4 \quad\quad
\frac{dI}{dy} = 
\left(\begin{array}{cc} 
-1 & -2 & -1\\
0 & 0 & 0\\
1 & 2 & 1\\
\end{array}\right)/4
$$ --> 

<div align="center"><img style="background: white;" src="svg\VsdvAtMCPA.svg"></div> 
- Mean of Derivative at $x$ and $x-1$:
<!-- $$\frac{I[x + 1] - I[x - 1]}{2}$$ --> 

<div align="center"><img style="background: white;" src="svg\FrYXlyHdqO.svg"></div>

---
### Luminance (Dark)
the value of the color. <br>
If the result of minus is lower than 0, set the condition where any pixels that lower than 0 is 0.
<!-- $$Dark\_ Luminance = pixel - dark$$ --> 

<div align="center"><img style="background: white;" src="svg\SkS3Ncd1v7.svg"></div>
where $dark$ is number that we want to minus. Example: dark = 100

---
### Luminance (Light)
To make the image brighter than the original, image's pixel should be add the value of the color. <br>
If the result of summing is higher than 255, set the condition where any pixels that higher than 255 is 255.
<!-- $$Light\_ Luminance = pixel + light$$ --> 

<div align="center"><img style="background: white;" src="svg\6nXiqLVIyN.svg"></div>
where $light$ is number that we want to minus. Example: light = 100

--- 
### Histogram Equalization
Let *f*  a given image represented as a mrby mcmatrix of integer pixel intensities ranging from 0 to $L–1$. *L* is the number of possible intensity values,
 often 256. <br>
Let *p* denote the normalized histogram of *f* with a bin for each possible intensity. So,

<!-- $$ p_n = \frac{\text{number of pixels with intensity}\quad n}{\text{total number of pixels}} $$ --> 

<div align="center"><img style="background: white;" src="svg\zzbz7aoM8H.svg"></div>

The histogram equalized image *g* will be defined by:
<!-- $$g_{i,j} = floor((L-1)\sum_{n=0}^{f_{i,j}}p_n)$$ --> 

<div align="center"><img style="background: white;" src="svg\7FpU04p9n4.svg"></div>
where floor() rounds down to the nearest integer. <br>
<br>
This is equivalent to transforming the pixel intensities, *k*, of *f* by the function:
<!-- $$T(k) = floor((L-1)\sum_{n=0}^{k}p_n)$$ --> 

<div align="center"><img style="background: white;" src="svg\k6h1qPZ9et.svg"></div>
Notice that *T* maps the levels into the range [0,1], since we used a normalized histogram of {x}. <br>
In order to map the values back into their original range, the following simple transformation needs to be applied on the result:

<!-- $$y' = y \times (max\{x\}-mix\{x\})+mix\{x\}$$ --> 

<div align="center"><img style="background: white;" src="svg\8QRi4WpVZv.svg"></div>