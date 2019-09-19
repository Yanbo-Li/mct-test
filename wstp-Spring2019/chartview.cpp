#include "chartview.h"
#include <iostream>
#include <tuple>
#include <QtCore>
#include <QColor>
#include <QtGlobal>
#include <QtGui/QMouseEvent>

ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    series(0),
    dragablePoints(0),
    m_isTouching(false)
{
    setRubberBand(QChartView::RectangleRubberBand);
    QChartView::chart()->setTitle("Click to interact with scatter points");
    QChartView::chart()->setTitle("Chart");
    pointToMove = nullptr;
}

ChartView::ChartView(QWidget *parent) :
    QChartView(parent),
    series(0),
    dragablePoints(0),
    m_isTouching(false)
{
    setRubberBand(QChartView::RectangleRubberBand);
    QChartView::chart()->setTitle("Click to interact with scatter points");
    QChartView::chart()->setTitle("Chart");
    pointToMove = nullptr;
}

ChartView::~ChartView()
{

}


void ChartView::addSeries(std::vector<std::pair<double, double> > dots, size_t idx) {
    // if the number of points in the current series is less than 60 (usually 52) and all of the points are the same, add them as scatter line
    if(dots.size() < 60) {
        bool isScatter = true;
        for(size_t i=0; i<dots.size(); i++) {
            for(size_t j=i+1; j<dots.size(); j++) {
                if(!qFuzzyCompare(dots[i].first, dots[j].first) || !qFuzzyCompare(dots[i].second, dots[j].second)) {
                    isScatter = false;
                }
            }
        }
        if(isScatter){
            this->addDragablePoint(dots, idx);
            return;
        }
    }

    QSplineSeries *series = new QSplineSeries();
    series->setName("graph" + QString("%1").arg(idx));

    for(auto dot: dots) {
        QPointF p(dot.first, dot.second);
        series->append(dot.first, dot.second);
    }
    chart()->addSeries(series);
    chart()->createDefaultAxes();
    this->series.push_back(series);
}

void ChartView::addDragablePoint(std::vector<std::pair<double, double> > dots, size_t idx) {
    QScatterSeries *series = new QScatterSeries();
    series->setName("point" + QString("%1").arg(idx));
    for(auto dot: dots) {
        QPointF p(dot.first, dot.second);
        series->append(dot.first, dot.second);
    }
    series->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    dragablePoints.push_back(series);
    chart()->addSeries(series);
    chart()->createDefaultAxes();
}

void ChartView::handleClickedPoint(const QPointF &point)
{
    QPointF clickedPoint = point;
    // Find the closest point from series 1
    QPointF closest(INT_MAX, INT_MAX);
    qreal distance(INT_MAX);
    const auto points = dragablePoints.back()->points();
    for (const QPointF &currentPoint : points) {
        qreal currentDistance = qSqrt((currentPoint.x() - clickedPoint.x())
                                      * (currentPoint.x() - clickedPoint.x())
                                      + (currentPoint.y() - clickedPoint.y())
                                      * (currentPoint.y() - clickedPoint.y()));
        if (currentDistance < distance) {
            distance = currentDistance;
            closest = currentPoint;
        }
    }
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    QChartView::mouseMoveEvent(event);
}


void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton)) {
        return;
    }
    findClosestPoint(transformCoordinate(event));
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if(pointToMove != nullptr) {
        QPointF* pointMoveTo = findClosestPointInOneSection(transformCoordinate(event), series[section]->points());

        // set the new point
        QScatterSeries *newSeries = new QScatterSeries();
        *newSeries << *pointMoveTo;
        newSeries->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
        newSeries->setColor(dragablePoints[section]->color());

        // remove the old point and insert new point
        chart()->removeSeries(dragablePoints[section]);

        // update the chart
        chart()->addSeries(newSeries);
        chart()->createDefaultAxes();
        chart()->axisX()->setRange(-5, 5);
        chart()->axisY()->setRange(-5, 5);
        chart()->show();

        // update set of all points
        dragablePoints.erase(dragablePoints.begin() + static_cast<int>(section));
        dragablePoints.insert(dragablePoints.begin() + static_cast<int>(section), newSeries);

        std::cout << "new point: " << pointMoveTo->rx() << " " << pointMoveTo->ry() << " added" << std::endl;
    }
    else {
        std::cout << "pointMoveTo is null" << std::endl;
    }
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Equal:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}

