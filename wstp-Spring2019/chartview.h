#ifndef CHARTVIEW_H
#define CHARTVIEW_H
#include <vector>
#include <tuple>
#include <QtCharts>
#include <QtWidgets/QRubberBand>

class ChartView : public QChartView
{
    Q_OBJECT
public:
    ChartView(QChart *chart, QWidget *parent = 0);
    ~ChartView();
    void addSeries(std::vector<std::pair<double, double> > dots, size_t idx);
    void addDragablePoint(std::vector<std::pair<double, double> > dots, size_t idx);
    std::vector<std::pair<double, double>> getRange(std::vector<std::pair<double, double>> series);
    std::vector<std::pair<double, double>> getRange(std::vector<std::vector<std::pair<double, double>>> series);

private Q_SLOTS:
    // bool viewportEvent(QEvent *event);
    void handleClickedPoint(const QPointF &point);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPointF transformCoordinate(QMouseEvent *event);
    void findClosestPoint(QPointF point);
    QPointF* findClosestPointInOneSection(QPointF clickedPoint, QList<QPointF> points);
    std::vector<QSplineSeries*> series;
    std::vector<QScatterSeries*> dragablePoints;
    bool m_isTouching;
    QPointF m_lastMousePos;
    QPointF *pointToMove;
    size_t section;
};

#endif // CHARTVIEW_H
