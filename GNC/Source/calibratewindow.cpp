#include "calibratewindow.h"

CalibrateWindow::CalibrateWindow(QWidget *parent) :
	QDialog(parent)
{
	CreateLayout(parent);
	CreateMenu();

	connect(slider1,SIGNAL(valueChanged(int)), this, SLOT(slider1_change(int)));
	connect(slider2,SIGNAL(valueChanged(int)), this, SLOT(slider2_change(int)));
	connect(vslider1,SIGNAL(valueChanged(int)), this, SLOT(slider3_change(int)));
	connect(vslider2,SIGNAL(valueChanged(int)), this, SLOT(slider4_change(int)));
	connect(chk1,SIGNAL(stateChanged(int)), this, SLOT(chk1_change()));
	connect(chk2,SIGNAL(stateChanged(int)), this, SLOT(chk2_change()));
	connect(back_btn, SIGNAL(released()), this, SLOT(back_clicked()));
	connect(next_btn, SIGNAL(released()), this, SLOT(next_clicked()));
	connect(replace_btn, SIGNAL(released()), this, SLOT(replace_clicked()));

	connect(a_open, SIGNAL(triggered(bool)),this,SLOT(open_clicked()));
	connect(a_open_image, SIGNAL(triggered(bool)),this,SLOT(openimage_clicked()));
	connect(a_save, SIGNAL(triggered(bool)),this,SLOT(save_clicked()));
	connect(a_replace, SIGNAL(triggered(bool)),this,SLOT(replace_clicked()));
	connect(a_loop, SIGNAL(triggered(bool)),this,SLOT(state_change()));
	connect(a_width, SIGNAL(triggered(bool)),this,SLOT(width_clicked()));
	connect(a_equal, SIGNAL(triggered(bool)),this,SLOT(equal_clicked(bool)));
	connect(a_mclose, SIGNAL(triggered(bool)),this,SLOT(mclose_clicked(bool)));
	connect(a_mreversed, SIGNAL(triggered(bool)),this,SLOT(mreversed_clicked(bool)));
	connect(a_mopen, SIGNAL(triggered(bool)),this,SLOT(mopen_clicked(bool)));
	connect(a_mnormal, SIGNAL(triggered(bool)),this,SLOT(mnormal_clicked(bool)));

	filename = filter_param.filename;
	isVideo = filter_param.isVideo;
	if (!isVideo)
	{
		imagesrc = cvLoadImage(filename.toLocal8Bit().data());
		image = cvLoadImage(filename.toLocal8Bit().data(),CV_LOAD_IMAGE_GRAYSCALE);

		slider1->setValue(filter_param.edge_1);
		slider2->setValue(filter_param.edge_2);
		vslider1->setValue(filter_param.erode);
		vslider2->setValue(filter_param.dilate);

		option_menu->addAction(a_width);
		option_menu->addAction(a_loop);

		state_change();
	}
	else
	{
		capture = cvCreateFileCapture( filename.toLocal8Bit().data() );
		if (capture == NULL)
			return;
		imagesrc = cvQueryFrame( capture );
		image = cvCreateImage( cvGetSize(imagesrc), 8, 1 );
		cvCvtColor( imagesrc, image, CV_BGR2GRAY );
		chk2->setChecked(false);
		calibrate_state = TRM_STATE_FRAME;

		option_menu->addAction(a_width);

		vslider1->setValue(0);
		chk1->setChecked(false);
		slider1->setValue(0);
		state_change(1);
		slider1->setValue(filter_param.frame_num);
		slider2->setValue(filter_param.calibre_width);
	}

	setGeometry((qApp->desktop()->geometry().center() - rect().center()).x(),(qApp->desktop()->geometry().center() - rect().center()).y(),rect().width(),rect().height());
}

CalibrateWindow::~CalibrateWindow()
{

}


