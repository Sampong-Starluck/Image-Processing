package processImage;

import org.opencv.core.Core;
import org.opencv.core.Mat;

public class invertColor {
    static{ System.loadLibrary(Core.NATIVE_LIBRARY_NAME); }

    public Mat invert_color() {

        return null;
    }

    public Mat invert_color(Mat img) {
        double[] rgb;
        Mat invert = Mat.zeros(img.size(), img.type());

        for (int i = 0; i < img.rows(); i++) {
            for (int j = 0; j < img.cols(); j++) {

                rgb = img.get(i, j);
                invert.put(i, j, (255 - rgb[0]));
                invert.put(i, j, (255 - rgb[1]));
                invert.put(i, j, (255 - rgb[2]));
            }
        }

        return invert;
    }
}
