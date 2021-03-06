#ifndef __MODULE_H__
#define __MODULE_H__

class Application;

class Module
{
public:

	Module(bool active = true) : active(active)
	{}

	virtual ~Module()
	{}

	bool IsEnabled() const
	{
		return active;
	}

	bool Enable()
	{
		if (active == false)
			return active = Start();

		return true;
	}

	bool Disable()
	{
		if (active == true)
			return active = !CleanUp();

		return true;
	}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float deltaTime)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(const float deltaTime)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float deltaTime)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	/*virtual void OnColision(Collider* c1, Collider* c2)
	{

	}*/

	// Callbacks ---

private:
	bool active = true;
};

#endif // __MODULE_H__