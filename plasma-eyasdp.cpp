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

#include <kworkspace/kworkspace.h>
#include <KConfigDialog>
#include <KMessageBox>
#include "plasma-eyasdp.h"

PlasmaEYasdp::PlasmaEYasdp(QObject *parent, const QVariantList &args) : Plasma::Applet(parent, args) {

	layout = NULL;

	// Initialize all icons to NULL
	shutdownIcon.iconWidget = NULL;
	rebootIcon.iconWidget = NULL;
	suspendIcon.iconWidget = NULL;
	logoutIcon.iconWidget = NULL;
	hibernateIcon.iconWidget = NULL;
	turnOffScreenIcon.iconWidget = NULL;
	lockScreenIcon.iconWidget = NULL;
	switchUserIcon.iconWidget = NULL;

	// Initialize all menuActions to NULL
	shutdownIcon.menuAction = NULL;
	rebootIcon.menuAction = NULL;
	suspendIcon.menuAction = NULL;
	logoutIcon.menuAction = NULL;
	hibernateIcon.menuAction = NULL;
	turnOffScreenIcon.menuAction = NULL;
	lockScreenIcon.menuAction = NULL;
	switchUserIcon.menuAction = NULL;
}
 
PlasmaEYasdp::~PlasmaEYasdp(){ 
	freeIconsAndMenuActions();
	if( layout != NULL && !layout->ownedByLayout() ) {
		delete layout;
		layout = NULL;
	}
}

void PlasmaEYasdp::init() {
	
	setHasConfigurationInterface(true);
	setAspectRatioMode(Plasma::IgnoreAspectRatio);
	
	readConfig();
	setupLayuts();
	setupIcons();
}


void PlasmaEYasdp::paintInterface(QPainter *p, const QStyleOptionGraphicsItem *option, const QRect &contentsRect) {
	Q_UNUSED( p );
	Q_UNUSED( option );
	
	// Adapt the layout depending on the panel orientiation
	if (formFactor() != Plasma::Vertical){
		// When horizontal, we'll scale them according to the height of the panel
		const int itemHeight = contentsRect.height() / layout->rowCount();
		setPreferredWidth( itemHeight * layout->columnCount() );
	}
	else {
		// When vertical, we'll scale them according to the width of the panel
		const int itemWidth = contentsRect.width() / layout->columnCount();
		setMaximumHeight( itemWidth * layout->rowCount() );
	}
}

void PlasmaEYasdp::freeIconsAndMenuActions() {
	
	// Free icons
	if( shutdownIcon.iconWidget != NULL ) {
		shutdownIcon.iconWidget->deleteLater();
		shutdownIcon.iconWidget = NULL;
	}
	if( rebootIcon.iconWidget != NULL ) {
		rebootIcon.iconWidget->deleteLater();
		rebootIcon.iconWidget = NULL;
	}
	if( suspendIcon.iconWidget != NULL ) {
		suspendIcon.iconWidget->deleteLater();
		suspendIcon.iconWidget = NULL;
	}
	if( logoutIcon.iconWidget != NULL ) {
		logoutIcon.iconWidget->deleteLater();
		logoutIcon.iconWidget = NULL;
	}
	if( hibernateIcon.iconWidget != NULL ) {
		hibernateIcon.iconWidget->deleteLater();
		hibernateIcon.iconWidget = NULL;
	}
	if( turnOffScreenIcon.iconWidget != NULL ) {
		turnOffScreenIcon.iconWidget->deleteLater();
		turnOffScreenIcon.iconWidget = NULL;
	}
	if( lockScreenIcon.iconWidget != NULL ) {
		lockScreenIcon.iconWidget->deleteLater();
		lockScreenIcon.iconWidget = NULL;
	}
	if( switchUserIcon.iconWidget != NULL ) {
		switchUserIcon.iconWidget->deleteLater();
		switchUserIcon.iconWidget = NULL;
	}
	
	// Free menu actions
	if( shutdownIcon.menuAction != NULL ) {
		shutdownIcon.menuAction->deleteLater();
		shutdownIcon.menuAction = NULL;
	}
	if( rebootIcon.menuAction != NULL ) {
		rebootIcon.menuAction->deleteLater();
		rebootIcon.menuAction = NULL;
	}
	if( suspendIcon.menuAction != NULL ) {
		suspendIcon.menuAction->deleteLater();
		suspendIcon.menuAction = NULL;
	}
	if( logoutIcon.menuAction != NULL ) {
		logoutIcon.menuAction->deleteLater();
		logoutIcon.menuAction = NULL;
	}
	if( hibernateIcon.menuAction != NULL ) {
		hibernateIcon.menuAction->deleteLater();
		hibernateIcon.menuAction = NULL;
	}
	if( turnOffScreenIcon.menuAction != NULL ) {
		turnOffScreenIcon.menuAction->deleteLater();
		turnOffScreenIcon.menuAction = NULL;
	}
	if( lockScreenIcon.menuAction != NULL ) {
		lockScreenIcon.menuAction->deleteLater();
		lockScreenIcon.menuAction = NULL;
	}
	if( switchUserIcon.menuAction != NULL ) {
		switchUserIcon.menuAction->deleteLater();
		switchUserIcon.menuAction = NULL;
	}
}

