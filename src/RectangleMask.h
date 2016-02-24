##ifndef RECTANGLEMASK_H
#define RECTANGLEMASK_H
class RectangleMask : public Mask{
public:
    RectangleMask(int w, int h);
    ~RectangleMask();
    virtual void fillInfluence();
}



#endif // RECTANGLEMASK_H
