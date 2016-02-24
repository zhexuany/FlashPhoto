#ifndef MASK_H
#define MASK_H
/*This Mask class store a 2D array of floats */
class Mask{
public:
    Mask(int w, int h);
    virtual ~Mask();
    int getHeight() const;
    int getWidth() const;
    float** getInfluence() const;
private:
    int height;
    int width;
    float** influence;
};
#endif
