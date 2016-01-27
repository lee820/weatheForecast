#include "weather.h"

Weather::Weather(QWidget *parent)
    : QDialog(parent)
{
    getBtn=new QPushButton(tr("获取天气"));
    cityLabel=new QLabel(tr("城市："));
    cityLineEdit=new QLineEdit;
    cityLineEdit->setText(tr("蚌埠"));
    provLabel=new QLabel(tr("省："));
    provLineEdit=new QLineEdit;
    provLineEdit->setText(tr("安徽"));
    textResult=new QTextEdit;
    connect(getBtn,SIGNAL(clicked(bool)),this,SLOT(analysisJson()));
    mainLayout=new QGridLayout;
    mainLayout->setSpacing(5);
    mainLayout->addWidget(provLabel,0,0);
    mainLayout->addWidget(provLineEdit,0,1);
    mainLayout->addWidget(cityLabel,1,0);
    mainLayout->addWidget(cityLineEdit,1,1);
    mainLayout->addWidget(getBtn,1,2);
    mainLayout->addWidget(textResult,2,0,3,3);
    setLayout(mainLayout);
}

Weather::~Weather()
{

}

void Weather::analysisJson()
{
    data="";
    QString city=cityLineEdit->text();
    QString prov=provLineEdit->text();
    QString url="http://apis.baidu.com/lib360/weatherapi/weather360";
    QString param="city="+city+"&prov="+prov;                           //城市和省来自LineEdit中输入的值
    QString strUrl=url+"?"+param;
    request.setUrl(strUrl);
    request.setRawHeader("apikey","c7f675bc03144dcc9510508588979439");
    this->replay=this->manager.get(this->request);
    QEventLoop eventLoop;
    connect(&this->manager,SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));
    eventLoop.exec();

    QString temp(this->replay->readAll());
    QJsonParseError error;
    //qDebug()<<temp;
    jsonDocument=QJsonDocument::fromJson(temp.toUtf8(),&error);
    if(error.error==QJsonParseError::NoError)
    {
        if(!(jsonDocument.isNull()||jsonDocument.isEmpty()))
        {
            if(jsonDocument.isObject())
            {
                QVariantMap result1=jsonDocument.toVariant().toMap();
                //qDebug()<<result1["pm25"].toString();

                QVariantList datalist=result1["data"].toList();
                foreach(QVariant plu,datalist)
                {
                    QVariantMap dataResult=plu.toMap();

                    data=data+
                            dataResult["Year"].toString()+"年"+dataResult["Month"].toString()+"月"+dataResult["Day"].toString()+"日"+"\n"
                            "天气："+dataResult["Weather"].toString()+"\n"
                            "温度："+dataResult["TempMin"].toString()+"~"+dataResult["TempMax"].toString()+"\n\r"
                            ;
                    textResult->setText(data);
                }
            }
        }
    }
}
