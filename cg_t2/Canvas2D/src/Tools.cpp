#include "Tools.h"

std::list<ITool*> ITool::toolList;

EventType OnToolEvent::GetStaticType()
{
	return EventType::ToolEvent;
}

/*
void FillTool::OnFillTool(BaseEvent* baseEvent)
{
	
	selectedPolygon->Fill();
	selectedPolygon->SetColor(ColorDisplay::selectedColor);
}

bool MoveTool::isMoving = false;

void MoveTool::OnMoveTool(BaseEvent* baseEvent)
{
	if (selectedPolygon == NULL)
	{
		return;
	}

	if (baseEvent->GetType() == ClickEvent)
	{
		OnClickEvent* click = (OnClickEvent*)baseEvent;
		if (!isMoving)
		{
			isMoving = true;
		}
		else
		{
			isMoving = false;
			selectedPolygon = NULL;
		}
	}
	else if (baseEvent->GetType() == MouseOverEvent)
	{
		OnMouseOverEvent* mouseOver = (OnMouseOverEvent*)baseEvent;
		if (isMoving)
		{
			selectedPolygon->SetPosition(Vector2(mouseOver->x, mouseOver->y));
		}
	}
}
*/
