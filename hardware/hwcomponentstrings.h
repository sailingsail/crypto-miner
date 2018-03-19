#ifndef HWCOMPONENTSTRINGS_H
#define HWCOMPONENTSTRINGS_H

#include <QtCore/QString>
#include "hardware.h"

namespace HwComponentStrings
{
  QString toString(const Hardware::Component &hwComponent);
};

#endif