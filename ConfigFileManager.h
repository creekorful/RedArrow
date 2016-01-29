#ifndef CONFIGFILEMANAGER_H
#define CONFIGFILEMANAGER_H

#include <iostream>
#include <rapidjson/rapidjson.h>


//todo in config file
// LEFT_ROTATE_KEY, RIGHT_ROTATE_KEY, FIRE_KEY, MUSIC_ENABLED

class ConfigFileManager
{
public:
    ConfigFileManager(std::string aConfigFilePath);
    bool getBoolValue(std::string aValue);
    int getIntValue(std::string aValue);
    std::string getStringValue(std::string aValue);
    void writeValue(std::string aValueName, std::string aValue);

private:
    std::string m_filePath;
};


#endif //CONFIGFILEMANAGER_H
