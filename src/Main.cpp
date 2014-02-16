#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "Motion.h"
using namespace std;
using namespace cv;
int main()
{
    Motion* m = new Motion();
    m->Init();    
    return 0;
}
