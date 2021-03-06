#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.h"
#include "Student_info.h"

using std::cin; using std::setprecision;
using std::cout; using std::sort;
using std::domain_error; using std::streamsize;
using std::endl; using std::string;
using std::max; using std::vector;

// predicate to determine whether a student failed
bool fgrade(const Student_info& s)
{
  return grade(s) < 60;
}

//// separate passing and failing student records: first try
//vector<Student_info> extract_fails(vector<Student_info>& students)
//{
//  vector<Student_info> pass,fail;
//  
//  for(vector<Student_info>::size_type i=0;
//      i != students.size(); ++i)
//  {
//    if(fgrade(students[i]))
//      fail.push_back(students[i]);
//    else
//      pass.push_back(students[i]);
//  }
//
//  students=pass;
//  return fail;
//}

// second try: correct but potentially slow
vector<Student_info> extract_fails(vector<Student_info>& students)
{
  vector<Student_info> fail;
  vector<Student_info>::size_type i = 0;

  // invariant: elements [0,i) of students represent passing grades
  while(i != students.size())
  {
    if(fgrade(students[i]))
    {
      fail.push_back(students[i]);
      students.erase(students.begin()+i);
    }
    else
    {
      ++i;
    }
  }
  return fail;
}

int main()
{
  vector<Student_info> students;
  Student_info record;
  string::size_type maxlen=0; // length of the longest name

  // read and store all the students data.
  // Invariant: students contains all the student records so far
  // maxlen constains the length of the longest name in students
  while(read(cin,record))
  {
    // find length of longest name
    maxlen = max(maxlen,record.name.size());
    students.push_back(record);
  }

  // alphabetize the student records
  sort(students.begin(),students.end(),compare);

  // write the names and grades
  for(vector<Student_info>::size_type i = 0;
      i != students.size(); ++i)
  {
    // write the name, padded on the right to maxlen+1 characters
    cout << students[i].name
      << string(maxlen+1 - students[i].name.size(),' ');

    // compute and write the grade
    try{
      double final_grade = grade(students[i]);
      streamsize prec = cout.precision();
      cout << setprecision(3) << final_grade
        << setprecision(prec);
    }catch(domain_error e){
      cout << e.what();
    }
    cout << endl;
  }
  return 0;
}
