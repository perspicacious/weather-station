#include "helperfuncs.h"

//get the console window buffer Width
int GetBufferWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	int bufferWidth, result;

	result = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

	if (result)
	{
		bufferWidth = bufferInfo.dwSize.X;
	}

	return bufferWidth;
}

//output text with word wrap
void OutputText(string s)
{
	int bufferWidth = GetBufferWidth();

	for (unsigned int i = 1; i <= s.length(); i++)
	{
		char c = s[i - 1];

		int spaceCount = 0;

		// Add whitespace if newline detected.
		if (c == '\n')
		{
			int charNumOnLine = ((i) % bufferWidth);
			spaceCount = bufferWidth - charNumOnLine;
			s.insert((i - 1), (spaceCount), ' ');			//insert space before newline break
			i += (spaceCount);							//jump forward in string to character at beginning of next line
			continue;
		}

		if ((i % bufferWidth) == 0)
		{
			if (c != ' ')
			{
				for (int j = (i - 1); j > -1; j--)
				{
					if (s[j] == ' ')
					{
						s.insert(j, spaceCount, ' ');
						break;
					}
					else spaceCount++;
				}
			}
		}
	}

	//output string to console
	cout << s;
}

//checks if a string is a number
bool is_number(const string& q)
{
	string::const_iterator it = q.begin();
	if (q[0] == '-' || q[0] == '+'){
		it++;
	}
	while (it != q.end() && isdigit(*it)){
		++it;
	}
	return !q.empty() && it == q.end();
}