void CalibrateWindow::state_change(int changed)
{
	if (imgout != NULL)
	{
		cvReleaseImage(&imgout);
	}
	if (image == NULL)
		return;
	if (changed)
	{
		chk1->setChecked(false);
		chk2->setChecked(false);
		treshold_1 = 0;
		treshold_3 = 0;
		slider1->setEnabled(true);
		slider2->setEnabled(true);
		slider1->setValue(0);
		slider2->setValue(0);
		vslider1->setValue(0);
		vslider2->setValue(0);
	}
	surface_height = floor((surface_width/image->width)*image->height);
	if ( calibrate_state == TRM_STATE_FRAME)
	{
		int frames = (int) cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_COUNT );
		if (frames - 100 < 0)
			return;
		//cvSetCaptureProperty(capture,CV_CAP_PROP_POS_MSEC,treshold_1);
		if (treshold_1 + 100 > frames )
			return;
		cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,treshold_1);
		//        std::cout << cvGrabFrame( capture ) << "\t" << frames << std::endl;
		if (!cvGrabFrame( capture ))
			return;
		imagesrc = cvQueryFrame( capture );
		image = cvCreateImage( cvGetSize(imagesrc), 8, 1 );
		cvCvtColor( imagesrc, image, CV_BGR2GRAY );
		imageView = QImage((const unsigned char*)(imagesrc->imageData), imagesrc->width,imagesrc->height,QImage::Format_RGB888).rgbSwapped();
		surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,surface_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
		chk1->setText("NULL");
		chk2->setText("NULL");
		slider1->setMaximum(frames - 100);
		slider2->setMinimum(200);
		slider2->setMaximum(2000);
		vslider1->setEnabled(false);
		vslider2->setEnabled(false);
	}
	else if (calibrate_state == TRM_STATE_EDGE)
	{
		if ( treshold_3 != 0 || treshold_4 != 0 )
		{
			IplConvKernel *convKernel = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_RECT, NULL);
			if (a_equal->isChecked())
			{
				treshold_4 = treshold_3;
				vslider2->setEnabled(false);
			}
			else
			{
				vslider2->setEnabled(true);
				treshold_4 = vslider2->value();
			}
			imgout = cvCreateImage(cvGetSize(image),image->depth,image->nChannels);
			if (morphology_state == MORPH_STATE_NORMALL)
			{
				cvErode( image, imgout , NULL , treshold_3 );
				cvDilate( imgout, imgout , NULL , treshold_4 );
			}
			else if (morphology_state == MORPH_STATE_REVERSED)
			{
				cvDilate( image, imgout , NULL , treshold_4 );
				cvErode( imgout, imgout , NULL , treshold_3 );
			}
			else if (morphology_state == MORPH_STATE_OPEN)
			{
				int kernel_size = treshold_3 * 2 + 1;
				IplConvKernel *convKernel = cvCreateStructuringElementEx(kernel_size, kernel_size, treshold_3, treshold_3, CV_SHAPE_RECT, NULL);
				imgout = cvCloneImage(image);
				cvMorphologyEx(imgout, imgout, NULL, convKernel, CV_MOP_OPEN);
			}
			else if (morphology_state == MORPH_STATE_CLOSE)
			{
				imgout = cvCloneImage(image);
				for (int i = 0 ; i < treshold_3; i++)
				{
					cvDilate( imgout, imgout , NULL , 1 );
					//cvErode( imgout, imgout , NULL , 1 );
				}

				//                int kernel_size = treshold_3 * 2 + 1;
				//                IplConvKernel *convKernel = cvCreateStructuringElementEx(kernel_size, kernel_size, treshold_3, treshold_3, CV_SHAPE_RECT, NULL);
				//                imgout = cvCloneImage(image);
				//                cvMorphologyEx(imgout, imgout, NULL, convKernel, CV_MOP_CLOSE);
			}
			imageView = QImage((const unsigned char*)(imgout->imageData), imgout->width,imgout->height,QImage::Format_Indexed8).rgbSwapped();
			surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,surface_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
			cvReleaseStructuringElement(&convKernel);
		}
		if (treshold_1 == 0 && treshold_2 == 0 )
		{
			if ( treshold_3 != 0 || treshold_4 != 0 )
			{
				imageView = QImage((const unsigned char*)(imgout->imageData), imgout->width,imgout->height,QImage::Format_Indexed8).rgbSwapped();
			}
			else
			{
				imageView = QImage((const unsigned char*)(imagesrc->imageData), imagesrc->width,imagesrc->height,QImage::Format_RGB888).rgbSwapped();
			}
		}
		else
		{
			if ( treshold_3 != 0 || treshold_4 != 0 )
			{
                imgout = trmMark::doCanny( imgout, treshold_1 ,treshold_2 );
				imageView = QImage((const unsigned char*)(imgout->imageData), imgout->width,imgout->height,QImage::Format_Indexed8).rgbSwapped();
			}
			else
            {
                imgout = trmMark::doCanny( cvCloneImage(image), treshold_1 ,treshold_2 );
				imageView = QImage((const unsigned char*)(imgout->imageData), imgout->width,imgout->height,QImage::Format_Indexed8).rgbSwapped();
			}
		}
		surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,surface_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
		chk1->setText("Proportion 3");
		chk2->setText("NULL");
		slider1->setMaximum(1000);
		slider2->setMaximum(1000);
		slider2->setMinimum(0);
		vslider1->setMaximum(30);
		vslider2->setMaximum(30);
		vslider1->setEnabled(true);
	}
	else if (calibrate_state == TRM_STATE_CORNER)
	{
		imgout = cvCloneImage(image);
		if (treshold_1 != 0 && treshold_1 < 15)
		{
            trmMark::bold_filter(imgout,treshold_1);
		}
		if (treshold_2 != 0 && treshold_2 < 15)
		{
            trmMark::narrowFilter(imgout,treshold_2);
		}
		if (chk1->isChecked())
		{
            imgout = trmMark::doCanny( imgout, 20 ,60);
		}
		IplImage *imgclone = cvCloneImage(imgout);
		CvSeq* firstContour = NULL;
		CvMemStorage* cnt_storage = cvCreateMemStorage();
		CvMemStorage* poly_storage = cvCreateMemStorage();
		cvFindContours(imgclone,cnt_storage,&firstContour,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
		cvReleaseImage( &imgclone );
		if (chk2->isChecked())
		{
			cvZero( imgout );
		}
		CvSeq *dummy_seq = firstContour;
		CvSeq *poly = NULL;

		int i = 0;
		cv::Mat matout = imgout;
		while( dummy_seq != NULL )
		{
			poly = cvApproxPoly(dummy_seq,sizeof(CvContour),poly_storage, CV_POLY_APPROX_DP,treshold_3);
			if (poly->total == 12 || a_loop->isChecked())
			{
				for(i = 0; i < poly->total; i++)
				{
					CvPoint *temp_point = (CvPoint*)cvGetSeqElem(poly,i);
					cv::circle( matout, *temp_point, 10.0, 255, 3, 1 );
				}
			}
			dummy_seq = dummy_seq->h_next;
		}
		cvClearMemStorage(poly_storage);
		cvReleaseMemStorage(&poly_storage);
		cvClearMemStorage(cnt_storage);
		cvReleaseMemStorage(&cnt_storage);
		slider2->setEnabled(false);
		vslider2->setEnabled(false);

		imageView = QImage((const unsigned char*)(imgout->imageData), imgout->width,imgout->height,QImage::Format_Indexed8).rgbSwapped();
		surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,surface_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
		chk1->setText("Canny");
		chk2->setText("Zero Input");
		slider1->setMaximum(20);
		slider2->setMaximum(20);
		vslider1->setMaximum(100);
		vslider2->setMaximum(50);
        slider1->setEnabled(true);
		vslider1->setEnabled(true);
		slider2->setEnabled(true);
		vslider2->setEnabled(true);
	}
	else if (calibrate_state == TRM_STATE_RESULT)
	{
		count = 0;
		if (filter_param.edge_1 == filter_param.edge_2 && filter_param.edge_2 == 0 )
		{
			imageView = QImage((const unsigned char*)(imagesrc->imageData), imagesrc->width,imagesrc->height,QImage::Format_Indexed8).rgbSwapped();
			surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,surface_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
		}
		else
		{
            if (!chk1->isChecked())
                treshold_1 = -1;

            bool isAuto;
            int temp_error = filter_param.maximum_error;
            filter_param.maximum_error = treshold_1;
            trmMark *plus = markFromImage(imagesrc,filter_param,&isAuto);
            filter_param.maximum_error = temp_error;
			imgout = cvCloneImage(imagesrc);
			cv::RNG rng(1234);
            CvScalar color = cvScalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));

			if (plus != NULL)
			{
				cv::Mat mat_temp = imgout;
				cv::line(mat_temp,(plus->getRect())[0],(plus->getRect())[1],color,2,16);
				cv::line(mat_temp,(plus->getRect())[1],(plus->getRect())[2],color,2,16);
				cv::line(mat_temp,(plus->getRect())[2],(plus->getRect())[3],color,2,16);
				cv::line(mat_temp,(plus->getRect())[3],(plus->getRect())[0],color,2,16);
				//cv::line(mat_temp,plus->center2,plus->center3,cvScalar(25,25,200),3);
				//cv::rectangle(mat_temp,plus->getRegion(),color,2,16);
				cv::circle( mat_temp, plus->middle, 4.0, cvScalar(200,50,0), 6, 1 );
				//drawMark( mat_temp, plus->middle, cvScalar(0) );
                if (isAuto)
                {
                    cv::putText(mat_temp,"Auto",cvPoint(30,30),1,2,cvScalar(0,0,255),2);
                }

				if (chk2->isChecked())
				{
            			color = cvScalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
						//find radius from inside edge --> *sqrt(2)/2
						if ( treshold_2 < ( plus->inside_edge * cv::sqrt(2) / 2 ) )
							cv::circle (mat_temp , plus->middle , ( plus->inside_edge * cv::sqrt(2) / 2 ) - treshold_2 , color , 6 , 1 );
						else
							cv::putText(mat_temp,"Error: CutOff is not right!",cvPoint(100,30),1,2,cvScalar(0,0,255),2);
				}

                char data_cache[50];
                sprintf(data_cache , "Erorr: %d" ,cvRound(plus->error));
                cv::putText(mat_temp,data_cache,cvPoint(30,imgout->height - 15),1,1.5,cvScalar(255,255,255),2);
                sprintf(data_cache , "Angle: %0.3f" ,90 - plus->findAngle());
                cv::putText(mat_temp,data_cache,cvPoint(30,imgout->height - 50),1,1.5,cvScalar(255,255,255),2);
				delete plus;
			}
			vslider1_label->setText(QString("value = %1").arg(count));
			imageView = QImage((const unsigned char*)(imgout->imageData), imgout->width,imgout->height,QImage::Format_RGB888).rgbSwapped();
			surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,surface_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
		}
        chk1->setText("Maximum Error");
		chk2->setText("Maximum Accuracy");
		slider1->setMaximum(100);
		slider2->setMaximum(50);
		slider2->setEnabled(chk2->isChecked());
		vslider1->setEnabled(false);
		vslider2->setEnabled(false);
	}
