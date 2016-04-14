#ifndef RECWINDOW_H
#define RECWINDOW_H

#include <QMainWindow>
#include <opencv/highgui.h>
#include <QtWidgets>
#include <cv.h>
#include <sys/time.h>
#include "trmmark.h"

#define TEMP_VIDEO_ADDRESS "/tmp/tremor.mpg"

void *capture_main(void *data);
void *record_main(void *data);

class RecWindow : public QDialog {
    Q_OBJECT
public:
    explicit RecWindow(QWidget *parent = 0);
    ~RecWindow();

    //Need external access for record function
    QImage        imageView;
    IplImage     *imagesrc;
    IplImage     *NA_image;
    CvCapture    *capture;
    QLabel       *surface;
    QLabel       *info_fps;
    QLabel       *info_time;
    QLabel       *info_frameNum;
    QAction		 *a_preview;
    double        surface_width;
    bool          thread_cam_active;
    bool          isRec;
    bool          doAnalysis;

protected:
    char        *FileOpName; //declare FileOpName as IplImage

    void resizeEvent ( QResizeEvent * event )
    {
        setGeometry((qApp->desktop()->geometry().center() - rect().center()).x(),(qApp->desktop()->geometry().center() - rect().center()).y(),rect().width(),rect().height());
    }

private slots:
    void slider1_change(int);
    void slider2_change(int);
    void open_clicked();
    void save_clicked();
    void rec_clicked();
    void exit_clicked();
    void analysis_clicked();
    void afocus_changed(bool state);
    void preview_changed(bool state);

private:
    void        CreateLayout(QWidget *parent);
    void        CreateMenu();
    QStringList getDeviceName();

    QMenuBar     *menu;
    QMenu        *file_menu;
    QMenu		 *option_menu;
    QMenu		 *help_menu;
    QAction		 *a_save;
    QAction		 *a_open;
    QAction		 *a_open_image;
    QAction		 *a_replace;
    QAction		 *a_about;
    QAction		 *a_focus;
    QAction		 *a_asave;
    QAction		 *a_mclose;
    IplImage     *image;
    IplImage     *imgout;
    QVBoxLayout  *main_layout;
    QHBoxLayout  *slider1_layout;
    QLabel       *slider1_label;
    QWidget      *Main_Widget;
    QSlider      *slider1;
    QSlider      *slider2;
    QHBoxLayout  *slider2_layout;
    QLabel       *slider2_label;
    QVBoxLayout  *info_layout;
    QHBoxLayout  *surface_layout;
    QVBoxLayout  *surface2_layout;
    QHBoxLayout  *option_layout;
    QHBoxLayout  *chkbox_layout;
    QHBoxLayout  *button_layout;
    QPushButton  *rec_btn;
    QPushButton  *save_btn;
    QPushButton  *analysis_btn;
    QString       filename;
    double        treshold_1;
    double        treshold_2;
    int           framePosition;
    int           surface_height;
    int           count;
    bool          isVideo;
    trmParam      filter_param;
    pthread_t     thread_cam;
    pthread_t     thread_rec;
    int           camID;
};


#endif // RECWINDOW_H
