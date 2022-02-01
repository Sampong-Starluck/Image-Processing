import cv2
import numpy as np
# from PIL import Image

image = cv2.imread("../k-landscape-wallpaper.jpg", cv2.IMREAD_COLOR)

def resizeImage():
    h, w, _ = image.shape
    rows = int(w/4)
    cols = int(h/4)

    img = cv2.resize(image, (rows, cols))

    return img

def sobel_filter():
    # get image with proper size
    img = resizeImage()

    # Matrice de sobel
    MaskSobelX = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    MaskSobelY = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]])

    # Demension de l'image
    height = img.shape[0]
    width = img.shape[1]
    # width, height = img.size

    pTmpXB = [width * height]
    pTmpXG = [width * height]
    pTmpXR = [width * height]
    pTmpYB = [width * height]
    pTmpYG = [width * height]
    pTmpYR = [width * height]

    # Donner les variables pour loop
    i = 0
    j = 0

    for i in range(height):
        for j in range(width):
            pTmpXB.insert(i * width + j, 0)
            pTmpXG.insert(i * width + j, 0)
            pTmpXR.insert(i * width + j, 0)
            pTmpYB.insert(i * width + j, 0)
            pTmpYG.insert(i * width + j, 0)
            pTmpYR.insert(i * width + j, 0)

    i = 0
    j = 0

    for i in range(height):
        for j in range(width):
            pTmpXG[i * width + j] = 0
            pTmpXB[i * width + j] = 0
            pTmpXR[i * width + j] = 0
            pTmpYB[i * width + j] = 0
            pTmpYG[i * width + j] = 0
            pTmpYR[i * width + j] = 0

    i = 1
    j = 1
    mr = 0
    mc = 0

    for i in range(height-1):
        for j in range(width-1):
            newValueB = 0
            newValueG = 0
            newValueR = 0
            for mr in range(3):
                for mc in range(3):
                    b = img[i+mc-1, j+mr-1][0]
                    g = img[i+mc-1, j+mr-1][1]
                    r = img[i+mc-1, j+mr-1][2]
                    newValueB += MaskSobelX[mr][mc] * b
                    newValueG += MaskSobelX[mr][mc] * g
                    newValueR += MaskSobelX[mr][mc] * r

            # On sort de la boucle et on assigne de la valeur du pixel
            pTmpXB[i * width + j] = newValueB
            pTmpXG[i * width + j] = newValueG
            pTmpXR[i * width + j] = newValueR

    i = 1
    j = 1
    mr = 0
    mc = 0

    for i in range(1, height-1):
        for j in range(1, width-1):
            newValueB = 0
            newValueG = 0
            newValueR = 0
            for mr in range(3):
                for mc in range(3):
                    b = img[i+mc-1, j+mr-1][0]
                    g = img[i+mc-1, j+mr-1][1]
                    r = img[i+mc-1, j+mr-1][2]
                    newValueB += MaskSobelY[mr][mc] * b
                    newValueG += MaskSobelY[mr][mc] * g
                    newValueR += MaskSobelY[mr][mc] * r

            # On sort de la boucle et on assigne de la valeur du pixel
            pTmpYB[i * width + j] = newValueB
            pTmpYG[i * width + j] = newValueG
            pTmpYR[i * width + j] = newValueR

    i = 1
    j = 1

    for i in range(height-1):
        for j in range(width-1):
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

    minB = minG = minR = 10**10
    maxB = maxG = maxR = -10**10
    i = 1
    j = 1

    for i in range(height - 1):
        for j in range(width - 1):
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

    constBVal1 = float(255.0 / (maxB - minB))
    constBVal2 = float(-255.0 * minB / (maxB - minB))
    constGVal1 = float(255.0 / (maxG - minG))
    constGVal2 = float(-255.0 * minG / (maxG - minG))
    constRVal1 = float(255.0 / (maxR - minR))
    constRVal2 = float(-255.0 * minR / (maxR - minR))

    i = 1
    j = 1

    for i in range(height - 1):
        for j in range(width - 1):
            # Step 1
            # b = pTmpXB[i * width + j]
            # g = pTmpXG[i * width + j]
            # r = pTmpXR[i * width + j]

            # #Step 2
            # b = int(constBVal1  + constBVal2) + b
            # g = int(constGVal1  + constGVal2) + g
            # r = int(constRVal1  + constRVal2) + r

            # #Step 3
            # img[i, j][0] = b
            # img[i, j][1] = g
            # img[i, j][2] = r
            
            img[i, j][0] = int(constBVal1 * pTmpXB[i * width + j] + constBVal2)
            img[i, j][1] = int(constGVal1 * pTmpXG[i * width + j] + constGVal2)
            img[i, j][2] = int(constRVal1 * pTmpXR[i * width + j] + constRVal2)
            
    sobel = img
    
    del pTmpXB
    del pTmpXG
    del pTmpXR
    del pTmpYB
    del pTmpYG
    del pTmpYR

    cv2.namedWindow("Sobel_Filter", cv2.WINDOW_AUTOSIZE)
    cv2.imshow("Sobel_Filter", sobel)


sobel_filter()

cv2.waitKey(0)
cv2.destroyAllWindows()
