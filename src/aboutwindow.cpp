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

#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "version.h"

#include <QScrollArea>
#include <QLabel>

// +-----------------------------------------------------------
ct::AboutWindow::AboutWindow(QWidget *pParent) :
	QDialog(pParent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
	ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

	QString sText = "<html><head/><body><p><span style=\" font-weight:600;\">CamTest - A simple webcam application (version %1)</span></p><p align=\"justify\">Copyright (C) 2016 <a href=\"http://www.luiz.vieira.nom.br/\"><span style=\" text-decoration: underline; color:#0000ff;\">Luiz Carlos Vieira</span></a></p><p align=\"justify\">This is a simple webcam application mainly used to test the installation and building of Qt and OpenCV both in Windows and Linux - but I suppose it also works as a testing tool for webcams. :)</p><p align=\"justify\">The application icons are either from or based on the Oxygen Icons Set, downloaded as <a href=\"https://github.com/pasnox/oxygen-icons-png\"><span style=\" text-decoration: underline; color:#0000ff;\">PNGs from Felipe Azevedo (pasnox)</span></a> and <a href=\"https://techbase.kde.org/Projects/Oxygen/Licensing\"><span style=\" text-decoration: underline; color:#0000ff;\">licensed under LGPL from KDE</span></a>.</p><p align=\"justify\">LICENSE</p><p align=\"justify\">This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p><p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.</p><p>You should have received a copy of the GNU General Public License along with this program. If not, see <a href=\"http://www.gnu.org/licenses/\"><span style=\" text-decoration: underline; color:#0000ff;\">http://www.gnu.org/licenses/</span></a>.</p></body></html>";
	QLabel *pLabel = new QLabel(this);
	pLabel->setText(sText.arg(CT_VERSION));
	pLabel->setWordWrap(true);
	pLabel->setOpenExternalLinks(true);
	ui->scrollArea->setWidget(pLabel);
}

// +-----------------------------------------------------------
ct::AboutWindow::~AboutWindow()
{
    delete ui;
}
