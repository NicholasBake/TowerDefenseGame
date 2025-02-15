#include "Button.h"
//bool exitCallLimit = false;
void Button::drawButton(const char* label, Color textColor){
    //Draw the label at the x/y 
    DrawText(label, x, y, 25, textColor);

    // If mouse is inside of button
    if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), cam), Rectangle {x, y, (float)MeasureText(label, 25), 25})){
        exitCallLimit = true;
        hoverMethod();
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            actionMethod();
        }
    }
    else if(exitCallLimit){
        exitMethod();
        exitCallLimit = false;
    }
}