#include "af/Utils.h"
#include <boost/date_time.hpp>

namespace af
{
    UInt64 getTimeMs()
    {
        /*
         * TODO: Use steady clock.
         */

        return (boost::posix_time::microsec_clock::universal_time() - boost::posix_time::from_time_t(0)).total_milliseconds();
    }
}
