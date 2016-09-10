#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <QObject>

class UiHandler : public QObject
{
    Q_OBJECT
public:
    explicit UiHandler(QObject *ui, QObject *parent = 0);

signals:

public slots:

private:
    QObject *root;
};

#endif // UIHANDLER_H
