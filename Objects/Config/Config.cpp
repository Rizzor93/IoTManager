#include "Config.h"

QObject *Config::config = nullptr;

Config::Config(QObject *parent) : QObject(parent){
    this->settings = new QSettings("config.ini",QSettings::IniFormat);
}