
#include <cv.h>
#include <highgui.h>

class Motion{

  public:
      Motion();
      void Tracking();
      void Detection();
      ~Motion();
      void Init(); 
      CvCapture * cap; 
  private:
      bool isHuman();
      bool isCar();

};
