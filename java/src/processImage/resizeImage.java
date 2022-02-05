package processImage;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Size;
import static org.opencv.imgproc.Imgproc.resize;

public class resizeImage {
    static{ System.loadLibrary(Core.NATIVE_LIBRARY_NAME); }

    public resizeImage() {
    }

    public Mat sizeImage(Mat image) {
        Mat images = new Mat();
        int height = image.rows() / 4;
        int width = image.cols() / 4;
        
        new Size(width,height);

        resize(image, images, new Size(width,height));

        return images;
    }
}