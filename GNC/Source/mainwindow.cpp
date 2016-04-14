#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    CreateLayout();
		
	//Actions
    connect(a_open, SIGNAL(triggered(bool)),this,SLOT(open_clicked()));
    connect(a_save, SIGNAL(triggered(bool)),this,SLOT(save_clicked()));
    connect(a_exit, SIGNAL(triggered(bool)),this,SLOT(exit_clicked()));
    connect(slider1,SIGNAL(valueChanged(int)), this, SLOT(slider1_change(int)));
    connect(slider2,SIGNAL(valueChanged(int)), this, SLOT(slider2_change(int)));
    connect(a_auto, SIGNAL(triggered(bool)),this,SLOT(auto_clicked()));
    connect(a_mahyar, SIGNAL(triggered(bool)),this,SLOT(mahyar_clicked()));
    connect(a_bijan, SIGNAL(triggered(bool)),this,SLOT(bijan_clicked()));
	//Buttons
    connect(open_btn, SIGNAL(released()), this, SLOT(open_clicked()));
    connect(analysis_btn, SIGNAL(released()), this, SLOT(analysis_clicked()));
    connect(rec_btn, SIGNAL(released()), this, SLOT(rec_clicked()));
    connect(calibrate_btn, SIGNAL(released()), this, SLOT(calibrate_clicked()));

    loadVideo();
}

MainWindow::~MainWindow()
{

}

//Open image function call
void MainWindow::loadVideo()
{
    if (!filter_param.isVideo)
    {
        imagerd = cvLoadImage(filter_param.filename.toLocal8Bit().data());
        slider1->setValue(0);
        slider2->setValue(0);
        slider1->setEnabled(false);
        slider2->setEnabled(false);
    }
    else
    {
        capture = cvCreateFileCapture( filter_param.filename.toLocal8Bit().data() );
        if (capture == NULL)
            return;
        imagerd = cvQueryFrame( capture );
        slider1->setEnabled(true);
        slider2->setEnabled(true);
        slider2->setMaximum((int) cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_COUNT ));
        slider1->setMaximum((int) cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_COUNT ));
        slider1->setValue(filter_param.frame_num);
        slider2->setValue(slider1->maximum()-1);
        videoLoaded = true;
    }

    updatePrev();
}

void MainWindow::exit_clicked()
{
	close();
}

void MainWindow::auto_clicked()
{
    a_mahyar->setChecked(false);
    a_bijan->setChecked(false);
    filter_param.algorithm = TRM_AUTO_SWITCH;
    updatePrev();
}

void MainWindow::mahyar_clicked()
{
    a_auto->setChecked(false);
    a_bijan->setChecked(false);
    filter_param.algorithm = TRM_ONLY_MAHYAR;
    updatePrev();
}

void MainWindow::bijan_clicked()
{
    a_auto->setChecked(false);
    a_mahyar->setChecked(false);
    filter_param.algorithm = TRM_ONLY_BIJAN;
    updatePrev();
}

void MainWindow::rec_clicked()
{
    rec_window = new RecWindow();
    rec_window->exec();
    if (rec_window->doAnalysis)
    {
        delete rec_window;
        analysis_clicked();
    }
    else
    {
        delete rec_window;
    }
}

void MainWindow::analysis_clicked()
{
    int frameNumber = 0;
    frameNumber = filter_param.frame_num;
    trmData *head,*ptr,*ptr_prev;
    int size = 0;
    if (videoLoaded)
    {
        head = createTrmdata(capture,filter_param,treshold_1,treshold_2,progress,&size);
        std::cout << size << std::endl;
        QVector< double > X(size);
        QVector< double > Y(size);
        QVector< double > T(size);
        QVector< double > V(size);
        ptr = head->next;
        double last_x , last_y;
        V[0] = 0;
        for (int i = 0 ; i < size ; i++)
        {
            if (ptr == NULL)
                break;
            X[i] = ptr->x;
            Y[i] = ptr->y;
            T[i] = ptr->frameNum;

            if (i)
                V[i] = cvSqrt((X[i] - last_x) * (X[i] - last_x) + (Y[i] - last_y) * (Y[i] - last_y) );
            last_x = X[i];
            last_y = Y[i];
            ptr_prev = ptr;
            ptr = ptr->next;
			delete ptr_prev;
        }

        xy_curve->setSamples(X,Y);
        xy_plot->update();
        xy_zoomer->zoomBase();
        xy_plot->replot();

        xt_curve->setSamples(T,X);
        xt_plot->update();
        xt_zoomer->zoomBase();
        xt_plot->replot();

        yt_curve->setSamples(T,Y);
        yt_plot->update();
        yt_zoomer->zoomBase();
        yt_plot->replot();

        vt_curve->setSamples(T,V);
        vt_plot->update();
        vt_zoomer->zoomBase();
        vt_plot->replot();

        X.clear();
        Y.clear();
        T.clear();
        V.clear();

        progress->setValue(0);
    }
    update();
}

