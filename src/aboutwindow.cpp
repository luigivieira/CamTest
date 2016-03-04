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
	ui->titleLabel->setText(ui->titleLabel->text().arg(CT_VERSION));
}

// +-----------------------------------------------------------
ct::AboutWindow::~AboutWindow()
{
    delete ui;
}
