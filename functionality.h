/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

// All the function prototypes
void anomalyCheck();
void rightLeftMovement(int &);
void rotation(bool &);
void deleteLines(int &);
void spacebarDown(int);
void setShadowPoint(int);

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float &timer, float &delay, int &colorNum, int &delta_x, int &currentBlock, int &score)
{
	if (timer > delay)
	{
		for (int i = 0; i < 4; i++)
		{
			rightLeftMovement(delta_x);
		}
		for (int i = 0; i < 4; i++)
		{
			point_2[i][0] = point_1[i][0];
			point_2[i][1] = point_1[i][1];
			point_1[i][1] += 1; // How much units downward
		}
		if (!anomaly())
		{
			// printGrid();
			deleteLines(score);
			for (int i = 0; i < 4; i++)
			{
				gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
			}
			colorNum = 1 + rand() % 7;
			int n = rand() % 7;
			currentBlock = n;
			for (int i = 0; i < 4; i++)
			{
				point_1[i][0] = BLOCKS[n][i] % 2;
				point_1[i][1] = BLOCKS[n][i] / 2;
			}
		}
		timer = 0;
	}
	delay = 0.3;
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

// Function to make the current piece fall all the way down when spacebar key is pressed
void spacebarDown(int currentBlock)
{
	if (currentBlock == -1)
	{
		int maxDepth = M - 1;
		point_1[0][1] = maxDepth;
		point_1[1][1] = maxDepth;
		point_1[2][1] = maxDepth;
		point_1[3][1] = maxDepth;
	}
	else if (currentBlock == 0)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[2][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[2][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthFirstColumn <= maxDepthSecondColumn)
		{
			point_1[0][1] = maxDepthFirstColumn - 2;
			point_1[1][1] = maxDepthFirstColumn - 2;
			point_1[2][1] = maxDepthFirstColumn - 1;
			point_1[3][1] = maxDepthFirstColumn - 1;
		}
		else
		{
			point_1[0][1] = maxDepthSecondColumn - 2;
			point_1[1][1] = maxDepthSecondColumn - 2;
			point_1[2][1] = maxDepthSecondColumn - 1;
			point_1[3][1] = maxDepthSecondColumn - 1;
		}
	}
	else if (currentBlock == 1)
	{
		int maxDepth = M - 1;
		for (int i = point_1[4][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[4][0]] != 0)
			{
				maxDepth = i;
				break;
			}
		}
		point_1[0][1] = maxDepth - 4;
		point_1[1][1] = maxDepth - 3;
		point_1[2][1] = maxDepth - 2;
		point_1[3][1] = maxDepth - 1;
	}
	else if (currentBlock == 2)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[1][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[1][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if ((maxDepthFirstColumn <= maxDepthSecondColumn) || ((maxDepthFirstColumn - maxDepthSecondColumn) < 3))
		{
			point_1[0][1] = maxDepthFirstColumn - 3;
			point_1[1][1] = maxDepthFirstColumn - 3;
			point_1[2][1] = maxDepthFirstColumn - 2;
			point_1[3][1] = maxDepthFirstColumn - 1;
		}
		else if ((maxDepthFirstColumn - maxDepthSecondColumn) >= 3)
		{
			point_1[0][1] = maxDepthSecondColumn - 1;
			point_1[1][1] = maxDepthSecondColumn - 1;
			point_1[2][1] = maxDepthSecondColumn;
			point_1[3][1] = maxDepthSecondColumn + 1;
		}
	}
	else if (currentBlock == 3)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[2][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[2][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthFirstColumn <= maxDepthSecondColumn)
		{
			point_1[0][1] = maxDepthFirstColumn - 2;
			point_1[1][1] = maxDepthFirstColumn - 2;
			point_1[2][1] = maxDepthFirstColumn - 1;
			point_1[3][1] = maxDepthFirstColumn - 1;
		}
		else
		{
			point_1[0][1] = maxDepthSecondColumn - 2;
			point_1[1][1] = maxDepthSecondColumn - 2;
			point_1[2][1] = maxDepthSecondColumn - 1;
			point_1[3][1] = maxDepthSecondColumn - 1;
		}
	}
	else if (currentBlock == 4)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[1][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[1][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthSecondColumn <= maxDepthFirstColumn)
		{
			point_1[0][1] = maxDepthSecondColumn - 3;
			point_1[1][1] = maxDepthSecondColumn - 2;
			point_1[2][1] = maxDepthSecondColumn - 2;
			point_1[3][1] = maxDepthSecondColumn - 1;
		}
		else
		{
			point_1[0][1] = maxDepthFirstColumn - 2;
			point_1[1][1] = maxDepthFirstColumn - 1;
			point_1[2][1] = maxDepthFirstColumn - 1;
			point_1[3][1] = maxDepthFirstColumn;
		}
	}
	else if (currentBlock == 5)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[2][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[2][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthFirstColumn <= maxDepthSecondColumn)
		{
			point_1[0][1] = maxDepthFirstColumn - 3;
			point_1[1][1] = maxDepthFirstColumn - 2;
			point_1[2][1] = maxDepthFirstColumn - 2;
			point_1[3][1] = maxDepthFirstColumn - 1;
		}
		else
		{
			point_1[0][1] = maxDepthSecondColumn - 2;
			point_1[1][1] = maxDepthSecondColumn - 1;
			point_1[2][1] = maxDepthSecondColumn - 1;
			point_1[3][1] = maxDepthSecondColumn;
		}
	}
	else if (currentBlock == 6)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[1][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[1][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthSecondColumn <= maxDepthFirstColumn)
		{
			point_1[0][1] = maxDepthSecondColumn - 3;
			point_1[1][1] = maxDepthSecondColumn - 2;
			point_1[2][1] = maxDepthSecondColumn - 2;
			point_1[3][1] = maxDepthSecondColumn - 1;
		}
		else
		{
			point_1[0][1] = maxDepthFirstColumn - 2;
			point_1[1][1] = maxDepthFirstColumn - 1;
			point_1[2][1] = maxDepthFirstColumn - 1;
			point_1[3][1] = maxDepthFirstColumn;
		}
	}
	anomalyCheck();
}

void setShadowPoint(int currentBlock)
{
	shadowPoint[0][0] = point_1[0][0];
	shadowPoint[1][0] = point_1[1][0];
	shadowPoint[2][0] = point_1[2][0];
	shadowPoint[3][0] = point_1[3][0];
	if (currentBlock == -1)
	{
		int maxDepth = M - 1;
		shadowPoint[0][1] = maxDepth;
		shadowPoint[1][1] = maxDepth;
		shadowPoint[2][1] = maxDepth;
		shadowPoint[3][1] = maxDepth;
	}
	else if (currentBlock == 0)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[2][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[2][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthFirstColumn <= maxDepthSecondColumn)
		{
			shadowPoint[0][1] = maxDepthFirstColumn - 2;
			shadowPoint[1][1] = maxDepthFirstColumn - 2;
			shadowPoint[2][1] = maxDepthFirstColumn - 1;
			shadowPoint[3][1] = maxDepthFirstColumn - 1;
		}
		else
		{
			shadowPoint[0][1] = maxDepthSecondColumn - 2;
			shadowPoint[1][1] = maxDepthSecondColumn - 2;
			shadowPoint[2][1] = maxDepthSecondColumn - 1;
			shadowPoint[3][1] = maxDepthSecondColumn - 1;
		}
	}
	else if (currentBlock == 1)
	{
		int maxDepth = M - 1;
		for (int i = point_1[4][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[4][0]] != 0)
			{
				maxDepth = i;
				break;
			}
		}
		shadowPoint[0][1] = maxDepth - 4;
		shadowPoint[1][1] = maxDepth - 3;
		shadowPoint[2][1] = maxDepth - 2;
		shadowPoint[3][1] = maxDepth - 1;
	}
	else if (currentBlock == 2)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[1][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[1][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if ((maxDepthFirstColumn <= maxDepthSecondColumn) || ((maxDepthFirstColumn - maxDepthSecondColumn) < 3))
		{
			shadowPoint[0][1] = maxDepthFirstColumn - 3;
			shadowPoint[1][1] = maxDepthFirstColumn - 3;
			shadowPoint[2][1] = maxDepthFirstColumn - 2;
			shadowPoint[3][1] = maxDepthFirstColumn - 1;
		}
		else if ((maxDepthFirstColumn - maxDepthSecondColumn) >= 3)
		{
			shadowPoint[0][1] = maxDepthSecondColumn - 1;
			shadowPoint[1][1] = maxDepthSecondColumn - 1;
			shadowPoint[2][1] = maxDepthSecondColumn;
			shadowPoint[3][1] = maxDepthSecondColumn + 1;
		}
	}
	else if (currentBlock == 3)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[2][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[2][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthFirstColumn <= maxDepthSecondColumn)
		{
			shadowPoint[0][1] = maxDepthFirstColumn - 2;
			shadowPoint[1][1] = maxDepthFirstColumn - 2;
			shadowPoint[2][1] = maxDepthFirstColumn - 1;
			shadowPoint[3][1] = maxDepthFirstColumn - 1;
		}
		else
		{
			shadowPoint[0][1] = maxDepthSecondColumn - 2;
			shadowPoint[1][1] = maxDepthSecondColumn - 2;
			shadowPoint[2][1] = maxDepthSecondColumn - 1;
			shadowPoint[3][1] = maxDepthSecondColumn - 1;
		}
	}
	else if (currentBlock == 4)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[1][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[1][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthSecondColumn <= maxDepthFirstColumn)
		{
			shadowPoint[0][1] = maxDepthSecondColumn - 3;
			shadowPoint[1][1] = maxDepthSecondColumn - 2;
			shadowPoint[2][1] = maxDepthSecondColumn - 2;
			shadowPoint[3][1] = maxDepthSecondColumn - 1;
		}
		else
		{
			shadowPoint[0][1] = maxDepthFirstColumn - 2;
			shadowPoint[1][1] = maxDepthFirstColumn - 1;
			shadowPoint[2][1] = maxDepthFirstColumn - 1;
			shadowPoint[3][1] = maxDepthFirstColumn;
		}
	}
	else if (currentBlock == 5)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[2][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[2][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthFirstColumn <= maxDepthSecondColumn)
		{
			shadowPoint[0][1] = maxDepthFirstColumn - 3;
			shadowPoint[1][1] = maxDepthFirstColumn - 2;
			shadowPoint[2][1] = maxDepthFirstColumn - 2;
			shadowPoint[3][1] = maxDepthFirstColumn - 1;
		}
		else
		{
			shadowPoint[0][1] = maxDepthSecondColumn - 2;
			shadowPoint[1][1] = maxDepthSecondColumn - 1;
			shadowPoint[2][1] = maxDepthSecondColumn - 1;
			shadowPoint[3][1] = maxDepthSecondColumn;
		}
	}
	else if (currentBlock == 6)
	{
		int maxDepthFirstColumn = M - 1;
		int maxDepthSecondColumn = M - 1;
		for (int i = point_1[1][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[1][0]] != 0)
			{
				maxDepthFirstColumn = i;
				break;
			}
		}
		for (int i = point_1[3][1] + 1; i < M; i++)
		{
			if (gameGrid[i][point_1[3][0]] != 0)
			{
				maxDepthSecondColumn = i;
				break;
			}
		}
		if (maxDepthSecondColumn <= maxDepthFirstColumn)
		{
			shadowPoint[0][1] = maxDepthSecondColumn - 3;
			shadowPoint[1][1] = maxDepthSecondColumn - 2;
			shadowPoint[2][1] = maxDepthSecondColumn - 2;
			shadowPoint[3][1] = maxDepthSecondColumn - 1;
		}
		else
		{
			shadowPoint[0][1] = maxDepthFirstColumn - 2;
			shadowPoint[1][1] = maxDepthFirstColumn - 1;
			shadowPoint[2][1] = maxDepthFirstColumn - 1;
			shadowPoint[3][1] = maxDepthFirstColumn;
		}
	}
}

