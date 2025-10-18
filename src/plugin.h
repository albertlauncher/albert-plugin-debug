// Copyright (c) 2025 Manuel Schneider
#pragma once
#include <albert/extensionplugin.h>
#include <albert/generatorqueryhandler.h>

class Plugin : public albert::ExtensionPlugin,
               public albert::GeneratorQueryHandler
{
    ALBERT_PLUGIN
public:

    Plugin();
    ~Plugin() override;

    bool allowTriggerRemap() const override;
    QString synopsis(const QString &) const override;
    albert::ItemGenerator items(albert::QueryContext &) override;
};
