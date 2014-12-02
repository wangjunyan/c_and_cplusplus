 #include <opencv2/highgui/highgui_c.h>
 #include<opencv/cv.h>

 int main(int argc, char** argv) {
    CvPoint2D32f srcTri[3], dstTri[3];
    CvMat* rot_mat = cvCreateMat(2, 3, CV_32FC1);
    CvMat* warp_mat = cvCreateMat(2, 3, CV_32FC1);
    IplImage *src, *dst;
    if(argc == 2 && ((src = cvLoadImage(argv[1], 1)) != 0)){
        dst = cvCloneImage(src);
        dst->origin = src->origin;
        cvZero(dst);

        cvNamedWindow("Ex0", CV_WINDOW_AUTOSIZE);
        //cvShowImage("Ex0", src);
        srcTri[0].x = 0;
        srcTri[0].y = 0;
        srcTri[1].x = src->width - 1;
        srcTri[1].y = 0;
        srcTri[2].x = 0;
        srcTri[2].y = src->height - 1;
        dstTri[0].x = src->width * 0.0 ;
        dstTri[0].y = src->height * 0.33;
        dstTri[1].x = src->width * 0.85;
        dstTri[1].y = src->height * 0.25;
        dstTri[2].x = src->width * 0.15;
        dstTri[2].y = src->height * 0.7;

        cvGetAffineTransform(srcTri, dstTri, warp_mat);
        cvWarpAffine(src, dst, warp_mat, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
        cvCopy(dst, src, NULL);

        cvNamedWindow("Ex", CV_WINDOW_AUTOSIZE);
        cvShowImage("Ex", dst);

        CvPoint2D32f center = cvPoint2D32f(src->width/2, src->height/2);
        double angle = -50.0;
        double scale = 0.6;
        cv2DRotationMatrix(center, angle, scale, rot_mat);
        cvWarpAffine(src, dst, rot_mat, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
        cvShowImage("Ex0", dst);
        cvWaitKey(0);

        cvDestroyWindow("Ex");
        cvDestroyWindow("Ex0");
    }
    cvReleaseImage(&dst);
    cvReleaseMat(&rot_mat);
    cvReleaseMat(&warp_mat);
    return 0;
 }
