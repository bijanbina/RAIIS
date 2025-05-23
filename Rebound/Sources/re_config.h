#ifndef RE_CONFIG_H
#define RE_CONFIG_H

#define COM_NAME        "com.binaee.rebound"
#define ORG_NAME        "org.binaee.rebound"
#define RE_PIPE_PATH    "\\\\.\\pipe\\com_binaee_rebound"
#define RE_PIPE_CHESS   "\\\\.\\pipe\\com_binaee_chess"
#define RE_PIPE_MOM     "\\\\.\\pipe\\com_binaee_mom"
#define CH_NP_SEPARATOR ","

#define RE_FIREFOX_DIR   "Scripts/Firefox"
#define MOM_LABEL_DIR    "..\\..\\Benjamin\\Mom\\Labels"
#define KAL_SI_DIR       "../../Benjamin/Tools/Scripts/interpreter"
#define KAL_SI_DIR_WIN   "..\\..\\Benjamin\\Tools\\Scripts\\interpreter"
#define BT_CONF_PATH     "../../Benjamin/Tools/BaTool.conf"
#define MOM_LABEL_PNAME  "\\r1_pname.lbl"
#define MOM_LABEL_STATUS "\\r2_status.lbl"

//#define RE_DEBUG_WIN //show window detection debug info


#define RE_CLIENT 0
#define RE_SERVER 1

#define RE_DIM_OPAC  230
#define RE_PORT      7610
#define RE_IP        "192.168.88.25"
#define RE_CPORT0    5000
#define RE_CPORT1    5001
#define RE_CIP       "5.255.113.20"

//#define RE_TEST_EN
//#define RE_DUBUG_TCP

#define RE_TIMEOUT        1000
#define RE_WATCHDOG       3000  //Watchdog interval
#define RE_RECONNECT      10000 //watchdog reconnect interval
#define RE_LIVE           300   //Live send interval
#define RE_CHECK_BTN      4     //Xbox send interval
#define RE_CHECK_IN       4     //check input(native mode)
#define RE_TAB_TIME       900   //Alt pressed time
#define RE_EXEC_TIMEOUT   2100  //Command execution timeout
#define RE_VIRT_TIMEOUT   300   //Command virtual index timeout

#define RE_SCR_UI      1     //UI Mode
#define RE_SCR_YOUTUBE 2     //YouTube Mode
#define RE_SCR_SPOTIFY 3     //Spotify Mode

#define RE_SCR_UINPUT  "Scripts/uDev/init.sh"
#define RE_NP_SEPARATOR ","

// The buffer size specified should be small enough that your process will not run out of nonpaged pool,
// but large enough to accommodate typical requests.
#define PIPE_BUFFER_SIZE (1024 * 8)


#endif // BACKEND_H
