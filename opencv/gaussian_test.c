 #include <opencv2/highgui/highgui_c.h>
 #include<opencv/cv.h>

void ex2_4(IplImage *image){
    cvNamedWindow("Ex4_in", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Ex4_out", CV_WINDOW_AUTOSIZE);
    cvShowImage("Ex4_in", image);
    IplImage* out = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
    cvSmooth(image, out, CV_GAUSSIAN, 3, 3, 0, 0);
    cvShowImage("Ex4_out", out);
    cvReleaseImage(&out);
    cvWaitKey(0);
    cvDestroyWindow("Ex4_in");
    cvDestroyWindow("Ex4_out");
}

 int main(int argc, char** argv) {
    IplImage* img = cvLoadImage(argv[1], 1);
    ex2_4(img);
 }