void PlasmaEYasdp::setupLayuts() {
	layout = new QGraphicsGridLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	setLayout( layout ); // The old layout will be deleted automatically
}

void PlasmaEYasdp::setupIcons() {

	// Reset the current row index controller
	currentRow = 0;
	
	if( shutdownIcon.showIcon ) { 
		shutdownIcon.iconWidget = new Plasma::IconWidget(KIcon(shutdownIcon.iconName), QString(), this);
		shutdownIcon.iconWidget->setIcon(KIcon(shutdownIcon.iconName));
		connect(shutdownIcon.iconWidget, SIGNAL(clicked()), this, SLOT(onShutdown()));
		setIconLayout(shutdownIcon.iconWidget); 
    }
    else  { 
		shutdownIcon.menuAction = new QAction(i18n("&Shutdown"), this);
		shutdownIcon.menuAction->setIcon(KIcon(shutdownIcon.iconName));
		connect(shutdownIcon.menuAction, SIGNAL(triggered(bool)), SLOT(onShutdown()));
    }
    
    if( rebootIcon.showIcon ) {
        rebootIcon.iconWidget = new Plasma::IconWidget(KIcon(rebootIcon.iconName), QString(), this);
        rebootIcon.iconWidget->setIcon(KIcon(rebootIcon.iconName));
        connect(rebootIcon.iconWidget, SIGNAL(clicked()), this, SLOT(onReboot()));
        setIconLayout(rebootIcon.iconWidget);
    }
    else {
		rebootIcon.menuAction = new QAction(i18n("&Reboot"), this);
		rebootIcon.menuAction->setIcon(KIcon(rebootIcon.iconName));
		connect(rebootIcon.menuAction, SIGNAL(triggered(bool)), SLOT(onReboot()));
    }

    if( suspendIcon.showIcon ) { 
        suspendIcon.iconWidget = new Plasma::IconWidget(KIcon(suspendIcon.iconName), QString(), this);
        suspendIcon.iconWidget->setIcon(KIcon(suspendIcon.iconName));
        connect(suspendIcon.iconWidget, SIGNAL(clicked()), this, SLOT(onSuspend()));
        setIconLayout(suspendIcon.iconWidget);
    }
    else {
		suspendIcon.menuAction = new QAction(i18n("&Suspend"), this);
		suspendIcon.menuAction->setIcon(KIcon(suspendIcon.iconName));
		connect(suspendIcon.menuAction, SIGNAL(triggered(bool)), SLOT(onSuspend()));
    }

    if( logoutIcon.showIcon ) { 
        logoutIcon.iconWidget = new Plasma::IconWidget(KIcon(logoutIcon.iconName), QString(), this);
        logoutIcon.iconWidget->setIcon(KIcon(logoutIcon.iconName));
        connect(logoutIcon.iconWidget, SIGNAL(clicked()), this, SLOT(onLogout()));
        setIconLayout(logoutIcon.iconWidget);
    }
    else {
		logoutIcon.menuAction = new QAction(i18n("&Logout"), this);
		logoutIcon.menuAction->setIcon(KIcon(logoutIcon.iconName));
		connect(logoutIcon.menuAction, SIGNAL(triggered(bool)), SLOT(onLogout()));
    }


    if( hibernateIcon.showIcon ) { 
        hibernateIcon.iconWidget = new Plasma::IconWidget(KIcon(hibernateIcon.iconName), QString(), this);
        hibernateIcon.iconWidget->setIcon(KIcon(hibernateIcon.iconName));
        connect(hibernateIcon.iconWidget, SIGNAL(clicked()), this, SLOT(onHibernate()));
        setIconLayout(hibernateIcon.iconWidget);
    }
    else {
		hibernateIcon.menuAction = new QAction(i18n("&Hibernate"), this);
		hibernateIcon.menuAction->setIcon(KIcon(hibernateIcon.iconName));
		connect(hibernateIcon.menuAction, SIGNAL(triggered(bool)), SLOT(onHibernate()));
    }
    
    if( turnOffScreenIcon.showIcon ) { 
        turnOffScreenIcon.iconWidget = new Plasma::IconWidget(KIcon(turnOffScreenIcon.iconName), QString(), this);
        turnOffScreenIcon.iconWidget->setIcon(KIcon(turnOffScreenIcon.iconName));
        connect(turnOffScreenIcon.iconWidget, SIGNAL(clicked()), this, SLOT(onTurnOffScreen()));
        setIconLayout(turnOffScreenIcon.iconWidget);
    }
    else {
		turnOffScreenIcon.menuAction = new QAction(i18n("&Turn off screen"), this);
		turnOffScreenIcon.menuAction->setIcon(KIcon(turnOffScreenIcon.iconName));
		connect(turnOffScreenIcon.menuAction, SIGNAL(triggered(bool)), SLOT(onTurnOffScreen()));
    }

    if( lockScreenIcon.showIcon) {
        lockScreenIcon.iconWidget = new Plasma::IconWidget(KIcon(lockScreenIcon.iconName), QString(), this);
        lockScreenIcon.iconWidget->setIcon(KIcon(lockScreenIcon.iconName));
        connect(lockScreenIcon.iconWidget, SIGNAL(clicked()), this, SLOT(onLockScreen()));
        setIconLayout(lockScreenIcon.iconWidget);
    }
    else {
      lockScreenIcon.menuAction = new QAction(i18n("&Lock screen"), this);
      lockScreenIcon.menuAction->setIcon(KIcon(lockScreenIcon.iconName));
      connect(lockScreenIcon.menuAction, SIGNAL(triggered(bool)), SLOT(onLockScreen()));
    }

    if( switchUserIcon.showIcon) {
        switchUserIcon.iconWidget = new Plasma::IconWidget(KIcon(switchUserIcon.iconName), QString(), this);
        switchUserIcon.iconWidget->setIcon(KIcon(switchUserIcon.iconName));
        connect(switchUserIcon.iconWidget, SIGNAL(clicked()), this, SLOT(onSwitchUser()));
        setIconLayout(switchUserIcon.iconWidget);
    }
    else {
      switchUserIcon.menuAction = new QAction(i18n("&Switch user"), this);
      switchUserIcon.menuAction->setIcon(KIcon(switchUserIcon.iconName));
      connect(switchUserIcon.menuAction, SIGNAL(triggered(bool)), SLOT(onSwitchUser()));
    }
}

