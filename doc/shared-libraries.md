Shared Libraries
================

## deimosconsensus

The purpose of this library is to make the verification functionality that is critical to DeiMos's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `deimosconsensus.h` located in  `src/script/deimosconsensus.h`.

#### Version

`deimosconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`deimosconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `deimosconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `deimosconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `deimosconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/deimos/bips/blob/master/bip-0016.mediawiki)) subscripts
- `deimosconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/deimos/bips/blob/master/bip-0066.mediawiki)) compliance
- `deimosconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/deimos/bips/blob/master/bip-0147.mediawiki))
- `deimosconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/deimos/bips/blob/master/bip-0065.mediawiki))
- `deimosconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/deimos/bips/blob/master/bip-0112.mediawiki))
- `deimosconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/deimos/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `deimosconsensus_ERR_OK` - No errors with input parameters *(see the return value of `deimosconsensus_verify_script` for the verification status)*
- `deimosconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `deimosconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `deimosconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `deimosconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NDeiMos](https://github.com/NicolasDorier/NDeiMos/blob/master/NDeiMos/Script.cs#L814) (.NET Bindings)
- [node-libdeimosconsensus](https://github.com/bitpay/node-libdeimosconsensus) (Node.js Bindings)
- [java-libdeimosconsensus](https://github.com/dexX7/java-libdeimosconsensus) (Java Bindings)
- [deimosconsensus-php](https://github.com/Bit-Wasp/deimosconsensus-php) (PHP Bindings)
