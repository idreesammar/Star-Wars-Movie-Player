#include <fstream>
#include <iostream>
#include <sstream>
#include "movie.h"

MoviePlayer::MoviePlayer(std::string filmName)
{
	// set appropriate member variables
	mFilmName = filmName;
	currFrameNum = 1;

	// clear the film
	mFilm.clear();
	
	loadTape(); // load film using input
	
	pos = mFilm.begin();
}

MoviePlayer::~MoviePlayer()
{
	// empties the list
	mFilm.clear();
}

void MoviePlayer::goFwrd()
{
	// make sure frames viewed hasn't passed total number of frames (can't go past end of movie)
	if (currFrameNum < getNumFrames()) //  
	{
		currFrameNum++; // increment the current frame forward by 1
		pos++;
	}
}

void MoviePlayer::goBack()
{
	// make sure frames viewed can't go before 0 (out of range error)
	if (currFrameNum > 1)  // 
	{
		currFrameNum--; // decrement the current frame back by 1
		pos--;
	}
}

void MoviePlayer::rewind()
{
	// sets current frame back to the beginning
	currFrameNum = 1;
	pos = mFilm.begin();
}

std::string MoviePlayer::getCurrFrame()
{
	// return string with contents of current frame
	return *pos;
}

void MoviePlayer::delCurrFrame()
{
	if (getCurrFrameNum() < getNumFrames())  // to avoid issues of deleting final frame (should do nothing)
	{
		// erase the current frame and move forward one
		ITPDoubleList<std::string>::Iterator temp = pos; // to match the current frame (so pos doesnt get deleted)
		pos++; // increment to next frame
		mFilm.erase(temp); // erase the current frame element
		// currFrameNum shouldn't change because since a frame was deleted the next will carry current frame number
	}
}

void MoviePlayer::copyCurrFrame()
{
	std::string copy = getCurrFrame(); // obtain the current frame/string to copy
	mFilm.insert(pos, copy); // insert the copy before the location of the currentFrame
	pos--; // set to newly added frame
	// currFrameNum shouldn't change because we are now pointing the newly inserted frame which took over the currentFrame's location
	// since it was pushed over one
}


unsigned MoviePlayer::getCurrFrameNum() const
{
	// return the "current" currFrame counter
	return currFrameNum;
}

unsigned int MoviePlayer::getNumFrames() const
{
	// return total number of frames in the movie
	return mFilm.size();
}

unsigned int MoviePlayer::getFrameSize() const
{
	// gets the number of lines in a frame
	return FRAMESIZE;
}

void MoviePlayer::loadTape()
{
	// open the inputted file
	std::ifstream fileStream(mFilmName); // assume appropriate file name given

	if (fileStream.is_open())  // if the input file was successfully opened
	{
		// will continue looping till reaching end of the file
		while (!(fileStream.eof()))  // while the end has not been reached
		{
			std::string sepLine; // separate frames in the file + tells how many times each frame should be added to tape
			std::getline(fileStream, sepLine);
			// make sure an actual number (indicating a frame and not a spare line is present) --> isdigit checks to see if char in ascii range for digits
			if (std::isdigit(sepLine[0]))  // checks first char's ascii values to match in range of 0-9
			{
				int separatorNum = std::stoi(sepLine); // since sepLine is confirmed a number, convert string to int
				std::string frame;
				std::string line; // each line of the frame

				// use loop to get lines of the frame
				for (int i = 0; i < FRAMESIZE; i++)
				{
					std::getline(fileStream, line); // obtain the input line from the file

					if (line.length() == 0) // for blank lines read in
					{
						line += " "; // add a space
					}

					frame += line; // add each line to the frame string object

					if (line[line.size() - 1] == '\\')  // to fix issue with lines ending with backslash
					{
						frame += " "; // add a space
					}

					frame += "\n"; // add newline
				}

				// add the frame separtorNum times
				for (int i = 0; i < separatorNum; i++)
				{
					mFilm.push_back(frame); // add the frame to the tape
				}
			}
		}

		fileStream.close(); // close the file
	}
	else // file could not be found or opened
	{
		throw std::invalid_argument("Error: file was not found");
	}
}

