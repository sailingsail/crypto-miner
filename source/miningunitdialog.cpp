#include "miningunitdialog.h"

#include "../miners/minerinterface.h"
#include "walletoptions.h"

MiningUnitDialog::MiningUnitDialog(const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin coin, QWidget *parent) : MiningUnitDialog(MUuidPtr::createUuid(), minerPlugin, hwComponent, coin, parent)
{
  _ui.tabs->setCurrentIndex(static_cast<int>(Tab::Pool));
}

MiningUnitDialog::MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, QWidget *parent) : QDialog(parent), _options(id), _minerPlugin(minerPlugin), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets();
  setupSettings();
}

MiningUnitDialog::MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin coin, QWidget *parent) : QDialog(parent), _options(id), _minerPlugin(minerPlugin), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets(hwComponent, coin);
  setupSettings();
}

const MiningUnitOptions &MiningUnitDialog::options() const
{
  return _options;
}

void MiningUnitDialog::setupSettings()
{
  // parameters
  _widgetSettings.setWidget(MinerOptions::Property::Parameters_HwComponent, _ui.parameterHwComponent, &_options.miner());
  _widgetSettings.setWidget(MinerOptions::Property::Parameters_Coin,        _ui.parameterCoin,        &_options.miner());

  // pool
  _widgetSettings.setWidget(MiningUnitOptions::Property::Pool_Address,  _ui.poolAddress);
  _widgetSettings.setWidget(MiningUnitOptions::Property::Pool_Username, _ui.poolUsername);
  _widgetSettings.setWidget(MiningUnitOptions::Property::Pool_Password, _ui.poolPassword);

  // arguments
  _widgetSettings.setWidget(MinerOptions::Property::Arguments_AdditionalCommandLine, _ui.agumentsAdditionalCommandLine);

  _widgetSettings.load();
}

void MiningUnitDialog::setupWidgets() const
{
  _ui.name->setText(_minerPlugin->name());

  // parameters
  for (const auto &hwComponent : _minerPlugin->supportedHardware())
  {
    auto value = hwComponent.toString();
    _ui.parameterHwComponent->addItem(value, value);
  }
  for (auto coin : _minerPlugin->supportedCoins())
  {
    _ui.parameterCoin->addItem(coin.toString(), coin.toString(Coin::Part::Name));
  }
}

void MiningUnitDialog::setupWidgets(const HwComponent &hwComponent, Coin coin) const
{
  setupWidgets();

  // parameters
  auto value = hwComponent.toString();
  auto index = _ui.parameterHwComponent->findData(value);
  _ui.parameterHwComponent->setCurrentIndex(index);

  value = coin.toString(Coin::Part::Name);
  index = _ui.parameterCoin->findData(value);
  _ui.parameterCoin->setCurrentIndex(index);
}

void MiningUnitDialog::accept()
{
  _options.miner().setName(_minerPlugin->name());

  _widgetSettings.save();

  QDialog::accept();
}

void MiningUnitDialog::on_parameterCoin_currentIndexChanged(int index) const
{
  auto coin = Coin::fromString(_ui.parameterCoin->currentData().toString(), Coin::Part::Name);

  WalletOptions _walletOptions;

  _ui.walletAddress->setEnabled(!_walletOptions.address(coin).isEmpty());
}

void MiningUnitDialog::on_walletAddress_clicked(bool checked /* false */) const
{
  auto coin = Coin::fromString(_ui.parameterCoin->currentData().toString(), Coin::Part::Name);

  WalletOptions _walletOptions;

  _ui.poolUsername->setText(_walletOptions.address(coin));
}