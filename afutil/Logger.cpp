#include "Logger.h"

namespace afutil
{
    log4cplus::Logger& logger()
    {
        static log4cplus::Logger logger = log4cplus::Logger::getInstance("afutil");
        return logger;
    }
}
