#include "SDL2/SDL.h"

#ifndef __ANIM__
#define __ANIM__



class Anim
{
private:
    int x;
    int y;
    int w;
    int h;

    bool done;
    float current_frame;
    int numframes;
    SDL_Rect *frames;
    float fps;
public:
    Anim();
    Anim(const Anim &ananim);
    Anim(int x,int y,int w,int h,int numframes);
    Anim(int x,int y,int w,int h,int numframes,float fps);
    virtual ~Anim();
    void run();
    void setanim(int x,int y,int w,int h,int numframes);
    void setanim(int x,int y,int numframes);
    SDL_Rect* getCurFrame();
    SDL_Rect* getFrame(int framenum);
    void setSpeed(float fps)
    {
        this->fps=fps;
        Reset();
    }
    void setCur_Frame(float frame)
    {
        current_frame=frame;
    }
    int getNumFrames()
    {
        return numframes;
    }
    void Reset();
    void PrintFrameStats();
    bool Done()
    {
        return done;
    }

};

#endif
