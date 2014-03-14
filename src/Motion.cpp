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
        Detection(path);
    }
    else
    {
        Tracking();
    }
    return 0;
}

int Motion::Detection(char *path)
{

    Mat frame;
    Mat back;
    Mat fore;
    Mat tracking, img, prev;
    //VideoCapture("./mv2_004/mv2_004.avi");
    VideoCapture c(path);
    Point2f pt;
    double width, height;
    TermCriteria term(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03);
    vector<Point2f> points[2];
    bool init = true; 
     if (!c.isOpened()) {
         cout << "Cannot open file" << endl;
         return -1;
     }
    BackgroundSubtractorMOG2 bg;
    bg.set("nmixtures",3);
    char key;
    int count = 0;
    bg.set("detectShadows",0);
    vector<std::vector <Point> > contours;
   namedWindow("Frame", 1);
   namedWindow("Fore",1);
   namedWindow("Back",1);
    width = c.get(CV_CAP_PROP_FRAME_WIDTH);
    height = c.get(CV_CAP_PROP_FRAME_HEIGHT);
    VideoWriter v1("track_and_detect.avi", CV_FOURCC('P','I','M','1'),20  ,Size((int)width,(int)height), true);
    VideoWriter v2("test_fore.avi", CV_FOURCC('M','J','P','G'),20  ,Size((int)width,(int)height), true);
    VideoWriter v3("track_optical_flow.avi", CV_FOURCC('P','I','M','1'),20  ,Size((int)width,(int)height), true);
    if(!v1.isOpened())
    {
         cout << "Cannot open1 file" << endl;
         return -1;
    }
    if(!v2.isOpened())
    {
         cout << "Cannot open2 file" << endl;
         return -1;
    }
    if(!v3.isOpened())
    {
         cout << "Cannot open3 file" << endl;
         return -1;
    }
    while(true)
    {
          /* code */
        bool isRun = c.read(frame);
        if(!isRun)
        {
            cout << "Reading is broken"<<endl;
            break;
        }
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
      Tracking(); 
       vector<vector<Point> > poly(contours.size());
       vector<Rect> ret (contours.size());
       
       for(int i =0; i < contours.size();i++)
       {
           approxPolyDP(Mat(contours[i]),poly[i], 3, true );
           ret[i] = boundingRect(Mat(poly[i]));

       }

       for(int i = 0; i <contours.size(); i++)
       {
        rectangle(frame, ret[i].tl(), ret[i].br(), cv::Scalar(0,255,0), 2, 8,0);
       }
       frame.copyTo(tracking);
       cvtColor(tracking,img, COLOR_BGR2GRAY);
       if(init)
       {
           goodFeaturesToTrack(img,points[1],500,0.01,10,Mat(),3,0,0.04);
           cornerSubPix(img,points[1],Size(10,10), Size(-1,1), term);

       }
       else if(!points[0].empty())
       {
                   vector<uchar> status;
                   vector<float> err;
                   if (prev.empty()) {
                        img.copyTo(prev);
                   }
                   calcOpticalFlowPyrLK(prev,img,points[0],points[1],status,err,
                           Size(10,10),3,term,0,0.001);
                   size_t i,k;
                   for (i=k = 0; i < points[1].size(); i++) {
                       /* code */
                        if(!status[i])
                            continue;
                        points[1][k++] = points[1][i];
                        circle(tracking,points[1][i],3, Scalar(255,0,0),-1,8);
                        
                   }
                   points[1].resize(k);

           }
       //init = false;


      imshow("Frame",frame);
      imshow("Fore",fore);
      imshow("Back",tracking);
         count = 1;
        key = cvWaitKey(10);
        if(char(key) == 27)
        {
            break;
        }
        switch(key)
        {
            case 'r':
                init= true;
                break;
            case 'c':
                points[0].clear();
                points[1].clear();
                break;
            case'e':
                init = false;
                break;
        } 
        std::swap(points[1],points[0]);
        cv::swap(prev,img);

         v1.write(frame);
         v2.write(fore);
         v3.write(tracking);
    }
    return 0; 
}

void Motion::Tracking()
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

