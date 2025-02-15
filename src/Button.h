#include "include.h"
class Button
{
private:
    bool exitCallLimit = false;
public:
    float x;
    float y;
    std::function<void()> actionMethod;    
    std::function<void()> hoverMethod;
    std::function<void()> exitMethod;
    Camera2D &cam;
    // Button with text constructor
    Button(Camera2D &Cam, float X, float Y, std::function<void()> actMethod, std::function<void()> hovMethod, std::function<void()> exiMethod) : cam(Cam), x(X), y(Y), actionMethod(actMethod), hoverMethod(hovMethod), exitMethod(exiMethod){};
    void drawButton(const char* label, Color textColor);
};
