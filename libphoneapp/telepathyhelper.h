/*
 * Copyright (C) 2012 Canonical, Ltd.
 *
 * Authors:
 *  Tiago Salem Herrmann <tiago.herrmann@canonical.com>
 *  Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
 *
 * This file is part of phone-app.
 *
 * phone-app is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * phone-app is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TELEPATHYHELPER_H
#define TELEPATHYHELPER_H

#include <QObject>
#include <TelepathyQt/AccountManager>
#include <TelepathyQt/Contact>
#include <TelepathyQt/Connection>
#include <TelepathyQt/ConnectionManager>
#include <TelepathyQt/Types>
#include "channelobserver.h"

class TelepathyHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    ~TelepathyHelper();

    static TelepathyHelper *instance();
    Tp::AccountPtr account() const;
    ChannelObserver *channelObserver() const;

    bool connected() const;

    void registerClient(Tp::AbstractClient *client, QString name);

Q_SIGNALS:
    void channelObserverCreated(ChannelObserver *observer);
    void accountReady();
    void connectionChanged();
    void connectedChanged();

public Q_SLOTS:
    void initializeTelepathyClients();
    void registerClients(void);

protected:
    QStringList supportedProtocols() const;
    void initializeAccount();
    void ensureAccountEnabled();
    void ensureAccountConnected();
    void watchSelfContactPresence();

private Q_SLOTS:
    void onAccountManagerReady(Tp::PendingOperation *op);
    void onAccountEnabled(Tp::PendingOperation *op);
    void onAccountStateChanged(bool enabled);
    void onAccountConnectionChanged(const Tp::ConnectionPtr &connection);
    void onPresenceChanged(const Tp::Presence &presence);

private:
    explicit TelepathyHelper(QObject *parent = 0);
    Tp::AccountManagerPtr mAccountManager;
    Tp::Features mAccountManagerFeatures;
    Tp::Features mAccountFeatures;
    Tp::Features mContactFeatures;
    Tp::Features mConnectionFeatures;
    Tp::ClientRegistrarPtr mClientRegistrar;
    Tp::AccountPtr mAccount;
    ChannelObserver *mChannelObserver;
    bool mFirstTime;
    bool mConnected;
};

#endif // TELEPATHYHELPER_H
