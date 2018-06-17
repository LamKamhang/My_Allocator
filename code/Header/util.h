#pragma once

#include <ctime>

/*
 * function: timer
 * Version: 1.0
 * Author: kk
 * Created Date: Sat Jun 16 10:41:14 DST 2018
 * -------------------------------------------
 * Usage：in the place where need a timer
 *          just use function, timer(),
 *        in the place where need to output time
 *          just use funciton, timer(), 
 *        it can auto do the minus, 
 *        the second time to use timer(), it can 
 *        return the delta time in seconds as unit
 * Example:
 *      timer()
 *      ...do something...
 *      cout << timer() << endl;
 */
inline double timer()
{
	static decltype(clock()) t = 0;
	if (t == 0)
	{
		t = clock();
		return 0;
	}
	else
	{
		auto p = t; t = 0;
		return double(clock() - p) / CLOCKS_PER_SEC;
	}
}

