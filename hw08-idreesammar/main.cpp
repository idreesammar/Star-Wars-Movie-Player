#include <iostream>
#include <string>

#include "movie.h"
#include "gwindow.h"

// Function: getCurrFrame
// Purpose: Retrieves the current "frame" from the film list
// Modifies the inputted vector of GLabels to contain the current frame
// Input: A vector of "GLabels" that are the "screen" -- passed by reference
// Returns: Nothing
void getCurrFrame(GTerminal& term, MoviePlayer& mp)
{
	term.clear();
	std::string currFrame = mp.getCurrFrame();
	std::string line = "";
	std::stringstream ss(currFrame);

	for (unsigned i = 0; i < mp.getFrameSize(); i++)
	{
		std::getline(ss, line);
		line += "\n";
		term.appendText(line);
	}
}

int main(int argc, const char* argv[])
{
	unsigned msDelay = 60;
	std::string aniFile;
	std::cout << "Input file: ";
	std::cin >> aniFile;
	std::cout << "MS delay between frames: ";
	std::cin >> msDelay;

	GTerminal term(760, 330);
	term.showCursor(false);
	// Load the movie
	MoviePlayer player(aniFile);
	player.rewind();

	char state = 'p'; // The movie player's state

	while (1)
	{
		getCurrFrame(term, player);

		while (term.hasEvents())
		{
			GEvent e = term.getEvent();
			if (e.Type == EventType::KeyDown)
			{
				int key = e.Event.Key.Code;
				if (key == 'f' || key == 'b' || key == 'c' ||
					key == 'd' || key == 'p')
				{
					state = key;
				}
				else if (key == 'x')
				{
					return 0;
				}
			}
		}

		std::stringstream ss;
		ss << "___________________________________________________________________\n";
		switch (state)
		{
		case 'f':
			player.goFwrd();
			ss << "Playing forward, frame # " << player.getCurrFrameNum() << " of " << player.getNumFrames();
			break;
		case 'b':
			player.goBack();
			ss << "Playing backward, frame # " << player.getCurrFrameNum() << " of " << player.getNumFrames();
			break;
		case 'c':
			player.copyCurrFrame();
			ss << "Copied current frame...";
			state = 'p';
			break;
		case 'd':
			player.delCurrFrame();
			ss << "Deleted current frame...";
			state = 'p';
			break;
		case 'p':
			ss << "Paused, frame # " << player.getCurrFrameNum() << " of " << player.getNumFrames();
			break;
		}

		term.appendText(ss.str());
		term.appendText("\nf->forward  b->backward  p->pause  d->delete  c->copy  x->exit");

		pause(msDelay);
	}

	return 0;
}
