#ifndef GUARD_SCREEN_H
#define GUARD_SCREEN_H

#include<iostream>
#include<string>

class Screen
{
public:
  typedef std::string::size_type pos;

  Screen() = default; // needed because Screen has another constructor

  // cursor initialized to 0 by its in-class initializer
  Screen(pos ht, pos wd, char c): height(ht), width(wd), 
                                  contents(ht*wd,c){}

  Screen(pos ht, pos wd): height(ht), width(wd),contents(ht*wd,' ')
  {}


  // display overloaded on whether the object is const or not
  Screen& display(std::ostream&os)
  {
    do_display(os);
    return *this;
  }
  
  const Screen& display(std::ostream& os) const
  {
    do_display(os);
    return *this;
  }

  // set the character at he current cursor location
  Screen &set(char);

  // set the character at a given location.
  Screen &set(pos, pos, char);

  // get the character at the cursor
  char get() const // implicitly inline
  {
    return contents[cursor];
  }

  inline char get(pos ht, pos wd) const; // explicitly inline

  Screen &move(pos r, pos c); // can be made inline later

private:

  // function to do the work of displaying a Screen
  void do_display(std::ostream& os) const
  {
    os << contents;
  }

  pos cursor = 0;
  pos height = 0;
  pos width = 0;
  std::string contents{""};
};

inline Screen& Screen::set(char c)
{
  contents[cursor] = c; // set the new value at the current cursor location
  return *this; // return this object as an lvalue
}

inline Screen& Screen::set(pos r, pos col, char ch)
{
  contents[r*width+col] = ch; // set specified location to given value
  return *this;
}


inline // we can specify inline on the definition
Screen &Screen::move(pos r, pos c) 
{
  pos row = r*width; // compute the row location
  cursor = row+c; // move cursor to the column within that row
  return *this; // return this object as an lvalue
}

char Screen::get(pos r, pos c) const // declared as inline in the class
{
  pos row = r*width; // compute row location
  return contents[row+c]; // return character at the given column
}

#endif
