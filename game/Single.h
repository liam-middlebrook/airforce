#ifndef _SINGLE_H_
#define _SINGLE_H_

#include <boost/noncopyable.hpp>
#include <stdexcept>

namespace af
{
    template <class T>
    class Single : boost::noncopyable
    {
    public:
        Single()
        {
            if (single) {
                throw std::runtime_error("Single already exists");
            }

            single = this;
        }

        virtual ~Single()
        {
            single = NULL;
        }

    private:
        static Single* single;
    };
}

#endif
