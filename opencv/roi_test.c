 #include <opencv2/highgui/highgui_c.h>
 #include<opencv/cv.h>

 int main(int argc, char** argv) {
    IplImage* src;
    char* lib;
    char* mod;
    cvGetModuleInfo(0, &lib, &mod);
    printf("Libraries: %s\nModules: %s\n", lib, mod);
    if(argc == 7 && ((src = cvLoadImage(argv[1], 1)) != 0)){
        cvNamedWindow("origin", CV_WINDOW_AUTOSIZE);
        cvShowImage("origin", src);
        int x = atoi(argv[2]);
        int y = atoi(argv[3]);
        int w = atoi(argv[4]);
        int h = atoi(argv[5]);
        int add = atoi(argv[6]);
        //cvSetImageROI(src, cvRect(x, y, w, h));
        //cvAddS(src, cvScalar(add, 0, 0, 0), src, NULL);
        //cvResetImageROI(src);

        CvRect i_rect = cvRect(x, y, w, h);
        IplImage* sub_img = cvCreateImageHeader(cvSize(i_rect.width, i_rect.height), src->depth, src->nChannels);
        sub_img->origin = src->origin;
        sub_img->widthStep = src->widthStep;
        sub_img->imageData = src->imageData+i_rect.y*src->widthStep+i_rect.x*src->nChannels;
        cvAddS(sub_img, cvScalar(255, 0, 0, 0), sub_img, NULL);

        cvNamedWindow("Roi_add", CV_WINDOW_AUTOSIZE);
        cvShowImage("Roi_add", src);
        cvWaitKey(0);
    }
    return 0;
 }
