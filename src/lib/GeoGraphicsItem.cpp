//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Bastian Holst <bastianholst@gmx.de>
//

// Self
#include "GeoGraphicsItem.h"
#include "GeoGraphicsItem_p.h"

//Marble
#include "GeoDataCoordinates.h"

// Qt
#include <QtCore/QDebug>

using namespace Marble;

GeoGraphicsItem::GeoGraphicsItem()
    : MarbleGraphicsItem( new GeoGraphicsItemPrivate )
{
    setFlag( ItemIsVisible, true );
}

GeoGraphicsItem::GeoGraphicsItem( GeoGraphicsItemPrivate *d_ptr )
    : MarbleGraphicsItem( d_ptr )
{
    setFlag( ItemIsVisible, true );
}

GeoGraphicsItem::~GeoGraphicsItem() {
}

GeoDataCoordinates GeoGraphicsItem::coordinate() const {
    return p()->m_coordinate;
}

void GeoGraphicsItem::coordinate( qreal &longitude, qreal &latitude, qreal &altitude ) const {
    longitude = p()->m_coordinate.longitude();
    latitude = p()->m_coordinate.latitude();
    altitude = p()->m_coordinate.altitude();
}

void GeoGraphicsItem::setCoordinate( qreal longitude, qreal latitude, qreal altitude ) {
    p()->m_coordinate.setLongitude( longitude );
    p()->m_coordinate.setLatitude( latitude );
    p()->m_coordinate.setAltitude( altitude );
}

void GeoGraphicsItem::setCoordinate( const GeoDataCoordinates &point ) {
    p()->m_coordinate = point;
}

QString GeoGraphicsItem::target() {
    return p()->m_target;
}

void GeoGraphicsItem::setTarget( const QString& target ) {
    p()->m_target = target;
}

GeoGraphicsItem::GeoGraphicsItemFlags GeoGraphicsItem::flags()
{
    return p()->m_flags;
}

void GeoGraphicsItem::setFlag( GeoGraphicsItemFlag flag, bool enabled )
 {
    if( enabled ) {
        p()->m_flags = p()->m_flags | flag;
    } else {
        p()->m_flags = p()->m_flags & ~flag;
    }
}

void GeoGraphicsItem::setFlags( GeoGraphicsItemFlags flags )
{
    p()->m_flags = flags;
}

QList<QPointF> GeoGraphicsItem::positions() {
    return p()->positions();
}

GeoGraphicsItemPrivate *GeoGraphicsItem::p() const {
    return reinterpret_cast<GeoGraphicsItemPrivate *>( d );
}
