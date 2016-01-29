//
// Created by creekorful on 30/09/2015.
//

#include "ConfigFileManager.h"

ConfigFileManager::ConfigFileManager(std::string aConfigFilePath)
{
    m_filePath = aConfigFilePath;
}

void ConfigFileManager::writeValue(std::string aValueName, std::string aValue)
{

}

std::string ConfigFileManager::getStringValue(std::string aValue)
{
    return "";
}

int ConfigFileManager::getIntValue(std::string aValue)
{
    return 0;
}

bool ConfigFileManager::getBoolValue(std::string aValue)
{
    return false;
}
