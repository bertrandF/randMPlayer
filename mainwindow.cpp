/*
 *  This file is part of the randMPlayer project
 *  Copyright (C) 17/04/2014 -- mainwindow.cpp -- bertrand
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * */

#include <QProcess>
#include <QDirIterator>
#include <QFileDialog>
#include <QDebug>
#include <QTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playlistdisplay.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    connect(ui->nextMediaButton, SIGNAL(clicked()),
            &(this->playlist), SLOT(next()));
    connect(ui->newPlaylistButton, SIGNAL(clicked()),
              this, SLOT(setNewPlaylist()));
    ui->centralWidget->show();

    this->setWindowTitle("Directory Random Player");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_restartButton_clicked()
{
    this->playlist.setCurrentIndex(0);
}

void MainWindow::on_showPlaylistButton_clicked()
{
    playlistDisplay pld(&(this->playlist), this->ui->centralWidget);
    pld.setWindowModality(Qt::WindowModal);
    pld.exec();
}

void MainWindow::on_videoWidget_wheelTurned(QWheelEvent *event)
{
        this->player.setVolume(this->player.volume() +
                               event->angleDelta().y()/120);
}

void MainWindow::setNewPlaylist()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                                "Select Directory", "/home");
    if(!dir.isEmpty())
    {
        QStringList fileFilters = QStringList();
        fileFilters << "*.mp4" << "*.flv" << "*.avi" << "*.wmv" << "*.mkv"
                    << "*.mpg" << "*.mpeg";
        QDirIterator it(dir, fileFilters, QDir::Readable | QDir::NoDotAndDotDot |
                        QDir::Files | QDir::NoSymLinks,
                        QDirIterator::Subdirectories);
        this->playlist.clear();
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        this->playlist.setPlaybackMode(QMediaPlaylist::Random);
        while(it.hasNext())
        {
            it.next();
            this->playlist.addMedia(QMediaContent(
                                        QUrl::fromLocalFile(it.filePath())));
        }
        this->playlist.shuffle();
        this->player.setPlaylist(&(this->playlist));
        this->player.setVideoOutput(ui->videoWidget);
        ui->videoWidget->show();
        this->player.play();
    }
}
