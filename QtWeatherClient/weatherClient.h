#pragma once
using namespace std;
#include "weatherClient/soapWeatherWebServiceSoapProxy.h"
#include<vector>
#include<string>
#include<qstring>
class weatherClient
{
public:
	weatherClient();
	~weatherClient();
	bool initClient();
	bool getAllSupportCities(vector<QString>& vecAllSupportCity);
	bool getCityWeatertherInfoByName(string cityName, vector<QString>& outXmlWeatherResult);
private:
	WeatherWebServiceSoapProxy* m_weatherProxy;
	bool                        m_bInit;
};
