#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <QtGui>
#include <QGraphicsEffect>

class Highlight : public QGraphicsEffect
{
 Q_OBJECT
 Q_PROPERTY( QColor color READ color WRITE setColor )
 Q_PROPERTY( QPointF offset READ offset WRITE setOffset )

 public:
  Highlight( qreal offset = 1.5 );
  virtual QRectF boundingRectFor( const QRectF& sourceRect ) const;
  QColor color() const { return mColor;}
  void setColor( QColor& color ) { mColor = color;}
  QPointF offset() const { return mOffset;}
  void setOffset( QPointF offset ) { mOffset = offset;}

 protected:
  virtual void draw( QPainter *painter ); // , QGraphicsEffectSource *source );

 private:
  QColor mColor;
  QPointF mOffset;
};

#endif // HIGHLIGHT_H
