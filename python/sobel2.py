import cv2
import numpy as np

image = cv2.imread("../resource/k-landscape-wallpaper.jpg", cv2.IMREAD_COLOR)

# Optional 
def resizeImage():
    h, w, _ = image.shape
    rows = int(w/4)
    cols = int(h/4)

    img = cv2.resize(image, (rows, cols))

    # cv2.imshow("Original",img)
    return img


def sobel_filter():
    # Optional 
    img = resizeImage()

    MaskSobelX = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    MaskSobelY = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]])

    height = img.shape[0]
    width = img.shape[1]
    # channel = img.shape[2]

    # mOutimg = np.zeros((height, width, channel), np.uint16)

    pTmpXB = [width * height]
    pTmpXG = [width * height]
    pTmpXR = [width * height]
    pTmpYB = [width * height]
    pTmpYG = [width * height]
    pTmpYR = [width * height]

    for i in range(0, height):
        for j in range(0, width):
            pTmpXB.insert(i * width + j, 0)
            pTmpXG.insert(i * width + j, 0)
            pTmpXR.insert(i * width + j, 0)
            pTmpYB.insert(i * width + j, 0)
            pTmpYG.insert(i * width + j, 0)
            pTmpYR.insert(i * width + j, 0)

    for i in range(0, height):
        for j in range(0, width):
            pTmpXG[i * width + j] = 0
            pTmpXB[i * width + j] = 0
            pTmpXR[i * width + j] = 0
            pTmpYB[i * width + j] = 0
            pTmpYG[i * width + j] = 0
            pTmpYR[i * width + j] = 0

    for i in range(1, height-1):
        for j in range(1, width-1):
            newValueB = 0
            newValueG = 0
            newValueR = 0

            for mr in range(0, 3):
                for mc in range(0, 3):
                    newValueB += MaskSobelX[mr][mc]*img[i+mc-1, j+mr-1][0]
                    newValueG += MaskSobelX[mr][mc]*img[i+mc-1, j+mr-1][1]
                    newValueR += MaskSobelX[mr][mc]*img[i+mc-1, j+mr-1][2]

            pTmpXB[i * width + j] = newValueB
            pTmpXG[i * width + j] = newValueG
            pTmpXR[i * width + j] = newValueR

    for i in range(1, height-1):
        for j in range(1, width-1):
            newValueB = 0
            newValueG = 0
            newValueR = 0

            for mr in range(0, 3):
                for mc in range(0, 3):
                    newValueB += MaskSobelY[mr][mc]*img[i+mc-1, j+mr-1][0]
                    newValueG += MaskSobelY[mr][mc]*img[i+mc-1, j+mr-1][1]
                    newValueR += MaskSobelY[mr][mc]*img[i+mc-1, j+mr-1][2]

            pTmpYB[i * width + j] = newValueB
            pTmpYG[i * width + j] = newValueG
            pTmpYR[i * width + j] = newValueR

    for i in range(1, height-1):
        for j in range(1, width-1):
            constBVal1 = pTmpXB[i * width + j]
            constGVal1 = pTmpXG[i * width + j]
            constRVal1 = pTmpXR[i * width + j]
            constBVal2 = pTmpYB[i * width + j]
            constGVal2 = pTmpYG[i * width + j]
            constRVal2 = pTmpYR[i * width + j]

            if constBVal1 < 0:
                constBVal1 = -constBVal1
            if constGVal1 < 0:
                constGVal1 = -constGVal1
            if constRVal1 < 0:
                constRVal1 = -constRVal1
            if constBVal2 < 0:
                constBVal2 = -constBVal2
            if constGVal2 < 0:
                constGVal2 = -constGVal2
            if constRVal2 < 0:
                constRVal2 = -constRVal2

            pTmpXB[i * width + j] = constBVal1 + constBVal2
            pTmpXG[i * width + j] = constGVal1 + constGVal2
            pTmpXR[i * width + j] = constRVal1 + constRVal2

    minB = 10**10
    minG = 10**10
    minR = 10**10
    maxB = -10**10
    maxG = -10**10
    maxR = -10**10

    for i in range(1, height-1):
        for j in range(1, width-1):
            newValueB = pTmpXB[i * width + j]
            newValueG = pTmpXG[i * width + j]
            newValueR = pTmpXR[i * width + j]

            if newValueB < minB:
                minB = newValueB
            if newValueB > maxB:
                maxB = newValueB
            if newValueG < minG:
                minG = newValueG
            if newValueG > maxG:
                maxG = newValueG
            if newValueR < minR:
                minR = newValueR
            if newValueR > maxR:
                maxR = newValueR

    constBVal1 = float(255.0/(maxB - minB))
    constGVal1 = float(255.0/(maxG - minG))
    constRVal1 = float(255.0/(maxR - minR))
    constBVal2 = float(-255.0 * minB / (maxB - minB))
    constGVal2 = float(-255.0 * minG / (maxG - minG))
    constRVal2 = float(-255.0 * minR / (maxR - minR))

    for i in range(1, height - 1):
        for j in range(1, width - 1):

            b = pTmpXB[i * width + j]
            g = pTmpXG[i * width + j]
            r = pTmpXR[i * width + j]

            b = constBVal1 * b + constBVal2
            g = constGVal1 * g + constGVal2
            r = constRVal1 * r + constRVal2

            img[i, j][0] = b
            img[i, j][1] = g
            img[i, j][2] = r

    mOutimg = img
    del pTmpXB
    del pTmpXG
    del pTmpXR
    del pTmpYB
    del pTmpYG
    del pTmpYR
    # print(mOutimg)

    cv2.namedWindow("Sobel_Filter", cv2.WINDOW_AUTOSIZE)
    cv2.imshow("Sobel_Filter", mOutimg)


# Main Function
sobel_filter()

cv2.waitKey(0)
cv2.destroyAllWindows()
