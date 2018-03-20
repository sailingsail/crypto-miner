#include "hwcomponent.h"

HwComponent::HwComponent(Company company, Type type) : _company(company), _type(type)
{
}

HwComponent::Company HwComponent::company() const
{
  return _company;
}

HwComponent::Type HwComponent::type() const
{
  return _type;
}

bool HwComponent::operator==(const HwComponent &other) const
{
  return other._company == _company && other._type == _type;
}

uint qHash(const HwComponent &key, uint seed /* 0 */)
{
  return qHash(static_cast<uchar>(key.company()), seed) ^ qHash(static_cast<uchar>(key.type()), seed);
}