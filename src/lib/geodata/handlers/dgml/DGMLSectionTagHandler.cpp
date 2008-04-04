/*
    Copyright (C) 2007 Nikolas Zimmermann <zimmermann@kde.org>
    Copyright (C) 2008 Torsten Rahn <tackat@kde.org>

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

#include <QDebug>

#include "DGMLSectionTagHandler.h"

#include "DGMLElementDictionary.h"
#include "DGMLAttributeDictionary.h"
#include "DGMLAuxillaryDictionary.h"
#include "GeoParser.h"
#include "GeoSceneLegend.h"
#include "GeoSceneSection.h"

using namespace GeoSceneElementDictionary;
using namespace GeoSceneAttributeDictionary;
using namespace GeoSceneAuxillaryDictionary;

DGML_DEFINE_TAG_HANDLER(Section)

DGMLSectionTagHandler::DGMLSectionTagHandler()
    : GeoTagHandler()
{
}

DGMLSectionTagHandler::~DGMLSectionTagHandler()
{
}

GeoNode* DGMLSectionTagHandler::parse(GeoParser& parser) const
{
    // Check whether the tag is valid
    Q_ASSERT(parser.isStartElement() && parser.isValidElement(dgmlTag_Section));

    QString name      = parser.attribute(dgmlAttr_name);
    QString checkable = parser.attribute(dgmlAttr_checkable).toLower().trimmed();
    int     spacing   = parser.attribute(dgmlAttr_spacing).toInt();

    GeoSceneSection* section = 0;

    // Checking for parent item
    GeoStackItem parentItem = parser.parentElement();
    if (parentItem.represents(dgmlTag_Legend)) {
        section = new GeoSceneSection( name );
        section->setCheckable( checkable == dgmlValue_true || dgmlValue_on );
        section->setSpacing( spacing );
        parentItem.nodeAs<GeoSceneLegend>()->addSection( section );
    }

    return section;
}
