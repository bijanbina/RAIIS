#ifndef TRMMARK_H
#define TRMMARK_H

#include <QtWidgets>
#include <cv.h>
#include <highgui.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <string.h>
#include "Track.h"

#define PI 3.14159265
#define calib_prev_size 800.0
#define MARK_EDGE_LENGHT 3.8
#define MAHYAR_MARK_LENGHT 20
#define MAHYAR_DIST_X 20
#define MAHYAR_DIST_Y 20

#define SETTING_FILENAME "settings.json"

#define MORPH_STATE_NORMALL     0
#define MORPH_STATE_REVERSED    1
#define MORPH_STATE_OPEN        2
#define MORPH_STATE_CLOSE       3


#define TRM_ONLY_BIJAN 0
#define TRM_ONLY_MAHYAR 1
#define TRM_AUTO_SWITCH 2

#define TRM_AUTO_SIZE   4
#define TRM_AUTO_BOLD   { 0 , 1 , 2 , 1 }
#define TRM_AUTO_NARROW { 0 , 0 , 0 , 1 }

struct trm_param
{
    double edge_1;
    double edge_2;
    int erode;
    int dilate;
    int bold;
    int narrow;
    bool edge_corner;
    int corner_min;
    int frame_num;
    bool isVideo;
    int calibre_width;
    int morph_algorithm;
    int maximum_error;
    int deviceID;
	int cutOff;
    int algorithm; // bijan || mahyar || auto
    QString filename;

    //Mahyar
    int window; //input from user
    int circle_diameter; // input from user
    double pixel2cm; // input from user
    cv::Scalar color[2]; // input from user

};

typedef trm_param trmParam;

class trmMark
{
public:
    trmMark();
	double findAngle();
    double findDerivative(CvPoint pt1, CvPoint pt2, CvPoint pt3, CvPoint pt4, bool reverse = false);
    CvPoint *getRect(); //return rectangle which contain plus
    CvRect   getRegion(); //return rectangle which contain plus
    static void bold_filter(IplImage *in,int kernel_size);
    static void narrowFilter(IplImage *in,int kernel_size);
    static IplImage* doCanny(IplImage* in, double lowThresh, double highThresh);
    double dist_cv(CvPoint pt1, CvPoint pt2);

    static QString QStr_create(std::string buffer);
    static trmParam Loadparam(char *filename);
    static void Saveparam(trmParam data, char *filename);

    CvPoint top1;
    CvPoint top2;
    CvPoint down1;
    CvPoint down2;
    CvPoint left1;
    CvPoint left2;
    CvPoint right1;
    CvPoint right2;
    CvPoint center1;
    CvPoint center2;
    CvPoint center3;
    CvPoint center4;
    CvPoint middle;

    CvPoint *rect;
    CvRect   region;
    double   edge; //mean value of marks side
	double   inside_edge;
    double   pr;//previeos angle
    double   error;//RMS Error

};
trmMark *markFromImage(IplImage *imagesrc, trmParam data, bool *isAuto);
trmMark *markFromMahyar (IplImage* image, trm_param pars);
trmMark *create_from_point(CvSeq *points,double previous);
trmMark *create_from_seq(CvSeq *head, double cornerMin, double treshold = -1 );

#endif // TRMMARK_H
