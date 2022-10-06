#include "re_win32_acc.h"

void reListChildren(IAccessible *pAcc, QString path)
{
    QString pAcc_name = reGetAccName(pAcc, CHILDID_SELF);
    qDebug() << "####### getChildren - acc path : " + pAcc_name;

    long childCount;
    long returnCount;
    HRESULT hr = pAcc->get_accChildCount(&childCount);
    VARIANT* pArray = new VARIANT[childCount];
    hr = AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);
    path += QString("/");

    for (int x = 0; x < returnCount; x++)
    {
        VARIANT vtChild = pArray[x];
        if (vtChild.vt == VT_DISPATCH)
        {
            IDispatch* pDisp = vtChild.pdispVal;
            IAccessible* pChild = NULL;
            hr = pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
            if (hr == S_OK)
            {
                QString child_name = reGetAccName(pChild, CHILDID_SELF);
                long child_count = reGetChildCount(pChild);
                qDebug() << "-> acc path : " + pAcc_name +
                            " - child[" + QString::number(x) + "/" +
                            QString::number(returnCount-1) + "], childname:" +
                            child_name + "child count" +
                            QString::number(child_count) +
                            " path:" + path + QString::number(x);
                if(child_count>0)
                {
                    reListChildren(pChild, path + QString::number(x));
                }
                pChild->Release();
            }
            pDisp->Release();
        }
        // Else it's a child element so we have to call accNavigate on the parent,
        //   and we do not recurse because child elements can't have children.
        else
        {
            qDebug() <<"-> acc path : " + pAcc_name +
                        " - child[" + QString::number(x) + "/" +
                       QString::number(returnCount-1) +
                        "] ELEMENT - " + reGetAccName(pAcc, vtChild.lVal)
                        + " path:" + path + QString::number(x);
        }
    }
    delete[] pArray;
    qDebug() <<"####### Exit getChildren - acc path : " + pAcc_name;
}

QString reGetAccName(IAccessible *pAcc, long childId)
{
    BSTR bstrName;
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = childId;
    /*HRESULT hr = */pAcc->get_accName(varChild, &bstrName);
    return QString::fromWCharArray(bstrName);
}

long reGetChildCount(IAccessible *pAcc)
{
    long cc;
    pAcc->get_accChildCount(&cc);
    return cc;
}

IAccessible* reGetPAcc(HWND hWnd)
{
    IAccessible *pAcc;

    AccessibleObjectFromWindow(hWnd, OBJID_WINDOW,
                               IID_IAccessible, (void**) &pAcc);
    if(pAcc == NULL)
    {
        qDebug() <<"Error: window is not open now, open it and try again ... !";
        return pAcc;
    }
    return pAcc;
}

// return Acc specific chilren
IAccessible* reFindAcc(QString path, IAccessible *pAcc)
{
    VARIANT vtChild;
    if( path.size()>0 )
    {
        long childCount = reGetChildCount(pAcc);
        long returnCount;
        VARIANT* pArray = new VARIANT[childCount];

        AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);

        int indx = QString(path.at(0)).toInt();
        vtChild = pArray[indx];

        qDebug() << QString("--path:") + path + " childCount:" +
                    QString::number(childCount) + " " +
                    reGetAccName(pAcc, CHILDID_SELF) +
                    " indx:" + QString::number(indx) + " " +
                    QString::number(returnCount);

        // return if path is not correct
        if(indx > childCount)
        {
            qDebug() <<"path is not correct, index greater than child";
            return NULL;
        }

        if(vtChild.vt != VT_DISPATCH)
        {
            qDebug() <<"path is not correct, child is element, not Acc";
            return NULL;
        }

        IDispatch* pDisp = vtChild.pdispVal;
        IAccessible* pChild = NULL;
        pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);

        return reFindAcc(path.mid(1), pChild);
    }
    else
    {
        return pAcc;
    }
}

