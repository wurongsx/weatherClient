#include "QtWeatherClient.h"
#include <QMessageBox>
#include <vector>
#include <QString>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QPainter>
using namespace std;
QtWeatherClient::QtWeatherClient(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_weatherClient = new weatherClient();
	if(m_weatherClient->initClient())
	{ 

	}
	ui.listViewAllCity->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.listViewAllCity, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(show_listViewMenu(const QPoint&)));

	QObject::connect(ui.pushButtonQuerySupport, SIGNAL(clicked()), this, SLOT(slot_showSupportAllCities()));
}

void QtWeatherClient::slot_showWeaterInfoByCityname()
{
	//ui.qlistViewAllCity->currentIndex;
	//ui.listViewAllCity;
	string cityName;
	vector<QString> outXmlWeatherResult;
	if (m_weatherClient->getCityWeatertherInfoByName(cityName, outXmlWeatherResult))
	{
		//outXmlWeatherResult
	}
}


void QtWeatherClient::slot_showSupportAllCities()
{
	vector<QString> vec;
	QStringListModel* Model;
	QStandardItemModel* ItemModel = new QStandardItemModel(this);
	if (m_weatherClient->getAllSupportCities(vec))
	{
		QStringList strList;
		for (auto it = vec.begin(); it != vec.end(); it++)
		{
			strList.append(*it);
		}
		int nCount = strList.size();
		for (int i = 0; i < nCount; i++)
		{
			QString string = static_cast<QString>(strList.at(i));
			QStandardItem* item = new QStandardItem(string);
			ItemModel->appendRow(item);
		}
	}
	ui.listViewAllCity->setModel(ItemModel);

	vector<QString> outXmlWeatherResult;
	if (m_weatherClient->getCityWeatertherInfoByName("西安", outXmlWeatherResult))
	{

	}
	outXmlWeatherResult.push_back("1233");
}
void QtWeatherClient::show_listViewMenu(const QPoint& pos)
{
	QMenu* cmenu = new QMenu(ui.listViewAllCity);
	QAction* InquireAction = cmenu->addAction(QString("天氣查詢"));
	slot_showWeaterInfoByCityname();
	//connect(InquireAction, SIGNAL(triggered(bool)), this, SLOT(slot_showWeaterInfoByCityname()));
	cmenu->exec(QCursor::pos());
	delete cmenu;
	cmenu = NULL;
}
