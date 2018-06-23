// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The DeiMos Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEIMOS_DEIMOSCONSENSUS_H
#define DEIMOS_DEIMOSCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_DEIMOS_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/deimos-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBDEIMOSCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define DEIMOSCONSENSUS_API_VER 1

typedef enum deimosconsensus_error_t
{
    deimosconsensus_ERR_OK = 0,
    deimosconsensus_ERR_TX_INDEX,
    deimosconsensus_ERR_TX_SIZE_MISMATCH,
    deimosconsensus_ERR_TX_DESERIALIZE,
    deimosconsensus_ERR_AMOUNT_REQUIRED,
    deimosconsensus_ERR_INVALID_FLAGS,
} deimosconsensus_error;

/** Script verification flags */
enum
{
    deimosconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    deimosconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    deimosconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    deimosconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    deimosconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    deimosconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    deimosconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    deimosconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = deimosconsensus_SCRIPT_FLAGS_VERIFY_P2SH | deimosconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               deimosconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | deimosconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               deimosconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | deimosconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int deimosconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, deimosconsensus_error* err);

EXPORT_SYMBOL int deimosconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, deimosconsensus_error* err);

EXPORT_SYMBOL unsigned int deimosconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // DEIMOS_DEIMOSCONSENSUS_H
