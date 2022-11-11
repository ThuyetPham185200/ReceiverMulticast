/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtNetwork>
#include <qstring.h>
#include "receiver.h"
#include <iostream>
#include <fstream>

MulticastReceiver::MulticastReceiver(QObject *parent)
    : QObject(parent)
{
    this->count_ = 0;
}
///////////////////////////////////////////////////////////////////////
MulticastReceiver::~MulticastReceiver()
{
    delete this->udpSocket_;
    this->udpSocket_ = nullptr;
}
///////////////////////////////////////////////////////////////////////
void MulticastReceiver::getInfor(QString gAddress, QString port)
{
    this->udpSocket_ = new QUdpSocket(this);
    this->groupAddress_ =  QHostAddress(gAddress);
    int n_ = port.toInt();
    this->udpSocket_->bind(QHostAddress::AnyIPv4, n_, QUdpSocket::ShareAddress);
    this->udpSocket_->joinMulticastGroup(groupAddress_);
    connect(this->udpSocket_, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
}
///////////////////////////////////////////////////////////////////////
void MulticastReceiver::processPendingDatagrams()
{
    while (this->udpSocket_->hasPendingDatagrams()) {
        QByteArray datagram_;
        datagram_.resize(this->udpSocket_->pendingDatagramSize());
        udpSocket_->readDatagram(datagram_.data(), datagram_.size());
        //qDebug(datagram_);
        std::vector<unsigned char> dataFrame_(datagram_.begin(), datagram_.end());
        this->count_ += 1;
        if (this->count_ == 1)
        {
            for (auto e : dataFrame_)
            {
                count_ += 1;
                printf("%02x ", e);
                if(count_ % 16 == 0) printf("\n");
            }
        }
//       this->count_ +=1;
       //printf("length of dataFrame: %d\n id: %d\n", dataFrame_.size(), this->count_);
       this->logData(dataFrame_);
    }
}
///////////////////////////////////////////////////////////////////////
void MulticastReceiver::logData(std::vector<unsigned char> data)
{
    std::ofstream myFile_ ("dataFrame.bin", std::ios::out | std::ios::binary);
    myFile_.write ((const char*)&data.front(), data.size());
}

