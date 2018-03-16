#ifndef OPTIONS_H
#define OPTIONS_H

#include <MkCore/MSettings>
#include <MkCore/MLazySingleton>

class Options : public MSettings
{
  public:
    struct Property
    {
      static Q_DECL_CONSTEXPR QString Startup_MineOnStart;
    };

             Options();
    virtual ~Options() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

extern MLazySingleton<Options> gOptions;

#endif