//    else if (calibrate_state = TRM_STATE_MAHYAR)
//    {
//        CVScalar color[2];

//    }
	else
	{
		;
	}
}
void CalibrateWindow::slider1_change(int value)
{
	treshold_1 = value;
	if (chk1->isChecked())
	{
		if (calibrate_state == TRM_STATE_EDGE)
		{
			slider2->setValue(value/3);
		}
		else if (calibrate_state == TRM_STATE_RESULT)
		{
			;
		}
	}
	else
	{
		;
	}
	if (chk2->isChecked())
	{
		if (calibrate_state == TRM_STATE_EDGE)
		{
			;
		}
		else if (calibrate_state == TRM_STATE_RESULT)
		{
			;
		}
	}
	else
	{
		;
	}
	state_change();

	slider1_label->setText(QString("value = %1").arg(value));
}

void CalibrateWindow::slider2_change(int value)
{
	treshold_2 = value;
	state_change();
	slider2_label->setText(QString("value = %1").arg(value));
}

void CalibrateWindow::slider3_change(int value)
{
	treshold_3 = value;
	vslider1_label->setText(QString("value = %1").arg(value));
	if (calibrate_state == TRM_STATE_EDGE && a_equal->isChecked())
	{
		vslider2->setValue(value);
	}
	else
	{
		state_change();
	}
}

