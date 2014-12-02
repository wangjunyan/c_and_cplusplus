 #include <opencv2/highgui/highgui_c.h>
 #include<opencv/cv.h>

IplImage* doPyrDown(IplImage* in, int filter){
    assert(in->width%2 == 0 && in->height%2 == 0);
    IplImage* out = cvCreateImage(cvSize(in->width/2, in->height/2), in->depth, in->nChannels);
    cvPyrDown(in, out, filter);
    return out;
}

IplImage* doCanny(IplImage* in, double lowThresh, double highThresh, double aperture){
    if(in->nChannels != 1){
        return 0;
    }
    IplImage* out = cvCreateImage(cvSize(in->width, in->height), IPL_DEPTH_8U, 1);
    cvCanny(in, out, lowThresh, highThresh, aperture);
    return out;
}

 int main(int argc, char** argv) {
    IplImage* image = cvLoadImage(argv[1], 0);
    cvNamedWindow("Ex4_in", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Ex4_out", CV_WINDOW_AUTOSIZE);
    cvShowImage("Ex4_in", image);
    IplImage* out = doPyrDown(image, IPL_GAUSSIAN_5x5);
    IplImage* out1 = doPyrDown(out, IPL_GAUSSIAN_5x5);
    IplImage* out2 = doCanny(out1, 10, 100, 3);
    cvShowImage("Ex4_out", out2);
    cvMoveWindow("Ex4_out", 0, 0);
    cvReleaseImage(&out);
    cvReleaseImage(&out2);
    cvWaitKey(0);
    cvDestroyWindow("Ex4_in");
    cvDestroyWindow("Ex4_out");
    return 0;
 }
