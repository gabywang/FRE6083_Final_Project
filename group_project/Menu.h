#ifndef Menu_h
#define Menu_h

class Menu
{
protected:
	Menu();
	Menu(const Menu& rhs);
	Menu& operator =(const Menu& rhs);

public:
	static Menu* get_instance()
	{
		static Menu _instance;
		return &_instance;
	}

	int run_forever();

	~Menu();
};

#endif