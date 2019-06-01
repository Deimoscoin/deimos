// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2018-2019 The DeimOS Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEIMOS_SHUTDOWN_H
#define DEIMOS_SHUTDOWN_H

void StartShutdown();
void AbortShutdown();
bool ShutdownRequested();

#endif
