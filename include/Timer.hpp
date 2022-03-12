#ifndef TIMER_HPP
#define TIMER_HPP

#define DEFAULT_FPS 60.0F
#define DEFAULT_DELTATIME 1.5F

class Timer
{   
    private:
        float _fps;
        float _previousTime;
        float _frameTime;

    public:
        Timer(float fps = DEFAULT_FPS);
        void Tick();
        float DeltaTime();
};

#endif