void CalibrateWindow::slider4_change(int value)
{
	treshold_4 = value;
	vslider2_label->setText(QString("value = %1").arg(value));
	state_change();
}

void CalibrateWindow::chk1_change()
{
	if (chk1->isChecked())
	{
		if (calibrate_state == TRM_STATE_EDGE)
		{
			slider2->setValue(slider1->value()/3);
			slider2->setEnabled(!chk1->isChecked());
		}
		else if (calibrate_state == TRM_STATE_CORNER)
		{
			;
		}
	}
	else
	{
		if (calibrate_state == TRM_STATE_EDGE)
		{
			slider2->setEnabled(!chk1->isChecked());
		}
		else if (calibrate_state == TRM_STATE_CORNER)
		{
			;
		}
	}
	if (calibrate_state == TRM_STATE_RESULT )
	{
		slider1->setEnabled(chk1->isChecked());
	}
	state_change();
}

void CalibrateWindow::chk2_change()
{
	state_change();
}

void CalibrateWindow::equal_clicked(bool state)
{
	state_change(0);
}

void CalibrateWindow::mclose_clicked(bool state)
{
	if (state)
	{
		a_mreversed->setChecked(false);
		a_mopen->setChecked(false);
		a_mnormal->setChecked(false);
		morphology_state = MORPH_STATE_CLOSE;
		state_change(0);
	}
	else
	{
		a_mclose->setChecked(true);
	}
}

