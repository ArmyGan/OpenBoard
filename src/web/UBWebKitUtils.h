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


#ifndef UBWEBKITUTILS_H_
#define UBWEBKITUTILS_H_

#include <QtWebKit>

class UBWebKitUtils
{
    public:
        UBWebKitUtils();
        virtual ~UBWebKitUtils();

        class HtmlObject
        {

            public:
                HtmlObject();
                HtmlObject(const QString &pSource, const QString &pObjectName, const QString &pObjectMimeType, const QString &pTagName, int pWidth, int pHeight);
                HtmlObject(const QString &pSource, const QString &metaDataString);

                QString source;
                QString tagName;
                QString objectName;
                QString objectMimeType;
                QString embedCode;
                int width;
                int height;


                bool operator == (const HtmlObject &obj);

        };
        static QString widgetNameFromUrl(QString pObjectUrl);
        static QList<UBWebKitUtils::HtmlObject> objectsInFrameByTag(QWebFrame* frame, QString tagName);
        static QStringList validUrl(QUrl& baseUrl,QStringList& list);
        static QStringList getUrls(QUrl& baseUrl,QWebElement& element);
        static QStringList getArgumentsValues(QString& string);

};

#endif /* UBWEBKITUTILS_H_ */