void PlasmaEYasdp::setIconLayout(Plasma::IconWidget* iconWidget) {
	const int col = currentRow / numRowsLayout;
	const int row = currentRow - col * numRowsLayout;

	// Adapt the layout depending on the panel orientiation (thanks to downdiagonal for this patch!)
	if (formFactor() != Plasma::Vertical){
		layout->addItem( iconWidget, row, col, Qt::AlignLeft );
	}
	else{
		layout->addItem( iconWidget, col, row, Qt::AlignLeft );
	}
	currentRow++;	
}

void PlasmaEYasdp::createConfigurationInterface(KConfigDialog* parent) {

    //Appearance
    parent->resize( 625, parent->height() );
    QWidget*const widgetAppear = new QWidget;
    uiAppear.setupUi(widgetAppear);
  
	// Icon names
    uiAppear.kiconbutton->setIcon(KIcon(shutdownIcon.iconName));
    uiAppear.kiconbutton_2->setIcon(KIcon(rebootIcon.iconName));
    uiAppear.kiconbutton_3->setIcon(KIcon(suspendIcon.iconName));
    uiAppear.kiconbutton_4->setIcon(KIcon(logoutIcon.iconName));
    uiAppear.kiconbutton_5->setIcon(KIcon(hibernateIcon.iconName));  
    uiAppear.kiconbutton_6->setIcon(KIcon(turnOffScreenIcon.iconName));
    uiAppear.kiconbutton_7->setIcon(KIcon(lockScreenIcon.iconName));
    uiAppear.kiconbutton_8->setIcon(KIcon(switchUserIcon.iconName));
    
	// Selected icons
	uiAppear.checkBox->setChecked(shutdownIcon.showIcon);
    uiAppear.checkBox_2->setChecked(rebootIcon.showIcon);
    uiAppear.checkBox_3->setChecked(suspendIcon.showIcon);
    uiAppear.checkBox_4->setChecked(logoutIcon.showIcon);
    uiAppear.checkBox_5->setChecked(hibernateIcon.showIcon);
    uiAppear.checkBox_8->setChecked(turnOffScreenIcon.showIcon);
    uiAppear.checkBox_9->setChecked(lockScreenIcon.showIcon);
    uiAppear.checkBox_11->setChecked(switchUserIcon.showIcon);

	// Misc options
    uiAppear.checkBoxAskConfirmation->setChecked(askConfirmation);
	uiAppear.checkBoxLockBeforeSuspend->setChecked(lockBeforeSuspend);
	switch( numRowsLayout ) {
		case 2:
			uiAppear.radioTwoRows->setChecked(true);
			break;
		case 3:
			uiAppear.radioThreeRows->setChecked(true);
			break;
		default:
			uiAppear.radioOneRow->setChecked(true);
			break;
	}
    
    // Combo box
	uiAppear.comboBoxBackground->setCurrentIndex(background);
    connect(uiAppear.comboBoxBackground, SIGNAL (currentIndexChanged (int)), this, SLOT(onBackgroundChanged(int)));
    
    // Add everything to the settings
    connect(parent, SIGNAL(okClicked()), this, SLOT(onConfigAccepted()));
    parent->addPage(widgetAppear, i18n("Appearance"), QString("video-display"));
}

