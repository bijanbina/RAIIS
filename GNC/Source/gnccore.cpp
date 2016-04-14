#include "trmmark.h"

trmMark *create_from_point(CvSeq *points,double previous)
{
    trmMark *obj = new trmMark;
    int ID = 0;
    obj->middle.x = 0;
    obj->middle.y = 0;
    obj->center1.x = 9999;
    obj->center1.y = 9999;
    obj->center2.x = 9999;
    obj->center2.y = 9999;
    obj->center3.x = 9999;
    obj->center3.y = 9999;
    obj->center4.x = 9999;
    obj->center4.y = 9999;
	
    //find centers
    for( int i=0; i < points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        obj->middle.x += p->x;
        obj->middle.y +=+ p->y;
    }
    obj->middle.x /= points->total;
    obj->middle.y /= points->total;
    for( int i=0; i < 4; i++ )
    {
        ID = 0;
        CvPoint *temp = (CvPoint*)cvGetSeqElem ( points, 0 );
        CvPoint *p;
        for( int j=1; j < points->total; j++ )
        {
            p = (CvPoint*)cvGetSeqElem ( points, j );
            if ( obj->dist_cv(obj->middle,*p) < obj->dist_cv(obj->middle,*temp) )
            {
                temp = p;
                ID = j;
            }
        }
        if ( temp->y <= obj->middle.y )
        {
            if (obj->center1.x == 9999)
            {
                obj->center1 = *temp;
            }
            else if (obj->center2.x == 9999)
            {
                obj->center2 = *temp;
            }
            else
            {
                obj->center3 = *temp;
            }
        }
        else
        {
            if (obj->center3.x == 9999)
            {
                obj->center3 = *temp;
            }
            else
            {
                obj->center4 = *temp;
            }
        }
        cvSeqRemove(points,ID);
    }

    if (obj->center1.x > obj->center2.x)
    {
        CvPoint temp = obj->center2;
        obj->center2 = obj->center1;
        obj->center1 = temp;
    }
    if (obj->center3.x < obj->center4.x)
    {
        CvPoint temp = obj->center3;
        obj->center3 = obj->center4;
        obj->center4 = temp;
    }

    obj->top1 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if ((p->y) < (obj->top1.y))
        {
            obj->top1 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);
    obj->top2 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if (obj->dist_cv(obj->top1,*p) < obj->dist_cv(obj->top1,obj->top2))
        {
            obj->top2 =  *p;
            ID = i;
        }
    }

    if (obj->top1.x > obj->top2.x)
    {
        CvPoint temp = obj->top2;
        obj->top2 = obj->top1;
        obj->top1 = temp;
    }

    cvSeqRemove(points,ID);

    obj->left1 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if ((p->x) < (obj->left1.x))
        {
            obj->left1 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);
    obj->left2 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if (obj->dist_cv(obj->left1,*p) < obj->dist_cv(obj->left1,obj->left2))
        {
            obj->left2 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);

    if (obj->left1.y > obj->left2.y)
    {
        CvPoint temp = obj->left2;
        obj->left2 = obj->left1;
        obj->left1 = temp;
    }

    obj->down1 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if ((p->y) > (obj->down1.y))
        {
            obj->down1 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);
    obj->down2 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if (obj->dist_cv(obj->down1,*p) < obj->dist_cv(obj->down1,obj->down2))
        {
            obj->down2 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);

    if (obj->down1.x > obj->down2.x)
    {
        CvPoint temp = obj->down2;
        obj->down2 = obj->down1;
        obj->down1 = temp;
    }

    obj->right1 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    obj->right2 = *(CvPoint*)cvGetSeqElem ( points, 1 );

    if (obj->right1.y > obj->right2.y)
    {
        CvPoint temp = obj->right2;
        obj->right2 = obj->right1;
        obj->right1 = temp;
    }

    obj->pr = previous;
    obj->rect = (CvPoint *)malloc( 4 * sizeof (CvPoint));
    obj->edge = (obj->dist_cv(obj->top2,obj->center2) + obj->dist_cv(obj->right1,obj->center2) + obj->dist_cv(obj->right2,obj->center3) +
                 obj->dist_cv(obj->down2,obj->center3) + obj->dist_cv(obj->down1,obj->center4) + obj->dist_cv(obj->left2,obj->center4)
                 + obj->dist_cv(obj->left1,obj->center1)) / 7.0;

    obj->inside_edge = ( obj->dist_cv(obj->center1,obj->center2) + obj->dist_cv(obj->center3,obj->center2) + obj->dist_cv(obj->center4,obj->center3) +
                 obj->dist_cv(obj->center1,obj->center4) ) / 4.0;

    obj->rect[0] = cvPoint(0,0);
    obj->rect[1] = cvPoint(0,0);
    obj->rect[2] = cvPoint(0,0);
    obj->rect[3] = cvPoint(0,0);

    if ( obj->center1.x == 9999 || obj->center1.y == 9999 || obj->center2.x == 9999 || obj->center2.y == 9999 ||
         obj->center3.x == 9999 || obj->center3.y == 9999 || obj->center4.x == 9999 || obj->center4.y == 9999)
    {
        return NULL;
    }

    //calculate RMS Error
    obj->error += cv::pow( obj->inside_edge - obj->dist_cv(obj->center1,obj->center4), 2 );
    obj->error += cv::pow( obj->inside_edge - obj->dist_cv(obj->center1,obj->center2), 2 );
    obj->error += cv::pow( obj->inside_edge - obj->dist_cv(obj->center3,obj->center2), 2 );
    obj->error += cv::pow( obj->inside_edge - obj->dist_cv(obj->center3,obj->center4), 2 );
    obj->error += cv::pow( obj->edge - obj->dist_cv(obj->top2,obj->center2), 2 );
    obj->error += cv::pow( obj->edge - obj->dist_cv(obj->right1,obj->center2), 2 );
    obj->error += cv::pow( obj->edge - obj->dist_cv(obj->right2,obj->center3), 2 );
    obj->error += cv::pow( obj->edge - obj->dist_cv(obj->down2,obj->center3), 2 );
    obj->error += cv::pow( obj->edge - obj->dist_cv(obj->down1,obj->center4), 2 );
    obj->error += cv::pow( obj->edge - obj->dist_cv(obj->left2,obj->center4), 2 );
    obj->error += cv::pow( obj->edge - obj->dist_cv(obj->left1,obj->center1), 2 );
    obj->error = obj->error / 11.0;
    obj->error = cv::sqrt(obj->error);

    return obj;
}


