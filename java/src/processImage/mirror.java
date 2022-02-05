package processImage;

import org.opencv.core.Core;
import org.opencv.core.Mat;

public class mirror {
    static{ System.loadLibrary(Core.NATIVE_LIBRARY_NAME); }
    public Mat mirror_image() {
        return null;
    }

    public Mat mirror_image(Mat img) {
        Mat mirrorImg = Mat.zeros(img.size(), img.type());

        for (int i = 0; i < img.rows(); i++) {
            for (int j = 0; j < img.cols(); j++) {
                mirrorImg.get(i, j, (img.get(i, img.cols() - 1 - j)));
            }
        }

        return mirrorImg;
    }
}
