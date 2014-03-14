#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "Motion.h"
using namespace std;
using namespace cv;
int main(int argc, char** arg)
{
    Motion* m = new Motion(arg[1]);
   // Motion* m = new Motion("./mv2_004/mv2_004.avi");
    m->Init(arg[1]); 
   // m->Init("./mv2_004/mv2_004.avi");  
    return 0;
}
