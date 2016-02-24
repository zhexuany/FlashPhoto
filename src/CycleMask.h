##ifndef CYCLEMASK_H
#define CYCLEMASK_H
#include "Mask.h"

class CycleMask : public Mask {
public:
    CycleMask(int radius);
    ~CycleMask();
    virtual void fillInfluence();
}

#endif // CYCLEMASK_H
