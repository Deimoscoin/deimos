// Copyright (c) 2011-2014 The DeiMos Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEIMOS_QT_DEIMOSADDRESSVALIDATOR_H
#define DEIMOS_QT_DEIMOSADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class DeiMosAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DeiMosAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** DeiMos address widget validator, checks for a valid deimos address.
 */
class DeiMosAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DeiMosAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // DEIMOS_QT_DEIMOSADDRESSVALIDATOR_H
