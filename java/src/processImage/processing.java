package processImage;

import java.util.*;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;

public class processing {
    static{ System.loadLibrary(Core.NATIVE_LIBRARY_NAME); }

    public void process() {

        System.loadLibrary( Core.NATIVE_LIBRARY_NAME );

        Scanner sc = new Scanner(System.in);

        grayscale gray = new grayscale();
        invertColor invert = new invertColor();
        mirror mirImg = new mirror();
        sobelFilter sobelFilter = new sobelFilter();

        resizeImage resizes = new resizeImage();
        
        Mat img;
        img = Imgcodecs.imread("landscape.jpg", Imgcodecs.IMREAD_COLOR);
        Mat image = resizes.sizeImage(img);
//        Mat image = img;

        HighGui.namedWindow("Grayscale", HighGui.WINDOW_AUTOSIZE);
        HighGui.imshow("Grayscale", image);

        Mat newImage;

        System.out.println("Choose the option to display the image:");
        System.out.print("""
                1. Display image in GrayScale.
                2. Display image in Reverse Color.
                3. Display Mirror image.
                4. Display image using Sobel Filter.
                5. Display image in different luminance(Dark and Light).
                6. Display image using Histogram Equalization.
                """);
        System.out.print("Enter the option: ");
        int choice = sc.nextInt();
        
        switch (choice){
            case 1 ->{
                newImage = gray.gray_image(image);
                 HighGui.namedWindow("Grayscale", HighGui.WINDOW_AUTOSIZE);
                 HighGui.imshow("Grayscale", newImage);
            }
            case 2 ->{
                newImage = invert.invert_color(image);
                HighGui.namedWindow("Invert_Color", HighGui.WINDOW_AUTOSIZE);
                HighGui.imshow("Invert_Color", newImage);
            }
            case 3->{
                newImage = mirImg.mirror_image(image);
                HighGui.namedWindow("Mirror_Image", HighGui.WINDOW_AUTOSIZE);
                HighGui.imshow("Mirror_Image", newImage);
            }
            case 4->{
                newImage = sobelFilter.sobel(image);
                HighGui.namedWindow("Sobel_Filter", HighGui.WINDOW_AUTOSIZE);
                HighGui.imshow("Sobel_Filter", newImage);
            }

            default -> System.out.print("Enter the correct choice");
        }
        
    }
}
