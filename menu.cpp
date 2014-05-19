#import <iostream>

class MenuItem
{
private:
	char * title;

	MenuItem * previous;
	MenuItem * next;

	int position;

public:
	MenuItem(const char * _title)
	{
		// Get length of title
		int title_length = strlen(_title);

		// Initilize the title with zeros
		title = new char[title_length + 1]();

		// Copy the title
		for (int i = 0; i < title_length; ++i)
		{
			title[i] = _title[i];
		}

		// Initilize the next and previous menus
		previous = 0;
		next = 0;

		// Set the position to default
		position = 1;

		// Set the next to default
		next = 0;
	}

	~MenuItem()
	{
		// Delete the title
		delete title;

		// If there is a next menu
		if (next) {
			// Delete it
			delete next;
		}
	}

	// Print the current menu tree
	void print()
	{
		// Print myself
		std::cout << position << ". " << title << std::endl;

		// If there is a next menu, print it
		if (next) {
			next->print();
		}
	}

	// Add the next menu
	void add_next(MenuItem * next_menu)
	{
		// Update the next item
		next = next_menu;
	}

	// Add the previous menu
	void add_previous(MenuItem * previous_menu)
	{
		// Update the previous menu
		previous = previous_menu;

		// Update my position based on the previous one
		position = previous_menu->get_position() + 1;
	}

	// Return the position in the menu
	int get_position()
	{
		return position;
	}
};

class Menu
{
private:
	MenuItem * first_menu_item;
	MenuItem * last_menu_item;
	int number_of_menus;

	// Add a new MenuItem
	void add_menu_item(MenuItem * menu_item) {
		// If this is the first item
		if (!first_menu_item)
		{
			// Set the first and the last menu to this one
			first_menu_item = menu_item;
			last_menu_item = menu_item;
		}
		// Otherwise 
		else
		{
			// Add the menu to the last item
			last_menu_item->add_next(menu_item);

			// Add the previos item to this one
			menu_item->add_previous(last_menu_item);

			// Update the last menu item
			last_menu_item = menu_item;
		}

		number_of_menus++;
	}

public:
	Menu()
	{
		// Initilize the empty menu
		first_menu_item = 0;
		last_menu_item = 0;
		number_of_menus = 0;
	}

	~Menu()
	{
		// If we have a menu...
		if (first_menu_item)
		{
			// Delete the first one, which will delete the rest!
			delete first_menu_item;
		}
	}

	void add_menu_item(const char * menu_text)
	{
		// Create a new menu item
		MenuItem * menuItem = new MenuItem(menu_text);

		// Add it
		add_menu_item(menuItem);
	}

	// Print a menu
	void print()
	{
		// If we have a menu
		if (first_menu_item)
		{
			// Start the print!
			first_menu_item->print();
		}
	}
};

int main () {
	// Create a menu
	Menu * my_menu = new Menu();

	// Add menu items
	my_menu->add_menu_item("Happy stuff!");
	my_menu->add_menu_item("Awesome stuff!");
	my_menu->add_menu_item("Great stuff!");
	my_menu->add_menu_item("Sad stuff!");

	// Print the menu
	my_menu->print();

	// Destroy the menu
	delete my_menu;

	// Return 0, as all happy c++ returns 0 from int main()
	return 0;
}