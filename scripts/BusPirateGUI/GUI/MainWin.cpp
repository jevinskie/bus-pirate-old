#include <QtGui>

#include "Interface.h"
#include "OtherIface.h"
#include "BPSettings.h"
#include "BinMode.h"
#include "MainWin.h"
#include "Events.h"
MainAppWindow::MainAppWindow()
{
	/* QSplashScreen */
	createActions();
	createMenus();
	setStatusBar(new QStatusBar);
	statusBar()->showMessage("Ready");
	bpstatus = new QLabel("Bus Pirate Closed");
	statusBar()->addPermanentWidget(bpstatus);
	frame = new MainWidgetFrame(this);
	setCentralWidget(frame);
}

void MainAppWindow::customEvent(QEvent *ev)
{
	if (static_cast<BPEventType>(ev->type()) == BPStatusMsgEventType)
	{
		statusBar()->showMessage(dynamic_cast<BPStatusMsgEvent* >(ev)->msg);
	}
	else if (static_cast<BPEventType>(ev->type()) == BPPortStatusMsgEventType)
	{
		bpstatus->setText(dynamic_cast<BPPortStatusMsgEvent *>(ev)->msg);
	}
}

void MainAppWindow::createActions(){}
void MainAppWindow::createMenus(){}

MainWidgetFrame::MainWidgetFrame(MainAppWindow *p) : QWidget(p)
{
	parent=p;
	tabs = new QTabWidget(p);
	cfg = new BPSettings;
	settings = new BPSettingsGui(this);
	spi = new SpiGui(this);
	i2c = new I2CGui(this);
	onewire = new OneWireGui(this);
	rawwire = new RawWireGui(this);
	raw_text = new RawTextGui(this);
	power = new PowerGui(this);
	bp = new BinMode(this);
	
	//connect(qApp, SIGNAL(aboutToQuit()), settings, SLOT(SaveSettings()));
	connect(qApp, SIGNAL(lastWindowClosed()), settings, SLOT(SaveSettings()));
	
	tabs->addTab(spi, "SPI");
	tabs->addTab(i2c, "I2C");
	tabs->addTab(onewire, "1Wire");
	tabs->addTab(rawwire, "Raw 2/3-Wire");
	tabs->addTab(raw_text, "Raw Text");
	tabs->addTab(power, "Bus Pirate");
	tabs->addTab(settings, "Settings");

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabs);
	setLayout(mainLayout);
	setWindowTitle("BusPirateGUI");
}
