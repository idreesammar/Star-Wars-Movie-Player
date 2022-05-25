#include <string>
#include <sstream>
#include <fstream>

#include "catch.hpp"
#include "ITPMemLeaks.h"
#include "ITPDoubleList.hpp"
#include <iostream>
#include "movie.h"


// Helper function declarations (don't change this)
extern bool CheckTextFilesSame(const std::string& fileNameA,
	const std::string& fileNameB);

TEST_CASE("Student list tests", "[student]")
{
	SECTION("Default constructor, size, and destructor")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor

			// double linked list already made above with default constructor
			REQUIRE(dl.size() == 0); // check size set to 0
			REQUIRE(dl.toString() == "{}");  // check toString is appropriately empty
			REQUIRE(dl.toReverseString() == "{}");

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("Push_front, front, back")  // exceptions are NOT being checked in this section
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor

			dl.push_front(5); // add an element
			REQUIRE(dl.size() == 1); // check size increased
			REQUIRE(dl.front() == 5); // check element appropriately placed in front
			REQUIRE(dl.back() == 5); // check element appropriately placed in back

			dl.push_front(4);
			REQUIRE(dl.size() == 2); // check size increased
			REQUIRE(dl.front() == 4); // check element appropriately placed in front
			REQUIRE(dl.back() == 5); // check element appropriately placed in back

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}
	
	SECTION("Push_front, front, back, pop_front")  // exceptions not checked in this section 
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor

			dl.push_front(1); // add an element
			dl.push_front(0);
			REQUIRE(dl.size() == 2); // check size increased
			REQUIRE(dl.front() == 0); // check element appropriately placed in front
			REQUIRE(dl.back() == 1); // check element appropriately placed in back

			// try pop_front and check size and front changed
			dl.pop_front();
			REQUIRE(dl.size() == 1); // check size increased
			REQUIRE(dl.front() == 1); // check element appropriately placed in front
			REQUIRE(dl.back() == 1); // check element appropriately placed in back

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("Push_back, front, back")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor

			// add elements
			dl.push_back(1);
			dl.push_back(2);
			// check size and element change
			REQUIRE(dl.size() == 2); // check size increased
			REQUIRE(dl.front() == 1); // check element appropriately placed in front
			REQUIRE(dl.back() == 2); // check element appropriately placed in front

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("Push_back, front, back, pop_back")  // exceptions not checked here
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor

			// add elemeents with push back
			dl.push_back(1);
			dl.push_back(2);

			// check front, back ,size
			REQUIRE(dl.size() == 2); // check size increased
			REQUIRE(dl.front() == 1); // check element appropriately placed in front
			REQUIRE(dl.back() == 2); // check element appropriately placed in front

			// use pop back and then check again
			dl.pop_back();
			REQUIRE(dl.size() == 1); // check size increased
			REQUIRE(dl.front() == 1); // check element appropriately placed in front
			REQUIRE(dl.back() == 1); // check element appropriately placed in front

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("Push_back, clear")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor

			// add elements with push back
			dl.push_back(1);
			dl.push_back(2);
			dl.push_back(3);
			REQUIRE(dl.size() == 3);

			// now use clear and check size
			dl.clear();
			REQUIRE(dl.size() == 0);

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}
	
	
	SECTION("Push_back, front, back, pop_back, copy constructor")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor
			// add elements with push back
			dl.push_back(1);
			dl.push_back(2);
			dl.push_back(3);

			ITPDoubleList<int> dl2 = dl; // check copy constructor;

			// check front, back of newList
			REQUIRE(dl2.front() == dl.front());
			REQUIRE(&(dl2.front()) != &(dl.front())); // address should be dif for deepy copy
			REQUIRE(dl2.back() == dl.back());
			REQUIRE(&(dl2.back()) != &(dl.back())); // address should be dif for deepy copy

			// use popback on dl2 (should match original list's second to last element)
			dl2.pop_back();
			REQUIRE(dl2.back() == 2); // should be 10

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("Push_back, front, back, pop_back, assignment")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor
			// add elements with push back
			dl.push_back(1);
			dl.push_back(2);
			dl.push_back(3);

			ITPDoubleList<int> dl2; // create new doubly linked list
			dl2 = dl; // use the assignment operator

			// check front, back of newList
			REQUIRE(dl2.front() == dl.front());
			REQUIRE(&(dl2.front()) != &(dl.front())); // address should be dif for deepy copy
			REQUIRE(dl2.back() == dl.back());
			REQUIRE(&(dl2.back()) != &(dl.back())); // address should be dif for deepy copy

			// use popback on dl2 (should match original list's second to last element)
			dl2.pop_back();
			REQUIRE(dl2.back() == 2); // should be 10

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("Back, front, pop_front, pop_back, exceptions")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor

			// currently size is 0 so these functions  should throw error
			std::ostringstream oss; // output string stream

			// 1st check front
			try
			{
				dl.front(); // should not work 
			}
			catch (const std::exception& e)
			{
				oss << e.what();
			}
			REQUIRE(oss.str() == "Error: no elements currently in list!"); // check error message is appropriate

			// 2nd check pop_front
			try
			{
				dl.pop_front(); // should not work 
			}
			catch (const std::exception& e)
			{
				oss.clear();
				oss.str("");
				oss << e.what();
			}
			REQUIRE(oss.str() == "Error: no elements currently in list!"); // check error message is appropriate

			// 3rd check back
			try
			{
				dl.back(); // should not work 
			}
			catch (const std::exception& e)
			{
				oss.clear();
				oss.str("");
				oss << e.what();
			}
			REQUIRE(oss.str() == "Error: no elements currently in list!"); // check error message is appropriate

			// 4th check pop back
			try
			{
				dl.pop_back(); // should not work 
			}
			catch (const std::exception& e)
			{
				oss.clear();
				oss.str("");
				oss << e.what();
			}
			REQUIRE(oss.str() == "Error: no elements currently in list!"); // check error message is appropriate

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("Push_front, front, back, begin, iterator dereference, copy constructor")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor
			// add elements with push back
			dl.push_front(3);
			dl.push_front(2);
			dl.push_front(1);

			// create iterator with copy constructor
			ITPDoubleList<int>::Iterator it = dl.begin();

			// testing begin versus iterator deref value
			REQUIRE(*it == dl.front()); // make sure begins properly assings pointer to first element (check with iterator dereference)

			// check iterator dereference value verusus back
			it++;
			it++; // now iterator matches last element of list
			REQUIRE(*it == dl.back());

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}
	
	SECTION("List: begin, end; Iterator: dereference, assignment, comparison")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor
			// add elements with push back
			dl.push_back(1);
			dl.push_back(2);
			dl.push_back(3);

			// create iterators for testing 
			ITPDoubleList<int>::Iterator it; // create iterator (no copy constructor)
			ITPDoubleList<int>::Iterator beg = dl.begin(); // this one uses copy constructor
			ITPDoubleList<int>::Iterator end = dl.end(); // this one uses copy constructor

			// use assignment operator for constructor
			it = dl.begin();
			REQUIRE(it == beg); // check comparison operator

			// testing begin versus iterator deref value (checks if assignment operator works)
			REQUIRE(*it == dl.front()); // make sure begins properly assings pointer to first element (check with iterator dereference)

			it = dl.end(); // one past the last element
			REQUIRE(it == end); // check comparison operator

			// check iterator dereference value verusus back (check assignent operator works)
			it = dl.begin();
			it++;
			it++; // now at end

			REQUIRE(*it == dl.back()); // make sure end properly assings pointer to one past last element (check with iterator dereference)

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("List: begin, end; Iterator: dereference, increment")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor
			// add elements with push back
			dl.push_back(1);
			dl.push_back(2);
			dl.push_back(3);

			// create iterator with copy constructor
			ITPDoubleList<int>::Iterator it = dl.begin();
			REQUIRE(*it == dl.front()); // test begin works

			// test dereference and iterator increment
			for (int x : dl)
			{
				REQUIRE(*it == x);
				it++;
			}

			// another test for iterator increment, going up to end(), and dereference
			std::ostringstream oss; // output string stream
			for (auto i = dl.begin(); i != dl.end(); i++)
			{
				oss << *i;
			}
			REQUIRE(oss.str() == "123");

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("List: begin, end; Iterator: dereference, increment, decrement")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor
			// add elements with push back
			dl.push_back(1);
			dl.push_back(2);
			dl.push_back(3);

			// create iterator with copy constructor
			ITPDoubleList<int>::Iterator it = dl.begin();
			REQUIRE(*it == dl.front()); // test begin works

			// test dereference and iterator increment
			for (int x : dl)
			{
				REQUIRE(*it == x);
				it++;
			}

			// create another iterator for decrement testing
			ITPDoubleList<int>::Iterator it2 = dl.begin();
			it2++;
			it2++; // now at last element, 3

			// test for iterator decrement and dereference
			std::ostringstream oss; // output string stream
			for (int i = dl.size() - 1; i > 0; i--)
			{
				oss << *(it2);
				it2--;
			}
			oss << *it2; // for last element
			REQUIRE(oss.str() == "321"); // confirms decrement worked appropriately

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("List: insert with iterator at begin, middle, and one away from end")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor
			// add elements with push back
			dl.push_back(1);
			dl.push_back(2);
			dl.push_back(3);

			ITPDoubleList<int>::Iterator it = dl.begin(); // create iterator

			// insert using a range-based loop
			for (it; it != dl.end(); it++)
			{
				dl.insert(it, 4); // insert a 4 before the each iterator pointer, (includes beginning, middle and one away from end)
			}

			// output values to stream for testing
			std::ostringstream oss; // output string stream
			for (int x : dl)
			{
				oss << x;
			}

			// confirm insert approprately inserted new nodes/iterator 
			REQUIRE(dl.front() == 4); // check for successful insertion befor original starting value
			REQUIRE(oss.str() == "414243"); // check if 4 was inserted before all 3 desired points mentioned

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}
	
	SECTION("List: erase with iterator at begin, middle, and one away from end")
	{
		{
			ITPDoubleList<int> dl;  // made with default constructor
			// add elements with push back
			dl.push_back(1);
			dl.push_back(2);
			dl.push_back(3);
			dl.push_back(4);
			dl.push_back(5);
			dl.push_back(6); // elements in dl now {1 2 3 4 5 6}

			// test erasing when iterator at begin
			ITPDoubleList<int>::Iterator itTemp = dl.begin(); // create iterator
			auto it2 = dl.erase(itTemp);
			REQUIRE(dl.front() == 2); // confirm erasure of begin iterator
			REQUIRE(*it2 == 2);
			REQUIRE(dl.size() == 5);

			// test erasing when iterator at middle
			ITPDoubleList<int>::Iterator itSecondTemp = dl.begin(); // create iterator
			itSecondTemp++;
			itSecondTemp++; // now pointin at 4
			auto it5 = dl.erase(itSecondTemp);
			REQUIRE(*it5 == 5);
			REQUIRE(dl.size() == 4);

			// test erasing when iterator at one away from end
			ITPDoubleList<int>::Iterator itThirdTemp = dl.begin(); // create iterator 
			itThirdTemp++;
			itThirdTemp++;
			itThirdTemp++; // now one away from end, at last element 6
			auto itEnd = dl.erase(itThirdTemp);
			REQUIRE(itEnd == dl.end());
			REQUIRE(dl.size() == 3);

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}
	
}

