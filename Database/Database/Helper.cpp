#include "Helper.h"

std::vector<std::string> splitLine(const std::string& line)
{
	std::vector<std::string> result;
	std::string currString;
	for (unsigned int i = 0; i < line.size() ; i++)
	{
		if (line[i] == ' ')
		{
			if (currString != "")
			{
				result.push_back(currString);
			}
			currString = "";
		}
		else if (line[i] == '"')
		{
			for (unsigned int j = i; j < line.size(); j++)
			{
				currString += line[j];
				if (line[j] == '"' && j != i)
				{
					i = j;
					result.push_back(currString);
					currString = "";
					break;
				}
			}
		}
		else
		{
			currString += line[i];
		}
	}
	if (currString.size() > 0)
	{
		result.push_back(currString);
	}
	return result;
}