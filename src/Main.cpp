#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace std;
int main()
{
    char key;
    printf("Hello world\n");
    cvNamedWindow("Camera",1);
    CvCapture * cap = cvCaptureFromCAM(CV_CAP_ANY);
    while(1){
        IplImage *frame = cvQueryFrame(cap);
        cvShowImage("Camera", frame);
        key = cvWaitKey(10);
        if(char(key) == 27)
        {
            break;
        }
    }
    cvReleaseCapture(&cap);
    cvDestroyWindow("Camera");
    return 0;
}
