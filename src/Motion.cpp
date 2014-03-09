#include "Motion.h"
#include "cv.h"
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
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
    int count = 0;
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

       Mat ee2 = getStructuringElement(MORPH_RECT, Size(1,1));
       Mat de2 = getStructuringElement(MORPH_RECT, Size(5,5));
       bg.operator ()(frame,fore);
     if (count==0)
      { 
       bg.getBackgroundImage(back);
      }
        erode(fore,fore,ee);
        erode(fore,fore,ee);
        erode(fore,fore,ee2);
        dilate(fore,fore,de);
        dilate(fore,fore,de);
       findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
       
       vector<vector<Point> > poly(contours.size());
       vector<Rect> ret (contours.size());
       
       for(int i =0; i < contours.size();i++)
       {
           approxPolyDP(Mat(contours[i]),poly[i], 3, true );
           ret[i] = boundingRect(Mat(poly[i]));

       }

       for(int i = 0; i <contours.size(); i++)
       {
       // drawContours(frame,poly,i ,cv::Scalar(0,255,0),1,8,vector<Vec4i>(),0,Point());
        rectangle(frame, ret[i].tl(), ret[i].br(), cv::Scalar(0,255,0), 2, 8,0);
       }
       imshow("Frame",frame);
        imshow("Fore",fore);
         imshow("Back",back);
         count = 1;
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
    vector<vector <Point> > contours;
    vector<Vec4i> hier;
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
//       vector<Rect> r (contours.size()); 
//       vector<vector<Point> > contours_poly (contours.size());
//       vector<Point2f>center(contours.size());
//       vector<float> rad(contours.size());
       for(int i = 0; i < contours.size();i++)
       {
           //approxPolyDP(Mat(contours[i]),poly[i], 3.0,true);
       //     approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
//           r[i] = boundingRect(Mat(contours_poly[i]));
       }
       for(int i = 0; i < contours.size(); i++)
       {
            //drawContours(frame,contours,-1,cv::Scalar(0,255,0),2);
       //rectangle( frame, r[i].tl(),r[i].br(), cv::Scalar(0,255,0), 2, 8, 0 );


       }
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