void PlasmaEYasdp::onConfigAccepted() {
    // If user changes the icon, update it
    if( !uiAppear.kiconbutton->icon().isEmpty() ) {
		shutdownIcon.iconName = uiAppear.kiconbutton->icon(); 
	}
    if( !uiAppear.kiconbutton_2->icon().isEmpty() ) {
		rebootIcon.iconName = uiAppear.kiconbutton_2->icon();
	}
    if( !uiAppear.kiconbutton_3->icon().isEmpty() ) {
		suspendIcon.iconName = uiAppear.kiconbutton_3->icon();
	}
    if( !uiAppear.kiconbutton_4->icon().isEmpty() ) {
		logoutIcon.iconName = uiAppear.kiconbutton_4->icon();
	}
    if( !uiAppear.kiconbutton_5->icon().isEmpty() ) {
		hibernateIcon.iconName = uiAppear.kiconbutton_5->icon();
	}
    if( !uiAppear.kiconbutton_6->icon().isEmpty() ) {
		turnOffScreenIcon.iconName = uiAppear.kiconbutton_6->icon();
	}
    if( !uiAppear.kiconbutton_7->icon().isEmpty() ) {
		lockScreenIcon.iconName = uiAppear.kiconbutton_7->icon();
	}
    if( !uiAppear.kiconbutton_8->icon().isEmpty() ) {
		switchUserIcon.iconName = uiAppear.kiconbutton_8->icon();
	}
    
    // Update showIcon flag for each icon
    shutdownIcon.showIcon = uiAppear.checkBox->isChecked();
    rebootIcon.showIcon = uiAppear.checkBox_2->isChecked();
    suspendIcon.showIcon = uiAppear.checkBox_3->isChecked();
    logoutIcon.showIcon = uiAppear.checkBox_4->isChecked();
    hibernateIcon.showIcon = uiAppear.checkBox_5->isChecked();
    turnOffScreenIcon.showIcon = uiAppear.checkBox_8->isChecked();
    lockScreenIcon.showIcon = uiAppear.checkBox_9->isChecked();
    switchUserIcon.showIcon = uiAppear.checkBox_11->isChecked();
    
    // Update some flags too
    askConfirmation = uiAppear.checkBoxAskConfirmation->isChecked();
	lockBeforeSuspend  = uiAppear.checkBoxLockBeforeSuspend->isChecked();

	if( uiAppear.radioTwoRows->isChecked() ) {
		this->numRowsLayout = 2;
	}
	else if( uiAppear.radioThreeRows->isChecked() ) {
		this->numRowsLayout = 3;
	}
	else {
		this->numRowsLayout = 1;
	}
		
    // Set up everything from scratch
	freeIconsAndMenuActions();
	setupLayuts();
	setupIcons();
	saveConfig();
}


