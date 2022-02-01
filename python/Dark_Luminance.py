import cv2

image = cv2.imread("../resource/k-landscape-wallpaper.jpg", cv2.IMREAD_COLOR)


def dark_luminance():
    img = image
    dark = 100

    height, width, _ = img.shape

    for i in range(height):
        for j in range(width):

            b = img[i, j][0] - dark
            g = img[i, j][1] - dark
            r = img[i, j][2] - dark

            if b < 0:
                b = 0
            if g < 0:
                g = 0
            if r < 0:
                r = 0

            img[i, j][0] = b
            img[i, j][1] = g
            img[i, j][2] = r

    cv2.namedWindow("Dark_Luminance", cv2.WINDOW_AUTOSIZE)
    cv2.imshow("Dark_Luminance", img)


dark_luminance()