trmMark *create_from_seq(CvSeq *head,double cornerMin,double treshold)
{
    double minErorr = 9999;

    CvSeq *dummy = head;
    CvSeq *poly;

    trmMark *temp,*result = NULL;

    CvMemStorage* strg = cvCreateMemStorage();

    while( dummy != NULL )
    {
        poly = cvApproxPoly(dummy,sizeof(CvContour),strg, CV_POLY_APPROX_DP,cornerMin);
        if (poly->total == 12)
        {
            temp = create_from_point(poly,0);
            if (temp != NULL)
            {
                if ( temp->error < minErorr )
                {
                    minErorr = temp->error;
                    if (result != NULL)
                        delete result;
                    result = temp;
                }
                else
                    delete temp;
            }
        }
        dummy = dummy->h_next;
    }
    cvClearMemStorage(strg);
    cvReleaseMemStorage(&strg);

    if (result != NULL)
    {
        if ( treshold > 0 && treshold < result->error)
            return NULL;
    }

    return result;
}

trmMark::trmMark()
{

}

double trmMark::findAngle()
{
    double gradiant1 = findDerivative(top1,down1,center1,center4,true);
    gradiant1 += findDerivative(left1,right1,center1,center2);
    gradiant1 += findDerivative(left2,right2,center3,center4);
    gradiant1 += findDerivative(top2,down2,center2,center3,true);
    gradiant1 /= 4.0;
//    std::cout << findDerivative(top1,down1,center1,center4,true) << " \t " << findDerivative(left1,right1,center1,center2) <<
//                 " \t "<< findDerivative(left2,right2,center3,center4) << " \t " << findDerivative(top2,down2,center2,center3,true) << std::endl;

    return (90 + (atan(gradiant1) * 180 / PI));
}


double trmMark::dist_cv(CvPoint pt1, CvPoint pt2)
{
    return cv::sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x)  + (pt1.y - pt2.y) *  (pt1.y - pt2.y));
}

