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

    printf("Desktop: %d\n", desktop_id);
    char *name;

    if (!children)
        return;

    for ( unsigned long i=0 ; i<nchildren ; i++ )
    {
        XFetchName(display, children[i], &name);
        if ( name )
        {
            if(!strcmp(name, "Desktop"))
            {
                continue;
            }
            int win_desktop = x11_getDesktop(children[i]);
            if ( win_desktop==desktop_id )
            {
                addWindow(children[i]);
            }
        }
    }

    XFree(children);
}

//Add a new Hwnd to wins_title vector
void ReThreadL::addWindow(Window window)
{
    ReWindow buf;
    char *name;

    XFetchName(display, window, &name);
    buf.desktop_id = x11_getDesktop(window);
    buf.title = name;
    buf.pid = x11_getPid(window);
    buf.pname = x11_getPname(buf.pid);
    printf("%d: <%s> pid=%d pname=%s\n", buf.desktop_id, name,
           buf.pid, buf.pname.toStdString().c_str());
    XFree(name);
}

void re_InsertWindow(ReThreadL *thread_w, ReWindow win)
{
    ;
}

QString ReThreadL::cleanTitle(QString app_title)
{
    QStringList title_split = app_title.split('-', QString::SkipEmptyParts);
    QString app_name = renameAppName(title_split.last().simplified());
    QStringList filename_split = title_split[0].split(" ", QString::SkipEmptyParts);
    app_title = app_name + ": " + title_split[0].simplified();
    if(filename_split.size()>1)
    {
        app_title += " " + filename_split[1].simplified();
    }
    return app_title;
}

QString ReThreadL::renameAppName(QString app_name)
{
    if(app_name.contains("qt", Qt::CaseInsensitive))
    {
        return "Qt";
    }
    else if(app_name.contains("foxit", Qt::CaseInsensitive))
    {
        return "Foxit";
    }
    else if(app_name.contains("firefox", Qt::CaseInsensitive))
    {
        return "Firefox";
    }
    else if(app_name.contains("spotify", Qt::CaseInsensitive))
    {
        return "Spotify";
    }
    else if(app_name.contains("excel", Qt::CaseInsensitive))
    {//////
        return "Excel";
    }
    else if(app_name.contains("snip", Qt::CaseInsensitive))
    {
        return "Snip";
    }
    return app_name;
}

void ReThreadL::sortApp()
{
    QVector<ReWindow> sorted_apps, unsorted_apps;
    int clover_ind = 0, firefox_ind = 0, spotify_ind = 0;
    for( int i=0 ; i<windows.size() ; i++)
    {
        if(windows[i].pname.contains("Clover", Qt::CaseInsensitive))
        {
            sorted_apps.insert(clover_ind, windows[i]);
            clover_ind++; firefox_ind++; spotify_ind++;
        }
        else if(windows[i].pname.contains("Firefox", Qt::CaseInsensitive))
        {
            sorted_apps.insert(firefox_ind, windows[i]);
            firefox_ind++; spotify_ind++;
        }
        else if(windows[i].pname.contains("Spotify", Qt::CaseInsensitive))
        {
            sorted_apps.insert(spotify_ind, windows[i]);
            spotify_ind++;
        }
        else
        {
            unsorted_apps.push_back(windows[i]);
        }
    }
    windows = sorted_apps + unsorted_apps;
}

void reListChildren(QString path)
{
    qDebug() <<"####### Exit getChildren - acc path : " << path;
}

QString reGetPName(long pid)
{
    ;
}

void ReThreadL::getHWND(QString appname)
{
    return;
}

long reGetPid()
{
    // get allegro pid of window handle
    long dwProcessId;

    return dwProcessId;
}

long reGetChildCount()
{
    long cc;
    return cc;
}

void reGetPAcc()
{
    ;
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

QString reGetAccName(long childId)
{
    return QString("");
}

ReElemSpec* ReThreadL::getElemSpec(QString name)
{
    for(auto e: elems_spec)
    {
        if(e->name == name)
        {
            return e;
        }
    }
    return NULL;
}

ReWindow ReThreadL::getWinSpec(QString title)
{
    for(int i=0; i<windows.size(); i++)
    {
        if(title == windows[i].title)
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

QString ReThreadL::getElemName(int index)
{
    if(index < elems_spec.size())
    {
        return elems_spec[index]->name;
    }
    return "";
}

// return Acc specific chilren
void reFindAcc(QString path)
{
    ;
}

void ReThreadL::updateElements(QString app_name, QString parent_path,
                               QString child_path)
{
    qDebug() << "updateElements" << app_name;
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
            qDebug() << "Remove Window" << windows[i].title;
            windows.remove(i);
            i--;
        }
    }
}

void ReThreadL::cleanElems()
{
    for(auto e : elems_spec)
    {
        delete e;
    }
    elems_spec.clear();
    elems_name.clear();
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

void ReThreadL::syncElemsName()
{
    for(int i=0; i<elems_name.size(); i++)
    {
        if(i < thread_data->elems_name->size())
        {
            (*(thread_data->elems_name))[i] = elems_name[i];
        }
        else
        {
            thread_data->elems_name->push_back(elems_name[i]);
        }
    }

    while( elems_name.size()<thread_data->elems_name->size() )
    {
        thread_data->elems_name->pop_front();
    }
}

void ReThreadL::updateActiveWindow()
{
    char buffer[128];
    titleA = buffer;
}

void reRunThread(void *thread_struct_void)
{
    qDebug() << "thread start";
    int cntr = 0;
    threadStruct *thread_data = (threadStruct *)thread_struct_void;
    ReThreadL *priv = new ReThreadL(thread_data);

    while(1)
    {
        if(cntr > 200)
        {
            if(re_state_mode == RE_MODE_HIDDEN)
            {
                //Get Active Window Name
                priv->updateActiveWindow();

                priv->clearWins();
//                EnumWindows(EnumWindowsProc, (LPARAM) priv);
                priv->cleanWins();
                priv->syncWinsTitle();
            }
            else if(re_state_mode == RE_MODE_MAIN)
            {
                priv->cleanElems();
                priv->updateElements("spotifys", RE_SPOTIFY_ALBUM_PARENT,
                                     RE_SPOTIFY_ALBUM_CHILD);
                priv->syncElemsName();
            }
            cntr = 0;
        }
        if(!thread_data->message.isEmpty())
        {
            if(thread_data->message == "Launch Nuclear missiles")
            {
                qDebug() << "Launched";
            }
            thread_data->message.clear();
        }
        cntr++;
        QThread::msleep(500);
    }
}
