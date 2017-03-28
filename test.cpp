/* Wadim Mueller
 * Tesbench for morphological filtering*/

#include "hls_opencv.h"
#include "top.h"
#include "opencv_top.h"
#include "image_utils.h"

using namespace cv;

extern void hls_image_filter(Mat src, Mat dst);
extern void opencv_image_filter(Mat src, Mat dst);

int main (int argc, char** argv) {

    Mat src_gray = imread(INPUT_IMAGE, CV_LOAD_IMAGE_GRAYSCALE);
    Mat dst(src_gray.size(), CV_8UC1);

    if (!src_gray.data) {
        printf("ERROR: could not open or find the input image!\n");
        return -1;
    }

    hls_image_filter(src_gray, dst);
    imwrite(OUTPUT_IMAGE, dst);
    opencv_image_filter(src_gray, dst);
    imwrite(OUTPUT_IMAGE_GOLDEN, dst);

    return image_compare(OUTPUT_IMAGE, OUTPUT_IMAGE_GOLDEN);
}
