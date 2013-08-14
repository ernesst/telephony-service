/*
 * Copyright (C) 2012-2013 Canonical, Ltd.
 *
 * Authors:
 *  Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
 *
 * This file is part of telephony-service.
 *
 * telephony-service is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * telephony-service is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef APPLICATIONUTILS_H
#define APPLICATIONUTILS_H

#include <QObject>
#include <QDBusServiceWatcher>

class ApplicationUtils : public QObject
{
    Q_OBJECT
    Q_ENUMS(Application)
    Q_PROPERTY(bool addressbookAppRunning READ addressbookAppRunning NOTIFY addressbookAppRunningChanged)
    Q_PROPERTY(bool dialerAppRunning READ dialerAppRunning NOTIFY dialerAppRunningChanged)
    Q_PROPERTY(bool messagingAppRunning READ messagingAppRunning NOTIFY messagingAppRunningChanged)

public:
    static ApplicationUtils *instance();

    Q_INVOKABLE void switchToAddressbookApp(const QString &argument = QString::null);
    Q_INVOKABLE void switchToDialerApp(const QString &argument = QString::null);
    Q_INVOKABLE void switchToMessagingApp(const QString &argument = QString::null);

    bool addressbookAppRunning();
    bool dialerAppRunning();
    bool messagingAppRunning();

Q_SIGNALS:
    void addressbookAppRunningChanged(bool running);
    void dialerAppRunningChanged(bool running);
    void messagingAppRunningChanged(bool running);

protected:
    bool checkApplicationRunning(const QString &serviceName);

protected Q_SLOTS:
    void onServiceRegistered(const QString &serviceName);
    void onServiceUnregistered(const QString &serviceName);

private:
    explicit ApplicationUtils(QObject *parent = 0);

    QDBusServiceWatcher mApplicationWatcher;
    bool mAddressbookAppRunning;
    bool mDialerAppRunning;
    bool mMessagingAppRunning;

};

#endif // APPLICATIONUTILS_H