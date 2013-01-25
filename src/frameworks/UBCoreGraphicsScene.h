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


#ifndef UBCOREGRAPHICSSCENE_H_
#define UBCOREGRAPHICSSCENE_H_

#include <QtGui>

class UBCoreGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

    public:
        UBCoreGraphicsScene(QObject * parent = 0);
        virtual ~UBCoreGraphicsScene();

        virtual void addItem(QGraphicsItem* item);

        virtual void removeItem(QGraphicsItem* item, bool forceDelete = false);

        virtual bool deleteItem(QGraphicsItem* item);

        void removeItemFromDeletion(QGraphicsItem* item);
        void addItemToDeletion(QGraphicsItem *item);

        bool isModified() const
        {
            return mIsModified;
        }

        void setModified(bool pModified)
        {
            mIsModified = pModified;
        }


    private:
        QSet<QGraphicsItem*> mItemsToDelete;

        bool mIsModified;
};

#endif /* UBCOREGRAPHICSSCENE_H_ */
