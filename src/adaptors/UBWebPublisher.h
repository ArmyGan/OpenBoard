/*
 * Copyright (C) 2012 Webdoc SA
 *
 * This file is part of Open-Sankoré.
 *
 * Open-Sankoré is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation, version 2,
 * with a specific linking exception for the OpenSSL project's
 * "OpenSSL" library (or with modified versions of it that use the
 * same license as the "OpenSSL" library).
 *
 * Open-Sankoré is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with Open-Sankoré; if not, see
 * <http://www.gnu.org/licenses/>.
 */


#ifndef UBWEBPUBLISHER_H_
#define UBWEBPUBLISHER_H_

#include <QtGui>

#include "UBExportAdaptor.h"

#include "frameworks/UBFileSystemUtils.h"
#include "ui_webPublishing.h"

class UBDocumentProxy;
class UBServerXMLHttpRequest;

class UBWebPublisher : public UBExportAdaptor
{
    Q_OBJECT

    public:
        UBWebPublisher(QObject *parent = 0);
        virtual ~UBWebPublisher();

        virtual QString exportName();

        virtual void persist(UBDocumentProxy* pDocument);

        virtual bool associatedActionactionAvailableFor(const QModelIndex &selectedIndex);
};


#endif /* UBWEBPUBLISHER_H_ */
