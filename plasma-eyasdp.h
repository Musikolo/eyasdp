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

	QGraphicsGridLayout *layout;
	void freeIconsAndMenuActions();
	void setupIcons();
	void setupLayuts();
	void setIconLayout( Plasma::IconWidget *iconWidget );
	void readConfig();
	void saveConfig();

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