#include "weatherClient.h"

#include <qstring>
#include "weatherClient/stdsoap2.h"
#include "weatherClient/WeatherWebServiceSoap.nsmap"
#include "weatherClient/soapWeatherWebServiceSoapProxy.h"
#include <string>
#include <vector>

weatherClient::weatherClient()
{
	m_bInit = false;
}

weatherClient::~weatherClient()
{
}



bool weatherClient::initClient()
{
	m_weatherProxy = new(nothrow) WeatherWebServiceSoapProxy();
	if (!m_weatherProxy)
	{
		return false;
	}
	soap_set_mode(m_weatherProxy, SOAP_C_UTFSTRING);
	return m_bInit = true;
}

bool weatherClient::getCityWeatertherInfoByName(string cityName, vector<QString>& outXmlWeatherResult)
{
	if (!m_bInit)
	{
		return false;
	}
	_ns1__getWeatherbyCityName ns1__getWeatherbyCityName;
	ns1__getWeatherbyCityName.theCityName = &cityName;
	_ns1__getWeatherbyCityNameResponse ns1__getWeatherbyCityNameResponse;
	if (SOAP_OK == m_weatherProxy->getWeatherbyCityName(&ns1__getWeatherbyCityName, ns1__getWeatherbyCityNameResponse))
	{
		if (nullptr != ns1__getWeatherbyCityNameResponse.getWeatherbyCityNameResult)
		{
			auto it = ns1__getWeatherbyCityNameResponse.getWeatherbyCityNameResult->string.begin();
			for (; it != ns1__getWeatherbyCityNameResponse.getWeatherbyCityNameResult->string.end(); it++)
			{
				outXmlWeatherResult.push_back(QString::fromStdString(*it));
			}
			return true;
		}
	}
	return false;
}


bool weatherClient::getAllSupportCities(vector<QString>& vecAllSupportCity)
{
	if (!m_bInit)
	{
		return false;
	}
	std::string provinceName = "";
	_ns1__getSupportCity supportCity;
	supportCity.byProvinceName = &provinceName;
	_ns1__getSupportCityResponse supportCityResponse;
	vector<string> result;
	bool bSuccess = false;
	int i = 0;
	int iTryCount = 3;
	do
	{
		if (SOAP_OK == m_weatherProxy->getSupportCity(&supportCity, supportCityResponse))
		{
			if (nullptr != supportCityResponse.getSupportCityResult)
			{
				result = supportCityResponse.getSupportCityResult->string;
				for (auto it = result.begin(); it != result.end(); it++)
				{
					vecAllSupportCity.push_back(QString::fromStdString(*it));
				}
			}
			bSuccess = true;
		}
		break;
	} while (++i<iTryCount);

	return bSuccess;
}


