#include "backend.h"
#include <QThread>

assistant_options option;

int getIntCommand(char *command)
{
    FILE *fp;
    int returnData;

    char path[1035];

    /* Open the command for reading. */
    fp = popen(command, "r");

    if (fp == NULL) {
      printf("Failed to run command\n" );
      return -1;
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
      returnData = atoi(path);
    }

    /* close */
    pclose(fp);
    return returnData;
}

QString getStrCommand(QString command)
{
    FILE *fp;
    QString returnData;

    char path[1035];

    /* Open the command for reading. */
    fp = popen(command.toStdString().c_str(), "r");

    if (fp == NULL) {
      printf("Failed to run command\n" );
      return returnData;
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
      returnData = QString(path);
    }

    returnData.remove('\n');

    /* close */
    pclose(fp);
    return returnData;
}

screen_pos getPrimaryScreen()
{
    FILE *fp;
    screen_pos returnData;
    returnData.x = -1;
    returnData.y = -1;
    returnData.x = getIntCommand("xrandr --current | grep primary | awk '{print $4}' | awk -F '+' '{print $2}'");
    returnData.y = getIntCommand("xrandr --current | grep primary | awk '{print $4}' | awk -F '+' '{print $3}'");
    return returnData;
}

void updateScreenInfo(QObject *item)
{
    screen_pos PrimaryScreen = getPrimaryScreen();
    QQmlProperty::write(item, "x_base", PrimaryScreen.x);
    QQmlProperty::write(item, "y_base", PrimaryScreen.y);
//    int minimumWidth = QQmlProperty::read(item, "minimumWidth");
//    int minimumHeight = QQmlProperty::read(item, "minimumHeight");
//    x:x_base + (Screen.width  - minimumWidth)  / 2
//    y:y_base + (Screen.height - minimumHeight) / 2
    QQmlProperty::write(item, "visible", 1);
    //QMetaObject::invokeMethod(item, "show");
}

assistant_options loadOptions()
{

}

