#pragma once
#include "Command.h"
#include "QBertComponent.h"

class MoveUpRightCommand final : public Command
{
public:
	MoveUpRightCommand(QBertComponent* pQbert) : m_pQbert{pQbert}{}
	virtual void Execute() override 
	{ 
		m_pQbert->Move(QBertComponent::MoveDirections::TopRight);
	}

private:
	QBertComponent* m_pQbert;
};

class MoveUpLeftCommand final : public Command
{
public:
	MoveUpLeftCommand(QBertComponent* pQbert) : m_pQbert{ pQbert } {}
	virtual void Execute() override 
	{
		m_pQbert->Move(QBertComponent::MoveDirections::TopLeft);
	}

private:
	QBertComponent* m_pQbert;
};

class MoveDownRightCommand final : public Command
{
public:
	MoveDownRightCommand(QBertComponent* pQbert) : m_pQbert{ pQbert } {}
	virtual void Execute() override 
	{ 
		m_pQbert->Move(QBertComponent::MoveDirections::BottomRight);
	}

private:
	QBertComponent* m_pQbert;
};

class MoveDownLeftCommand final : public Command
{
public:
	MoveDownLeftCommand(QBertComponent* pQbert) : m_pQbert{ pQbert } {}
	virtual void Execute() override 
	{ 
		m_pQbert->Move(QBertComponent::MoveDirections::BottomLeft);
	}

private:
	QBertComponent* m_pQbert;
};