void CalibrateWindow::mopen_clicked(bool state)
{
	if (state)
	{
		a_mclose->setChecked(false);
		a_mreversed->setChecked(false);
		a_mnormal->setChecked(false);
		morphology_state = MORPH_STATE_OPEN;
		state_change(0);
	}
	else
	{
		a_mopen->setChecked(true);
	}
}

void CalibrateWindow::mnormal_clicked(bool state)
{
	if (state)
	{
		a_mclose->setChecked(false);
		a_mreversed->setChecked(false);
		a_mopen->setChecked(false);
		morphology_state = MORPH_STATE_NORMALL;
		state_change(0);
	}
	else
	{
		a_mnormal->setChecked(true);
	}
}

void CalibrateWindow::mreversed_clicked(bool state)
{
	if (state)
	{
		a_mclose->setChecked(false);
		a_mopen->setChecked(false);
		a_mnormal->setChecked(false);
		morphology_state = MORPH_STATE_REVERSED;
		state_change(0);
	}
	else
	{
		a_mreversed->setChecked(true);
	}
}

void CalibrateWindow::save_clicked()
{
	filename = QFileDialog::getSaveFileName(this, "Save File", "","");
	if (!filename.isEmpty() && !imageView.isNull())
	{
		QPixmap::fromImage(imageView).save(filename.toLocal8Bit().data(),"PNG",100);
	}
}

void CalibrateWindow::back_clicked()
{
	if (calibrate_state == TRM_STATE_FRAME)
	{
		close();
	}
	else if (calibrate_state == TRM_STATE_EDGE)
	{
		if (isVideo)
		{
			calibrate_state = TRM_STATE_FRAME;
			state_change(1);
			slider1->setValue(filter_param.frame_num);
			slider2->setValue(filter_param.calibre_width);
			option_menu->removeAction(a_equal);
			option_menu->addAction(a_width);
			morphology_menu->setEnabled(false);
		}
		else
		{
			close();
		}
	}
	else if (calibrate_state == TRM_STATE_CORNER)
	{
		if (image != NULL)
		{
			cvReleaseImage(&image);
		}
		image = cvCreateImage( cvGetSize(imagesrc), 8, 1 );
		cvCvtColor( imagesrc, image, CV_BGR2GRAY );
		calibrate_state = TRM_STATE_EDGE;
		state_change(1);
		chk2->setChecked(false);
		slider1->setValue(filter_param.edge_1);
		slider2->setValue(filter_param.edge_2);
		vslider1->setValue(filter_param.erode);
		vslider2->setValue(filter_param.dilate);
		morphology_state = filter_param.morph_algorithm;
		option_menu->addAction(a_equal);
		option_menu->removeAction(a_loop);
		morphology_menu->setEnabled(true);
	}
	else if (calibrate_state == TRM_STATE_RESULT)
	{
		if (image != NULL)
		{
			cvReleaseImage(&image);
		}

		image = cvCreateImage( cvGetSize(imagesrc), 8, 1 );
		cvCvtColor( imagesrc, image, CV_BGR2GRAY );
		if (filter_param.erode)
			cvErode( image, image , NULL , filter_param.erode );
		if (filter_param.dilate)
            cvDilate( image, image , NULL , filter_param.dilate );

        image = trmMark::doCanny( image, filter_param.edge_1 ,filter_param.edge_2);

		calibrate_state = TRM_STATE_CORNER;

		option_menu->addAction(a_loop);
		option_menu->setEnabled(true);

		state_change(1);
		slider1->setValue(filter_param.bold);
		vslider1->setValue(filter_param.corner_min);
        slider2->setValue(filter_param.narrow);
        chk1->setChecked(filter_param.edge_corner);
		next_btn->setText("Next");
	}
}

