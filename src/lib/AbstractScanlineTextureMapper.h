//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2007      Andrew Manson    <g.real.ate@gmail.com>
//


#ifndef ABSTRACTSCANLINETEXTUREMAPPER_H
#define ABSTRACTSCANLINETEXTUREMAPPER_H

#include <QtCore/QObject>
#include <QtGui/QColor>

#include <cmath>
#include <math.h>

#include "GeoSceneTexture.h"

class TextureTile;
class TileLoader;
class ViewParams;


class AbstractScanlineTextureMapper : public QObject
{
    Q_OBJECT

public:
    explicit AbstractScanlineTextureMapper( TileLoader *tileLoader, QObject * parent=0 );
    ~AbstractScanlineTextureMapper();

    virtual void mapTexture( ViewParams *viewParams ) = 0;

    void setTextureLayer( GeoSceneTexture *textureLayer );
    void setMaxTileLevel( int level );
    virtual void resizeMap( int width, int height );
    void selectTileLevel( ViewParams* viewParams );
    bool interlaced() const;
    void setInterlaced( bool enabled );

    void centerTiles( ViewParams *viewParams, const int tileLevel,
                      double& tileCol, double& tileRow );

 Q_SIGNALS:
    void mapChanged();

 private Q_SLOTS:
    void notifyMapChanged();

 protected:
    void pixelValue( const double& lon, const double& lat, 
                     QRgb* scanLine, bool smooth = false );
    void nextTile();
    void detectMaxTileLevel();
    void tileLevelInit( int tileLevel );

    int globalWidth() const;
    int globalHeight() const;

    // Converts Radian to global texture coordinates 
    // ( with origin in center, measured in pixel) 
    double rad2PixelX( const double longitude ) const;
    double rad2PixelY( const double latitude ) const;

    QRgb bilinearSmooth( const QRgb& topLeftValue ) const;

    // Coordinates on the tile
    double     m_posX;
    double     m_posY;

    // maximum values for global texture coordinates
    // ( with origin in upper left corner, measured in pixel) 
    int     m_maxGlobalX;
    int     m_maxGlobalY;

    int     m_imageHeight;
    int     m_imageWidth;
    int     m_imageRadius;

    // Previous coordinates
    double  m_prevLat;
    double  m_prevLon;

    // Coordinate transformations:

    // Converts global texture coordinates 
    // ( with origin in center, measured in pixel) 
    // to tile coordinates ( measured in pixel )
    double  m_toTileCoordinatesLon;
    double  m_toTileCoordinatesLat;

    bool m_interlaced;

    // ------------------------
    // Tile stuff
    TileLoader  *m_tileLoader;
    GeoSceneTexture::Projection m_tileProjection;
    QRgb        *m_scanLine;


    TextureTile *m_tile;

    int          m_tileLevel;
    int          m_maxTileLevel;

    int          m_preloadTileLevel;
    int          m_previousRadius;

    // Position of the tile in global Texture Coordinates
    // ( with origin in upper left corner, measured in pixel) 
    int          m_tilePosX;
    int          m_tilePosY;

 private:
    int          m_globalWidth;
    int          m_globalHeight;
    double       m_normGlobalWidth;
    double       m_normGlobalHeight;
};

inline void AbstractScanlineTextureMapper::setMaxTileLevel( int level )
{
    m_maxTileLevel = level;
}

inline bool AbstractScanlineTextureMapper::interlaced() const
{
    return m_interlaced;
}

inline void AbstractScanlineTextureMapper::setInterlaced( bool enabled )
{
    m_interlaced = enabled;
}

inline int AbstractScanlineTextureMapper::globalWidth() const
{
    return m_globalWidth;
}

inline int AbstractScanlineTextureMapper::globalHeight() const
{
    return m_globalHeight;
}

inline double AbstractScanlineTextureMapper::rad2PixelX( const double longitude ) const
{
    return longitude * m_normGlobalWidth;
}

inline double AbstractScanlineTextureMapper::rad2PixelY( const double latitude ) const
{
    switch ( m_tileProjection ) {
    case GeoSceneTexture::Equirectangular:
        return -latitude * m_normGlobalHeight;
    case GeoSceneTexture::Mercator:
        if ( fabs( latitude ) < 1.4835 )
            return - asinh( tan( latitude ) ) * 0.5 * m_normGlobalHeight;
        if ( latitude > +1.4835 )
            return - asinh( tan( +1.4835 ) ) * 0.5 * m_normGlobalHeight; 
        if ( latitude < -1.4835 )
            return - asinh( tan( -1.4835 ) ) * 0.5 * m_normGlobalHeight; 
    }
}

#endif