void PlasmaEYasdp::onShutdown() {
	KWorkSpace::ShutdownConfirm confirm = askConfirmation ? 
			KWorkSpace::ShutdownConfirmYes : KWorkSpace::ShutdownConfirmNo;
	KWorkSpace::requestShutDown( confirm, KWorkSpace::ShutdownTypeHalt ,
								 KWorkSpace::ShutdownModeInteractive);
}
void PlasmaEYasdp::onReboot() {
	KWorkSpace::ShutdownConfirm confirm = askConfirmation ? 
			KWorkSpace::ShutdownConfirmYes : KWorkSpace::ShutdownConfirmNo;
	KWorkSpace::requestShutDown( confirm, KWorkSpace::ShutdownTypeReboot ,
                                 KWorkSpace::ShutdownModeInteractive);
}

void PlasmaEYasdp::onLogout() {   
	KWorkSpace::ShutdownConfirm confirm = askConfirmation ? 
			KWorkSpace::ShutdownConfirmYes : KWorkSpace::ShutdownConfirmNo;
	KWorkSpace::requestShutDown( confirm, KWorkSpace::ShutdownTypeNone , 
								 KWorkSpace::ShutdownModeInteractive);
}

void PlasmaEYasdp::onSwitchUser() {   
	const int result = system("qdbus --session org.kde.screensaver /App org.kde.krunner.App.switchUser");
	if( result != 0 ) {
		KMessageBox::sorry( NULL,  i18n( "The operation has failed!" ) );
	}
}

void PlasmaEYasdp::onSuspend() {
	if( askConfirmation ) {
		if( KMessageBox::questionYesNo( NULL, i18n( "Do you want to sleep (suspend to RAM) the system now?" ), 
										i18n( "Suspend confirmation") ) == KMessageBox::No ) {
			return;
		}
	}
	if( lockBeforeSuspend ) {
	   onLockScreen();
	}
	const int result = system("qdbus --system org.freedesktop.UPower /org/freedesktop/UPower org.freedesktop.UPower.Suspend");
	if( result != 0 ) {
	KMessageBox::sorry( NULL,  i18n( "The operation has failed!" ) );
	}
}

void PlasmaEYasdp::onHibernate() {  
	if( askConfirmation ) {
		if( KMessageBox::questionYesNo( NULL, i18n( "Do you want to hibernate (suspend to disk) the system now?" ), 
										i18n( "Hibernate confirmation") ) == KMessageBox::No ) {
			return;
		}
	}
	if( lockBeforeSuspend ) {
	   onLockScreen();
	}
	const int result = system("qdbus --system org.freedesktop.UPower /org/freedesktop/UPower org.freedesktop.UPower.Hibernate");
	if( result != 0 ) {
		KMessageBox::sorry( NULL,  i18n( "The operation has failed!" ) );
	}
}  

void PlasmaEYasdp::onTurnOffScreen() {   
	const int result = system("xset dpms force off");
	if( result != 0 ) {
		KMessageBox::sorry( NULL,  i18n( "The operation has failed!" ) );
	}
}

void PlasmaEYasdp::onLockScreen() {  
   const int result = system("qdbus org.freedesktop.ScreenSaver /ScreenSaver Lock");
	if( result != 0 ) {
		KMessageBox::sorry( NULL,  i18n( "The operation has failed!" ) );
	}
}  

void PlasmaEYasdp::onBackgroundChanged(const int& background) {
	switch( background )  {
		default:
		case 0:
			this->background = background;
			setBackgroundHints(NoBackground);
			break;
		case 1:
			this->background = background;
			setBackgroundHints(StandardBackground);
			break;
		case 2:
			this->background = background;
			setBackgroundHints(TranslucentBackground);
			break;
	}
}

