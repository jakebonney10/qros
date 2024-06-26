#pragma once

#include "qros_subscriber.h"
#include <sensor_msgs/msg/temperature.hpp>
#include <QString>

QROS_NS_HEAD

class QRosTemperatureSubscriber : public QRosSubscriber{
  Q_OBJECT
public:
  Q_PROPERTY(double temperature READ getTemperature NOTIFY temperatureChanged)
  Q_PROPERTY(double variance READ getVariance NOTIFY varianceChanged)

public slots:
  double getTemperature() {
    return subscriber_.msgBuffer().temperature;
  }

  double getVariance() {
    return subscriber_.msgBuffer().variance;
  }

signals:
  void temperatureChanged();
  void varianceChanged();

protected:
  void onMsgReceived() override {
    emit temperatureChanged();
    emit varianceChanged();
  }

private:
  QRosSubscriberInterface* interfacePtr() { return &subscriber_; }
  QRosTypedSubscriber<sensor_msgs::msg::Temperature> subscriber_;
};

QROS_NS_FOOT