TEST_CASE("Student movie", "[student]")
{
	SECTION("Bad constructor")
	{
		// make sure an exception is thrown if user attempts to read a file that does not exist
		std::ostringstream oss; // output string stream
		try
		{
			MoviePlayer myMovie = MoviePlayer("fail.ani");
		}
		catch (const std::exception& e)
		{
			oss << e.what();
		}
		REQUIRE(oss.str() == "Error: file was not found");

		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}
	
	SECTION("Creating scene 2")
	{
		MoviePlayer myMovie = MoviePlayer("input/scene2.ani");
		
		// check number frames, current frames, etc. 
		REQUIRE(myMovie.getNumFrames() == 69);
		REQUIRE(myMovie.getCurrFrameNum() == 1);
		REQUIRE(myMovie.getFrameSize() == 13);

		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}

	SECTION("Checking frames, scene 2")
	{
		{
			MoviePlayer myMovie = MoviePlayer("input/scene2.ani");

			// obtain output of first frames
			std::ostringstream oss; // output string stream
			std::ifstream inputFile("input/scene2.ani");
			std::string frame;
			std::string line;
			std::getline(inputFile, line); // get the number to ignore
			// use loop to get lines of the frame
			for (int i = 0; i < myMovie.getFrameSize(); i++)
			{
				std::getline(inputFile, line); // obtain the input line from the file
				frame += line; // add each line to the frame string object
				if (line[line.size() - 1] == '\\')
				{
					frame += " "; // to fix issue with lines ending with backslash
				}
				frame += "\n"; // add newline
			}
			oss << frame; // place frame in output stream
			inputFile.close();

			// test to make sure current frame (which should be frame 1) matches what was outputted
			REQUIRE(myMovie.getCurrFrame() == oss.str());

		}
		// Leave this at the end
		REQUIRE(ITPMemLeaks::CheckIfMemoryFreed());
	}
	
}