void CalibrateWindow::next_clicked()
{
	if (imgout != NULL)
	{
		cvReleaseImage(&image);
		image = imgout;
		imgout = NULL;
	}
	if (calibrate_state == TRM_STATE_FRAME)
	{
		filter_param.frame_num = treshold_1;
		if (chk2->isChecked())
		{
			filter_param.calibre_width = treshold_1;
		}
		calibrate_state = TRM_STATE_EDGE;
		state_change(1);
		chk1->setChecked(true);
		chk2->setChecked(false);
		slider1->setValue(filter_param.edge_1);
		slider2->setValue(filter_param.edge_2);
		vslider1->setValue(filter_param.erode);
		vslider2->setValue(filter_param.dilate);
		morphology_state = filter_param.morph_algorithm;

		option_menu->addAction(a_equal);
		option_menu->removeAction(a_width);
		morphology_menu->setEnabled(true);
	}
	else if (calibrate_state == TRM_STATE_EDGE)
	{
		filter_param.edge_1 = treshold_1;
		filter_param.edge_2 = treshold_2;
		filter_param.erode = treshold_3;
		filter_param.dilate = treshold_4;
		filter_param.morph_algorithm = morphology_state;
		treshold_1 = 0;
		treshold_2 = 0;
		calibrate_state = TRM_STATE_CORNER;
		state_change(1);
        vslider1->setValue(filter_param.corner_min);
		slider1->setValue(filter_param.bold);
		slider2->setValue(filter_param.narrow);
        chk1->setChecked(filter_param.edge_corner);

		option_menu->removeAction(a_equal);
		option_menu->removeAction(a_width);
		option_menu->addAction(a_loop);
		morphology_menu->setEnabled(false);

	}
	else if (calibrate_state == TRM_STATE_CORNER)
	{
		filter_param.bold = treshold_1;
		filter_param.narrow = treshold_2;
		filter_param.corner_min = treshold_3;
        filter_param.edge_corner = chk1->isChecked();
		calibrate_state = TRM_STATE_RESULT;
		state_change(1);
		slider1->setEnabled(false);
		next_btn->setText("Finish");
        if (filter_param.maximum_error > 0)
        {
            chk1->setChecked(true);
            slider1->setEnabled(true);
            slider1->setValue(filter_param.maximum_error);
        }
		option_menu->removeAction(a_loop);
		option_menu->setEnabled(false);
	}
	else if (calibrate_state == TRM_STATE_RESULT)
	{
        if (chk1->isChecked())
            filter_param.maximum_error = treshold_1;
        else
            filter_param.maximum_error = -1;
        trmMark::Saveparam(filter_param,SETTING_FILENAME);
		close();
	}


}

void CalibrateWindow::replace_clicked()
{
	if (imgout != NULL)
	{
		cvReleaseImage(&image);
		cvReleaseImage(&imagesrc);
		image = imgout;
		imagesrc = cvCreateImage( cvGetSize(image), 8, 3 );
		cvCvtColor( image, imagesrc, CV_GRAY2BGR );
		imgout = NULL;
	}
}

