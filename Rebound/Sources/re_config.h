#ifndef RE_CONFIG_H
#define RE_CONFIG_H

#define COM_NAME        "com.binaee.rebound"
#define ORG_NAME        "org.binaee.rebound"
#define PIPE_PATH       "\\\\.\\pipe\\com_binaee_rebound"
#define CH_PIPE_PATH    "\\\\.\\pipe\\com_binaee_chess"
#define CH_PIPE_MOM     "\\\\.\\pipe\\com_binaee_mom"
#define CH_NP_SEPARATOR ","

#define RE_FIREFOX_DIR   "Scripts\\Firefox"
#define MOM_LABEL_DIR    "..\\..\\Benjamin\\Mom\\Labels"
#define MOM_LABEL_PNAME  "\\r1_pname.lbl"
#define MOM_LABEL_STATUS "\\r2_status.lbl"

//#define RE_DEBUG_WIN //show window detection debug info

#define RE_CLIENT 0
#define RE_SERVER 1

#define RE_PORT      7610
#define RE_IP        "192.168.88.25"

//#define RE_TEST_EN
//#define RE_DUBUG_TCP

#define RE_TIMEOUT        1000
#define RE_WATCHDOG       1000  //Watchdog interval
#define RE_Live           100   //Live send interval
#define RE_CHECK_BTN      4     //Live send interval
#define RE_CHECK_IN       4     //check input(native mode)
#define RE_TAB_TIME       900   //Alt pressed time
#define RE_EXEC_TIMEOUT   2100  //Command execution timeout
#define RE_VIRT_TIMEOUT   300   //Command virtual index timeout

#define RE_SCR_UI      1     //UI Mode
#define RE_SCR_YOUTUBE 2     //YouTube Mode
#define RE_SCR_SPOTIFY 3     //Spotify Mode

#define RE_SCR_UINPUT  "Scripts/uDev/init.sh"
#define RE_NP_SEPARATOR ","

#endif // BACKEND_H
