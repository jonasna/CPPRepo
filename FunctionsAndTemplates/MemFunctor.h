#pragma once
#include <forward_list>
#include <vector>

template<class Return, class Type>
class MemFunctor
{
public:

	MemFunctor(Return (Type::*mf)())
	{
		memFunctor_ = mf;
	}

	Return operator()(Type* target)
	{
		return (target->*memFunctor_)();
	}

private:
	
	Return(Type::*memFunctor_)();
};

template<typename>
class memfc;

template<class R, class... A>
class memfc<R(A...)>
{
	typedef R(*functionType)(A...);

	functionType  function_;

public:

	memfc(functionType function)
	{
		function_ = function;
	}

	R operator()(A&&... a)
	{
		R r = function_(std::forward<A>(a)...);
		return r;
	}

};

template<class R, class... A>
memfc<R(A...)> mem_fc(R(*function)(A...))
{
	return memfc<R(A...)>(function);
}

template<typename>
class memfunc;

template<typename R, typename C, typename ... A>
class memfunc<R(C::*)(A...)>
{
	typedef R(C::*func)(A...);
	func func_;
public:
	memfunc(func func) : func_(func) {}
	R operator()(C* self, A&&... a)
	{
		return (self->*func_)(std::forward<A>(a)...);
	}
};

template<class R, typename C, typename... A>
memfunc<R(C::*)(A...)> mem_fc(R(C::*func)(A...))
{
	return memfunc<R(C::*)(A...)>(func);
}

template<class Ret, class Arg>
class Deligate
{
public:

	template<typename R, typename C, typename ... A>
	Deligate()
	
private:

};