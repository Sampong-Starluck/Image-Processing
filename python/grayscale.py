import cv2
from cv2 import IMREAD_COLOR
import numpy as np

def grayscale(img):
    rows, cols, _ = img.shape
    for i in range(rows):
        for j in range(cols):
            blue = img[i,j][0]
            green = img[i,j][1]
            red = img[i,j][2]
            
            img[i,j] = (0.299 * blue) + (0.587 * green) + (0.114 * red)
    
    cv2.imshow("grayScale",img)
    

image = cv2.imread("../k-landscape-wallpaper.jpg",IMREAD_COLOR)

h, w, _ = image.shape

rows = int(w/4)
cols = int(h/4)
# print(rows, cols)
img = cv2.resize(image, (rows, cols))

cv2.namedWindow("Original", cv2.WINDOW_AUTOSIZE)
cv2.imshow("Original", img)
grayscale(img)
cv2.waitKey()
