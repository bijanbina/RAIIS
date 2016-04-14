#include "recwindow.h"

void *capture_main(void *data)
{
    RecWindow *window = (RecWindow*)data;
    window->thread_cam_active = true;
    IplImage *imagesrc;
    while (!window->isRec)
    {
        imagesrc = cvQueryFrame( window->capture );
        if (imagesrc == NULL)
        {
            window->imageView = QImage((const unsigned char*)(window->NA_image->imageData), window->NA_image->width,window->NA_image->height,QImage::Format_RGB888).rgbSwapped();
            window->surface->setPixmap(QPixmap::fromImage(window->imageView.scaled(window->surface_width,
                                       floor((window->surface_width/window->NA_image->width)*window->NA_image->height),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
            window->thread_cam_active = false;
            return NULL;
        }
        window->imageView = QImage((const unsigned char*)(imagesrc->imageData), imagesrc->width,imagesrc->height,QImage::Format_RGB888).rgbSwapped();
        window->surface->setPixmap(QPixmap::fromImage(window->imageView.scaled(window->surface_width,
                                      floor((window->surface_width/imagesrc->width)*imagesrc->height),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    }
    window->thread_cam_active = false;
    return NULL;
}

void *record_main(void *data)
{
    RecWindow *window = (RecWindow*)data;

    IplImage *imagesrc = cvQueryFrame(window->capture);//Init the video read
    double fps = 30;
    CvSize size = cvSize((int)cvGetCaptureProperty( window->capture, CV_CAP_PROP_FRAME_WIDTH),
                (int)cvGetCaptureProperty( window->capture, CV_CAP_PROP_FRAME_HEIGHT));
    CvVideoWriter *writer = cvCreateVideoWriter(TEMP_VIDEO_ADDRESS, CV_FOURCC('M','P','E','G'), fps, size );

    int i = 0;
    timeval time_start,time_now;
    gettimeofday(&time_start,NULL);
    i = gettimeofday(&time_now,NULL);
    while (true)
    {
        i++;
        imagesrc = cvQueryFrame( window->capture );
        if (window->a_preview->isChecked()) //slow mode
        {
            if (imagesrc == NULL)
            {
                window->imageView = QImage((const unsigned char*)(window->NA_image->imageData), window->NA_image->width,window->NA_image->height,QImage::Format_RGB888).rgbSwapped();
                window->surface->setPixmap(QPixmap::fromImage(window->imageView.scaled(window->surface_width,
                                           floor((window->surface_width/window->NA_image->width)*window->NA_image->height),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
                return NULL;
            }
            window->imageView = QImage((const unsigned char*)(imagesrc->imageData), imagesrc->width,imagesrc->height,QImage::Format_RGB888).rgbSwapped();
            window->surface->setPixmap(QPixmap::fromImage(window->imageView.scaled(window->surface_width,
                                          floor((window->surface_width/imagesrc->width)*imagesrc->height),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));


        }
        cvWriteFrame( writer, imagesrc );
        if (gettimeofday( &time_now , NULL ) < 0)
        {
            printf("Error in getting time");
            return NULL;
        }
        //update info
        window->info_frameNum->setText(QString("Farme = %1").arg(i));
        window->info_time->setText(QString("Time : 0:%1:%2").arg((int)(time_now.tv_sec) - (int)(time_start.tv_sec)).arg((int)(time_now.tv_usec/100000)));
        int elapsed = ((int)(time_now.tv_sec) - (int)(time_start.tv_sec));
        if (elapsed)
            window->info_fps->setText(QString("RPS = %1").arg(i/elapsed));

        if (!window->isRec)
        {
            break;
        }
    }
    cvReleaseVideoWriter( &writer );
    return NULL;
}

RecWindow::RecWindow(QWidget *parent) :
    QDialog(parent)
{
    CreateLayout(parent);
    CreateMenu();

    connect(slider1,SIGNAL(valueChanged(int)), this, SLOT(slider1_change(int)));
    connect(slider2,SIGNAL(valueChanged(int)), this, SLOT(slider2_change(int)));
    connect(rec_btn, SIGNAL(released()), this, SLOT(rec_clicked()));
    connect(save_btn, SIGNAL(released()), this, SLOT(save_clicked()));
    connect(analysis_btn, SIGNAL(released()), this, SLOT(analysis_clicked()));

    connect(a_open, SIGNAL(triggered(bool)),this,SLOT(open_clicked()));
    connect(a_focus, SIGNAL(triggered(bool)),this,SLOT(afocus_changed(bool)));
    connect(a_preview, SIGNAL(triggered(bool)),this,SLOT(preview_changed(bool)));
    filename = filter_param.filename;

    setGeometry((qApp->desktop()->geometry().center() - rect().center()).x(),(qApp->desktop()->geometry().center() - rect().center()).y(),rect().width(),rect().height());

    //load camera
    QString DeviceName;
    if (filter_param.deviceID == -1)
    {
        QStringList cam_list = getDeviceName();
        if (cam_list.size() > 1)
        {
            DeviceName = QInputDialog::getItem(this,"Select Camera","Camera",cam_list);
            DeviceName = DeviceName[DeviceName.size()-1];
            filter_param.deviceID = DeviceName.toInt();
        }
        else if (cam_list.size() == 1)
        {
            DeviceName = cam_list[0];
            DeviceName = DeviceName[DeviceName.size()-1];
            filter_param.deviceID = DeviceName.toInt();
        }
        //else device id is unchanged
    }
    capture = cvCreateCameraCapture(filter_param.deviceID);
    if (!capture)
    {
        if (filter_param.deviceID != -1)
        {
            QStringList cam_list = getDeviceName();
            if (cam_list.size() > 1)
            {
                DeviceName = QInputDialog::getItem(this,"Select Camera","Camera",cam_list);
                DeviceName = DeviceName[DeviceName.size()-1];
                filter_param.deviceID = DeviceName.toInt();
            }
            else if (cam_list.size() == 1)
            {
                DeviceName = cam_list[0];
                DeviceName = DeviceName[DeviceName.size()-1];
                filter_param.deviceID = DeviceName.toInt();
            }
            else
            {
                imageView = QImage((const unsigned char*)(NA_image->imageData), NA_image->width,NA_image->height,QImage::Format_RGB888).rgbSwapped();
                surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,
                                           floor((surface_width/NA_image->width)*NA_image->height),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
				printf("no camera detected\n");
                return;
            }
            capture = cvCreateCameraCapture(filter_param.deviceID);
        }
        else
        {
            imageView = QImage((const unsigned char*)(NA_image->imageData), NA_image->width,NA_image->height,QImage::Format_RGB888).rgbSwapped();
            surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,
                                       floor((surface_width/NA_image->width)*NA_image->height),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
			printf("no camera detected\n");
            return;
        }
    }
    camID = filter_param.deviceID;
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH,1280);
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT,720);
    char command[50];
    sprintf(command,"v4l2-ctl -d %d -c exposure_auto=1",camID);
    system(command);
    sprintf(command,"v4l2-ctl -d %d -c exposure_absolute=1",camID);
    system(command);
    sprintf(command,"v4l2-ctl -d %d -c focus_auto=0",camID);
    system(command);
    if (thread_cam_active)
        pthread_cancel(thread_cam);
	printf("tread started\n");
    pthread_create( &thread_cam, NULL, capture_main, (void*) this);
}

RecWindow::~RecWindow()
{

}

void RecWindow::open_clicked()
{
    QString DeviceName;
    QStringList cam_list = getDeviceName();
    camID = -1;
    if (thread_cam_active)
        pthread_cancel(thread_cam);
    if (cam_list.size() > 1)
    {
        DeviceName = QInputDialog::getItem(this,"Select Camera","Camera",cam_list);
        DeviceName = DeviceName[DeviceName.size()-1];
        camID = DeviceName.toInt();
    }
    else if (cam_list.size() == 1)
    {
        DeviceName = cam_list[0];
        DeviceName = DeviceName[DeviceName.size()-1];
        camID = DeviceName.toInt();
    }
    //else device id is unchanged
    if(capture)
	{
		cvReleaseCapture(&capture);
	}
    capture = cvCreateCameraCapture(camID);
    if (!capture)
    {
        return;
    }

    char command[50];
    sprintf(command,"v4l2-ctl -d %d -c exposure_auto=1",camID);
    system(command);
    sprintf(command,"v4l2-ctl -d %d -c exposure_absolute=1",camID);
    system(command);
    sprintf(command,"v4l2-ctl -d %d -c focus_auto=0",camID);
    system(command);
	printf("Thread started\n");
    pthread_create( &thread_cam, NULL, capture_main, (void*) this);
}

void RecWindow::save_clicked()
{
    char *file_name = QFileDialog::getSaveFileName(this, "Save File","","*.mpg").toLocal8Bit().data();
    if (strcmp(file_name,"") && !imageView.isNull())
    {
        char command[50];
        sprintf(command,"mv %s %s",TEMP_VIDEO_ADDRESS,file_name);
        system(command);
    }
}

void RecWindow::rec_clicked()
{
    if(!capture)
        return;
    if (!isRec)
    {
        isRec = true;//this will stop pipeline to preview!
        pthread_create( &thread_rec, NULL, record_main, (void*) this);
        rec_btn->setText("Stop");
    }
    else
    {
        isRec = false;//this will stop recording!
        rec_btn->setText("Record");
    }
}

void RecWindow::exit_clicked()
{

}

void RecWindow::analysis_clicked()
{
    ;
}

void RecWindow::afocus_changed(bool state)
{
    if(!capture)
        return;
    char command[50];
    sprintf(command,"v4l2-ctl -d %d -c focus_auto=%d",camID,state);
    system(command);
    slider1->setEnabled(state);
}

void RecWindow::preview_changed(bool state)
{
    if (state)
    {

    }
    else if(isRec)
    {
        imageView = QImage((const unsigned char*)(NA_image->imageData), NA_image->width,NA_image->height,QImage::Format_RGB888).rgbSwapped();
        surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,
                                   floor((surface_width/NA_image->width)*NA_image->height),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    }
}

void RecWindow::slider1_change(int value)
{
    if (!(a_focus->isChecked()))
    {
        treshold_1 = value;
        char command[50];
        sprintf(command,"v4l2-ctl -d %d -c focus_absolute=%f",camID,treshold_1);
        system(command);
        slider1_label->setText(QString("Focus = %1").arg(value));
    }
}

void RecWindow::slider2_change(int value)
{
    treshold_2 = value;
    slider2_label->setText(QString("value = %1").arg(value));
}

void RecWindow::CreateMenu()
{
    menu = new QMenuBar (this);
    //setMenuBar(menu);
    main_layout->setMenuBar(menu);

    file_menu = menu->addMenu("File");
    a_open = file_menu->addAction("Open");
    a_open_image = file_menu->addAction("Open Image");
    a_save = file_menu->addAction("Save");
    a_replace = file_menu->addAction("Replace");

    option_menu = menu->addMenu("Option");
    a_focus = option_menu->addAction("Auto Focus");
    a_asave = option_menu->addAction("Save On File");
    a_preview = option_menu->addAction("Show Preview");

    a_focus->setCheckable(true);
    a_asave->setCheckable(true);
    a_preview->setCheckable(true);

    a_preview->setChecked(true);

    help_menu = menu->addMenu("Help");
    a_about = help_menu->addAction("About");
}

void RecWindow::CreateLayout(QWidget *parent)
{
    //Default
    imgout = NULL;
    thread_cam_active = false;
    doAnalysis = false;
	capture = NULL;
    surface = new QLabel();
    main_layout = new QVBoxLayout;
    Main_Widget = new QWidget;

    slider1_layout = new QHBoxLayout;
    slider1_label = new QLabel("value = 0");
    slider1 = new QSlider(Qt::Horizontal);
    slider1->setMaximum(40);
    slider1_layout->addWidget(slider1_label);
    slider1_layout->addWidget(slider1);

    slider2_layout = new QHBoxLayout;
    slider2_label = new QLabel("value = 0");
    slider2 = new QSlider(Qt::Horizontal);
    slider2->setMaximum(1000);
    slider2_layout->addWidget(slider2_label);
    slider2_layout->addWidget(slider2);

    info_layout = new QVBoxLayout;
    info_fps = new QLabel("FPS = 0");
    info_frameNum = new QLabel("Frame = 0");
    info_time = new QLabel("Time : 0");
    info_layout->addWidget(info_fps);
    info_layout->addWidget(info_frameNum);
    info_layout->addWidget(info_time);

    surface_layout = new QHBoxLayout;
    surface_layout->addLayout(info_layout);
    surface_layout->addWidget(surface);

    //Button
    button_layout = new QHBoxLayout;
    rec_btn = new QPushButton("Record");
    save_btn = new QPushButton("Save");
    analysis_btn = new QPushButton("Analysis");
    button_layout->addWidget(rec_btn);
    button_layout->addWidget(save_btn);
    button_layout->addWidget(analysis_btn);
    //Options
    surface2_layout = new QVBoxLayout;
    option_layout = new QHBoxLayout;
    chkbox_layout = new QHBoxLayout;
    surface2_layout->addLayout(option_layout);
    //Start making layout
    main_layout->addLayout(slider1_layout);
    main_layout->addLayout(slider2_layout);
    main_layout->addLayout(surface2_layout);
    main_layout->addLayout(surface_layout);
    main_layout->addLayout(button_layout);
    //Side object
    //file_name = "/home/bijan/Downloads/IMG_20140630_213804.jpg";
    filter_param = trmMark::Loadparam(SETTING_FILENAME);
    NA_image = cvLoadImage("../Resources/NA.jpg");
    //default
    treshold_1 = 0;
    treshold_2 = 0;
    surface_width = filter_param.calibre_width;

    //Window
    setLayout(main_layout);
    setWindowTitle(trUtf8("Capture Vide"));
    //setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Window);
    //setSizePolicy(QSizePolicy::Minimum);
    //setLayoutDirection(Qt::RightToLeft);
}

//---------Base Code -----------

QStringList RecWindow::getDeviceName()
{
    QStringList return_data;
    QDir *dip = new QDir("/dev","video*",QDir::SortFlags(QDir::Name | QDir::IgnoreCase ), QDir::AllEntries | QDir::System);
    return_data = dip->entryList();
    return return_data;
}
