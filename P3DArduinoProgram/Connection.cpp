#include "Connection.h"

int     quit = 0;
HANDLE  hSimConnect = NULL;
HRESULT hr;

Data simdata;
Data *pS = &simdata;

static enum EVENT_ID {
	EVENT_SIM_START,
	EVENT_SIM_6HZ
};


static enum DATA_DEFINE_ID {
	DEFINITION_1,
};

static enum DATA_REQUEST_ID {
	REQUEST_1,
};



void CALLBACK MyDispatchProcRD(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{
	HRESULT hr;

	switch (pData->dwID)
	{
	case SIMCONNECT_RECV_ID_EVENT:
	{
		SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

		switch (evt->uEventID)
		{
		case EVENT_SIM_6HZ:

			// Now the sim is running, request information on the user aircraft
			hr = SimConnect_RequestDataOnSimObjectType(hSimConnect, REQUEST_1, DEFINITION_1, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);

			break;

		default:
			break;
		}
		break;
	}

	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE:
	{
		SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE*)pData;

		switch (pObjData->dwRequestID)
		{
		case REQUEST_1:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			pS = (Data*)&pObjData->dwData;
			if (SUCCEEDED(StringCbLengthA(&pS->title[0], sizeof(pS->title), NULL))) // security check
			{
				//printf("\nObjectID=%d  Title=\"%s\"\nLat=%f  Lon=%f  Alt=%f  Kohlsman=%.2f", ObjectID, pS->title, pS->latitude, pS->longitude, pS->altitude, pS->kohlsmann);
			}
			break;
		}

		default:
			break;
		}
		break;
	}


	case SIMCONNECT_RECV_ID_QUIT:
	{
		quit = 1;
		break;
	}

	default:
		//printf("\nReceived:%d", pData->dwID);
		break;
	}
}


int openSimConnection()
{
	

	if (SUCCEEDED(SimConnect_Open(&hSimConnect, "Request Data", NULL, 0, 0, 0)))
	{
		printf("\nConnected to Prepar3D!");

		// Set up the data definition, but do not yet do anything with it
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Title", NULL, SIMCONNECT_DATATYPE_STRING256);
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Kohlsman setting hg", "inHg");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Plane Altitude", "feet");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Plane Latitude", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Plane Longitude", "degrees");

		// Request an event when the simulation starts
		hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_6HZ, "6Hz");

		return 1;

		//while (0 == quit)
		//{
		//	SimConnect_CallDispatch(hSimConnect, MyDispatchProcRD, NULL);
		//	Sleep(1);
		//}

		//hr = SimConnect_Close(hSimConnect);
	}
	else
		return -1;
}

void callSimConnect()
{
	SimConnect_CallDispatch(hSimConnect, MyDispatchProcRD, NULL);
	return;
}

void closeSimConnection()
{
	hr = SimConnect_Close(hSimConnect);
}


Data* retrieveData() {
	return pS;
}