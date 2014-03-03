#include "Motion.h"
#include "cv.h"
#include "highgui.h"
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


Motion::Motion()
{
}
Motion::Motion(char *path)
{
    p = new char (sizeof(path));
    p = path;    
}
Motion::~Motion()
{
    cvReleaseCapture(&cap);
    cvDestroyWindow("Camera");
}

int Motion::Init(char *path)
{

    if(path != NULL)
    {
        Tracking(path);
    }
    else
    {
        Detection();
    }
    return 0;
}

int Motion::Tracking(char *path)
{

    Mat frame;
    Mat back;
    Mat fore;
        VideoCapture c(path);
     if (!c.isOpened()) {
         cout << "Cannot open file" << endl;
         return -1;
     }
    BackgroundSubtractorMOG2 bg;
    bg.set("nmixtures",3);
    char key;
    bg.set("detectShadows",0);
// HOGDescriptor h;
    vector<std::vector <Point> > contours;
//    h.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
   namedWindow("Frame", 1);
   namedWindow("Fore",1);
   namedWindow("Back",1);
    while(true)
    {
          /* code */
        bool isRun = c.read(frame);

       Mat ee = getStructuringElement(MORPH_RECT, Size(3,3));
       Mat de = getStructuringElement(MORPH_RECT, Size(8,8));

       bg.operator ()(frame,fore);
       
       bg.getBackgroundImage(back);
        erode(fore,fore,ee);
        erode(fore,fore,ee);
        dilate(fore,fore,de);
        dilate(fore,fore,de);
       findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
       vector<Rect> r (contours.size());
       drawContours(frame,contours,-1,cv::Scalar(0,255,0),2);
       imshow("Frame",frame);
        imshow("Fore",fore);
         imshow("Back",back);
    //    Tracking(h,frame);
    /*double t = (double)getTickCount();
    vector<Rect> f, filtered;
    h.detectMultiScale(frame, f, 0, Size(8,8), Size(32,32), 1.05, 1);

    size_t j, i ;
    for (i = 0; i < f.size(); i++) {
        Rect ret = f[i];
        for ( j = 0; i < f.size(); i++) {
            if (j != i && (ret & f[j])==ret) {
                break;
           }

        }
        if (j == f.size()) {

              cout << "Test 12"<< endl;
              filtered.push_back(ret);
        }
    }
    for (int i = 0; i < filtered.size(); i++) {

         Rect r = filtered[i];
            r.x += cvRound(r.width*0.1);
		    r.width = cvRound(r.width*0.8);
		    r.y += cvRound(r.height*0.07);
		    r.height = cvRound(r.height*0.8);
            cout << "test \n" <<endl;
		    rectangle(frame, r.tl(), r.br(), Scalar(0,0,255), 3);
    }*/
   imshow("Frame",frame); 
        key = cvWaitKey(10);
        if(char(key) == 27)
        {
            break;
        }

    }
    return 0; 
}

void Motion::Detection()
{
    Mat frame;
    Mat back;
    Mat fore;
        VideoCapture c(1);

    BackgroundSubtractorMOG2 bg;
    bg.set("nmixtures",3);
    char key;
    bg.setBool("detectShadows",false);
// HOGDescriptor h;
    vector<std::vector <Point> > contours;
//    h.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
   namedWindow("Frame", 1);
   namedWindow("Fore",1);
   namedWindow("Back",1);
    while(true)
    {
          /* code */
       c >> frame;
       Mat ee = getStructuringElement(MORPH_RECT, Size(3,3));
       Mat de = getStructuringElement(MORPH_RECT, Size(8,8));

       bg.operator ()(frame,fore);
       
       bg.getBackgroundImage(back);
        erode(fore,fore,ee);
        erode(fore,fore,ee);
        dilate(fore,fore,de);
        dilate(fore,fore,de);
        findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
       vector<Rect> r (contours.size());
       drawContours(frame,contours,-1,cv::Scalar(0,255,0),2);
       imshow("Frame",frame);
        imshow("Fore",fore);
         imshow("Back",back);
    //    Tracking(h,frame);
    /*double t = (double)getTickCount();
    vector<Rect> f, filtered;
    h.detectMultiScale(frame, f, 0, Size(8,8), Size(32,32), 1.05, 1);

    size_t j, i ;
    for (i = 0; i < f.size(); i++) {
        Rect ret = f[i];
        for ( j = 0; i < f.size(); i++) {
            if (j != i && (ret & f[j])==ret) {
                break;
           }

        }
        if (j == f.size()) {

              cout << "Test 12"<< endl;
              filtered.push_back(ret);
        }
    }
    for (int i = 0; i < filtered.size(); i++) {

         Rect r = filtered[i];
            r.x += cvRound(r.width*0.1);
		    r.width = cvRound(r.width*0.8);
		    r.y += cvRound(r.height*0.07);
		    r.height = cvRound(r.height*0.8);
            cout << "test \n" <<endl;
		    rectangle(frame, r.tl(), r.br(), Scalar(0,0,255), 3);
    }*/
   imshow("Frame",frame); 
        key = cvWaitKey(10);
        if(char(key) == 27)
        {
            break;
        }

    }
}

bool Motion::isHuman()
{
    return false;
}

bool Motion::isCar()
{
    return false;
}

