#pragma once

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "SimConnect.h"
#include <strsafe.h>



struct Data
{
	char    title[256];
	double  kohlsmann;
	double  altitude;
	double  latitude;
	double  longitude;
};



int openSimConnection();
void callSimConnect();
void closeSimConnection();
struct Data* retrieveData();