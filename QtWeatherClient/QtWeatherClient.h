#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWeatherClient.h"
#include "weatherClient.h"
#include <QModelIndex>
class QtWeatherClient : public QMainWindow
{
	Q_OBJECT

public:
	QtWeatherClient(QWidget *parent = Q_NULLPTR);


private:
	Ui::QtWeatherClientClass ui;
	weatherClient* m_weatherClient;

private slots:
	void show_listViewMenu(const QPoint& pos);

	void slot_showSupportAllCities();
	void slot_showWeaterInfoByCityname();

};
