#include "re_chapar.h"
#include <QDebug>
#include <QQmlProperty>


ReChapar::ReChapar(QObject *item, QObject *parent) : QObject(parent)
{
    ui = item;
}

void ReChapar::setPage(RePage page)
{
    QQmlProperty::write(ui, "x_action", page.x_action);
    QQmlProperty::write(ui, "y_action", page.y_action);
    QQmlProperty::write(ui, "a_action", page.a_action);
    QQmlProperty::write(ui, "b_action", page.b_action);
    QQmlProperty::write(ui, "m_action", page.m_action);
    QQmlProperty::write(ui, "s_action", page.s_action);
    QQmlProperty::write(ui, "r1_action", page.r1_action);
    QQmlProperty::write(ui, "r2_action", page.r2_action);
    QQmlProperty::write(ui, "l1_action", page.l1_action);
    QQmlProperty::write(ui, "l2_action", page.l2_action);
    QQmlProperty::write(ui, "lau_action", page.lau_action);
    QQmlProperty::write(ui, "lad_action", page.lad_action);
    QQmlProperty::write(ui, "lal_action", page.lal_action);
    QQmlProperty::write(ui, "lar_action", page.lar_action);
    QQmlProperty::write(ui, "rau_action", page.rau_action);
    QQmlProperty::write(ui, "rad_action", page.rad_action);
    QQmlProperty::write(ui, "ral_action", page.ral_action);
    QQmlProperty::write(ui, "rar_action", page.rar_action);
    QQmlProperty::write(ui, "left_action", page.left_action);
    QQmlProperty::write(ui, "up_action", page.up_action);
    QQmlProperty::write(ui, "down_action", page.down_action);
    QQmlProperty::write(ui, "right_action", page.right_action);
    QQmlProperty::write(ui, "axis_state", page.axis_state);
}

void ReChapar::setMode(int mode)
{
    RePage page;
    if(mode == RE_MODE_APPLICATION)
    {
        page.x_action = "Firefox";
        page.y_action = "Spotify";
        page.a_action = "Qt";
        page.b_action = "Explorer";
        page.m_action = "PDF";
        page.s_action = "Home";
        page.r1_action = "PNA";
        page.r2_action = "GT6";
        page.l1_action = "DOA";
        page.l2_action = "Put PC to Sleep";
        page.lau_action = "Sajad jooOon";
        page.lad_action = "Bijan Joon";
        page.lal_action = "Karim joon";
        page.lar_action = "Ehsan Joon";
        page.rau_action = "Abdi joooon";
        page.rad_action = "Aflatoon joon";
        page.ral_action = "Narges joon";
        page.rar_action = "Sepehr joon";
        page.left_action = "Switch to Workspace #1";
        page.up_action = "Switch to Workspace #2";
        page.down_action = "Switch to Workspace #3";
        page.right_action = "Switch to Workspace #4";
        page.axis_state = "0";
    }
    else if(mode == RE_MODE_SWITCH)
    {

    }
    else if(mode == RE_MODE_MAIN)
    {
        page.x_action = "Close Active Window";
        page.y_action = "Switch to Firefox";
        page.a_action = "Switch to Spotify";
        page.b_action = "Open New Firefox Window";
        page.m_action = "Put PC to Sleep";
        page.s_action = "Mute/UnMute";
        page.r1_action = "Switch to Book";
        page.r2_action = "Switch to EPUB Reader";
        page.l1_action = "Switch to Nautilus";
        page.l2_action = "Put PC to Sleep";
        page.lau_action = QString::number(RE_MODE_MAIN);
        page.lad_action = QString::number(RE_MODE_MAIN);
        page.lal_action = QString::number(RE_MODE_MAIN);
        page.lar_action = QString::number(RE_MODE_MAIN);
        page.rau_action = QString::number(RE_MODE_MAIN);
        page.rad_action = QString::number(RE_MODE_MAIN);
        page.ral_action = QString::number(RE_MODE_MAIN);
        page.rar_action = QString::number(RE_MODE_MAIN);
        page.left_action = "Switch to Workspace #1";
        page.up_action = "Switch to Workspace #2";
        page.down_action = "Switch to Workspace #3";
        page.right_action = "Switch to Workspace #4";
        page.axis_state = "1";
    }
    else if(mode == RE_MODE_READING)
    {

    }
    else if(mode == RE_MODE_FIREFOX)
    {

    }

    setPage(page);
}

