#include "re_hardware_w.h"
#include <QThread>

ReHardwareW::ReHardwareW(QObject *parent) : QObject(parent)
{
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->setSingleShot(true);

    timer_state = RE_TIMER_STATE_INIT;
    int i = 0;
    char dev_path[MAX_PATH];
    char dev_desc[MAX_PATH];


    // Create a HDEVINFO with all present devices.
    hDevInfo = SetupDiGetClassDevs(NULL,0, 0,DIGCF_PRESENT | DIGCF_ALLCLASSES );

    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        return;
    }

    // Enumerate through all devices in Set.

    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    while ( SetupDiEnumDeviceInfo(hDevInfo,i,&DeviceInfoData) )
    {
        wchar_t  dev_path_w[MAX_PATH];
        wchar_t  dev_desc_w[MAX_PATH];


        while (!SetupDiGetDeviceRegistryProperty(hDevInfo,&DeviceInfoData,SPDRP_PHYSICAL_DEVICE_OBJECT_NAME,0L,(PBYTE)dev_path,2048,0)){}

        SetupDiGetDeviceRegistryProperty(hDevInfo,&DeviceInfoData,SPDRP_DEVICEDESC,0L,(PBYTE)dev_desc_w,2048,0);

        wcstombs(dev_path, dev_path_w, wcslen(dev_path_w) + 1);
        wcstombs(dev_desc, dev_desc_w, wcslen(dev_desc_w) + 1);

        QString dev_desc_q = dev_desc;

        if ( dev_desc_q.contains("XBox", Qt::CaseInsensitive) )
        {
            qDebug() << dev_path << dev_desc;
            break;
        }
        i++;
    }
}

void ReHardwareW::timerTimeout()
{
    if ( timer_state==RE_TIMER_STATE_DIS0)
    {
        timer_state = RE_TIMER_STATE_ENB1;
        enableXbox();
        timer->start(1000);
    }
    else if ( timer_state==RE_TIMER_STATE_ENB1 )
    {
        timer_state = RE_TIMER_STATE_DIS2;
        disableXbox();
        timer->start(30000);
    }
    else if ( timer_state==RE_TIMER_STATE_DIS2 )
    {
        timer_state = RE_TIMER_STATE_INIT;
        enableXbox();
    }
}

void ReHardwareW::disconnectXbox()
{
    if ( timer_state==RE_TIMER_STATE_INIT )
    {
        timer_state = RE_TIMER_STATE_DIS0;
        disableXbox();
        timer->start(2000);
    }
}

void ReHardwareW::disableXbox()
{
    qDebug() << "Disabling XBox";
    setDevice(DICS_DISABLE);
}

void ReHardwareW::enableXbox()
{
    qDebug() << "Enabling XBox";
    setDevice(DICS_ENABLE);
}

void ReHardwareW::setDevice(long state)
{
    SP_PROPCHANGE_PARAMS params; // params to set in order to enable/disable the device
    params.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
    params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
    params.HwProfile = 0;
    params.Scope = DICS_FLAG_CONFIGSPECIFIC;
    params.StateChange = state;
    // prepare operation
    if (!SetupDiSetClassInstallParams(hDevInfo, &DeviceInfoData,&params.ClassInstallHeader, sizeof(params)))
    {
        qDebug() << "Error while preparing params!";
        return;
    }
    // launch op
    if (!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &DeviceInfoData))
    {
        qDebug() << "Error while calling OP ! Return code is " << QString("%1").arg(GetLastError() , 0, 16);;
    }
}
