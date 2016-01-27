#ifndef WEATHER_H
#define WEATHER_H

#include <QDialog>
#include <QtNetwork>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class Weather : public QDialog
{
    Q_OBJECT

public:
    Weather(QWidget *parent = 0);
    ~Weather();
private slots:
    void analysisJson();
private:
    QPushButton *getBtn;
    QNetworkReply *replay;
    QNetworkRequest request;
    QJsonDocument jsonDocument;
    QJsonObject jsonObj;
    QNetworkAccessManager manager;
    QString data;
    QGridLayout *mainLayout;
    QString time;
    QLabel *cityLabel;
    QLineEdit *cityLineEdit;
    QLabel *provLabel;
    QLineEdit *provLineEdit;
    QTextEdit *textResult;
};

#endif // WEATHER_H
