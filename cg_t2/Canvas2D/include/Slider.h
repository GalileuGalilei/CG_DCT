#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
#include <iostream>
#include <string>

/// <summary>
/// Classe que desenha um slider na tela que pode ser ajustado com o mouse
/// </summary>
class Slider : IClickable, IRenderable
{
private:
    float x, y, r;
    float width;
    float height;
    float value;
    float maxValue;
    float minValue;
    bool isDragging;
    const char* label;

public:
    Slider(float x, float y, float width, float minValue, float maxValue, const char* label)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->value = minValue;
        this->maxValue = maxValue;
        this->minValue = minValue;
        this->label = label;
        this->isDragging = false;
        this->r = 8;
        height = 5;
    }

    float GetValue()
    {
        return value;
    }

    void OnRender(OnRenderEvent* args) override
    {
        CV::color(0.2, 0.2, 0.2);
        CV::text(x, y + 20, label);
        CV::rectFill(x, y, x + width, y + height);

        float normValue = (value - minValue) / maxValue;
        float cx = x + normValue * width;

        //valor atual
        CV::color(0,0,0);
        CV::text(cx, y - 15, std::to_string((int)value).c_str());
        CV::color(0.8, 0.6, 0.2);
        CV::circleFill(cx, y + height / 2, r, 12);
    }

    void OnClick(OnClickEvent* args) override
    {
        float normValue = (value - minValue) / maxValue;
        float cx = x + normValue * width;
        // Verifica se o botão do mouse foi pressionado
        if (args->button == 0 && args->state == 0)
        {
            float dist = std::sqrt(std::pow(args->x - cx, 2) + std::pow(args->y - y - height / 2, 2));
            if (dist <= r)
            {
                isDragging = true;
            }
        }

        // Verifica se o botão do mouse foi solto
        else if (args->button == 0 && args->state == 1)
        {
            isDragging = false;
        }
    }

    void OnMouseOver(OnMouseOverEvent* args) override
    {
        float ratio = width / (maxValue - minValue);

        // Se estiver arrastando o círculo
        if (isDragging)
        {
            value = args->x - x;
            value /= ratio;
            value = std::max(value, minValue);
            value = std::min(value, maxValue);
        }
            printf("value: %f\n", value);
    }

    GameLayer GetLayer() override
    {
        return GameLayer::UI;
    }
};


