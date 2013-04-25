
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include "GUI.h"

namespace Graph_lib {

//------------------------------------------------------------------------------

void Button::attach(Window& win)
{
    pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
    own = &win;
}

//------------------------------------------------------------------------------

int In_box::get_int()
{
    Fl_Input& pi = reference_to<Fl_Input>(pw);
    // return atoi(pi.value());
    const char* p = pi.value();
    if (!isdigit(p[0])) return -999999;
    return atoi(p);
}

//------------------------------------------------------------------------------

string In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	return string(pi.value());
}

//------------------------------------------------------------------------------

void In_box::attach(Window& win)
{
    pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

//------------------------------------------------------------------------------

void Out_box::put(const string& s)
{
    reference_to<Fl_Output>(pw).value(s.c_str());
}

//------------------------------------------------------------------------------

void Out_box::attach(Window& win)
{
    pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

//------------------------------------------------------------------------------

int Menu::attach(Button& b)
{
    b.width = width;
    b.height = height;

    switch(k) {
    case horizontal:
        b.loc = Point(loc.x+offset,loc.y);
        offset+=b.width;
        break;
    case vertical:
        b.loc = Point(loc.x,loc.y+offset);
        offset+=b.height;
        break;
    }
    selection.push_back(b); // b is NOT OWNED: pass by reference
    return int(selection.size()-1);
}

//------------------------------------------------------------------------------

int Menu::attach(Button* p)
{
    Button& b = *p;
    b.width = width;
    b.height = height;

    switch(k) {
    case horizontal:
        b.loc = Point(loc.x+offset,loc.y);
        offset+=b.width;
        break;
    case vertical:
        b.loc = Point(loc.x,loc.y+offset);
        offset+=b.height;
        break;
    }
    selection.push_back(&b); // b is OWNED: pass by pointer
    return int(selection.size()-1);
}

//------------------------------------------------------------------------------

	calendar_window::calendar_window(Point xy, int w, int h, const string& title)
	:Window(w,h,title),
	submit1(Point((this->x_max()-100),0),90,20, "Submit:",cb_submit),
	req_month(Point(60,0),90,20, "Month:"),
	req_year(Point(200,0),90,20, "Year:"),
	current_date(Point(100,70),100,20, " "),
	calendar_template(Point(50,50),"calendar_template.jpg"),
	button_pushed(false),
	text_box(Point(100,100), day_num, event_text)
{
	current_month = -5;
	current_year = -5;
	month_display = new Text(Point(x_max()/2, 30), "January 2000");
	month_display->set_font_size(30);
	attach(*month_display);
	//Image calendar_template(Point(50,50),"calendar_template.jpg");
	attach(calendar_template); 
	attach(req_month);
	attach(req_year);
	attach(submit1);
	attach(current_date);
	attach(text_box);
}

	text_cont::text_cont(Point xy, const string& day_num, const string& event_text),
	xy1 = xy,
	day_num = Out_box(xy1,150,20, "test"),
	event_text = Out_box(xy1,150,100, "alsotest")
{
	/*attach(text_cont.day_num);
	attach(text_cont.event_text); */
}

void calendar_window::refresh(int m, int y)
{
	req_month.label = "Month: ";	// Clear the inbox text
	req_year.label = "Year: ";
	current_month = m;
	current_year = y;
	ostringstream ss;
	ss << m;	// Put the month - currently an int - into the buffer
	string month = ss.str();	// Pull the characters - the month - out of the buffer as a string
	
	ostringstream sss;
	sss << y;	// Put the month - currently an int - into the buffer
	string year = sss.str();	// Pull the characters - the month - out of the buffer as a string
	detach(*month_display);
	month_display = new Text(Point(x_max()/2, 30),  month + " " + year);
	month_display->set_font_size(30);
	attach(*month_display);
	
	wait_for_button();
}

int calendar_window::getYear()
{
	if(current_year == -5)	// Month has not been changed. Read from the inbox
		return req_year.get_int();
	else
		return current_year;
}

int calendar_window::getMonth()
{
	if(current_month == -5)	// Month has not been changed. Read from the inbox
		return req_month.get_int();
	else
		return current_month;
	
}

void calendar_window::cb_submit(Address,Address pw)
{
	reference_to<calendar_window>(pw).next();
}

void calendar_window::next()
{
    button_pushed = true;
    hide();
}

bool calendar_window::wait_for_button()
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else 
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

}; // of namespace Graph_lib