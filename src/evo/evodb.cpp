// Copyright (c) 2018 The e4Coin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "evodb.h"

CEvoDB* evoDb;

CEvoDB::CEvoDB(size_t nCacheSize, bool fMemory, bool fWipe) :
    db(fMemory ? "" : (GetDataDir() / "evodb"), nCacheSize, fMemory, fWipe),
    dbTransaction(db)
{
}

bool CEvoDB::VerifyBestBlock(const uint256& hash)
{
    // Make sure evodb is consistent.
    // If we already have best block hash saved, the previous block should match it.
    uint256 hashBestBlock;
    bool fHasBestBlock = Read(EVODB_BEST_BLOCK, hashBestBlock);
    uint256 hashBlockIndex = fHasBestBlock ? hash : uint256();
    assert(hashBestBlock == hashBlockIndex);

    return fHasBestBlock;
}

void CEvoDB::WriteBestBlock(const uint256& hash)
{
    Write(EVODB_BEST_BLOCK, hash);
}