void MainWindow::slider1_change(int value)
{
    treshold_1 = value;
    filter_param.frame_num = treshold_1;
    slider1_label->setText(QString("Start Frame = %1").arg(value));
    updatePrev();
}

void MainWindow::slider2_change(int value)
{
    treshold_2 = value;
    slider2_label->setText(QString("End Frame = %1").arg(value));
}

void MainWindow::updatePrev()
{
    IplImage *imagesrc;
    if (!filter_param.isVideo)
    {
        imagesrc = cvLoadImage(filter_param.filename.toLocal8Bit().data());
    }
    else
    {
        if (capture == NULL)
            return;
        cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,filter_param.frame_num);
        if (!cvGrabFrame( capture ))
            return;
        imagesrc = cvQueryFrame( capture );
    }
    if (imagesrc == NULL)
    {
        return;
    }
    bool isAuto = false;
    bool isSwitch = false; //toggle on if use mahyar algorithm in auto mode
    trmMark *plus_obj;
    if (a_mahyar->isChecked())
    {
        //plus_obj = markFromMahyar(imagesrc,filter_param);
    }
    else
    {
        plus_obj = markFromImage(imagesrc,filter_param,&isAuto) ;
        if (plus_obj == NULL && a_auto->isChecked())
        {
            //plus_obj = markFromMahyar(imagesrc,filter_param);
            isSwitch = true;
        }
    }
    if (plus_obj != NULL)
    {
        if (a_mahyar->isChecked() || isSwitch)
        {
            cvSetImageROI(imagesrc, plus_obj->region);
        }
        else
        {
            cvSetImageROI(imagesrc, plus_obj->getRegion());
        }
        IplImage *imgout  = cvCreateImage(cvGetSize(imagesrc), imagesrc->depth, imagesrc->nChannels);
        cvCopy(imagesrc, imgout, NULL);
        cvResetImageROI(imagesrc);

        if (isAuto)
        {
            cv::Mat mat_temp = imgout;
            cv::putText(mat_temp,"Auto",cvPoint(10,20),1,1,cvScalar(0,0,255));
        }

        //std::cout << imagesrc->widthStep << " and " <<  imagesrc->width << std::endl;
        imageView = QImage((const unsigned char*)(imgout->imageData), imgout->width,imgout->height,QImage::Format_RGB888).rgbSwapped();
        preview->setPixmap(QPixmap::fromImage(imageView.scaled(prev_size,floor((prev_size/imgout->width)*imgout->height),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        cvReleaseImage( &imgout );

        delete plus_obj;
        return;
    }
    imageView = QImage((const unsigned char*)(NA_image->imageData), NA_image->width,NA_image->height,QImage::Format_RGB888).rgbSwapped();
    preview->setPixmap(QPixmap::fromImage(imageView.scaled(prev_size,floor((prev_size/NA_image->width)*NA_image->height),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
}

void MainWindow::calibrate_clicked()
{
    calibrate_window = new CalibrateWindow(this);
    filter_param = calibrate_window->start(filter_param.frame_num);
    updatePrev();
    delete calibrate_window;
}

void MainWindow::open_clicked()
{
    filter_param.filename = QFileDialog::getOpenFileName(this, "Open File", "","Videos (*.mp4 *.avi *.mov *.mod)");
    if (!filter_param.filename.isEmpty())
    {
        filter_param.isVideo = true;
        capture = cvCreateFileCapture( filter_param.filename.toLocal8Bit().data() );
        if (capture == NULL)
            return;
        trmMark::Saveparam(filter_param,SETTING_FILENAME);
        slider2->setMaximum((int) cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_COUNT ));
        slider1->setMaximum((int) cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_COUNT ));
        videoLoaded = true;
        updatePrev();
    }

}

void MainWindow::save_clicked()
{
    filter_param.filename = QFileDialog::getOpenFileName(this, "Save File", "","data (*.dat)");
    if (!filter_param.filename.isEmpty())
    {

    }
}

void MainWindow::CreateMenu()
{
    menu = new QMenuBar (this);
	setMenuBar(menu);

	file_menu = menu->addMenu("File");
	a_open = file_menu->addAction("Open");
	a_save = file_menu->addAction("Save");
	a_exit = file_menu->addAction("Exit");

    option_menu = menu->addMenu("Option");
    a_mahyar = option_menu->addAction("Only Mahyar");
    a_bijan = option_menu->addAction("Only Bijan");
    a_auto = option_menu->addAction("Auto switch");

	help_menu = menu->addMenu("Help");
	a_about = help_menu->addAction("About");

    a_bijan->setCheckable(true);
    a_mahyar->setCheckable(true);
    a_auto->setCheckable(true);

    if (filter_param.algorithm == TRM_AUTO_SWITCH)
    {
        a_auto->setChecked(true);
    }
    else if (filter_param.algorithm == TRM_ONLY_MAHYAR)
    {
        a_mahyar->setChecked(true);
    }
    else if (filter_param.algorithm == TRM_ONLY_BIJAN)
    {
        a_bijan->setChecked(true);
    }
}

void MainWindow::CreateLayout()
{
    main_layout = new QVBoxLayout;
    Main_Widget = new QWidget;

    filter_param = trmMark::Loadparam(SETTING_FILENAME);
	CreateMenu();

    option_layout = new QHBoxLayout;
    data_layout = new QGridLayout;
    plot_layout = new QGridLayout;
    progress_layout = new QHBoxLayout;
    button_layout = new QHBoxLayout;
    surface_layout = new QHBoxLayout;
    //Button
	button_layout = new QHBoxLayout;
    open_btn = new QPushButton("Open");
    calibrate_btn = new QPushButton("Calibrate");
    analysis_btn = new QPushButton("Analysis");
    rec_btn = new QPushButton("Record");
	button_layout->addWidget(open_btn);
	button_layout->addWidget(calibrate_btn);
	button_layout->addWidget(analysis_btn);
    button_layout->addWidget(rec_btn);

    //
    slider1_layout = new QHBoxLayout;
    slider1_label = new QLabel("Start Frame = 0");
    slider1 = new QSlider(Qt::Horizontal);
    slider1_layout->addWidget(slider1_label);
    slider1_layout->addWidget(slider1);

    slider2_layout = new QHBoxLayout;
    slider2_label = new QLabel("End Frame = 0");
    slider2 = new QSlider(Qt::Horizontal);
    slider2_layout->addWidget(slider2_label);
    slider2_layout->addWidget(slider2);

    //Options
    surface2_layout = new QVBoxLayout;
    surface2_layout->addLayout(option_layout);

	progress = new QProgressBar;
    progress->setValue(0);
	progress_layout->addWidget(progress);

	//Plot
    xy_plot = new QwtPlot(QwtText("XY Plot"));
    xt_plot = new QwtPlot(QwtText("XT Plot"));
    yt_plot = new QwtPlot(QwtText("YT Plot"));
    vt_plot = new QwtPlot(QwtText("VT Plot"));

    plot_layout->addWidget(xy_plot,0,0);
    plot_layout->addWidget(xt_plot,0,1);
    plot_layout->addWidget(yt_plot,1,0);
    plot_layout->addWidget(vt_plot,1,1);


    QFont font = QFont("Tahoma",10);
    QwtText title;
    title.setFont(font);

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::yellow ), QPen( Qt::red , 1 ), QSize( 1, 1 ) );

    //XY
    xy_grid = new QwtPlotGrid();
    xy_curve = new QwtPlotCurve(trUtf8("Path"));
    xy_curve->setPen( Qt::blue, 1 );
    xy_curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    xy_curve->setSymbol( symbol );
    xy_curve->attach(xy_plot);
    xy_plot ->canvas()->setStyleSheet("border: 0px;");
    xy_plot->titleLabel()->setStyleSheet("font-size: 12px");
    xy_plot ->insertLegend(new QwtLegend(), QwtPlot::RightLegend);
    title.setText("X (cm)");
    xy_plot->setAxisTitle(xy_plot->xBottom, title);
    title.setText("Y (cm)");
    xy_plot->setAxisTitle(xy_plot->yLeft, title);
    xy_zoomer = new QwtPlotZoomer(xy_plot->canvas());
    xy_zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton);

    //Xt
    xt_grid = new QwtPlotGrid();
    xt_curve = new QwtPlotCurve(trUtf8("Signal"));
    xt_curve->setPen( Qt::blue, 1 );
    xt_curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    xt_curve->setSymbol( symbol );
    xt_curve->attach(xt_plot);
    xt_plot ->canvas()->setStyleSheet("border: 0px;");
    xt_plot->titleLabel()->setStyleSheet("font-size: 12px");
    xt_plot ->insertLegend(new QwtLegend(), QwtPlot::RightLegend);
    title.setText("Time (s)");
    xt_plot->setAxisTitle(xt_plot->xBottom, title);
    title.setText("X (cm)");
    xt_plot->setAxisTitle(xt_plot->yLeft, title);
    xt_zoomer = new QwtPlotZoomer(xt_plot->canvas());
    xt_zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton);

    //Yt
    yt_grid = new QwtPlotGrid();
    yt_curve = new QwtPlotCurve(trUtf8("Signal"));
    yt_curve->setPen( Qt::blue, 1 );
    yt_curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    yt_curve->setSymbol( symbol );
    yt_curve->attach(yt_plot);
    yt_plot ->canvas()->setStyleSheet("border: 0px;");
    yt_plot->titleLabel()->setStyleSheet("font-size: 12px");
    yt_plot ->insertLegend(new QwtLegend(), QwtPlot::RightLegend);
    title.setText("Time (s)");
    yt_plot->setAxisTitle(yt_plot->xBottom, title);
    title.setText("Y (cm)");
    yt_plot->setAxisTitle(yt_plot->yLeft, title);
    yt_zoomer = new QwtPlotZoomer(yt_plot->canvas());
    yt_zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton);

    //Vt
    vt_grid = new QwtPlotGrid();
    vt_curve = new QwtPlotCurve(trUtf8("Signal"));
    vt_curve->setPen( Qt::blue, 1 );
    vt_curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    vt_curve->setSymbol( symbol );
    vt_curve->attach(vt_plot);
    vt_plot ->canvas()->setStyleSheet("border: 0px;");
    vt_plot->titleLabel()->setStyleSheet("font-size: 12px");
    vt_plot ->insertLegend(new QwtLegend(), QwtPlot::RightLegend);
    title.setText("Time (s)");
    vt_plot->setAxisTitle(vt_plot->xBottom, title);
    title.setText("Speed (m/s)");
    vt_plot->setAxisTitle(vt_plot->yLeft, title);
    vt_zoomer = new QwtPlotZoomer(vt_plot->canvas());
    vt_zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton);

    //Data
    feature = new QGroupBox("Feature");
    radial_label = new QLabel("Radial : 0 cm");
    freq_label = new QLabel("Frequency : 0 Hz");
    peiod_label = new QLabel("Period : 0 ms");
    amp_label = new QLabel ("Amplitude : 0 cm");
    data_layout->addWidget(radial_label,0,0);
    data_layout->addWidget(freq_label,0,1);
    data_layout->addWidget(peiod_label,1,0);
    data_layout->addWidget(amp_label,1,1);
    feature->setLayout(data_layout);

    //Preview
    preview = new QLabel;
    preview_layout = new QHBoxLayout;
    preview_layout->addWidget(preview);
    preview_group = new QGroupBox("Preview");
    preview_group->setLayout(preview_layout);

    //
    surface2_layout->addWidget(feature);
    surface2_layout->addWidget(preview_group);

    surface_layout->addLayout(plot_layout);
    surface_layout->addLayout(surface2_layout);

    //Start making layout
    main_layout->addLayout(slider1_layout);
    main_layout->addLayout(slider2_layout);
    main_layout->addLayout(surface_layout);
    main_layout->addLayout(progress_layout);
    main_layout->addLayout(button_layout);
    //Side object
    NA_image = cvLoadImage("../Resources/NA.jpg");
    //std::cout << filter_param.color[0][0] << filter_param.color[0][1] << filter_param.color[0][2]  << std::endl;
    videoLoaded = false;
    //Window
    Main_Widget->setLayout(main_layout);
    setWindowTitle(trUtf8("Tremor"));
    setCentralWidget(Main_Widget);
    //move
    //setLayoutDirection(Qt::RightToLeft);
}

