#pragma once

namespace ECS {

class System
{
public:
	virtual ~System() = default;

    virtual void OnCreate()
	{
	}

    virtual void OnDelete()
    {
    }

    virtual void OnUpdate()
    {
	}
};

} // namespace ECS