CvPoint* trmMark::getRect()
{
    double angle = findAngle();

    double m = tan((angle + 45)/180.0 * PI);
    rect[0] = center1;
    double b = -rect[0].y - m*rect[0].x;
    double d = b + rect[0].y;
    double b1 = rect[0].x - m * d;
    double a1 = (m * m + 1);
    double c1 = ( rect[0].x * rect[0].x  + d * d - 3 * edge * edge);
    double x = (b1 - cv::sqrt(b1 * b1 - a1 * c1 ))/ a1;
    rect[0].x = x;rect[0].y = - (m * x + b);

    m = tan((angle - 45)/180.0 * PI);
    rect[1] = center2;
    b = -rect[1].y - m*rect[1].x;
    d = b + rect[1].y;
    b1 = rect[1].x - m * d;
    a1 = (m * m + 1);
    c1 = ( rect[1].x * rect[1].x  + d * d - 3 * edge * edge);
    x = (b1 + cv::sqrt(b1 * b1 - a1 * c1 ))/ a1;
    rect[1].x = x;rect[1].y = - (m * x + b);


    m = tan((angle + 45)/180.0 * PI);
    rect[2] = center3;
    b = -rect[2].y - m*rect[2].x;
    d = b + rect[2].y;
    b1 = rect[2].x - m * d;
    a1 = (m * m + 1);
    c1 = ( rect[2].x * rect[2].x  + d * d - 3 * edge * edge);
    x = (b1 + cv::sqrt(b1 * b1 - a1 * c1 ))/ a1;
    rect[2].x = x;rect[2].y = - (m * x + b);

    m = tan((angle - 45)/180.0 * PI);
    rect[3] = center4;
    b = -rect[3].y - m*rect[3].x;
    d = b + rect[3].y;
    b1 = rect[3].x - m * d;
    a1 = (m * m + 1);
    c1 = ( rect[3].x * rect[3].x  + d * d - 3 * edge * edge);
    x = (b1 - cv::sqrt(b1 * b1 - a1 * c1 ))/ a1;
    rect[3].x = x;rect[3].y = - (m * x + b);

    return rect;
}


CvRect trmMark::trmMark::getRegion()
{
    getRect();
    CvRect return_data = cvRect(rect[0].x,rect[0].y,rect[0].x,rect[0].y);
    for( int i = 1; i < 4; i++ )
    {
        if ( rect[i].x < return_data.x )
            return_data.x = rect[i].x;
        if ( rect[i].y < return_data.y)
            return_data.y = rect[i].y;
        if ( rect[i].x > return_data.width )
            return_data.width = rect[i].x;
        if ( rect[i].y > return_data.height)
            return_data.height = rect[i].y;
    }

    return_data.width = return_data.width - return_data.x;
    return_data.height = return_data.height - return_data.y;

    return return_data;

}

double trmMark::findDerivative(CvPoint pt1, CvPoint pt2, CvPoint pt3, CvPoint pt4,bool reverse)
{
    long a1 = 4;
    long a2 = pt1.x + pt2.x + pt3.x + pt4.x;
    long b1 = a2;
    long b2 = pt1.x * pt1.x + pt2.x * pt2.x + pt3.x * pt3.x + pt4.x * pt4.x;
    long c1 = -(pt1.y + pt2.y + pt3.y + pt4.y);
    long c2 = -(pt1.x * pt1.y + pt2.x * pt2.y + pt3.x * pt3.y + pt4.x * pt4.y);

    if (reverse)
    {
        a1 = 4;
        a2 = -(pt1.y + pt2.y + pt3.y + pt4.y);
        b1 = a2;
        b2 = pt1.y * pt1.y + pt2.y * pt2.y + pt3.y * pt3.y + pt4.y * pt4.y;
        c1 = -(pt1.x + pt2.x + pt3.x + pt4.x);
        c2 = (pt1.x * pt1.y + pt2.x * pt2.y + pt3.x * pt3.y + pt4.x * pt4.y);
    }

    double mat_1 = (a1 * c2 - a2 * c1);
    double mat_2 = (a1 * b2 - a2 * b1);

    double slope = mat_1 / mat_2;

    return slope;
}

QString trmMark::QStr_create(std::string buffer)
{
    QString return_data;
    int len = strlen(buffer.c_str());
    char *buffer2 = (char *)malloc(len + 1);
    strncpy(buffer2, buffer.c_str(), len);
    buffer2[len] = '\0';   /* null character manually added */
    return_data = buffer2;
    free(buffer2);
    return return_data;
}

