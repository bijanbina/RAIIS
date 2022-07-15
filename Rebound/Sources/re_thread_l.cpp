#include "re_thread_l.h"
#include <QThread>

#define re_state_mode thread_data->state->i_mode

int counter = 0;
int child_num = 3;

void ReThreadL::enumWindows()
{
    Window* children;
    unsigned long nchildren;

    children = x11_getWinList(&nchildren);
    int desktop_id = x11_currentDesktop();

    char *name;

    if (!children)
        return;

    for ( unsigned long i=0 ; i<nchildren ; i++ )
    {
        XFetchName(display, children[i], &name);
        if ( name ) // Name may be null as in GitKraken
        {
            if( !strcmp(name, "Desktop") )
            {
                continue;
            }
        }
        int win_desktop = x11_getDesktop(children[i]);
        if ( win_desktop==desktop_id )
        {
            addWindow(children[i]);
        }
    }

    XFree(children);
}

//Add a new Hwnd to wins_title vector
void ReThreadL::addWindow(Window window)
{
    ReWindow buf;
    XTextProperty name;

    XGetWMName(display, window, &name);
    buf.desktop_id = x11_getDesktop(window);
    buf.title = QString((char *)name.value);
    buf.pid = x11_getPid(window);
    buf.pname = x11_getPname(buf.pid);
    buf.hWnd = window;
    insertWindow(buf);
}

void ReThreadL::insertWindow(ReWindow win)
{
    //push active window to front
    if ( win.hWnd==HwndA )
    {
//        qDebug() << win.hWnd << HwndA << win.pname;
        if ( windows.size() )
        {
            if ( windows[0].hWnd!=win.hWnd )
            {
                windows.push_front(win);

#ifdef RE_DEBUG_WIN
                qDebug() << "Active Changed" << win.title;
#endif
            }
            else
            {
                windows[0].verify = 1;
                windows[0].title = win.title;
            }
            thread_data->state->updateApp(win);
        }
        else
        {
            windows.push_front(win);
            thread_data->state->updateApp(win);
            qDebug() << "First Time" << win.title;
            return;
        }
    }

    for( int i=1 ; i<windows.size() ; i++ )
    {
        if ( windows[i].hWnd==HwndA )
        {
            windows.remove(i);
            i--;
        }
        else if ( windows[i].hWnd==win.hWnd )
        {
            windows[i].verify = 1;
            windows[i].title = win.title;
//            qDebug() << "Ver Window" << i << win.title;
            return;
        }
    }

    if ( win.hWnd!=HwndA )
    {
        windows.push_back(win);
#ifdef RE_DEBUG_WIN
        qDebug() << "New Window" << win.hWnd;
#endif
    }

}

int ReThreadL::getIndex(QString app_name)
{
    for( int i=0 ; i<windows.size() ; i++ )
    {
        if(windows[i].pname.contains(app_name, Qt::CaseInsensitive))
        {
            return i;
        }
    }
    return -1;
}

ReWindow ReThreadL::getWinSpec(QString title)
{
    for(int i=0; i<windows.size(); i++)
    {
        if( title==windows[i].title )
        {
            return windows[i];
        }
    }

    ReWindow shit;
    return shit;
}

QString ReThreadL::getWinTitle(int index)
{
    if( index<windows.size() )
    {
        return windows[index].title;
    }
    return "";
}


ReThreadL::ReThreadL(threadStruct *thread_data)
{
    this->thread_data = thread_data;
    display = XOpenDisplay(NULL);
}

//clear verify flag
void ReThreadL::clearWins()
{
    for( int i=0 ; i<windows.size() ; i++ )
    {
        windows[i].verify = 0;
    }
}

//clean-up windows
void ReThreadL::cleanWins()
{
    for( int i=0 ; i<windows.size() ; i++ )
    {
        if( windows[i].verify==0 )
        {
#ifdef RE_DEBUG_WIN
            qDebug() << "Remove Window" << windows[i].title;
#endif
            windows.remove(i);
            i--;
        }
    }
}

void ReThreadL::syncWinsTitle()
{
    for(int i=0; i<windows.size(); i++)
    {
        if( i<thread_data->wins_title->size() )
        {
            (*(thread_data->wins_title))[i] = windows[i].title;
            thread_data->windows[i] = windows[i];
        }
        else
        {
            thread_data->wins_title->push_back(windows[i].title);
            thread_data->windows.push_back(windows[i]);
        }
    }

    for(int i=windows.size(); i<thread_data->wins_title->size(); i++)
    {
        thread_data->wins_title->removeAt(i);
        i--;
    }
}

void ReThreadL::updateActiveWindow()
{
    HwndA = x11_currentWindow();
    //XFetchName will not always work, XGetWMName used instead
    XTextProperty buffer;
    int written = XGetWMName(display, HwndA, &buffer);
    char *buffer_c = (char *)buffer.value;

    titleA = buffer_c;
}

void reRunThread(void *thread_struct_void)
{
    int cntr = 0;
    threadStruct *thread_data = (threadStruct *)thread_struct_void;
    ReThreadL *priv = new ReThreadL(thread_data);

    while( 1 )
    {
        if( cntr>200 )
        {
            if( re_state_mode==RE_MODE_HIDDEN )
            {
                //Get Active Window Name
                priv->updateActiveWindow();

                priv->clearWins();
                priv->enumWindows();
                priv->cleanWins();
                priv->syncWinsTitle();
            }
            else if( re_state_mode==RE_MODE_MAIN )
            {
//                priv->syncElemsName();
            }
            cntr = 0;
        }
        if( !thread_data->message.isEmpty() )
        {
            if(thread_data->message == "Launch Nuclear missiles")
            {
                qDebug() << "Launched";
            }
            thread_data->message.clear();
        }
        cntr++;
        QThread::msleep(2);
    }
}
