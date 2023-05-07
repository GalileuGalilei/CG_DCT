#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"
#include <functional>
class Button : IRenderable, IClickable 
{
private:
	std::function<void()> callback;

protected:
    const float mouseOverColorChange = 0; //o quanto a cor escurece 

	char label[100];
	bool isMouseOver = false;
	Color color;
	Vector2 position, size;

public:
  Button(Vector2 position, Vector2 size, Color color, const char label[], std::function<void()> callback)
  {
     strcpy_s(this->label, 100, label);

     this->position = position;
	 this->size = size;
     this->color = color;
	 this->callback = callback;
  }

  void OnRender(OnRenderEvent* args) override
  {
	  CV::color(color.r, color.g, color.b);
	  CV::rectFill(position, position + size);
      CV::color(0, 0, 0);
      CV::text(position.x+5, position.y + size.y / 2, label);
  }

  void OnClick(OnClickEvent* args) override
  {
	  if (!CheckBounds(args->x, args->y) || args->state != 0)
	  {
		  return;
	  }
	  
	  callback();
  }

  void OnMouseOver(OnMouseOverEvent* args) override
  {
	  if (!CheckBounds(args->x, args->y))
	  {
		  return;
	  }
  }

  GameLayer GetLayer() override
  {
	  return GameLayer::UI;
  }
  
private:
	bool CheckBounds(int x, int y)
	{
		if (x > position.x + size.x || x < position.x)
		{
			return false;
		}

		if (y > position.y + size.y || y < position.y)
		{
			return false;
		}

		return true;
	}

};

#endif
