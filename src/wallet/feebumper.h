// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DeimOS Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEIMOS_WALLET_FEEBUMPER_H
#define DEIMOS_WALLET_FEEBUMPER_H

#include <primitives/transaction.h>

class CWallet;
class CWalletTx;
class uint256;
class CCoinControl;
enum class FeeEstimateMode;

namespace feebumper {

enum class Result
{
    OK,
    INVALID_ADDRESS_OR_KEY,
    INVALID_REQUEST,
    INVALID_PARAMETER,
    WALLET_ERROR,
    MISC_ERROR,
};

//! Return whether transaction can be bumped.
bool TransactionCanBeBumped(const CWallet* wallet, const uint256& txid);

//! Create bumpfee transaction.
Result CreateTransaction(const CWallet* wallet,
                         const uint256& txid,
                         const CCoinControl& coin_control,
                         CAmount total_fee,
                         std::vector<std::string>& errors,
                         CAmount& old_fee,
                         CAmount& new_fee,
                         CMutableTransaction& mtx);

//! Sign the new transaction,
//! @return false if the tx couldn't be found or if it was
//! impossible to create the signature(s)
bool SignTransaction(CWallet* wallet, CMutableTransaction& mtx);

//! Commit the bumpfee transaction.
//! @return success in case of CWallet::CommitTransaction was successful,
//! but sets errors if the tx could not be added to the mempool (will try later)
//! or if the old transaction could not be marked as replaced.
Result CommitTransaction(CWallet* wallet,
                         const uint256& txid,
                         CMutableTransaction&& mtx,
                         std::vector<std::string>& errors,
                         uint256& bumped_txid);

} // namespace feebumper

#endif // DEIMOS_WALLET_FEEBUMPER_H
