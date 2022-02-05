package processImage;

import org.opencv.core.*;

public class grayscale {
    static{ System.loadLibrary(Core.NATIVE_LIBRARY_NAME); }

    public Mat gray_image() {

        return null;
    }

    public Mat gray_image(Mat img) {
        Scalar scale = new Scalar(0);
        double[] rgb;
        Mat lumime = new Mat(img.size(), CvType.CV_8UC1, scale);

        for (int i = 0; i < img.rows(); i++) {
            for (int j = 0; j < img.cols(); j++) {
                rgb = img.get(i, j);
                lumime.put(i, j, (0.299 * rgb[2] + 0.587 * rgb[1] + 0.114 * rgb[0]));
            }
        }
        // HighGui.namedWindow("Grayscale", HighGui.WINDOW_AUTOSIZE);
        // HighGui.imshow("Grayscale", lumime);
        return lumime;

    }
}
