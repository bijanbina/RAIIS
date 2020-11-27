#ifndef RE_THREAD_L_H
#define RE_THREAD_L_H

#include <QStringList>

#include "re_state.h"

#define RE_SPOTIFY_ALBUM_CHILD  "0000"
#define RE_SPOTIFY_ALBUM_PARENT "301000000201201"

#define RE_EXPLORER_ID 0
#define RE_FIREFOX_ID  1
#define RE_SPOTIFY_ID  2

typedef struct ReElemSpec
{
    QString name;
}ReElemSpec;

typedef struct threadStruct
{
    QString  message;
    ReState *state;
    QStringList *wins_title;
    QStringList *elems_name;
    QVector<ReWinSpec> windows;
}threadStruct;

class ReThreadL
{
public:
    ReThreadL(threadStruct *thread_data);
    void cleanWins();
    void clearWins();
    void cleanElems();
    void updateElements(QString app_name, QString parent_path, QString child_path);
    void selectButton(QString name);
    QString cleanTitle(QString title);
    void sortApp();
    void syncWinsTitle();
    void syncElemsName();
    void updateActiveWindow();


    QVector<ReWinSpec> windows;
    threadStruct *thread_data;
    QStringList elems_name;
    QString titleA;
    long HwndA;

private:
    ReElemSpec* getElemSpec(QString name);
    ReWinSpec getWinSpec(QString title);
    int getIndex(QString app_name);
    void getHWND(QString title);
    QString renameAppName(QString app_name);

    QVector<ReElemSpec*> elems_spec;
    QString getElemName(int index);
    QString getWinTitle(int index);
};

void re_AddHwnd(ReThreadL *thread_w);
void re_InsertWindow(ReThreadL *thread_w, ReWinSpec win);

long reGetPid();
QString reGetPName(long pid);
void reGetPAcc();
long reGetChildCount();
void reListChildren(QString path);
QString reGetAccName(long childId);
void reFindAcc(QString path);
int reSelectButton(QString name);

void reRunThread(void *thread_struct_void);
void reCleanWins(threadStruct *thread_data);
void reCleanElems(threadStruct *thread_data);

#endif // RE_THREAD_L_H
