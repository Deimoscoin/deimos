// Copyright (c) 2011-2014 The DeimOS Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEIMOS_QT_DEIMOSADDRESSVALIDATOR_H
#define DEIMOS_QT_DEIMOSADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class DeimOSAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DeimOSAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** DeimOS address widget validator, checks for a valid deimos address.
 */
class DeimOSAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DeimOSAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // DEIMOS_QT_DEIMOSADDRESSVALIDATOR_H
