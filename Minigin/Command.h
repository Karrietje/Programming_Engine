#pragma once
#include <iostream>
#include "SubjectComponent.h"

using namespace dae;
class Command
{
public:
	virtual ~Command() = default; 
	virtual void Execute() = 0; 
};

class JumpCommand final : public Command 
{	
public:
	virtual void Execute() override { std::cout << "You jumped!\n"; }
};

class SmileCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You smiled!\n"; }
};

class FireCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You fired!\n"; }
};

class RunCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You ran!\n"; }
};

class LeftHandpCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You attacked with your left hand!\n"; }
};

class RightHandCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You attacked with your right hand!\n"; }
};

class KillCommand final : public Command
{
public:
	KillCommand(std::weak_ptr<SubjectComponent> pSubject)
		:m_pSubject{pSubject}
	{}

	virtual void Execute() override 
	{
		if (!m_pSubject.expired())
		{
			m_pSubject.lock()->Notify(Event::Kill);
		} 
	}

private:
	std::weak_ptr<SubjectComponent> m_pSubject; 
};

class ColorChangeCommand final : public Command
{
public:
	ColorChangeCommand(std::weak_ptr<SubjectComponent> pSubject)
		:m_pSubject{ pSubject }
	{}

	virtual void Execute() override
	{
		if (!m_pSubject.expired())
		{
			m_pSubject.lock()->Notify(Event::ColorChange);
		}
	}

private:
	std::weak_ptr<SubjectComponent> m_pSubject;
};

class KillByFlyingDiscCommand final : public Command
{
public:
	KillByFlyingDiscCommand(std::weak_ptr<SubjectComponent> pSubject)
		:m_pSubject{ pSubject }
	{}

	virtual void Execute() override
	{
		if (!m_pSubject.expired())
		{
			m_pSubject.lock()->Notify(Event::KillByFlyingDisc);
		}
	}

private:
	std::weak_ptr<SubjectComponent> m_pSubject;
};

class RemainingDiscCommand final : public Command
{
public:
	RemainingDiscCommand(std::weak_ptr<SubjectComponent> pSubject)
		:m_pSubject{ pSubject }
	{}

	virtual void Execute() override
	{
		if (!m_pSubject.expired())
		{
			m_pSubject.lock()->Notify(Event::RemainingDisc);
		}
	}

private:
	std::weak_ptr<SubjectComponent> m_pSubject;
};

class CatchingCommand final : public Command
{
public:

	CatchingCommand(std::weak_ptr<SubjectComponent> pSubject)
		:m_pSubject{ pSubject }
	{}

	virtual void Execute() override
	{
		if (!m_pSubject.expired())
		{
			m_pSubject.lock()->Notify(Event::CatchingSlick);
		}
	}

private:
	std::weak_ptr<SubjectComponent> m_pSubject;
};