// Function that checks for anomaly cases and tells what to do if there are no anomalies
void anomalyCheck()
{
	if (!anomaly())
	{
		for (int i = 0; i < 4; i++)
		{
			point_1[i][0] = point_2[i][0];
			point_1[i][1] = point_1[i][1];
		}
	}
}

// Function to move the pieces horizontally
void rightLeftMovement(int &delta_x)
{
	for (int i = 0; i < 4; i++)
	{
		point_2[i][0] = point_1[i][0];
		point_2[i][1] = point_1[i][1];
		point_1[i][0] += delta_x;
	}
	anomalyCheck();
	delta_x = 0;
}

// Function to rotate the current piece about it's own axis
void rotation(bool &rotate)
{
	if (rotate)
	{
		int tempx = point_1[1][0];
		int tempy = point_1[1][1];
		for (int i = 0; i < 4; i++)
		{
			int eks = point_1[i][1] - tempy;
			int why = point_1[i][0] - tempx;
			point_1[i][0] = tempx - eks;
			point_1[i][1] = tempy + why;
		}
		anomalyCheck();
	}
	rotate = false;
}

// Function to delete a whole row of pieces when the row becomes filled
void deleteLines(int &score)
{
	int count = 0;
	int numRowsDeleted = 0;
	for (int currRow = point_1[0][1]; currRow < M; currRow++)
	{
		count = 0;
		for (int j = 0; j < N; j++)
		{
			if (gameGrid[currRow][j] != 0)
				count++;
		}
		if (count == N)
		{
			for (int colToNuke = 0; colToNuke < N; colToNuke++)
				gameGrid[currRow][colToNuke] = 0;
			for (int currRowAbove = currRow - 1; currRowAbove >= 0; currRowAbove--)
				for (int colToShift = 0; colToShift < N; colToShift++)
					gameGrid[currRowAbove + 1][colToShift] = gameGrid[currRowAbove][colToShift];
			numRowsDeleted++;
		}
	}
	if (numRowsDeleted == 1)
	{
		score += 10;
	}
	else if (numRowsDeleted == 2)
	{
		score += 30;
	}
	else if (numRowsDeleted == 3)
	{
		score += 60;
	}
	else if (numRowsDeleted == 4)
	{
		score += 100;
	}
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
