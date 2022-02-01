import cv2

image = cv2.imread("../resource/k-landscape-wallpaper.jpg", cv2.IMREAD_COLOR)

# Option function

def resizeImage():
    h, w, c = image.shape
    rows = int(w/4)
    cols = int(h/4)

    img = cv2.resize(image, (rows, cols))

    return img


def histogram_equalisation():

    image = resizeImage()
    imgEqual = image

    hight = image.shape[0]
    width = image.shape[1]

    histoB = [0]*256
    histoG = [0]*256
    histoR = [0]*256

    LUTB = [0]*256
    LUTG = [0]*256
    LUTR = [0]*256

    for i in range(0, hight):
        for j in range(0, width):
            intensityB = image[i, j][0]
            intensityG = image[i, j][1]
            intensityR = image[i, j][2]

            histoB[intensityB] += 1
            histoG[intensityG] += 1
            histoR[intensityR] += 1

    for i in range(0, 256):
        if (i == 0):
            histoB[i] = histoB[0]
            histoG[i] = histoG[0]
            histoR[i] = histoR[0]
        else:
            histoB[i] = histoB[i]+histoB[i-1]
            histoG[i] = histoG[i]+histoG[i-1]
            histoR[i] = histoR[i]+histoR[i-1]

    for i in range(0, 256):
        LUTB[i] = (float(histoB[i])/float(width*hight))*255
        LUTG[i] = (float(histoG[i])/float(width*hight))*255
        LUTR[i] = (float(histoR[i])/float(width*hight))*255

    for i in range(0, hight):
        for j in range(0, width):
            b = image[i, j][0]
            g = image[i, j][1]
            r = image[i, j][2]

            r = int(LUTR[r])
            g = int(LUTG[g])
            b = int(LUTB[b])

            imgEqual[i, j][0] = b
            imgEqual[i, j][1] = g
            imgEqual[i, j][2] = r

    cv2.namedWindow("Histogram_Equalization", cv2.WINDOW_AUTOSIZE)
    cv2.imshow("Histogram_Equalization", imgEqual)

image = resizeImage()

cv2.namedWindow("Original", cv2.WINDOW_AUTOSIZE)
cv2.imshow("Original", image)

histogram_equalisation()

cv2.waitKey(0)
cv2.destroyAllWindows()
