#ifndef ISTATEMACHINE_H
#define ISTATEMACHINE_H

template<typename state>
class IStateMachine
{
public:
	IStateMachine(const state& pInitialState);
	~IStateMachine();

	virtual void ChangeState(const state& pNewState) = 0;
	const virtual state GetState() const;
protected:
	state mCurrentState;
};

template<typename state>
IStateMachine<state>::IStateMachine(const state& pInitialState) :
	mCurrentState(pInitialState)
{}

template<typename state>
IStateMachine<state>::~IStateMachine()
{}

template<typename state>
const state IStateMachine<state>::GetState() const
{
	return mCurrentState;
}

#endif