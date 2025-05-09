#ifndef AJ_DLLGEN_H
#define AJ_DLLGEN_H

#include <QFile>
#include <QDir>
#include <windows.h>

void aj_dllGen();
void aj_setWorkingDir();
void aj_fillBatFile(QFile *bat_file);
void aj_addCopyDllCmds(QFile *bat_file, QString project_path);
void aj_addLuaDll(QFile *bat_file, QString project_path);
int  aj_qmlExist(QString path);
QString aj_getQtCompiler();
QString aj_getQtPath();
QString aj_getQtShortCut();
QString aj_getExePath(QString name);
QString aj_findCompiler(QString pattern, QString dirname);
QString aj_findQtShortcut(QString dirname);
QString aj_getFirstDir(QString path);
QString aj_makeToolsPath();
QStringList aj_listGccCompilers(QString tools_path);
QStringList aj_getConfList();
QFileInfoList aj_searchDir(QString path, QString pattern,
                           QDir::Filters filter);

//following functions duplicated to maintain single header/cpp for dll gen
//main implementation exist in aj_application
QString dl_getLinkPathA(QString name);
QString dl_getLinkPathB(QString name);
HRESULT dl_resolveIt(LPCSTR lnk_path, char *target);
QString dl_findAppPath(QString path, QString pattern);

#endif // AJ_DLLGEN_H