trmParam trmMark::Loadparam(char *filename)
{
    trmParam return_data;
    QFile json_file(filename);
    if(json_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Json::Value json_obj;
        Json::Reader reader;
        if (reader.parse(QString(json_file.readAll()).toUtf8().data(), json_obj))
        {
            return_data.bold = json_obj.get("Bold",2).asInt();
            return_data.erode = json_obj.get("Erode",2).asInt();
            return_data.dilate = json_obj.get("Dilate",2).asInt();
            return_data.narrow = json_obj.get("Narrow",0).asInt();
            return_data.maximum_error = json_obj.get("Maximum RMS Error",5).asInt();
            return_data.edge_corner = json_obj.get("Do canny after bold",true).asBool();
            return_data.calibre_width = json_obj.get("Calibre Image Width",calib_prev_size).asInt();
            return_data.morph_algorithm = json_obj.get("Morphology Algorithm",MORPH_STATE_NORMALL).asInt();
            return_data.cutOff = json_obj.get("ROI CutOff",3).asInt();
            return_data.frame_num = json_obj.get("Start Frame Number",0).asInt();
            return_data.isVideo = json_obj.get("Is Video",true).asBool();
            return_data.deviceID = json_obj.get("Device ID",-1).asInt();
            return_data.window = json_obj.get("Window",-1).asInt();
            return_data.filename = QStr_create(json_obj.get("File Address","../Resources/Sample.mp4").asString());
            return_data.algorithm = json_obj.get("Algorithm",TRM_AUTO_SWITCH).asInt();

            const Json::Value HSV1 = json_obj["Color1"];
            if (!HSV1.empty())
            {
                return_data.color[0] = cv::Scalar(HSV1.get("Hue",100).asInt(),
                                               HSV1.get("Saturation",100).asInt(),
                                               HSV1.get("Value",100).asInt());
            }

            const Json::Value HSV2 = json_obj["Color2"];
            if (!HSV2.empty())
            {
                return_data.color[1] = cv::Scalar(HSV2.get("Hue",100).asInt(),
                                               HSV2.get("Saturation",100).asInt(),
                                               HSV2.get("Value",100).asInt());
            }

            const Json::Value edge = json_obj["Edge Detection"];
            if (!edge.empty())
            {
                return_data.edge_1 = edge.get("Treshold 1",214).asDouble();
                return_data.edge_2 = edge.get("Treshold 2",71).asDouble();
            }
            return_data.corner_min = json_obj.get("Corner Minimum Distance",25).asInt();
        }

    }
    else
    {
        return_data.bold = 2;
        return_data.narrow = 0;
        return_data.erode = 2;
        return_data.dilate = 2;
        return_data.edge_1 = 214;
        return_data.edge_2 = 71;
        return_data.corner_min = 25;
        return_data.filename = "../Resources/Sample.mp4";
        return_data.isVideo = true;
        return_data.edge_corner = true;
        return_data.frame_num = 0;
        return_data.deviceID = -1;
        return_data.calibre_width = calib_prev_size;
        return_data.morph_algorithm = MORPH_STATE_NORMALL;
        return_data.algorithm = TRM_AUTO_SWITCH;

    }
    return return_data;
}

void trmMark::Saveparam(trmParam data,char *filename)
{
    Json::Value json_main;
    Json::Value edge;
    Json::Value HSV1;
    Json::Value HSV2;
    edge["Treshold 1"] = data.edge_1;
    edge["Treshold 2"] = data.edge_2;
    HSV1["Hue"] = data.color[0][0];
    HSV1["Saturation"] = data.color[0][1];
    HSV1["Value"] = data.color[0][2];
    HSV2["Hue"] = data.color[1][0];
    HSV2["Saturation"] = data.color[1][1];
    HSV2["Value"] = data.color[1][2];
    json_main["Erode"] = data.erode;
    json_main["Dilate"] = data.dilate;
    json_main["Bold"] = data.bold;
    json_main["Narrow"] = data.narrow;
    json_main["Do canny after bold"] = data.edge_corner;
    json_main["Bold"] = data.bold;
    json_main["Corner Minimum Distance"] = data.corner_min;
    json_main["File Address"] = data.filename.toUtf8().data();
    json_main["Start Frame Number"] = data.frame_num;
    json_main["Edge Detection"] = edge;
    json_main["Color1"] = HSV1;
    json_main["Color2"] = HSV2;
    json_main["Is Video"] = data.isVideo;
    json_main["Device ID"] = data.deviceID;
    json_main["Calibre Image Width"] = data.calibre_width;
    json_main["Morphology Algorithm"] = data.morph_algorithm;
    json_main["Maximum RMS Error"] = data.maximum_error;
    json_main["Window"] = data.window;
    json_main["ROI CutOff"] = data.cutOff;
    json_main["Algorithm"] = data.algorithm;

    // write in a nice readible way
    Json::StyledWriter styledWriter;
    std::string str = styledWriter.write(json_main);
    std::vector<char> json_data(str.begin(), str.end());
    json_data.push_back('\0');
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(json_data.data());
    file.close();
}

