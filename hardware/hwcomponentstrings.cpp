#include "hwcomponentstrings.h"

#include "hwcompanystrings.h"
#include "hwtypestrings.h"

namespace HwComponentStrings
{

QString toString(const Hardware::Component &hwComponent)
{
  QString value;

  static CompanyStrings companyStrings;
  static HardwareStrings hardwareStrings;

  if (hwComponent.company != Hardware::Company::Any)
  {
    value.append(companyStrings.toString(hwComponent.company));
    value.append(' ');
  }
  value.append(hardwareStrings.toString(hwComponent.type));

  return value;
}

}