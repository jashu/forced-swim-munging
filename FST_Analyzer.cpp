#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

enum BehaviorType {I,S,C};
const unsigned short NUM_BEHAVIORS = 3;
const unsigned short NUM_MINS = 5;

//helper function to convert behavior (char) into index (int)
unsigned short getIndex (char behav)
{
	unsigned short index;
	if (behav == 'I')
		index = I;
	else if (behav == 'S')
		index = S;
	else if (behav == 'C')
		index = C;
	else
		cerr << "Error with behavioral coding.";
	return index;
}

//helper function to write and empty contents of output stack
ostream& write (ostream & out, stack < unsigned short, vector<unsigned short> > & behavior)
{
	while (!behavior.empty())
	{
		out << behavior.top() << "\t";
		behavior.pop();
	}
	return out;
}

int main()
{
	string subject;
	unsigned short minute, second, totals[NUM_BEHAVIORS];
	stack < unsigned short, vector<unsigned short> > min, sec, immobile, swim, climb;
	char behavior;
	stack < char, vector<char> > behav;
	ifstream in("FSTdata.txt");

	if (!in.fail())
	{
		ofstream out ("FSTsummary.txt");

		if (!out.fail())
		{
			// Output column headings
			out << "Subj\tI1\tI2\tI3\tI4\tI5\tS1\tS2\tS3\tS4\tS5\tC1\tC2\tC3\tC4\tC5" << endl;

			while (!in.eof())
			{
				behavior = 0;
				// Push each subject's data except for the last line (ending in 'E')
				while (in >> subject >> minute >> second >> behavior && behavior != 'E')
				{
					min.push(minute);
					sec.push(second);
					behav.push(behavior);
				}

				// Make sure there is valid data to process by checking for a successful read
				// (by making sure an 'E' for end of test was registered)
				if (behavior == 'E')
				{
					// Process the total seconds spent doing each behavior during each minute t.
					for (short t = NUM_MINS-1; t >= 0; t--) 
					{
						// Reset totals to 0 before summing the behavior durations for the next minute of data.
						for (unsigned short i = 0; i < NUM_BEHAVIORS; i++)
							totals[i] = 0;

						// A new minute is starting, so start with a full 60 seconds.
						second = 60;

						// While there are still minutes left on the stack 
						// and while the value at the top of the minute stack is equal to the current minute,
						while (!min.empty() && min.top() == t)
						{
							// Subtract from previous time in seconds (or from 60 if new minute), and
							// add the seconds for the current behavior to the corresponding element in the totals array.
							totals[getIndex(behav.top())] += second-sec.top();

							// Retain the value of _second_ for the next subtraction, and pop off used data.
							second = sec.top();
							min.pop();
							sec.pop();
							behav.pop();
						}

						// Add any remaining seconds for the current behavior to the corresponding totals array element.
						if (!min.empty())
							totals[getIndex(behav.top())] += second;

						// Push the behavior totals for the current minute of the current subject onto the output stacks.
						immobile.push(totals[I]);
						swim.push(totals[S]);
						climb.push(totals[C]);
					}

					// Write the current subject's summary data on a new line.
					out << subject << "\t";
					write(out,immobile);
					write(out,swim);
					write(out,climb);
					out << endl;
				}
			}
		}
		else
		{
			cerr << "Output file failed to open." << endl;
			system("Pause");
		}
	}
	else
	{
		cerr << "Input file failed to open." << endl;
		system("Pause");
	}

	return 0;
}