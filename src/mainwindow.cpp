/* Copyright (C) 2016 Luiz Carlos Vieira (http://www.luiz.vieira.nom.br)
 *
 * This file is part of CamTest.
 *
 * CamTest is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CamTest is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QResizeEvent>

using namespace std;
using namespace cv;

// +-----------------------------------------------------------
ct::MainWindow::MainWindow(QWidget *pParent) :
    QMainWindow(pParent),
    ui(new Ui::MainWindow)
{
	// Setup the UI
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/camera-web-on.png"));
	setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

	QObject::connect(&m_oTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
	m_oVCap.open(0);
	if (!m_oVCap.isOpened())
	{
		ui->actionCameraOn->setChecked(false);
		ui->actionCameraOn->setText(tr("&Turn Camera On"));
		setWindowIcon(QIcon(":/resources/camera-web-off.png"));
	}
	else
		m_oTimer.start(UPDATE_INTERVAL);
}

// +-----------------------------------------------------------
ct::MainWindow::~MainWindow()
{
    delete ui;
}

// +-----------------------------------------------------------
void ct::MainWindow::showEvent(QShowEvent *pEvent)
{
	QMainWindow::showEvent(pEvent);
	setMinimumSize(10, 10);
	resize(600, 480);
	QRect oGeo = QApplication::desktop()->screenGeometry();
	int x = (oGeo.width() - width()) / 2;
	int y = (oGeo.height() - height()) / 2;
	move(x, y);
}

// +-----------------------------------------------------------
void ct::MainWindow::on_actionCameraOn_toggled(bool bChecked)
{
	if (bChecked)
	{
		m_oVCap.open(0);
		if (!m_oVCap.isOpened())
		{
			QMessageBox::warning(this, tr("Error accessing webcam"), tr("It was not possible to start the webcam. Please verify if it is correctly installed in the operating system and try again."), QMessageBox::Ok);
			ui->actionCameraOn->setChecked(false);
			return;
		}

		m_oTimer.start(UPDATE_INTERVAL);
		ui->actionCameraOn->setText(tr("&Turn Camera Off"));
		setWindowIcon(QIcon(":/resources/camera-web-on.png"));
	}
	else
	{
		ui->actionCameraOn->setText(tr("&Turn Camera On"));
		setWindowIcon(QIcon(":/resources/camera-web-off.png"));
		m_oTimer.stop();
		m_oVCap.release();
		ui->imageLabel->setPixmap(QPixmap());
	}
}

// +-----------------------------------------------------------
void ct::MainWindow::on_actionStayOnTop_toggled(bool bChecked)
{
	if (bChecked)
		setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	else
		setWindowFlags(windowFlags() ^ Qt::WindowStaysOnTopHint);
	show();
}

// +-----------------------------------------------------------
void ct::MainWindow::on_actionFullScreen_toggled(bool bChecked)
{
	if (bChecked)
		setWindowState(windowState() | Qt::WindowFullScreen);
	else
		setWindowState(windowState() ^ Qt::WindowFullScreen);
}

// +-----------------------------------------------------------
void ct::MainWindow::on_actionAbout_triggered()
{
    (new AboutWindow(this))->show();
}

// +-----------------------------------------------------------
void ct::MainWindow::on_actionExit_triggered()
{
	QApplication::exit(0);
}

// +-----------------------------------------------------------
void ct::MainWindow::onTimeout()
{
	if (m_oVCap.isOpened())
	{
		Mat oFrame;
		m_oVCap.read(oFrame);
		cvtColor(oFrame, oFrame, CV_BGR2RGB);
		QImage oImage = QImage((uchar*) oFrame.data, oFrame.cols, oFrame.rows, QImage::Format_RGB888);
		ui->imageLabel->setPixmap(QPixmap::fromImage(oImage));
	}
}