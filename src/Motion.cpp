#include "Motion.h"
#include "cv.h"
#include "highgui.h"
using namespace std;
using namespace cv;


Motion::Motion()
{
    cap = cvCaptureFromCAM(CV_CAP_ANY);
}

Motion::~Motion()
{
    cvReleaseCapture(&cap);
    cvDestroyWindow("Camera");
}

void Motion::Init()
{

    char key;
    printf("Hello world\n");
    cvNamedWindow("Camera",1);
    while(1){
        IplImage *frame = cvQueryFrame(cap);
        cvShowImage("Camera", frame);
        key = cvWaitKey(10);
        if(char(key) == 27)
        {
            break;
        }
    }
}

void Motion::Tracking()
{
}

void Motion::Detection()
{
}

bool Motion::isHuman()
{
    return false;
}

bool Motion::isCar()
{
    return false;
}

