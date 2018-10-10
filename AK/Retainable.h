#pragma once

#include "Assertions.h"

namespace AK {

template<typename T>
class Retainable {
public:
    Retainable() { }

    void retain()
    {
        ASSERT(m_retainCount);
        ++m_retainCount;
    }

    void release()
    {
        assert(m_retainCount);
        if (!--m_retainCount)
            delete static_cast<const T*>(this);
    }

    int retainCount() const
    {
        return m_retainCount;
    }

protected:
    ~Retainable()
    {
        ASSERT(!m_retainCount);
    }

private:
    int m_retainCount { 1 };
};

}

using AK::Retainable;

