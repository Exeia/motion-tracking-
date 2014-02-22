#include "Motion.h"
#include "cv.h"
#include "highgui.h"
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


Motion::Motion()
{
}

Motion::~Motion()
{
    cvReleaseCapture(&cap);
    cvDestroyWindow("Camera");
}

int Motion::Init()
{

    /*cap = cvCaptureFromCAM(1);
    if(!cap)
    {
        cout<< "Capture failure" <<endl;
        return -1;
    }

    IplImage *frame = cvQueryFrame(cap);
    if (!frame) {
        return -1;    
    }


    char key;
    cvNamedWindow("Camera",1);
    cvNamedWindow("Camera1",1);
    while(1){
        
        cvShowImage("Camera", frame);
        frame = cvQueryFrame(cap);
        if (!frame) {
            break;
        }
        frame = cvCloneImage(frame);

        key = cvWaitKey(10);
        if(char(key) == 27)
        {
            break;
        }
    }*/
    Mat frame;
    Mat back;
    Mat fore;
    VideoCapture cap(1);
    BackgroundSubtractorMOG2 bg;
    bg.set("nmixtures",3);
    char key;
    bg.setBool("detectShadows",false);
 
    vector<std::vector <Point> > contours;
    cv::namedWindow("Frame");
    while(true)
    {
        cap >> frame;
        bg.operator ()(frame,fore);
        bg.getBackgroundImage(back);
        cv::erode(fore,fore,cv::Mat());
        cv::dilate(fore,fore,cv::Mat());
        cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
        cv::drawContours(frame,contours,-1,cv::Scalar(0,0,255),2);
        cv::imshow("Frame",frame);
        cv::imshow("Background",back);
        key = cvWaitKey(10);
        if(char(key) == 27)
        {
            break;
        }

    }
    return 0;
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

