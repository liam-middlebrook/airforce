#include "Logger.h"

namespace af
{
    log4cplus::Logger& logger()
    {
        static log4cplus::Logger logger = log4cplus::Logger::getInstance("af");
        return logger;
    }
}
