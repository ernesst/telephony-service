/*
 * Copyright 2012 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

.pragma library

function areSameDay(date1, date2) {
    return date1.getFullYear() == date2.getFullYear()
        && date1.getMonth() == date2.getMonth()
        && date1.getDate() == date2.getDate()
}

function formatLogDate(timestamp) {
    var today = new Date()
    var date = new Date(timestamp)
    if (areSameDay(today, date)) {
        return Qt.formatTime(timestamp, Qt.DefaultLocaleShortDate)
    } else {
        return Qt.formatDateTime(timestamp, Qt.DefaultLocaleShortDate)
    }
}

function friendlyDay(date) {
    var today = new Date();
    var yesterday = new Date();
    yesterday.setDate(today.getDate()-1);
    if (areSameDay(today, date)) {
        return "Today";
    } else if (areSameDay(yesterday, date)) {
        return "Yesterday";
    } else {
        return Qt.formatDate(date, Qt.DefaultLocaleShortDate);
    }
}

function formatFriendlyDate(timestamp) {
    var date = new Date(timestamp);
    return Qt.formatTime(timestamp, Qt.DefaultLocaleShortDate) + " - " + friendlyDay(date);
}