//imagesrc: rgb image
trmMark *markFromImage(IplImage *imagesrc,trmParam filterParam,bool *isAuto)
{
    IplImage *imgclone = cvCreateImage( cvGetSize(imagesrc), 8, 1 );
    cvCvtColor( imagesrc, imgclone, CV_BGR2GRAY );
    if (filterParam.erode)
        cvErode( imgclone, imgclone , NULL , filterParam.erode );
    if (filterParam.dilate)
        cvDilate( imgclone, imgclone , NULL , filterParam.dilate );
    imgclone = trmMark::doCanny( imgclone, filterParam.edge_1 ,filterParam.edge_2 );

    IplImage *autoimg = cvCloneImage(imgclone); //used for automode

    if (filterParam.bold)
        trmMark::bold_filter(imgclone,filterParam.bold);
    if (filterParam.narrow)
        trmMark::narrowFilter(imgclone,filterParam.narrow);
    if (filterParam.edge_corner)
    {
        imgclone = trmMark::doCanny( imgclone, filterParam.edge_corner ,filterParam.edge_corner * 3);
    }

//    cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
//    cvShowImage( "Example1", imgclone );
//    cvWaitKey(0);
//    cvDestroyWindow( "Example1" );

    CvSeq* firstContour = NULL;
    CvMemStorage* cnt_storage = cvCreateMemStorage();
    cvFindContours(imgclone,cnt_storage,&firstContour,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
    cvReleaseImage( &imgclone );

    trmMark *plus_mark = create_from_seq(firstContour,filterParam.corner_min,filterParam.maximum_error);

    int auto_bold  [TRM_AUTO_SIZE] = TRM_AUTO_BOLD;
    int auto_narrow[TRM_AUTO_SIZE] = TRM_AUTO_NARROW;

    if (isAuto != NULL)
        (*isAuto) = false;
    if (plus_mark == NULL )
    {
        cvClearMemStorage(cnt_storage);

        if (isAuto != NULL)
            (*isAuto) = true;
        for (int i = 0 ; i < TRM_AUTO_SIZE ; i++)
        {
            IplImage *tempimg = cvCloneImage(autoimg); //used for automode
            if (auto_bold[i])
                trmMark::bold_filter(tempimg,auto_bold[i]);
            if (auto_narrow[i])
                trmMark::narrowFilter(tempimg,auto_narrow[i]);
            cvFindContours(tempimg,cnt_storage,&firstContour,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
            plus_mark = create_from_seq(firstContour,filterParam.corner_min , filterParam.maximum_error);
            if ( plus_mark != NULL )
			{
            	cvReleaseImage(&tempimg);
                break;
			}
            tempimg = trmMark::doCanny( tempimg, filterParam.edge_corner ,filterParam.edge_corner * 3 );//Do canny after bold filter
            cvFindContours(tempimg,cnt_storage,&firstContour,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
            plus_mark = create_from_seq(firstContour,filterParam.corner_min , filterParam.maximum_error);
            cvReleaseImage(&tempimg);
            if ( plus_mark != NULL )
                break;
        }
    }
    //Second try for auto setting
    if (plus_mark == NULL )
    {
        cvClearMemStorage(cnt_storage);

        cvReleaseImage( &autoimg );
        autoimg = cvCreateImage( cvGetSize(imagesrc), 8, 1 );
        cvCvtColor( imagesrc, autoimg, CV_BGR2GRAY );
        cvErode( autoimg, autoimg , NULL , 25 );
        cvDilate( autoimg, autoimg , NULL , 25 );
        autoimg = trmMark::doCanny( autoimg, filterParam.edge_1 ,filterParam.edge_2 );

        if (isAuto != NULL)
            (*isAuto) = true;
        for (int i = 0 ; i < TRM_AUTO_SIZE ; i++)
        {
            IplImage *tempimg = cvCloneImage(autoimg); //used for automode
            if (auto_bold[i])
                trmMark::bold_filter(tempimg,auto_bold[i]);
            if (auto_narrow[i])
                trmMark::narrowFilter(tempimg,auto_narrow[i]);
            cvFindContours(tempimg,cnt_storage,&firstContour,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
            plus_mark = create_from_seq(firstContour,filterParam.corner_min , filterParam.maximum_error);
            if ( plus_mark != NULL )
			{
            	cvReleaseImage(&tempimg);
                break;
			}
            tempimg = trmMark::doCanny( tempimg, filterParam.edge_corner ,filterParam.edge_corner * 3 );//Do canny after bold filter
            cvFindContours(tempimg,cnt_storage,&firstContour,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
            plus_mark = create_from_seq(firstContour,filterParam.corner_min , filterParam.maximum_error);
            cvReleaseImage(&tempimg);
            if ( plus_mark != NULL )
                break;
        }
		cvReleaseImage( &autoimg );
    }

    cvClearMemStorage(cnt_storage);
    cvReleaseMemStorage(&cnt_storage);
    
	cvReleaseImage( &autoimg );
    return plus_mark;
}

//Note:this function release in
IplImage* trmMark::doCanny( IplImage* in, double lowThresh, double highThresh )
{
    if(in->nChannels != 1)
    {
        printf("Not supported\n");
        exit(0); //Canny only handles gray scale images
    }
    IplImage *out = cvCreateImage( cvGetSize( in ) , IPL_DEPTH_8U, 1 );
    cvCanny( in, out, lowThresh, highThresh, 3 );
    cvReleaseImage( &in );
    return( out );
}

void trmMark::bold_filter(IplImage *in,int kernel_size)
{
    cv::Mat grayFrame = cv::Mat(in);
    unsigned char imgdata[grayFrame.cols][grayFrame.rows];
    for (int y = 0 ; y < grayFrame.rows ; y++)
    {
        const unsigned char* ptr = (unsigned char*)(grayFrame.data + y * grayFrame.step);
        for (int x = 0 ; x < grayFrame.cols ; x++ )
        {
            imgdata[x][y] = *ptr;
            ptr++;
        }
    }
    for (int x = 0 ; x < grayFrame.cols - kernel_size ; x++)
    {
        for (int y = 0 ; y < grayFrame.rows - kernel_size ; y++ )
        {
            if (imgdata[x+kernel_size/2][y+kernel_size/2] == 255 )
            {
                cvRectangle(in,cvPoint(x,y),cvPoint(x+kernel_size,y+kernel_size),cvScalarAll(255));
                //cvCircle(in,cvPoint(x,y),kernel_size,cvScalarAll(255),kernel_size/2+1);

            }
        }
    }
}

void trmMark::narrowFilter(IplImage *in,int kernel_size)
{
    cv::Mat grayFrame = cv::Mat(in);
    unsigned char imgdata[grayFrame.cols][grayFrame.rows];
    for (int y = 0 ; y < grayFrame.rows ; y++)
    {
        const unsigned char* ptr = (unsigned char*)(grayFrame.data + y * grayFrame.step);
        for (int x = 0 ; x < grayFrame.cols ; x++ )
        {
            imgdata[x][y] = *ptr;
            ptr++;
        }
    }
    for (int x = 0 ; x < grayFrame.cols - kernel_size ; x++)
    {
        for (int y = 0 ; y < grayFrame.rows - kernel_size ; y++ )
        {
            if (imgdata[x+kernel_size/2][y+kernel_size/2] == 0 )
            {
                cvRectangle(in,cvPoint(x,y),cvPoint(x+kernel_size,y+kernel_size),cvScalarAll(0));
                //cvCircle(in,cvPoint(x,y),kernel_size,cvScalarAll(0),kernel_size/2+1);

            }
        }
    }
}
