/*
 * Copyright (C) 2012 Canonical, Ltd.
 *
 * Authors:
 *  Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
 *  Tiago Salem Herrmann <tiago.herrmann@canonical.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "callmanager.h"
#include "telepathyhelper.h"

#include <TelepathyQt/ContactManager>
#include <TelepathyQt/PendingContacts>

CallManager::CallManager(QObject *parent)
: QObject(parent)
{
}

bool CallManager::isChattingToContact(const QString &contactId)
{
    return mChannels.contains(contactId);
}

void CallManager::startCall(const QString &contactId)
{
    if (!mChannels.contains(contactId)) {
        // Request the contact to start audio call
        Tp::AccountPtr account = TelepathyHelper::instance()->account();
        connect(account->connection()->contactManager()->contactsForIdentifiers(QStringList() << contactId),
                SIGNAL(finished(Tp::PendingOperation*)),
                SLOT(onContactsAvailable(Tp::PendingOperation*)));
    }
}

void CallManager::endCall(const QString &contactId)
{
    if (!mChannels.contains(contactId))
        return;

    mChannels[contactId]->hangup();
    mChannels[contactId]->requestClose();
    mChannels.remove(contactId);
    mContacts.remove(contactId);
}

void CallManager::onCallChannelAvailable(Tp::CallChannelPtr channel)
{
    mChannels[channel->targetContact()->id()] = channel;

    channel->accept();
    emit callReady(channel->targetContact()->id());
}

void CallManager::onContactsAvailable(Tp::PendingOperation *op)
{
    Tp::PendingContacts *pc = qobject_cast<Tp::PendingContacts*>(op);

    if (!pc) {
        qCritical() << "The pending object is not a Tp::PendingContacts";
        return;
    }

    Tp::AccountPtr account = TelepathyHelper::instance()->account();

    // start call to the contacts
    Q_FOREACH(Tp::ContactPtr contact, pc->contacts()) {
        account->ensureAudioCall(contact, QLatin1String("audio"), QDateTime::currentDateTime(), "org.freedesktop.Telepathy.Client.TelephonyApp");

        // hold the ContactPtr to make sure its refcounting stays bigger than 0
        mContacts[contact->id()] = contact;
    }
}
