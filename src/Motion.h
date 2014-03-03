
#include <cv.h>
#include <highgui.h>

#include<opencv2/opencv.hpp>
using namespace cv;
class Motion{

  public:
      Motion();
      Motion(char *path);
      int Tracking(char *p);
      void Detection();
      ~Motion();
      int Init(char *p); 
      CvCapture * cap;
      Mat frame;
      char *p;
      IplImage * track; 
  private:
      bool isHuman();
      bool isCar();
};
