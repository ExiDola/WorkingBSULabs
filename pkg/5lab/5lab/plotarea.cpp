#include "plotarea.h"
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>

LineSegmentData::LineSegmentData(const QPointF& p1, const QPointF& p2, const QColor& color)
{
    _p1 = p1;
    _p2 = p2;
    _color = color;
}

qreal LineSegmentData::x1() const
{
    return _p1.x();
}

qreal LineSegmentData::x2() const
{
    return _p2.x();
}

qreal LineSegmentData::y1() const
{
    return _p1.y();
}

qreal LineSegmentData::y2() const
{
    return _p2.y();
}
QPointF LineSegmentData::p1() const
{
    return _p1;
}
QPointF LineSegmentData::p2() const
{
    return _p2;
}
QColor LineSegmentData::color() const
{
    return _color;
}

PolygonData::PolygonData(const std::vector<QPointF>& points, const QColor& color)
{
    _points = points;
    _color = color;
}
QColor PolygonData::getColor() const
{
    return _color;
}
std::vector<QPointF> PolygonData::getPoints() const
{
    return _points;
}
PlotArea::PlotArea(QWidget *parent, PlotMode _mode):QWidget(parent)
{
    multix = std::min(width(), height()) / 20;
    mode = _mode;
}
QPointF PlotArea::Adjust(const QPointF& p)
{
    return QPointF(zx + p.x() * multix, zy - p.y() * multix);
}

void PlotArea::drawGrid(QPainter& p)
{
    QPen gridPen(gridColor);
    gridPen.setWidth(grid_line_width);
    p.setPen(gridPen);
    int i = 0;
    while(zx + i * multix <= width() - box_offset)
    {
        i++;
        p.drawLine(zx + i * multix, box_offset, zx + i * multix, height() - box_offset);
        p.drawLine(zx - i * multix, box_offset, zx - i * multix, height() - box_offset);
    }
    i = 0;
    while(zy + i * multix < height())
    {
        i++;
        p.drawLine(box_offset, zy + i * multix, width() - box_offset, zy + i * multix);
        p.drawLine(box_offset, zy - i * multix, width() - box_offset, zy - i * multix);
    }
}
void PlotArea::drawAxis(QPainter& p)
{
    QPen axisPen(axisColor);
    axisPen.setWidth(axis_width);
    p.setPen(axisPen);
    p.drawLine(box_offset, zy, width() - box_offset, zy);
    p.drawLine(zx, box_offset, zx, height() - box_offset);
}
void PlotArea::drawTicks(QPainter& p)
{
    QPen ticksPen(axisColor);
    ticksPen.setWidth(axis_width);
    p.setPen(ticksPen);
    QFont font = p.font();
    font.setPixelSize(12);
    p.setFont(font);
    //ticks x
    int i = 0;
    int alignFlags = Qt::AlignRight | Qt::AlignTop;
    p.drawText(QRect{zx  - multix + pixel_width, zy + pixel_width, multix - pixel_width, multix - pixel_width}, alignFlags, QString::number(0));
    while(zx + (i + 2) * multix < width())
    {
        i++;
        p.drawLine(zx + i * multix, zy + tick_length, zx + i * multix, zy - tick_length);
        p.drawLine(zx - i * multix, zy + tick_length, zx - i * multix, zy - tick_length);
        if (zx + (i + 1) * multix < width())
            p.drawText(QRect{zx + (i - 1) * multix + pixel_width, zy + pixel_width, multix - pixel_width, multix - pixel_width}, alignFlags, QString::number(i));
        p.drawText(QRect{zx - (i + 1) * multix + pixel_width, zy + pixel_width, multix - pixel_width, multix - pixel_width}, alignFlags, QString::number(-i));
    }
    i = 0;
    while(zy + (i + 2) * multix < height())
    {
        i++;
        p.drawLine(zx - tick_length, zy + i * multix, zx + tick_length, zy + i * multix);
        p.drawLine(zx - tick_length, zy - i * multix, zx + tick_length, zy - i * multix);
        if (zy - (i + 1) * multix > 0)
            p.drawText(QRect{zx  - multix + pixel_width, zy - (i) * multix +  pixel_width, multix - pixel_width, multix - pixel_width}, alignFlags, QString::number(i));
        p.drawText(QRect{zx - multix + pixel_width, zy + (i) * multix + pixel_width, multix - pixel_width, multix - pixel_width}, alignFlags, QString::number(-i));
    }
}

void PlotArea::drawClippingWindow(QPainter& p)
{
    p.setPen(QPen(clippingWindowColor, line_width));
    p.setBrush(Qt::NoBrush);
    p.drawRect(QRectF{Adjust(clippingWindowp1), Adjust(clippingWindowp2)});
}
void PlotArea::drawLineSegments(QPainter& p)
{
    for (const auto& segmentData : segments)
    {
        p.setPen(QPen(segmentData.color(), line_width));
        p.drawLine(Adjust(segmentData.p1()), Adjust(segmentData.p2()));
    }
}
void PlotArea::drawPolygons(QPainter& p)
{
    p.setPen(QPen(polygonBorderColor, line_width));
    for (const auto& polygon : polygons)
    {
        std::vector<QPointF> polygonData = polygon.getPoints();
        p.setBrush(polygon.getColor());
        if (polygonData.empty())
        {
            QMessageBox::warning(nullptr, "Ошибка", "Нет многоугольников");
            return;
        }
        QPainterPath path;
        path.moveTo(Adjust(polygonData[0]));
        for (size_t i = 1; i < polygonData.size(); ++i)
        {
            path.lineTo(Adjust(polygonData[i]));
        }
        path.lineTo(Adjust(polygonData[0]));
        p.drawPath(path);
    }
}
void PlotArea::AddLineSegment(const LineSegmentData& data)
{
    segments.push_back(data);
}
void PlotArea::AddPolygon(const std::vector<QPointF>& points, const QColor& fillingColor)
{
    polygons.push_back(PolygonData(points, fillingColor));
}
void PlotArea::SetPolygonBorderColor(const QColor& color)
{
    polygonBorderColor = color;
}
void PlotArea::SetClippingWindow(const QPoint& p1, const QPoint& p2)
{
    clippingWindowp1 = QPoint(std::min(p1.x(), p2.x()), std::max(p1.y(), p2.y()));
    clippingWindowp2 = QPoint(std::max(p1.x(), p2.x()), std::min(p1.y(), p2.y()));
}
QPoint PlotArea::getClippingWindowP1() const
{
    return clippingWindowp1;
}
QPoint PlotArea::getClippingWindowP2() const
{
    return clippingWindowp2;
}
void PlotArea::ChangeMode(PlotMode newMode)
{
    mode = newMode;
}
void PlotArea::Clear()
{
    segments.clear();
    polygons.clear();
}
void PlotArea::paintEvent(QPaintEvent*)
{
    zx = width() / 2;
    zy = height() / 2;
    QPainter pt(this);
    drawAxis(pt);
    drawTicks(pt);
    drawGrid(pt);
    switch(mode)
    {
        case PlotMode::Segments:
            drawClippingWindow(pt);
            drawLineSegments(pt);
            break;
        case PlotMode::Polygons:
            drawPolygons(pt);
            drawClippingWindow(pt);
            break;
        case PlotMode::None:
            break;
    }
}

