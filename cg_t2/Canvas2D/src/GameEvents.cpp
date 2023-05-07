#include "GameEvents.h"

int OnMouseOverEvent::oldX = 0;
int OnMouseOverEvent::oldY = 0;

EventType OnMouseOverEvent::GetStaticType()
{
	return EventType::MouseOverEvent;
}

EventType OnRenderEvent::GetStaticType()
{
	return EventType::RenderEvent;
}

std::list<IRenderable*> IRenderable::renderList;
void IRenderable::RenderAll(BaseEvent* baseEvent)
{
	OnRenderEvent* args = (OnRenderEvent*)baseEvent;

	for (int i = GameLayer::LayersCount - 1; i >= 0; i--)
	{
		for (auto j : IRenderable::renderList)
		{
			if (i == j->GetLayer())
			{
				j->OnRender(args);
			}
		}
	}
}

EventType OnClickEvent::GetStaticType()
{
	return EventType::ClickEvent;
}

std::list<IClickable*> IClickable::clickList;
void IClickable::ClickAll(BaseEvent* baseEvent)
{
	OnClickEvent* args = (OnClickEvent*)baseEvent;

	for (auto i : IClickable::clickList)
	{
		i->OnClick(args);
	}
}

void IClickable::MouseOverAll(BaseEvent* baseEvent)
{
	OnMouseOverEvent* args = (OnMouseOverEvent*)baseEvent;

	for (auto i : IClickable::clickList)
	{
		i->OnMouseOver(args);
	}
}