QList< QAction* > PlasmaEYasdp::contextualActions() {
	QList< QAction* > menuActions;
	if( shutdownIcon.menuAction != NULL ) {
		menuActions.append( shutdownIcon.menuAction );
	}
	if( rebootIcon.menuAction != NULL ) {
		menuActions.append( rebootIcon.menuAction );
	}
	if( suspendIcon.menuAction != NULL ) {
		menuActions.append( suspendIcon.menuAction );
	}
	if( logoutIcon.menuAction != NULL ) {
		menuActions.append( logoutIcon.menuAction );
	}
	if( hibernateIcon.menuAction != NULL ) {
		menuActions.append( hibernateIcon.menuAction );
	}
	if( turnOffScreenIcon.menuAction != NULL ) {
		menuActions.append( turnOffScreenIcon.menuAction );
	}
	if( lockScreenIcon.menuAction != NULL ) {
		menuActions.append( lockScreenIcon.menuAction );
	}	
	if( switchUserIcon.menuAction != NULL ) {
		menuActions.append( switchUserIcon.menuAction );
	}	
    return menuActions;
}

void PlasmaEYasdp::readConfig() {
	KConfigGroup cg = config();
    shutdownIcon.iconName = cg.readEntry("sh-iconname", "system-shutdown");
    rebootIcon.iconName = cg.readEntry("re-iconname", "system-reboot");
    suspendIcon.iconName = cg.readEntry("su-iconname", "system-suspend");
    logoutIcon.iconName = cg.readEntry("lo-iconname","system-log-out");
    hibernateIcon.iconName = cg.readEntry("hi-iconname","system-suspend-hibernate");
    lockScreenIcon.iconName = cg.readEntry("loscreen-iconname","system-lock-screen");
    turnOffScreenIcon.iconName = cg.readEntry("toscreen-iconname","preferences-desktop-screensaver");
    switchUserIcon.iconName = cg.readEntry("sw-iconname","system-switch-user");	
	
    shutdownIcon.showIcon = cg.readEntry("sh-iconshow", true);
    rebootIcon.showIcon = cg.readEntry("re-iconshow", true);
    suspendIcon.showIcon = cg.readEntry("su-iconshow", true);
    logoutIcon.showIcon = cg.readEntry("lo-iconshow", true);
    hibernateIcon.showIcon = cg.readEntry("hi-iconshow", true);
    turnOffScreenIcon.showIcon = cg.readEntry("toscreen-iconshow", true);
    lockScreenIcon.showIcon = cg.readEntry("loscreen-iconshow", true);
    switchUserIcon.showIcon = cg.readEntry("sw-iconshow", true);
    
	this->numRowsLayout = cg.readEntry("numRowsLayout", 1);
    askConfirmation = cg.readEntry("askconf", true);
	lockBeforeSuspend = cg.readEntry( "lockBeforeSuspend", true );
    onBackgroundChanged( cg.readEntry("background", 0) );
}

void PlasmaEYasdp::saveConfig() {
	KConfigGroup cg = config();
    cg.writeEntry("sh-iconname", shutdownIcon.iconName);
    cg.writeEntry("re-iconname", rebootIcon.iconName);
    cg.writeEntry("su-iconname", suspendIcon.iconName);
    cg.writeEntry("lo-iconname", logoutIcon.iconName);
    cg.writeEntry("hi-iconname", hibernateIcon.iconName);
    cg.writeEntry("toscreen-iconname", turnOffScreenIcon.iconName);
    cg.writeEntry("loscreen-iconname", lockScreenIcon.iconName);
    cg.writeEntry("loscreen-iconname", lockScreenIcon.iconName);
    cg.readEntry("sw-iconname",switchUserIcon.iconName);	

    cg.writeEntry("sh-iconshow", shutdownIcon.showIcon);
    cg.writeEntry("re-iconshow", rebootIcon.showIcon);
    cg.writeEntry("su-iconshow", suspendIcon.showIcon);
    cg.writeEntry("lo-iconshow", logoutIcon.showIcon);
    cg.writeEntry("hi-iconshow", hibernateIcon.showIcon);
    cg.writeEntry("toscreen-iconshow", turnOffScreenIcon.showIcon);
    cg.writeEntry("loscreen-iconshow", lockScreenIcon.showIcon);
	cg.writeEntry("sw-iconshow", switchUserIcon.showIcon);
	
    cg.writeEntry("numRowsLayout", numRowsLayout);
    cg.writeEntry("askconf", askConfirmation);
    cg.writeEntry("lockBeforeSuspend", lockBeforeSuspend);
    cg.writeEntry("background", background);

	emit configNeedsSaving();
}
 
#include "plasma-eyasdp.moc"