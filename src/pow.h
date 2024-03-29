// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DeimOS Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEIMOS_POW_H
#define DEIMOS_POW_H

#include <consensus/params.h>

#include <stdint.h>

class CBlockHeader;
class CBlockIndex;
class uint256;

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int GetNextWorkRequiredv1(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int GetNextWorkRequiredv2(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int GetNextWorkRequiredv3(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int GetNextWorkRequiredv4(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params&);

/** Check whether a block hash satisfies the proof-of-work requirement specified by nBits */
bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params&);
const CBlockIndex* GetLastBlockIndexForAlgo(const CBlockIndex* pindex, const Consensus::Params&, int algo);
const CBlockIndex* GetAlgo();

#endif // DEIMOS_POW_H
