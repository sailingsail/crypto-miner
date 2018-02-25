#include "miningunitoptions.h"

#include "miningunits.h"

Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Miner = "miner";

Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Pool_Address  = "pool/address";
Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Pool_Password = "pool/password";
Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Pool_Wallet   = "pool/wallet";

MiningUnitOptions::MiningUnitOptions(const MUuidPtr &id) : _id(id)
{
  beginGroup(MiningUnits::Property::Group);
  beginGroup(id.toString());
}

const MUuidPtr &MiningUnitOptions::id() const
{
  return _id;
}

QString MiningUnitOptions::miner() const
{
  return value(Property::Miner).toString();
}

QString MiningUnitOptions::poolAddress() const
{
  return value(Property::Pool_Address).toString();
}

QString MiningUnitOptions::poolPassword() const
{
  return value(Property::Pool_Password).toString();
}

QString MiningUnitOptions::poolWallet() const
{
  return value(Property::Pool_Wallet).toString();
}

void MiningUnitOptions::setMiner(const QString &name)
{
  setValue(Property::Miner, name);
}