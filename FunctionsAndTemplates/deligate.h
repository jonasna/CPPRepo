#pragma once
#include <functional>
#include <optional>
#include <vector>

namespace detail
{
	template<typename Type, typename Arg>
	struct mem_function
	{
		using type = void(Type::*)(Arg);
			};
}

template <typename Arg>
class deligate
{

	template<class Type>
	using func = typename detail::mem_function<Type, Arg>::type;
	template<class Type>
	using funcs = std::vector<std::function<func<Type>>>;

public:
	deligate() = default;


private:


	

};



