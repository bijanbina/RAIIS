#ifndef RE_WIN32_ACC_H
#define RE_WIN32_ACC_H

#include <oleacc.h>
#include <QDebug>

typedef struct ReElemSpec
{
    IAccessible *pAcc;
    QString name;
}ReElemSpec;

void reListChildren(IAccessible *pAcc, QString path);
QString reGetAccName(IAccessible *pAcc, long childId);
long reGetChildCount(IAccessible *pAcc);
IAccessible* reGetPAcc(HWND hWnd);
IAccessible* reFindAcc(QString path, IAccessible *pAcc);

#endif // RE_WIN32_ACC_H
