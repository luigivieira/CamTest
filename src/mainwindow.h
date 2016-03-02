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
 
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "opencv2/opencv.hpp"

namespace Ui {
    class MainWindow;
}

namespace ct
{
    /**
     * Main GUI window class.
     */
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        /**
         * Class constructor.
         * @param pParent QWidget with the parent window.
         */
        explicit MainWindow(QWidget *pParent = 0);

        /**
         * Class destructor.
         */
        virtual ~MainWindow();

	private slots:
		/**
		 * Slot for the toggling of the action Camera On/Off.
		 * @param bChecked Boolean with the checked state.
		 */
		void on_actionCameraOn_toggled(bool bChecked);

		/**
		 * Slot for the toggling of the action Stay on Top.
		 * @param bChecked Boolean with the checked state.
		 */
		void on_actionStayOnTop_toggled(bool bChecked);

		/**
		 * Slot for the toggling of the action Full Screen.
		 * @param bChecked Boolean with the checked state.
		 */
		void on_actionFullScreen_toggled(bool bChecked);
        
        /**
		 * Slot for the triggering of the action About.
		 */
		void on_actionAbout_triggered();

		/**
		 * Slot for the triggering of the action Exit.
		 */
		void on_actionExit_triggered();

		/**
		 * Slot for receiving the timer updates.
 		 */
		void onTimeout();

    private:
        /** Instance of the ui for GUI element access. */
        Ui::MainWindow *ui;

		/** Constant with the timer interval for video capturing */
		static const int UPDATE_INTERVAL = 100;

		/** Instance of the OpenCV's object used to capture frames from the webcam. */
		cv::VideoCapture m_oVCap;

        /** Instance of the timer used to trigger the capture of frames. */
		QTimer m_oTimer;
    };
};

#endif // MAINWINDOW_H