//size: return by function as size of data
//progress: update by function to show progress
//mode: can be auto,only bijan,only mahar
trmData *createTrmdata(CvCapture *capture,trmParam param,int startFrame,int endFrame,QProgressBar *progress,int *size)
{
    trmData *head,*temp,*ptr;
    head = new trmData;
    head->next = NULL;
    ptr = head;
    *size = 0;
    progress->setMaximum(endFrame - startFrame);
    for  (int frameNumber = startFrame; frameNumber < endFrame ; frameNumber++)
    {
        IplImage *imagesrc;
        if (capture == NULL)
            break;
        cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,frameNumber);
        if (!cvGrabFrame( capture ))
            break;
        imagesrc = cvQueryFrame( capture );
        if (imagesrc == NULL)
        {
            break;
        }
		trmMark *plus_obj;
        if (param.algorithm == TRM_ONLY_MAHYAR)
		{
            //plus_obj = markFromMahyar(imagesrc,param);
		}
		else
		{
			plus_obj = markFromImage(imagesrc,param,NULL) ;
		}
        if (plus_obj != NULL && (plus_obj->middle.x < 3000 && plus_obj->middle.y < 3000))
        {
            temp = new trmData;
            temp->x = plus_obj->middle.x;
            temp->y = plus_obj->middle.y;
            temp->frameNum = frameNumber;
            temp->next = NULL;
            ptr->next = temp;
            ptr = ptr->next;
            delete plus_obj;
            (*size)++;
        }
        else
        {
            std::cout << "Erorr: frame number: " << frameNumber << std::endl;
        }
        progress->setValue(frameNumber - startFrame);
    }
    return head;
}
