#include "std_lib_facilities_3.h"
#include "Point.h"
#include "Window.h"
#include "Simple_window.h"
#include "Graph.h"
#include "GUI.h"

using namespace Graph_lib;

int main()
{
	Point tl(50,50);
	
	calendar_window win(Point(0,0),1300,800,"Calendar");
	
	/* making a matrix to hold text data that will correspond with the grid of the calendar */
	// Vector_ref<Shape> text_grid;
	//for(int i=0; i<7; ++i) // i = number of x divisions (columns) ; Should be 7 columns (corresponding to days of the week)
		//for(int j=0; j<6; ++j){ // j = number of y divisions (rows) ; Should be 6 rows (corresponding to weeks)
		//	text_grid.push_back(new Rectangle(Point(i*150,j*120),150,120)); /* i is the x width, j is y height of 
		//	text grid boxes. These boxes should be able to be filled later by grabbing data from the file, etc. 
		//	The code for that should probably go in this for statement somewhere? */
		//	text_grid[text_grid.size()-1].label = "Stuff"; 
		//	win.attach(text_grid[text_grid.size()-1]);
	//	}
		
	win.wait_for_button();
	
	while(true)
	{
		int month = win.getMonth();
		int year = win.getYear();
		cout << "Month: " << month << endl;
		cout << "Year: " << year << endl;
		
		win.refresh(++month, year);
	}	
	
	return 0;
}


/* Thoughts for displaying month

// Pseudo-code
// For all days in month
// 1) Figure out where (x,y) the day should go on the calendar
// 2) Get all events for that day
// 3) Display all events
// 4) Move to next day



	// Need running variables - xpos and ypos
	// events is your Vector_ref of objects that represent each day
	for(int i = 0; i < events.size(); i++)
	{
		Day weekday = events[i].getDay()	// Sunday = 0 - Saturday = 6
		if (weekday == Saturday)
		{
			displayDayInfo();
			// move to next line
			ypos = ypos + 100;
		}
		else
			displayDayInfo();
	}
*/