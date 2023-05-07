#pragma once
#include "EventManager.h"
#include "GameEvents.h"

class OnToolEvent : public BaseEvent
{
public:

	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}
};

class ITool
{
private:
	static std::list<ITool*> toolList;

public:
	static void DisableAllTools()
	{
		for (ITool* tool : toolList)
		{
			tool->RemoveToolListeners();
		}
	}

	static void OnTool(BaseEvent* baseEvent)
	{
		OnToolEvent* args = (OnToolEvent*)baseEvent;
	}

protected:
	ITool()
	{
		toolList.push_back(this);
	}

	virtual void RemoveToolListeners() = 0;
	virtual void AddToolListeners() = 0;
};


class FillTool : public ITool
{
public:
	static void OnFillTool(BaseEvent* baseEvent);

	void RemoveToolListeners() override
	{
		EventManager::Instance()->RemoveListener<OnClickEvent>(OnFillTool);
	}

	void AddToolListeners() override
	{
		EventManager::Instance()->AddListener<OnClickEvent>(OnFillTool);
	}
};

class MoveTool : public ITool
{
private:
	static bool isMoving;

public:
	static void OnMoveTool(BaseEvent* baseEvent);

	void RemoveToolListeners() override
	{
		EventManager::Instance()->RemoveListener<OnClickEvent>(OnMoveTool);
		EventManager::Instance()->RemoveListener<OnMouseOverEvent>(OnMoveTool);
	}

	void AddToolListeners() override
	{
		EventManager::Instance()->AddListener<OnClickEvent>(OnMoveTool);
		EventManager::Instance()->AddListener<OnMouseOverEvent>(OnMoveTool);
	}
};

class RotateTool : public ITool
{
private:
	static bool isRotating;

public:
	static void OnRotateTool(BaseEvent* baseEvent);

	void RemoveToolListeners() override
	{
		EventManager::Instance()->RemoveListener<OnClickEvent>(OnRotateTool);
		EventManager::Instance()->RemoveListener<OnMouseOverEvent>(OnRotateTool);
	}

	void AddToolListeners() override
	{
		EventManager::Instance()->AddListener<OnClickEvent>(OnRotateTool);
		EventManager::Instance()->AddListener<OnMouseOverEvent>(OnRotateTool);
	}
};

class ScaleTool : public ITool
{
private:
	static bool isScaling;

public:
	static void OnScaleTool(BaseEvent* baseEvent);

	void RemoveToolListeners() override
	{
		EventManager::Instance()->RemoveListener<OnClickEvent>(OnScaleTool);
		EventManager::Instance()->RemoveListener<OnMouseOverEvent>(OnScaleTool);
	}

	void AddToolListeners() override
	{
		EventManager::Instance()->AddListener<OnClickEvent>(OnScaleTool);
		EventManager::Instance()->AddListener<OnMouseOverEvent>(OnScaleTool);
	}
};

class DeleteTool : public ITool
{
public:

};