void CalibrateWindow::open_clicked()
{
	filename = QFileDialog::getOpenFileName(this, "Open File", "","Videos (*.mp4 *.avi *.mov *.mod)");
	if (!filename.isEmpty())
	{
		isVideo = true;
		capture = cvCreateFileCapture( filename.toLocal8Bit().data() );
		if (capture == NULL)
			return;
		imagesrc = cvQueryFrame( capture );
		image = cvCreateImage( cvGetSize(imagesrc), 8, 1 );
		cvCvtColor( imagesrc, image, CV_BGR2GRAY );
		int diff = surface_height - floor((surface_width/image->width)*image->height);
		chk2->setChecked(false);

		calibrate_state = TRM_STATE_FRAME;

		option_menu->addAction(a_width);

		vslider1->setValue(0);
		chk1->setChecked(false);
		slider1->setValue(0);
		state_change(1);
		setMinimumHeight(minimumHeight()-diff);
		resize(minimumSize());
	}

}

void CalibrateWindow::openimage_clicked()
{
	filename = QFileDialog::getOpenFileName(this, "Open File", "","Images (*.png *.jpg)");
	if (!filename.isEmpty())
	{
		isVideo = false;
		imagesrc = cvLoadImage(filename.toLocal8Bit().data());
		image = cvLoadImage(filename.toLocal8Bit().data(),CV_LOAD_IMAGE_GRAYSCALE);
		calibrate_state = TRM_STATE_EDGE;
		chk1->setChecked(false);
		slider1->setValue(0);

		option_menu->addAction(a_equal);

		int diff = surface_height - floor((surface_width/image->width)*image->height);
		state_change(1);
		slider1->setValue(filter_param.edge_1);
		slider2->setValue(filter_param.edge_2);
		vslider1->setValue(filter_param.erode);
		vslider2->setValue(filter_param.dilate);
		chk2->setChecked(true);
		if ( filter_param.erode == filter_param.dilate && filter_param.dilate == 0 )
		{
			chk2->setChecked(false);
		}
		setMinimumHeight(minimumHeight()-diff);
		resize(minimumSize());
	}
}

void CalibrateWindow::width_clicked()
{
	filter_param.calibre_width = QInputDialog::getInt(this,"Diplay Width","Image Width (200,2000)",surface_width,200,2000);;
	int diff_x = surface_width - filter_param.calibre_width;
	surface_width = filter_param.calibre_width;
	int diff_y = surface_height - floor((surface_width/image->width)*image->height);
	surface_height = floor((surface_width/image->width)*image->height);
	state_change();
	setMinimumSize(minimumWidth() - diff_x,minimumHeight() - diff_y);
	resize(minimumSize());
}

void CalibrateWindow::CreateMenu()
{
	menu = new QMenuBar (this);
	//setMenuBar(menu);
	main_layout->setMenuBar(menu);

	file_menu = menu->addMenu("File");
	a_open = file_menu->addAction("Open");
	a_open_image = file_menu->addAction("Open Image");
	a_save = file_menu->addAction("Save");
	a_replace = file_menu->addAction("Replace");

	morphology_menu = menu->addMenu("Morphology");
	a_mnormal = morphology_menu->addAction("Normal");
	a_mreversed = morphology_menu->addAction("Reversed");
	a_mopen = morphology_menu->addAction("Open");
	a_mclose = morphology_menu->addAction("Close");

	option_menu = menu->addMenu("Option");
	a_equal = new QAction("Erode = Dilate",NULL);
	a_width = new QAction("Set Width",NULL);
	a_loop = new QAction("Show All Corner",NULL);


	a_equal->setCheckable(true);
	a_loop->setCheckable(true);
	a_mclose->setCheckable(true);
	a_mopen->setCheckable(true);
	a_mreversed->setCheckable(true);
	a_mnormal->setCheckable(true);

	calibrate_state = TRM_STATE_EDGE;
	a_equal->setChecked(true);
	a_mnormal->setChecked(true);
	morphology_menu->setEnabled(false);

	help_menu = menu->addMenu("Help");
	a_about = help_menu->addAction("About");
}

