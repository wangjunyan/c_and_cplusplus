 #include <opencv2/highgui/highgui_c.h>

 int main(int argc, char** argv) {
        cvNamedWindow("Ex2", CV_WINDOW_AUTOSIZE);
        CvCapture* capture;
        if(argc == 1){
            capture = cvCreateCameraCapture(0);
        } else {
            capture = cvCreateFileCapture(argv[1]);
        }
        assert(capture != NULL);
        IplImage* frame;
        while(1) {
            frame = cvQueryFrame(capture);
            if(!frame) break;
            cvShowImage("Ex2", frame);
            char c = cvWaitKey(33);
            if(c == 27) break;
        }
        cvReleaseCapture(&capture);
        cvDestroyWindow("Ex2");
 }
