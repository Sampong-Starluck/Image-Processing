package processImage;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Size;

public class sobelFilter {
    static{ System.loadLibrary(Core.NATIVE_LIBRARY_NAME); }

    public Mat sobel() {
        return null;
    }

    public Mat sobel(Mat img) {

        // TODO: Create a sobel Filter using formulas

        int[][] MaskSobelX = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
        int[][] MaskSobelY = { { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } };
        int height = img.rows();
        int width = img.cols();
        int r;
        int g;
        int b;
        int mr, mc; // Mask row and Mask column
        int minB, maxB, minG, maxG, minR, maxR;
        int newValueB, newValueG, newValueR;
        double[] rgb;
        int[] pTmpXB;
        int[] pTmpYB;
        int[] pTmpXG;
        int[] pTmpYG;
        int[] pTmpXR;
        int[] pTmpYR;
        float constBVal1, constBVal2, constGVal1, constGVal2, constRVal1, constRVal2;
        Size size_img;
        size_img = new Size(img.rows(), img.cols());
        new Mat(size_img, CvType.CV_8UC3);
        Mat sobel;

        pTmpXB = new int[width * height];
        pTmpXG = new int[width * height];
        pTmpXR = new int[width * height];
        pTmpYB = new int[width * height];
        pTmpYG = new int[width * height];
        pTmpYR = new int[width * height];

        sobel = Mat.zeros(size_img, img.type());

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                pTmpXB[i * width + j] = 0;
                pTmpXG[i * width + j] = 0;
                pTmpXB[i * width + j] = 0;
                pTmpYB[i * width + j] = 0;
                pTmpYG[i * width + j] = 0;
                pTmpYR[i * width + j] = 0;
            }
        }

        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                rgb = img.get(i, j);

                newValueB = 0;
                newValueG = 0;
                newValueR = 0;

                for (mr = 0; mr < 3; mr++) {
                    for (mc = 0; mc < 3; mc++) {
                        newValueB += MaskSobelX[mr][mc] * img.put(i + mr - 1, j + mc - 1, rgb[0]);
                        newValueG += MaskSobelX[mr][mc] * img.put(i + mr - 1, j + mc - 1, rgb[1]);
                        newValueR += MaskSobelX[mr][mc] * img.put(i + mr - 1, j + mc - 1, rgb[2]);
                    }
                }
                pTmpXB[i * width + j] = newValueB;
                pTmpXG[i * width + j] = newValueG;
                pTmpXR[i * width + j] = newValueR;
            }
        }

        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                rgb = img.get(i, j);

                newValueB = 0;
                newValueG = 0;
                newValueR = 0;

                for (mr = 0; mr < 3; mr++) {
                    for (mc = 0; mc < 3; mc++) {
                        newValueB += MaskSobelY[mr][mc] * img.put(i + mr - 1, j + mc - 1, rgb[0]);
                        newValueG += MaskSobelY[mr][mc] * img.put(i + mr - 1, j + mc - 1, rgb[1]);
                        newValueR += MaskSobelY[mr][mc] * img.put(i + mr - 1, j + mc - 1, rgb[2]);
                    }
                }
                pTmpYB[i * width + j] = newValueB;
                pTmpYG[i * width + j] = newValueG;
                pTmpYR[i * width + j] = newValueR;
            }
        }

        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                constBVal1 = pTmpXB[i * width + j];
                constGVal1 = pTmpXG[i * width + j];
                constRVal1 = pTmpXR[i * width + j];
                constBVal2 = pTmpYB[i * width + j];
                constGVal2 = pTmpYG[i * width + j];
                constRVal2 = pTmpYR[i * width + j];

                if (constBVal1 < 0) {
                    constBVal1 = -constBVal1;
                }
                if (constGVal1 < 0) {
                    constGVal1 = -constGVal1;
                }
                if (constRVal1 < 0) {
                    constRVal1 = -constRVal1;
                }
                if (constBVal2 < 0) {
                    constBVal2 = -constBVal2;
                }
                if (constGVal2 < 0) {
                    constGVal2 = -constGVal2;
                }
                if (constRVal2 < 0) {
                    constRVal2 = -constRVal2;
                }

                pTmpXB[i * width + j] = (int) (constBVal1 + constBVal2);
                pTmpXG[i * width + j] = (int) (constGVal1 + constGVal2);
                pTmpXR[i * width + j] = (int) (constRVal1 + constRVal2);
            }
        }
        
        minB = minG = minR = (int) 10e10;
        maxB = maxG = maxR = (int) -10e10;
        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                newValueB = pTmpXB[i * width + j];
                newValueG = pTmpXG[i * width + j];
                newValueR = pTmpXR[i * width + j];

                if (newValueB < minB) {
                    minB = newValueB;
                }
                if (newValueB > maxB) {
                    maxB = newValueB;
                }
                if (newValueG < minG) {
                    minG = newValueG;
                }
                if (newValueG > maxG) {
                    maxG = newValueG;
                }
                if (newValueR < minR) {
                    minR = newValueR;
                }
                if (newValueR > maxR) {
                    maxR = newValueR;
                }
            }
        }
        constBVal1 = (float) (255.0 / (maxB - minB));
        constGVal1 = (float) (255.0 / (maxG - minG));
        constRVal1 = (float) (255.0 / (maxR - minR));
        constBVal2 = (float) (-255.0 * minB / (maxB - minB));
        constGVal2 = (float) (-255.0 * minG / (maxG - minG));
        constRVal2 = (float) (-255.0 * minR / (maxR - minR));
        
        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                rgb = sobel.get(i, j);

                b = pTmpXB[i * width + j];
                g = pTmpXG[i * width + j];
                r = pTmpXR[i * width + j];

                b = (int) (constBVal1 * b + constBVal2);
                g = (int) (constGVal1 * g + constGVal2);
                r = (int) (constRVal1 * r + constRVal2);

                rgb[0] = b;
                rgb[1] = g;
                rgb[2] = r;

                sobel.put(i, j, rgb[0]);
                sobel.put(i, j, rgb[1]);
                sobel.put(i, j, rgb[2]);

            }
        }
        pTmpXB = null;
        pTmpXG = null;
        pTmpXR = null;
        pTmpYB = null;
        pTmpYG = null;
        pTmpYR = null;

        return sobel;
    }
}
