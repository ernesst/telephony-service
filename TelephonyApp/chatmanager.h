/*
 * Copyright (C) 2012 Canonical, Ltd.
 *
 * Authors:
 *  Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
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

#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <TelepathyQt/TextChannel>
#include <TelepathyQt/ReceivedMessage>

class ChatManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString activeChat READ activeChat WRITE setActiveChat NOTIFY activeChatChanged)
    Q_PROPERTY(int unreadMessagesCount READ unreadMessagesCount NOTIFY unreadMessagesChanged)
public:
    static ChatManager *instance();

    Q_INVOKABLE bool isChattingToContact(const QString &phoneNumber);
    Q_INVOKABLE void startChat(const QString &phoneNumber);
    Q_INVOKABLE void endChat(const QString &phoneNumber);
    Q_INVOKABLE void sendMessage(const QString &phoneNumber, const QString &message);
    Q_INVOKABLE void acknowledgeMessages(const QString &phoneNumber);

    QString activeChat() const;
    void setActiveChat(const QString &value);

    int unreadMessagesCount() const;
    int unreadMessages(const QString &phoneNumber);

signals:
    void chatReady(const QString &phoneNumber);
    void messageReceived(const QString &phoneNumber, const QString &message, const QDateTime &timestamp);
    void messageSent(const QString &phoneNumber, const QString &message);
    void activeChatChanged();
    void unreadMessagesChanged(const QString &phoneNumber);

public Q_SLOTS:
    void onTextChannelAvailable(Tp::TextChannelPtr channel);
    void onContactsAvailable(Tp::PendingOperation *op);
    void onMessageReceived(const Tp::ReceivedMessage &message);
    void onPendingMessageRemoved(const Tp::ReceivedMessage &message);

protected:
    Tp::TextChannelPtr existingChat(const QString &phoneNumber);


private:
    explicit ChatManager(QObject *parent = 0);

    QMap<QString, Tp::TextChannelPtr> mChannels;
    QMap<QString, Tp::ContactPtr> mContacts;
    QString mActiveChat;
};

#endif // CHATMANAGER_H
