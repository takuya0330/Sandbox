#include <array>
#include <iostream>

template<typename T, typename R, typename... Args>
class Functor
{
public:
	using MethodType = R (T::*)(Args...);

	Functor()
	    : m_obj(nullptr)
	    , m_method(nullptr)
	{
	}

	void Bind(T* obj, MethodType method)
	{
		m_obj    = obj;
		m_method = method;
	}

	void Unbind()
	{
		m_obj    = nullptr;
		m_method = nullptr;
	}

	R operator()(Args... args) const
	{
		return (m_obj->*m_method)(args...);
	}

private:
	T*         m_obj;
	MethodType m_method;
};

template<typename R, typename... Args>
class Functor<void, R, Args...>
{
public:
	using MethodType = R (*)(Args...);

	Functor()
	    : m_method(nullptr)
	{
	}

	void Bind(MethodType method)
	{
		m_method = method;
	}

	void Unbind()
	{
		m_method = nullptr;
	}

	R operator()(Args... args) const
	{
		return (*m_method)(args...);
	}

private:
	MethodType m_method;
};

template<typename T, size_t Size = 16>
class Function;

template<typename R, typename... Args, size_t Size>
class Function<R(Args...), Size>
{
public:
	Function()
	    : m_memory()
	    , m_invoker(nullptr)
	{
	}

	~Function()
	{
		Unbind();
	}

	template<typename F>
	void Bind(F&& f)
	{
		static_assert(sizeof(CInvoker<F>) <= sizeof(m_memory));
		m_invoker = new (m_memory) CInvoker<F>(std::forward<F>(f));
	}

	void Unbind()
	{
		if (m_invoker)
		{
			m_invoker->~IInvoker();
			m_invoker = nullptr;
		}
		std::memset(m_memory, 0, Size);
	}

	R operator()(Args... args) const
	{
		return (*m_invoker)(std::forward<Args>(args)...);
	}

private:
	class IInvoker
	{
	public:
		virtual ~IInvoker()                        = default;
		virtual R operator()(Args&&... args) const = 0;
	};

	template<typename T>
	class CInvoker : public IInvoker
	{
	public:
		template<typename F>
		CInvoker(F&& f)
		    : m_functor(std::forward<F>(f))
		{
		}

		R operator()(Args&&... args) const override
		{
			return m_functor(std::forward<Args>(args)...);
		}

	private:
		T m_functor;
	};

private:
	uint8_t   m_memory[Size];
	IInvoker* m_invoker;
};

template<typename T>
class Delegate;

template<typename R, typename... Args>
class Delegate<R(Args...)>
{
public:
	using FunctionType = Function<R(Args...), 16 + sizeof(void*)>;

public:
	Delegate()
	    : m_functor()
	{
	}

	template<typename T, typename F>
	void Bind(T* obj, F&& f)
	{
		m_functor.Bind([obj, f](Args... args) -> R
		    {
			    return (obj->*f)(std::forward<Args>(args)...);
		    });
	}

	template<typename F>
	void Bind(F&& f)
	{
		m_functor.Bind(std::forward<F>(f));
	}

	void Unbind()
	{
		m_functor.Unbind();
	}

	R operator()(Args... args) const
	{
		return m_functor(std::forward<Args>(args)...);
	}

private:
	FunctionType m_functor;
};

template<typename T, size_t N>
class MulticastDelegate;

template<typename R, typename... Args, size_t N>
class MulticastDelegate<R(Args...), N>
{
public:
	using FunctionType = Function<R(Args...), 16 + sizeof(void*)>;

public:
	MulticastDelegate()
	    : m_functors()
	{
	}

	template<typename T, typename F>
	void Bind(int index, T* obj, F&& f)
	{
		m_functors.at(index).Bind([obj, f](Args... args) -> R
		    {
			    return (obj->*f)(std::forward<Args>(args)...);
		    });
	}

    template<typename F>
	void Bind(int index, F&& f)
	{
		m_functors.at(index).Bind(std::forward<F>(f));
	}

	void Unbind(int index)
	{
		m_functors.at(index).Unbind();
	}

    void Broadcast(Args... args) const
    {
		for (const auto& func : m_functors)
		{
			func(std::forward<Args>(args)...);
		}
    }

private:
	std::array<FunctionType, N> m_functors;
};

class Test
{
public:
	void Foo(int, float)
	{
		std::cout << "Test::Foo(int, float) called." << std::endl;
	}
};

class Test2
{
public:
	void Bar(int, float)
	{
		std::cout << "Test2::Bar(int, float) called." << std::endl;
	}
};

int hoge(int, int, int)
{
	std::cout << "hoge(int, int, int) called." << std::endl;
	return 0;
}

int main(int, char**)
{
	Test                            t;
	Functor<Test, void, int, float> f;
	f.Bind(&t, &Test::Foo);
	f(1, 2.0f);
	constexpr size_t f_size = sizeof(f);

	Functor<void, int, int, int, int> g;
	g.Bind(&hoge);
	g(1, 2, 3);
	constexpr size_t g_size = sizeof(g);

	Function<void(int, float)> func1;
	func1.Bind([&t](int a, float b)
	    {
		    t.Foo(a, b);
	    });
	func1(1, 2.0f);
	constexpr size_t func1_size = sizeof(func1);

	Function<int(int, int, int)> func2;
	func2.Bind(&hoge);
	func2(1, 2, 3);
	constexpr size_t func2_size = sizeof(func2);

	Delegate<void(int, float)> delegate1;
	delegate1.Bind(&t, &Test::Foo);
	delegate1(1, 2.0f);
	constexpr size_t delegate1_size = sizeof(delegate1);

	Delegate<int(int, int, int)> delegate2;
	delegate2.Bind(&hoge);
	delegate2(1, 2, 3);
	constexpr size_t delegate2_size = sizeof(delegate2);

    MulticastDelegate<void(int, float), 2> mdelegate;
    Test2 t2;
	mdelegate.Bind(0, &t, &Test::Foo);
	mdelegate.Bind(1, &t2, &Test2::Bar);
	mdelegate.Broadcast(1, 2.0f);
	constexpr size_t mdelegate_size = sizeof(mdelegate);

	return 0;
}
