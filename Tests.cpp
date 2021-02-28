//#include "Tests.h"
//
//#include <assert.h>
//#include <iostream>
//
//#include "Square.h"
//
////typedef unsigned short (Square::*someFunc)()
//
//std::string gErrors[] = { "Rank out of bounds",
//						  "File out of bounds" };
//
////void basicSquareTest(Square s)
////{
////	for (size_t i = 0; i < num; i++)
////	{
////		if (!(testFunc(testSquares[i]) == funcAns[i]))
////		{
////			std::cout << "Error" << std::endl;
////		}
////	}
////}
//
//unsigned int testSquare()
//{
//
//	unsigned int errors = 0;
//	size_t numOfSquares = 9;
//	size_t i = 0;
//
//	Square tSquare0(2, 3);
//	Square tSquare1(1, 8);
//	Square tSquare2(8, 1);
//	Square tSquare3(4, 5);
//	Square tSquare4(6, 3);
//	Square tSquare5(8, 8);
//	Square tSquare6(1, 1);
//	Square tSquare7(5, 7);
//	Square tSquare8(7, 4);
//
//	Square tSquares[9] = { tSquare0,
//						   tSquare1,
//						   tSquare2,
//						   tSquare3,
//						   tSquare4,
//						   tSquare5,
//						   tSquare6,
//						   tSquare7,
//						   tSquare8 };
//
//	unsigned short expRanks[9] = { 2,
//								   1,
//								   8,
//								   4,
//								   6,
//								   8,
//								   1,
//								   5,
//								   7 };
//
//	unsigned short expFiles[9] = { 3,
//								   8,
//								   1,
//								   5,
//								   3,
//								   8,
//								   1,
//								   7,
//								   4 };
//
//	char expColors[9] = { 'B', 
//						  'B',
//						  'B',
//						  'B',
//						  'B',
//						  'W',
//						  'W',
//						  'W',
//						  'B' };
//
//	//unsigned short (Square::*func)() = Square::getRank;
//
//	//basicSquareTest(tSquares, Square::getRank, expRanks, numOfSquares);
//
//
//	//Test Bound Errors
//	try
//	{
//		Square tSquareTest1(9, 8);
//	}
//	catch (const char* e)
//	{
//		if (e != gErrors[0])
//		{
//			std::cout << "ERROR: " << gErrors[0] << " EXECEPTION NOT RAISED" << std::endl;
//			errors++;
//		}
//	}
//
//	try
//	{
//		Square tSquareTest2(1, 9);
//	}
//	catch (const char* e)
//	{
//		if (e != gErrors[1])
//		{
//			std::cout << "ERROR: " << gErrors[1] << " EXECEPTION NOT RAISED" << std::endl;
//			errors++;
//		}
//	}
//
//	//Test getRank
//	i = 0;
//	for (Square s : tSquares)
//	{
//		if (!(s.getRank() == expRanks[i]))
//		{
//			std::cout << "ERROR: SQUARE RANK tSquare" << i << ".getRank() == " << s.getRank() << std::endl;
//			errors += 1;
//		}
//		i += 1;
//	}
//
//	//Test getFile
//	i = 0;
//	for (Square s : tSquares)
//	{
//		if (!(s.getFile() == expFiles[i]))
//		{
//			std::cout << "ERROR: SQUARE FILE tSquare" << i << ".getFile() == " << s.getFile() << std::endl;
//			errors += 1;
//		}
//		i += 1;
//	}
//
//	//Test Color
//	i = 0;
//	for (Square s : tSquares)
//	{
//		if (!(s.getColor() == expColors[i]))
//		{
//			std::cout << "ERROR: SQUARE COLOR tSquare" << i << ".getColor() == " << s.getColor() << std::endl;
//			errors += 1;
//		}
//		i += 1;
//	}
//
//	return errors;
//}