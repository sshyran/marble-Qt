/*
    Copyright (C) 2008 Torsten Rahn <rahn@kde.org>

    This file is part of the KDE project

    This library is free software you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    aint with this library see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef GEOSCENEMAP_H
#define GEOSCENEMAP_H

#include <QtCore/QString>
#include <QtCore/QVector>

#include "GeoDocument.h"

class GeoSceneLayer;

/**
 * @short Map layer structure of a GeoScene document.
 */

class GeoSceneMap : public GeoNode {
 public:
    GeoSceneMap();
    ~GeoSceneMap();

    QString backgroundColor() const;
    void setBackgroundColor( const QString& );

    /**
     * @brief  Add a section to the legend
     * @param  section  the new section
     */
    void addLayer( GeoSceneLayer* );
    GeoSceneLayer* layer( const QString& );
    QVector<GeoSceneLayer*> layers() const;

 protected:
    /// The vector holding all the sections in the legend.
    /// (We want to preserve the order and don't care 
    /// much about speed here), so we don't use a hash
    QVector<GeoSceneLayer*> m_layers;

    QString m_backgroundColor;
};


#endif // GEOSCENEMAP_H
