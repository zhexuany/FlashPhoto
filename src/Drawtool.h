#ifndef DRAWTOOL_H
#define DRAWTOOL_H
class Mask;
class DrawTool {
public:
    DrawTool(int red, int green, int blue);
    virtual ~DrawTool();
    virtual void paint();
    virtual void setMask(int h, int w);
    Mask getMask() const;
private:
    Mask* m_mask;
    ColorData* m_CurrentColor;
    const int maskHeight = 3;
    const int maskWidth = 3;
}



#endif DRAWTOOL_H
