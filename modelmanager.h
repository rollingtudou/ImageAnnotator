#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>
#include <QString>
#include <QImage>
#include <Python.h>
#include <numpy/arrayobject.h>

class ModelManager : public QObject
{
    Q_OBJECT

public:
    static ModelManager* instance();
    ~ModelManager();

    bool initializePython();
    bool loadModel(const QString &modelPath);
    QVector<QPolygonF> runSegmentation(const QImage &image);

signals:
    void segmentationProgress(int percent);
    void segmentationCompleted();
    void segmentationError(const QString &error);

private:
    explicit ModelManager(QObject *parent = nullptr);
    static ModelManager* s_instance;

    PyObject *pModule;
    PyObject *pFunc;
    bool pythonInitialized;

    QImage convertMaskToPolygons(PyObject *maskArray);
    PyObject* convertQImageToPyArray(const QImage &image);
};

#endif // MODELMANAGER_H 