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
Note: 
- The fully render explaination can be found in python jupiter notebook. (image_processing.ipynb)
- Java code cannot run properly. I recommend to use C++ or Python instead of Java.
---
### Grayscale
The formula for this function is 
$$ Luminance = (0.299 \times blue) + (0.587 \times green) + (0.114 \times red) $$ 
where red have color channel: 2, green color channel: 1 and blue color channel: 0

---
### Invert_Color
The formulas for changing the color of image from original color to invert color is:
$$ Invert = 255 - color $$
where the color is the image color in each pixels and the invert function must do it in all color channels (3 color channels).

---
### Mirror_image
To get the reflextion of the current image, there are two ways to do: <br>
- Shift position from up to down: by running the outer loop (i): 
$$ mirror_{up} = rows - i - 1 $$ 
- Shift position from right to left: by running the inner loop (j): 
$$ mirror_{side} = cols - j - 1 $$

---
### Sobel_filter
The formula for this function has two parts:
- Convolutional: Smoothing [1 2 1] and Derivative [1 0 -1]
$$ 
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
$$ 
- Mean of Derivative at $x$ and $x-1$:
$$\frac{I[x + 1] - I[x - 1]}{2}$$

---
### Luminance (Dark)
the value of the color. <br>
If the result of minus is lower than 0, set the condition where any pixels that lower than 0 is 0.
$$Dark\_ Luminance = pixel - dark$$
where $dark$ is number that we want to minus. Example: dark = 100

---
### Luminance (Light)
To make the image brighter than the original, image's pixel should be add the value of the color. <br>
If the result of summing is higher than 255, set the condition where any pixels that higher than 255 is 255.
$$Light\_ Luminance = pixel + light$$
where $light$ is number that we want to minus. Example: light = 100

--- 
### Histogram Equalization
Let *f*  a given image represented as a mrby mcmatrix of integer pixel intensities ranging from 0 to $L–1$. *L* is the number of possible intensity values,
 often 256. <br>
Let *p* denote the normalized histogram of *f* with a bin for each possible intensity. So,

$$ p_n = \frac{\text{number of pixels with intensity}\quad n}{\text{total number of pixels}} $$

The histogram equalized image *g* will be defined by:
$$g_{i,j} = floor((L-1)\sum_{n=0}^{f_{i,j}}p_n)$$
where floor() rounds down to the nearest integer. <br>
<br>
This is equivalent to transforming the pixel intensities, *k*, of *f* by the function:
$$T(k) = floor((L-1)\sum_{n=0}^{k}p_n)$$
Notice that *T* maps the levels into the range [0,1], since we used a normalized histogram of {x}. <br>
In order to map the values back into their original range, the following simple transformation needs to be applied on the result:
$$y' = y \times (max\{x\}-mix\{x\})+mix\{x\}$$
