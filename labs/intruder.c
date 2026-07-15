#include <opencv/cv.h>
#include <opencv2/core/core_c.h>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/tracking.hpp>
#include <stdio.h>
#include <time.h>

void delay(int seconds) {
  clock_t start_time = clock();

  while (clock() < start_time + seconds * CLOCKS_PER_SEC)
    ;
}

int main() {
  delay(5);
  puts("Started");
  CvCapture *webcam = cvCreateCameraCapture(0);
  if (!webcam) {
    puts("Could not create camera");
    return 0;
  }

  IplImage *prevImage = NULL;
  while (1) {
    IplImage *image = cvQueryFrame(webcam);
    IplImage *gray_image = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
    cvCvtColor(image, gray_image, CV_BGR2GRAY);
    if (image) {
      if (prevImage) {
        IplImage *flow = cvCreateImage(cvGetSize(prevImage), IPL_DEPTH_32F, 2);
        cvCalcOpticalFlowFarneback(prevImage, gray_image, flow, 0.5, 5, 13, 10,
                                   5, 1.1, 0);
        double total_x_movement = 0;
        double total_y_movement = 0;
        for (int y = 0; y < flow->height; y++) {
          float *diff_row = (float *)(flow->imageData + y * flow->widthStep);
          for (int x = 0; x < flow->width; x++) {
            total_x_movement += diff_row[x * 2];
            total_y_movement += diff_row[x * 2 + 1];
          }
        }
        if (fabs(total_x_movement) > 30000 || fabs(total_y_movement) > 30000) {
          puts("Intruder detected");
          cvSaveImage("intruder.jpg", image, 0);
          return 0;
        }
      }

      prevImage = gray_image;
    }
  }
  cvReleaseImage(&prevImage);
  return 0;
}
