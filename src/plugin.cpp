// Copyright (c) 2025 Manuel Schneider

#include "plugin.h"
#include <albert/app.h>
#include <albert/iconutil.h>
#include <albert/logging.h>
#include <albert/notification.h>
#include <albert/standarditem.h>
#include <QCoroGenerator>
#include <chrono>
#include <thread>
ALBERT_LOGGING_CATEGORY("debug")
using namespace Qt::StringLiterals;
using namespace albert;
using namespace std;


Plugin::Plugin() { DEBG << "'Debug' created."; }

Plugin::~Plugin() { DEBG << "'Debug' destroyed."; }

QString Plugin::synopsis(const QString &) const { return u"debug-debug-debug"_s; }

bool Plugin::allowTriggerRemap() const { return false; }

static auto makeIcon() { return makeStandardIcon(MessageBoxWarning); }

ItemGenerator Plugin::items(albert::QueryContext &ctx)
{
    if (ctx.query() == u"busy"_s)
    {
        for(int i = 0; ctx.isValid() && i < 3; ++i)
        {
            for (int nap = 0; nap < 100; ++nap){
                if (!ctx.isValid())
                    co_return;
                this_thread::sleep_for(chrono::milliseconds(10));
            }
            co_yield {StandardItem::make(u"debug"_s,
                                         u"Item #%1"_s.arg(i),
                                         u"Wow, Item #%1"_s.arg(i),
                                         makeIcon)};
        }
        co_return;
    }

    if (u"notification"_s.startsWith(ctx.query()))
    {
        co_yield {StandardItem::make(u"debug"_s,
                                     u"Memleaking notification"_s,
                                     u"Leaks memory"_s,
                                     makeIcon,
                                     {{u"Debug"_s, u"Open website"_s, [] {
                                           auto *n = new Notification;
                                           n->setTitle(u"Memory leak"_s);
                                           n->setText(u"Ok."_s);
                                           n->send();
                                       }}})};
    }

    if (u"busy"_s.startsWith(ctx.query()))
    {
        co_yield {StandardItem::make(u"debug"_s,
                                     u"busy"_s,
                                     u"Test delayed queries"_s,
                                     makeIcon)};
    }
}