void CalibrateWindow::CreateLayout(QWidget *parent)
{
	//Default
	imgout = NULL;
	surface = new QLabel();
	main_layout = new QVBoxLayout;
	Main_Widget = new QWidget;
	chk1 = new QCheckBox("prop 3");
	chk2 = new QCheckBox("option 2");
	chk2->setChecked(true);

	slider1_layout = new QHBoxLayout;
	slider1_label = new QLabel("value = 0");
	slider1 = new QSlider(Qt::Horizontal);
	slider1->setMaximum(1000);
	slider1_layout->addWidget(slider1_label);
	slider1_layout->addWidget(slider1);
	slider1_layout->addWidget(chk1);

	slider2_layout = new QHBoxLayout;
	slider2_label = new QLabel("value = 0");
	slider2 = new QSlider(Qt::Horizontal);
	slider2->setMaximum(1000);
	slider2_layout->addWidget(slider2_label);
	slider2_layout->addWidget(slider2);
	slider2_layout->addWidget(chk2);

	vslider1_layout = new QVBoxLayout;
	vslider1_label = new QLabel("value = 0");
	vslider1 = new QSlider();
	vslider1->setMaximum(30);
	vslider1_layout->addWidget(vslider1);
	vslider1_layout->addWidget(vslider1_label);

	vslider2_layout = new QVBoxLayout;
	vslider2_label = new QLabel("value = 0");
	vslider2 = new QSlider();
	vslider2->setMaximum(30);
	vslider2_layout->addWidget(vslider2);
	vslider2_layout->addWidget(vslider2_label);

	surface_layout = new QHBoxLayout;
	surface_layout->addLayout(vslider1_layout);
	surface_layout->addLayout(vslider2_layout);
	surface_layout->addWidget(surface);

	//Button
	button_layout = new QHBoxLayout;
	back_btn = new QPushButton("Back");
	replace_btn = new QPushButton("Replace");
	next_btn = new QPushButton("Next");
	button_layout->addWidget(back_btn);
	button_layout->addWidget(replace_btn);
	button_layout->addWidget(next_btn);
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
	//default
	treshold_1 = 0;
	treshold_2 = 0;
	treshold_3 = 0;
	treshold_4 = 0;
	morphology_state = MORPH_STATE_NORMALL;
	surface_width = filter_param.calibre_width;


	if ( filter_param.erode == filter_param.dilate && filter_param.dilate == 0 )
	{
		chk2->setChecked(false);
	}

	//Window
	setLayout(main_layout);
	setWindowTitle(trUtf8("Calibration"));
	//setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::Window);
	//setSizePolicy(QSizePolicy::Minimum);
	//setLayoutDirection(Qt::RightToLeft);
}

void CalibrateWindow::MyFilledCircle( cv::Mat img, cv::Point center )
{
	int thickness = 3;
	int lineType = 8;

	cv::circle( img, center, 10.0, 255, thickness, lineType );
}

trmParam CalibrateWindow::start(int startFrame)
{
	if (startFrame && isVideo)
	{
		filter_param.frame_num = startFrame;
		slider1->setValue(filter_param.frame_num);
	}
	exec();
	return filter_param;
}

void CalibrateWindow::find_corner(IplImage* in ,double quality_level ,double min_distance ,int MAX_CORNERS , double k )
{
	cv::Mat grayFrame;
	std::vector<cv::Point2f> corners;
	grayFrame = cv::Mat(in);
	cv::goodFeaturesToTrack(grayFrame, corners, MAX_CORNERS, quality_level,  min_distance ,cv::noArray() ,10,false,k);
	for (int i = 0 ; i < MAX_CORNERS ; i++)
	{
		MyFilledCircle(grayFrame,corners[i]);
	}
	IplImage out = grayFrame;
	imageView = QImage((const unsigned char*)(out.imageData), out.width,out.height,QImage::Format_Indexed8).rgbSwapped();
	surface->setPixmap(QPixmap::fromImage(imageView.scaled(surface_width,floor((surface_width/imageView.width())*imageView.height()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
}

void CalibrateWindow::drawMark(cv::Mat img ,CvPoint pt,CvScalar color)
{
	int height = floor(img.rows / 100.0);
	cv::line(img,cvPoint(pt.x - height,pt.y),cvPoint(pt.x + height,pt.y),color,2);
	cv::line(img,cvPoint(pt.x,pt.y - height),cvPoint(pt.x,pt.y + height),color,2);
}