void ChartView::findClosestPoint(QPointF clickedPoint) {
    // Find the closest point from series 1
    QPointF *closest = new QPointF(INT_MAX, INT_MAX);
    qreal distance(INT_MAX);
    for(size_t i=0; i<dragablePoints.size(); i++) {
        auto set = dragablePoints[i];
        const auto points = set->points();
        for (const QPointF &currentPoint : points) {
            qreal currentDistance = qSqrt((currentPoint.x() - clickedPoint.x())
                                          * (currentPoint.x() - clickedPoint.x())
                                          + (currentPoint.y() - clickedPoint.y())
                                          * (currentPoint.y() - clickedPoint.y()));
            if (currentDistance < distance) {
                distance = currentDistance;
                closest->setX(currentPoint.x());
                closest->setY(currentPoint.y());
                section = i;
            }
        }
    }
    // if the distance to the closest point is smaller than a certain value, move it.
    if(distance < 1) {
        pointToMove = closest;
        return;
    }
    pointToMove = nullptr;
}

QPointF* ChartView::findClosestPointInOneSection(QPointF clickedPoint, QList<QPointF> points) {
    qreal distance(INT_MAX);
    QPointF *closest = new QPointF(INT_MAX, INT_MAX);
    for (const QPointF &currentPoint : points) {
        qreal currentDistance = qSqrt((currentPoint.x() - clickedPoint.x())
                                      * (currentPoint.x() - clickedPoint.x())
                                      + (currentPoint.y() - clickedPoint.y())
                                      * (currentPoint.y() - clickedPoint.y()));
        if (currentDistance < distance) {
            distance = currentDistance;
            closest->setX(currentPoint.x());
            closest->setY(currentPoint.y());
        }
    }
    return closest;
}

// function to transform widge coordinate to chart coordinate
QPointF ChartView::transformCoordinate(QMouseEvent *event) {
    auto const widgetPos = event->localPos();
    auto const scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
    auto const chartItemPos = chart()->mapFromScene(scenePos);
    auto const valueGivenSeries = chart()->mapToValue(chartItemPos);
//    qDebug() << "widgetPos:" << widgetPos;
//    qDebug() << "scenePos:" << scenePos;
//    qDebug() << "chartItemPos:" << chartItemPos;
//    qDebug() << "valSeries:" << valueGivenSeries;
    return valueGivenSeries;
}


std::vector<std::pair<double, double>> ChartView::getRange(std::vector<std::pair<double, double>> series) {
    std::vector<std::pair<double, double>> result; // first pair is x_min and x_max, second pair is y_min and y_max
    std::pair<double, double> rangeX(INT_MAX, INT_MIN);
    std::pair<double, double> rangeY(INT_MAX, INT_MIN);
    for (size_t i = 0; i < series.size(); i++) {
        if(series[i].first < rangeX.first) {
            rangeX.first = series[i].first;
        }
        if(series[i].first> rangeX.second) {
            rangeX.second = series[i].first;
        }
        if(series[i].second < rangeY.first) {
            rangeY.first = series[i].second;
        }
        if(series[i].second> rangeY.second) {
            rangeY.second = series[i].second;
        }
    }
    rangeX.first -= 5;
    rangeX.second += 5;
    rangeY.first -= 5;
    rangeY.second += 5;
    result.push_back(rangeX);
    result.push_back(rangeY);
    return result;
}

std::vector<std::pair<double, double>> ChartView::getRange(std::vector<std::vector<std::pair<double, double>>> series) {
    std::vector<std::pair<double, double>> result; // first pair is x_min and x_max, second pair is y_min and y_max
    std::pair<double, double> rangeX(INT_MAX, INT_MIN);
    std::pair<double, double> rangeY(INT_MAX, INT_MIN);
    result.push_back(rangeX);
    result.push_back(rangeY);
    for(size_t i = 0; i < series.size(); i++) {
        std::vector<std::pair<double, double>> tempResult = getRange(series[i]);
        if(tempResult[0].first < result[0].first) {
            result[0].first = tempResult[0].first;
        }
        if(tempResult[0].second > result[0].second) {
            result[0].second = tempResult[0].second;
        }
        if(tempResult[1].first < result[1].first) {
            result[1].first = tempResult[1].first;
        }
        if(tempResult[1].second > result[1].second) {
            result[1].second = tempResult[1].second;
        }
    }
    return result;
}







