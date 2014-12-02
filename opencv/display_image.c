 // gcc display_image.c -lopencv_core -lopencv_highgui -lopencv_imgproc

 #include <opencv2/highgui/highgui_c.h>

 int main(int argc, char** argv){
    IplImage* img = cvLoadImage(argv[1], 1);
    cvNamedWindow("Ex1", CV_WINDOW_AUTOSIZE);
    cvShowImage("Ex1", img);
    while(1){
        char c = cvWaitKey(100);
        if(c == 27) break;
    }
    cvReleaseImage(&img);
    cvDestroyWindow("Ex1");
 }
