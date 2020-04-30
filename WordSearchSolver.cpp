#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>
#include <Windows.h>
using namespace std;
using namespace std;

enum direction { up_right, up, up_left, lleft, down_left, down, down_right, rright };

const short NUM_DIRECTIONS = 8;

int main()
{
	string input;
	vector<vector<char>> words;
	vector<char> line;
	int xPos0;
	int yPos0;
	int xPos1;
	int yPos1;
	ifstream in;
	direction mode;
	bool found = false;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<int> foundX;
	vector<int> foundY;
	bool colorText = false;

	in.open("Search.txt");
	if (!in.fail())
	{
		while (in >> input)
		{
			line.clear();
			for (int i = 0; i < input.length(); i++)
				line.push_back(input[i]);
			words.push_back(line);
		}

		do
		{
			for (int i = 0; i < words.size(); i++)
			{
				for (int j = 0; j < words[i].size(); j++)
				{
					//if (found)
					//{
						for (int k = 0; k < foundX.size() && !colorText; k++)
						{
							if (i == foundY[k] && j == foundX[k])
							{
								SetConsoleTextAttribute(hConsole, 12);
								colorText = true;
							}
						}
					//}
					cout << words[i][j] << ' ';
					//cout << '(' << i << ',' << j << ')';
					if (colorText)
					{
						SetConsoleTextAttribute(hConsole, 15);
						colorText = false;
					}
				}
				cout << endl;

				//if (t = !t)
				//	SetConsoleTextAttribute(hConsole, 15);	//White
				//else
				//	SetConsoleTextAttribute(hConsole, 12);	//Red
			}
			cout << endl;

			cout << "Enter: ";
			cin >> input;

			if (input == "xxx")
			{
				cout << endl;
				continue;
			}

			found = false;

			for (int i = 0; i < words.size() && !found; i++)
			{
				for (int j = 0; j < words[i].size() && !found; j++)
				{
					if (words[i][j] == input[0])
					{
						if (input.length() <= 1)
						{
							xPos0 = j;
							yPos0 = i;
							xPos1 = j;
							yPos1 = i;
							found = true;
						}

						mode = up_right;
						for (int k = 0; k < NUM_DIRECTIONS && !found; k++)
						{
							switch (mode)
							{
								case up_right:
									if (i - 1 >= 0 && j + 1 < words[i].size() && words[i - 1][j + 1] == input[1])
									{
										xPos0 = j;
										yPos0 = i;
										for (int l = 2; i - l > 0 && j + l < words[i].size() && l < input.size() && words[i - l][j + l] == input[l] && !found; l++)
										{
											if (l == input.size() - 1)
											{
												xPos1 = j + l;
												yPos1 = i - l;
												found = true;
											}
										}
									}
									if (!found)
										mode = up;
									break;
								case up:
									if (i - 1 >= 0 && words[i - 1][j] == input[1])
									{
										xPos0 = j;
										yPos0 = i;
										for (int l = 2; i - l >= 0 && l < input.size() && words[i - l][j] == input[l] && !found; l++)
										{
											if (l == input.size() - 1)
											{
												xPos1 = j;
												yPos1 = i - l;
												found = true;
											}
										}
									}
									if (!found)
										mode = up_left;
									break;
								case up_left:
									if (i - 1 >= 0 && j - 1 >= 0 && words[i - 1][j - 1] == input[1])
									{
										xPos0 = j;
										yPos0 = i;
										for (int l = 2; i - l >= 0 && j - l >= 0 && l < input.size() && words[i - l][j - l] == input[l] && !found; l++)
										{
											if (l == input.size() - 1)
											{
												xPos1 = j - l;
												yPos1 = i - l;
												found = true;
											}
										}
									}
									if (!found)
										mode = lleft;
									break;
								case lleft:
									if (j - 1 >= 0 && words[i][j - 1] == input[1])
									{
										xPos0 = j;
										yPos0 = i;
										for (int l = 2; j - l >= 0 && l < input.size() && words[i][j - l] == input[l] && !found; l++)
										{
											if (l == input.size() - 1)
											{
												xPos1 = j - l;
												yPos1 = i;
												found = true;
											}
										}
									}
									if (!found)
										mode = down_left;
									break;
								case down_left:
									if (i + 1 < words.size() && j - 1 >= 0 && words[i + 1][j - 1] == input[1])
									{
										xPos0 = j;
										yPos0 = i;
										for (int l = 2; i + l < words.size() && j - l >= 0 && l < input.size() && words[i + l][j - l] == input[l] && !found; l++)
										{
											if (l == input.size() - 1)
											{
												xPos1 = j - l;
												yPos1 = i + l;
												found = true;
											}
										}
									}
									if (!found)
										mode = down;
									break;
								case down:
									if (i + 1 < words.size() && words[i + 1][j] == input[1])
									{
										xPos0 = j;
										yPos0 = i;
										for (int l = 2; i + l < words.size() && l < input.size() && words[i + l][j] == input[l] && !found; l++)
										{
											if (l == input.size() - 1)
											{
												xPos1 = j;
												yPos1 = i + l;
												found = true;
											}
										}
									}
									if (!found)
										mode = down_right;
									break;
								case down_right:
									if (i + 1 < words.size() && j + 1 < words[i].size() && words[i + 1][j + 1] == input[1])
									{
										xPos0 = j;
										yPos0 = i;
										for (int l = 2; i + l < words.size() && j + l < words[i].size() && l < input.size() && words[i + l][j + l] == input[l] && !found; l++)
										{
											if (l == input.size() - 1)
											{
												xPos1 = j + l;
												yPos1 = i + l;
												found = true;
											}
										}
									}
									if (!found)
										mode = rright;
									break;
								case rright:
									if (j + 1 < words[i].size() && words[i][j + 1] == input[1])
									{
										xPos0 = j;
										yPos0 = i;
										for (int l = 2; j + l < words[i].size() && l < input.size() && words[i][j + l] == input[l] && !found; l++)
										{
											if (l == input.size() - 1)
											{
												xPos1 = j + l;
												yPos1 = i;
												found = true;
											}
										}
									}
									break;
								default:
									cout << "Something went wrong.\n";
							}
						}
					}
				}
			}
			if (found)
			{
				cout << "Start: (" << xPos0 << ',' << yPos0 << ")\n";
				cout << "End:   (" << xPos1 << ',' << yPos1 << ")\n";
				cout << endl;

				//foundX.clear();
				//foundY.clear();
				switch (mode)
				{
					case up_right:
						foundX.push_back(xPos0);
						foundY.push_back(yPos0);
						for (int j = xPos0 + 1; j <= xPos1; j++)
							foundX.push_back(j);
						for (int i = yPos0 - 1; i >= yPos1; i--)
							foundY.push_back(i);
						break;
					case up:
						foundX.push_back(xPos0);
						foundY.push_back(yPos0);
						for (int i = yPos0 - 1; i >= yPos1; i--)
						{
							foundX.push_back(xPos0);
							foundY.push_back(i);
						}
						break;
					case up_left:
						foundX.push_back(xPos0);
						foundY.push_back(yPos0);
						for (int j = xPos0 - 1; j >= xPos1; j--)
							foundX.push_back(j);
						for (int i = yPos0 - 1; i >= yPos1; i--)
							foundY.push_back(i);
						break;
					case lleft:
						foundX.push_back(xPos0);
						foundY.push_back(yPos0);
						for (int j = xPos0 - 1; j >= xPos1; j--)
						{
							foundX.push_back(j);
							foundY.push_back(yPos0);
						}
						break;
					case down_left:
						foundX.push_back(xPos0);
						foundY.push_back(yPos0);
						for (int j = xPos0 - 1; j >= xPos1; j--)
							foundX.push_back(j);
						for (int i = yPos0 + 1; i <= yPos1; i++)
							foundY.push_back(i);
						break;
					case down:
						foundX.push_back(xPos0);
						foundY.push_back(yPos0);
						for (int i = yPos0 + 1; i <= yPos1; i++)
						{
							foundX.push_back(xPos0);
							foundY.push_back(i);
						}
						break;
					case down_right:
						foundX.push_back(xPos0);
						foundY.push_back(yPos0);
						for (int j = xPos0 + 1; j <= xPos1; j++)
							foundX.push_back(j);
						for (int i = yPos0 + 1; i <= yPos1; i++)
							foundY.push_back(i);
						break;
					case rright:
						foundX.push_back(xPos0);
						foundY.push_back(yPos0);
						for (int j = xPos0 + 1; j <= xPos1; j++)
						{
							foundX.push_back(j);
							foundY.push_back(yPos0);
						}
						break;
					default:
						cout << "Something went wrong.\n";
				}
			}
			else
			{
				cout << "\"" << input << "\" was not found.\n";
				cout << endl;
			}
		} while (input != "xxx");
	}
	else
	{
		cout << "Could not find Search.txt.\n";
		cout << endl;
	}

	in.close();

	system("Pause");
	return 0;
}