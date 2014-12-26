//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2013 Mihail Ivchenko <ematirov@gmail.com>
// Copyright 2014 Sanjiban Bairagya <sanjiban22393@gmail.com>
// Copyright 2014 Illya Kovalevskyy <illya.kovalevskyy@gmail.com>
//

#include <QDoubleSpinBox>
#include <QToolButton>
#include <QLabel>
#include <QHBoxLayout>

#include "FlyToEditWidget.h"
#include "MarbleWidget.h"
#include "geodata/data/GeoDataFlyTo.h"
#include "GeoDataTypes.h"
#include "GeoDataCamera.h"
#include "MarblePlacemarkModel.h"

namespace Marble
{

FlyToEditWidget::FlyToEditWidget( const QModelIndex &index, MarbleWidget* widget, QWidget *parent ) :
    QWidget( parent ),
    m_widget( widget ),
    m_index( index )
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing( 5 );

    QLabel* iconLabel = new QLabel;
    iconLabel->setPixmap( QPixmap( ":/marble/flag.png" ) );
    layout->addWidget( iconLabel );

    QLabel *waitLabel = new QLabel;
    waitLabel->setText(tr("Wait duration:"));
    layout->addWidget(waitLabel);

    m_waitSpin = new QDoubleSpinBox;
    layout->addWidget(m_waitSpin);
    m_waitSpin->setValue(flyToElement()->duration());
    m_waitSpin->setSuffix( tr(" s", "seconds") );

    QToolButton* flyToPinCenter = new QToolButton;
    flyToPinCenter->setIcon(QIcon(":/marble/places.png"));
    flyToPinCenter->setToolTip(tr("Current map center"));
    connect(flyToPinCenter, SIGNAL(clicked()), this, SLOT(updateCoordinates()));
    layout->addWidget(flyToPinCenter);

    QToolButton *button = new QToolButton;
    button->setIcon( QIcon( ":/marble/document-save.png" ) );
    connect(button, SIGNAL(clicked()), this, SLOT(save()));
    layout->addWidget( button );

    setLayout( layout );
}

void FlyToEditWidget::updateCoordinates()
{
    m_coord = m_widget->focusPoint();
}

void FlyToEditWidget::save()
{
    if (flyToElement()->view() != 0 && m_coord != GeoDataCoordinates()) {
        GeoDataCoordinates coords = m_coord;
        if ( flyToElement()->view()->nodeType() == GeoDataTypes::GeoDataCameraType ) {
            GeoDataCamera* camera = dynamic_cast<GeoDataCamera*>( flyToElement()->view() );
            camera->setCoordinates( coords );
        } else if ( flyToElement()->view()->nodeType() == GeoDataTypes::GeoDataLookAtType ) {
            GeoDataLookAt* lookAt = dynamic_cast<GeoDataLookAt*>( flyToElement()->view() );
            lookAt->setCoordinates( coords );
        } else{
            GeoDataLookAt* lookAt = new GeoDataLookAt;
            lookAt->setCoordinates( coords );
            flyToElement()->setView( lookAt );
        }
    }

    flyToElement()->setDuration(m_waitSpin->value());

    emit editingDone(m_index);
}

GeoDataFlyTo* FlyToEditWidget::flyToElement()
{
    GeoDataObject *object = qvariant_cast<GeoDataObject*>(m_index.data( MarblePlacemarkModel::ObjectPointerRole ) );
    Q_ASSERT( object );
    Q_ASSERT( object->nodeType() == GeoDataTypes::GeoDataFlyToType );
    return static_cast<GeoDataFlyTo*>( object );
}

} // namespace Marble

#include "FlyToEditWidget.moc"