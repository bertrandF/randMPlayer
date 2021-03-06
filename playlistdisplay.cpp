/*
 *  This file is part of the randMPlayer project
 *  Copyright (C) 17/04/2014 -- playlistdisplay.cpp -- bertrand
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


#include "playlistdisplay.h"
#include "ui_playlistdisplay.h"

playlistDisplay::playlistDisplay(QMediaPlaylist *playlist, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playlistDisplay)
{
    int i;
    QListWidgetItem *currentMedia;

    ui->setupUi(this);

    for(i=0 ; i<playlist->mediaCount() ; ++i)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(playlist->media(i).canonicalUrl().toDisplayString());
        ui->playlistWidget->addItem(item);
    }
    currentMedia = ui->playlistWidget->item(playlist->currentIndex());
    if(currentMedia != NULL)
        currentMedia->setBackgroundColor(Qt::red);

    this->setWindowTitle("Playlist");
}

playlistDisplay::~playlistDisplay()
{
    delete ui;
}
