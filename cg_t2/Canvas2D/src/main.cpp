/*********************************************************************
// Canvas2D
// Autor: Cesar Tadeu Pozzer
//        04/2021
// *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "EventManager.h"
#include "GameEvents.h"
#include "ToolBar.h"
#include <time.h>
#include "Slider.h"
#include "DCT.h"

void keyboard(int key) {}

void keyboardUp(int key) {}

void render()
{
    OnRenderEvent renderEvent = OnRenderEvent();
    EventManager::Instance()->InvokeEvent<OnRenderEvent>((BaseEvent*)&renderEvent);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if (state != -2)
    {
        OnClickEvent clickEvent = OnClickEvent(button, state, x, y);
        EventManager::Instance()->InvokeEvent<OnClickEvent>((BaseEvent*)&clickEvent);
    }

    OnMouseOverEvent mouseOverEvent = OnMouseOverEvent(x, y, direction);
    EventManager::Instance()->InvokeEvent<OnMouseOverEvent>((BaseEvent*)&mouseOverEvent);
}

int main(void)
{
    int screenWidth = 800, screenHeight = 500;
    srand(time(NULL));

    EventManager::Instance()->AddListener<OnRenderEvent>(IRenderable::RenderAll);
    EventManager::Instance()->AddListener<OnClickEvent>(IClickable::ClickAll);
    EventManager::Instance()->AddListener<OnMouseOverEvent>(IClickable::MouseOverAll);

    Sample* sample = new Sample();
    DCT* dct = new DCT(Vector2(100, 100), Vector2(screenWidth - 200, screenHeight - 200), sample, 20);
    ToolBar toolBar(sample, Vector2(0, 0), Vector2(100, screenHeight), 10);

    CV::init(&screenWidth, &screenHeight, "Canvas 2D");
    CV::run();
}
