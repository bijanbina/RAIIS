#ifndef RE_WINDOW_W_H
#define RE_WINDOW_W_H

#include <QStringList>

#include "re_state.h"
#include "re_win32_acc.h"
#include "re_win32_win.h"
#include "re_callback_w.h"

#define RE_SPOTIFY_ALBUM_CHILD  "0000"
#define RE_SPOTIFY_ALBUM_PARENT "301000000201201"

#define RE_EXPLORER_ID 0
#define RE_FIREFOX_ID  1
#define RE_SPOTIFY_ID  2

#define MM_MINWIN_HEIGHT   600
#define MM_MINWIN_WIDTH    100
#define MM_MINWIN_OPACITY  100

class ReWindowW : public QObject
{
    Q_OBJECT
public:
    explicit ReWindowW();
    void cleanWins();
    void clearWins();
    void addHwnd(HWND hwnd);
    void applyOpacity(ReWindow win);
    void updateRemoteID(ReWindow win);
    void updateActiveWindow();
    void handleNewWin(ReWindow win);

    QVector<ReWindow> windows;
    ReWindow          win_active;

public slots:
    void    start();

private:
};

#endif // RE_WINDOW_W_H
