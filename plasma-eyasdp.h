/*
    Copyright (c) 2011 Carlos López Sánchez <musikolo{AT}hotmail[DOT]com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLASMAEYASDP_H
#define PLASMAEYASDP_H

#include <Plasma/Applet>
#include <plasma/widgets/iconwidget.h>
#include <QGraphicsGridLayout>
#include "ui_AppearanceConfig.h"
 
class QSizeF;

namespace General {
	static const char* APP_UI_NAME  	  = "eYaSDP";
	static const uchar APP_VERSION_MAJOR  =  0;
	static const uchar APP_VERSION_MINOR  =  8;
	static const uchar APP_VERSION_BUGFIX =  0;
	static const QString APP_VERSION	  = QString( QString( "%1.%2.%3" ).arg( APP_VERSION_MAJOR ).arg( APP_VERSION_MINOR ).arg( APP_VERSION_BUGFIX ) );
	static const char* APP_HOMEPAGE 	  = "http://kde-apps.org/content/show.php?content=146530";
	static const char* APP_AUTHOR		  = "Carlos López Sánchez";
}

// Define our plasma Applet
class PlasmaEYasdp : public Plasma::Applet
{
Q_OBJECT

private:
	typedef struct {
		Plasma::IconWidget *iconWidget;
		QAction* menuAction;
		QString iconName;
		bool showIcon;
	} Icon;
	
	Ui::AppearanceConfig uiAppear;
	int currentRow;
	
	Icon shutdownIcon;
	Icon rebootIcon;
	Icon suspendIcon;
	Icon logoutIcon;
	Icon hibernateIcon;
	Icon turnOffScreenIcon;
	Icon lockScreenIcon;
	Icon switchUserIcon;
	bool askConfirmation;
	bool lockBeforeSuspend;
	int numRowsLayout;
	int background;
	QAction* helpAction;

	QGraphicsGridLayout *layout;
	void freeIconsAndMenuActions();
	void setupIcons();
	void setupLayuts();
	void setIconLayout( Plasma::IconWidget *iconWidget );
	void readConfig();
	void saveConfig();
	void createAboutMenu();

protected:
	void createConfigurationInterface(KConfigDialog *parent);
	QList<QAction*> contextualActions();

public:
	// Basic Create/Destroy
	PlasmaEYasdp(QObject *parent, const QVariantList &args);
	~PlasmaEYasdp();

	// The paintInterface procedure paints the applet to screen
	void paintInterface(QPainter *p, const QStyleOptionGraphicsItem *option, const QRect& contentsRect);
	void init();

public slots:
	void onConfigAccepted();
	void onShutdown();
	void onReboot();
	void onSuspend();
	void onLogout();
	void onHibernate();
	void onTurnOffScreen();
	void onLockScreen();
	void onSwitchUser();
	void onBackgroundChanged(const int&);       
};

// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(eyasdp, PlasmaEYasdp)

#endif