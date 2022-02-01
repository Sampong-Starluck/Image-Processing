import cv2

image = cv2.imread("../resource/k-landscape-wallpaper.jpg", cv2.IMREAD_COLOR)


def light_luminance():
    img = image
    light = 100

    height, width, _ = img.shape

    for i in range(height):
        for j in range(width):

            b = img[i, j][0] + light
            g = img[i, j][1] + light
            r = img[i, j][2] + light

            if b > 255:
                b = 255
            if g > 255:
                g = 255
            if r > 255:
                r = 255

            img[i, j][0] = b
            img[i, j][1] = g
            img[i, j][2] = r

    cv2.namedWindow("Light_Luminance", cv2.WINDOW_AUTOSIZE)
    cv2.imshow("Light_Luminance", img)


light_luminance()
