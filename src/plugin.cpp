// Copyright (c) 2023 Manuel Schneider

#include "plugin.h"
#include <albert/albert.h>
#include <albert/logging.h>
#include <albert/notification.h>
#include <albert/standarditem.h>
#include <chrono>
#include <thread>
ALBERT_LOGGING_CATEGORY("debug")
using namespace Qt::Literals;
using namespace albert;
using namespace std;
using namespace util;

static auto icon = {u"qsp:SP_MessageBoxWarning"_s};

Plugin::Plugin() { DEBG << "'Debug' created."; }

Plugin::~Plugin() { DEBG << "'Debug' destroyed."; }

QString Plugin::synopsis(const QString &) const { return u"debug-debug-debug"_s; }

bool Plugin::allowTriggerRemap() const { return false; }

void Plugin::handleTriggerQuery(Query &query)
{
    if (query.string() == u"busy"_s)
    {
        for(int i = 0; query.isValid() && i < 3; ++i)
        {
            for (int nap = 0; nap < 100; ++nap){
                if (!query.isValid())
                    return;
                this_thread::sleep_for(chrono::milliseconds(10));
            }
            query.add(StandardItem::make({},
                                         u"Item #%1"_s.arg(i),
                                         u"Wow, Item #%1"_s.arg(i),
                                         icon,
                                         {{u"Debug"_s, u"Open website"_s, []() { openWebsite(); }}}));
        }
        return;
    }

    if (u"notification"_s.startsWith(query.string()))
    {
        query.add(StandardItem::make({},
                                     u"Memleaking notification"_s,
                                     u"Leaks memory"_s,
                                     icon,
                                     {{u"Debug"_s, u"Open website"_s, [] {
                                           auto *n = new Notification;
                                           n->setTitle(u"Memory leak"_s);
                                           n->setText(u"Ok."_s);
                                           n->send();
                                       }}}));
    }

    if (u"busy"_s.startsWith(query.string()))
    {
        query.add(StandardItem::make({}, u"busy"_s, u"Test delayed queries"_s, u"busy"_s, icon, {}));
    }
}
