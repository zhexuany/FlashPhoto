#ifndef MASK_H
#define MASK_H
/*This Mask class store a 2D array of floats */
class Mask{
public:
    Mask(int w, int h);
    virtual ~Mask();
    virtual void fillInfluence();
    virtual int getHeight() const;
    virtual int getWidth() const;
    float const ** const getInfluence() const;
private:
    int height;
    int weight;
    float** influence;
};
#endif
