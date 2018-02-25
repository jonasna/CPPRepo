#pragma once
#include <forward_list>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>

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

template<class Arg>
class Deligate
{
public:
	Deligate() = default;

	template <class Type>
	void add(void(Type::*deligate)(Arg), Type* obj)
	{
		using std::placeholders::_1;
		deligates_.push_back(std::bind(deligate, obj, _1));
	}

	void add(void(*deligate)(Arg))
	{
		deligates_.push_back(deligate);
	}

	void invoke(Arg&& a)
	{
		for (const auto& deligate : deligates_)
		{
			deligate(std::forward<Arg>(a));
		}
	}
		
private:

	std::vector<std::function<void(Arg)>> deligates_;

};


template<>
class Deligate<void>
{
public:
	Deligate() = default;

	template <class Type>
	void add(void(Type::*deligate)(), Type* obj)
	{
		using std::placeholders::_1;
		deligates_.push_back(std::bind(deligate, obj, _1));
	}

	void add(void(*deligate)())
	{
		deligates_.emplace_back(deligate);
	}

	void invoke()
	{
		for (const auto& deligate : deligates_)
		{
			deligate();
		}
	}
private:
	std::vector<std::function<void()>> deligates_;
};

template<typename Owner, class Arg>
class Event
{
	friend Owner;

public:

	explicit Event(Deligate<Arg>* deligate) : deligate_(deligate)
	{
		
	}

	template <class Type>
	void add(void(Type::*deligate)(Arg), Type* obj)
	{
		deligate_->add(deligate, obj);
	}

	void add(void(*deligate)(Arg))
	{
		deligate_->add(deligate);
	}


private:

	void invoke(Arg&& arg)
	{
		deligate_->invoke(std::forward<Arg>(arg));
	}

	std::unique_ptr<Deligate<Arg>> deligate_;
};