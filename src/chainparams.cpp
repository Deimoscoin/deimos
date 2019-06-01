// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2018-2019 The DeimOS Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "arith_uint256.h"
#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = CScript() << ParseHex("12309afff1df5116212646d1b11821a1217ff6d165d91999f66677e0ef1f11dea777f6db1b7fde31c1f21504e11cf122ef1f311dd1af1b1c771d1d403f1cf17d1d") << OP_CHECKSIG;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "06/Feb/2018: SpaceX launch the Historic Falcon Heavy Rocket";
    const CScript genesisOutputScript = CScript() << ParseHex("12309afff1df5116212646d1b11821a1217ff6d165d91999f66677e0ef1f11dea777f6db1b7fde31c1f21504e11cf122ef1f311dd1af1b1c771d1d403f1cf17d1d") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        //consensus.nSubsidyHalvingInterval = 600000; - DEI
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x254ab08bacfe8f22c9c881acb97ce88d95d4a80c4ffe8e02d0799f4e5e9e5056");
        consensus.BIP65Height = 73078;
        consensus.BIP66Height = 73078;

        consensus.powLimit = ArithToUint256(~arith_uint256(0) >> 20);
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 60 / 1;

        consensus.nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
        consensus.nTargetSpacing = 60;
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nDiffChangeTarget = 0;
        consensus.patchBlockRewardDuration = 10080;
        consensus.patchBlockRewardDuration2 = 20160;
        consensus.nTargetTimespanRe = 1*60; // 60 Seconds
        consensus.nTargetSpacingRe = 1*60; // 60 seconds
        consensus.nIntervalRe = consensus.nTargetTimespanRe / consensus.nTargetSpacingRe; // 1 block

        consensus.nAveragingInterval = 10; // 10 blocks
        consensus.multiAlgoTargetSpacing = 30*5; // NUM_ALGOS * 30 seconds
        consensus.multiAlgoTargetSpacingV4 = 15*5; // NUM_ALGOS * 15 seconds
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacing; // 10* NUM_ALGOS * 30
        consensus.nAveragingTargetTimespanV4 = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacingV4; // 10 * NUM_ALGOS * 15

        consensus.nMaxAdjustDown = 40; // 40% adjustment down
        consensus.nMaxAdjustUp = 20; // 20% adjustment up
        consensus.nMaxAdjustDownV3 = 16; // 16% adjustment down
        consensus.nMaxAdjustUpV3 = 8; // 8% adjustment up
        consensus.nMaxAdjustDownV4 = 16;
        consensus.nMaxAdjustUpV4 = 8;

        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nMinActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUpV3) / 100;
        consensus.nMaxActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDownV3) / 100;
        consensus.nMinActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 - consensus.nMaxAdjustUpV4) / 100;
        consensus.nMaxActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 + consensus.nMaxAdjustDownV4) / 100;

        consensus.nLocalTargetAdjustment = 4;
        consensus.nLocalDifficultyAdjustment = 4;

        // DeimOS Hard Fork Block Heights
        consensus.multiAlgoDiffChangeTarget = 0;
        consensus.alwaysUpdateDiffChangeTarget = 0;
        consensus.workComputationChangeTarget = 0;
        consensus.DEIComputationRewardD = 333238;
	    consensus.DEIComputationRewardD2 = 393632;
	    consensus.DEIComputationRewardD3 = 1067702;

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 7056;
        consensus.nMinerConfirmationWindow = 10080;
        consensus.fRbfEnabled = false;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 27; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 12; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1489997089; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1521891345; // March 24th, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 13; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1490355345; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1521891345; // March 24th, 2018

        // Deployment of BIP65, BIP66, and BIP34.
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].bit = 14; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].nStartTime = 1489997089; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].nTimeout = 1521891345;    // March 24th, 2018

        // Reservation of version bits for future algos
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].bit = 12;
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nStartTime = 1542672000; // 20 Nov, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nTimeout = 1574208000;   // 20 Nov, 2019

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xd31be058fc5dfc617fe890737597e4060d2da4b6d30bdaeabbba5feeedfdefe1"); //320598

        pchMessageStart[0] = 0xdc;
        pchMessageStart[1] = 0xc8;
        pchMessageStart[2] = 0xcd;
        pchMessageStart[3] = 0xd2;
        nDefaultPort = 9150;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1519282800, 333390, 0x1e0ffff0, 1, 300);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x254ab08bacfe8f22c9c881acb97ce88d95d4a80c4ffe8e02d0799f4e5e9e5056"));
        assert(genesis.hashMerkleRoot == uint256S("0x6e186310739809c4c387facddfa7f19a086f5bc1548cacb114c16ed4b4285f89"));

        vSeeds.emplace_back("seed1.deimoscoin.org");
        vSeeds.emplace_back("seed2.deimoscoin.org");
        vSeeds.emplace_back("seed3.deimoscoin.org");
        vSeeds.emplace_back("deipool.xyz");
        vSeeds.emplace_back("deimos.network");
        vSeeds.emplace_back("deimoscoin.org");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,31);
        base58Prefixes[SCRIPT_ADDRESS_OLD] = std::vector<unsigned char>(1,5);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,33);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,138);
        base58Prefixes[SECRET_KEY_OLD] = std::vector<unsigned char>(1,158);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "dei";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
         {
      {      0, uint256S("0x254ab08bacfe8f22c9c881acb97ce88d95d4a80c4ffe8e02d0799f4e5e9e5056")},
      {    5000, uint256S("0x000000008a4601f422c89efbbffb060ff43a6e47b981ce601e8258f6949dca3a")},
      {   10000, uint256S("0x0000000066a0d050f191edb12fa732cdca578b1b2b09f539a24528f7aa0103cf")},
      {   15000, uint256S("0x5f81a9ba9272ea6d95c601986a3e18159b1d2397634728811214b706917522a9")},
      {   25000, uint256S("0xc7648369458fc473f116ea28f8bc881304174f91daa6e31a942f6d0c41ed43b1")},
      {   48000, uint256S("0x00000000511ae8d73c10ae279cd0633ab2809ac7e649a944c64999619f2d29a6")},
      {  120000, uint256S("0x0000010431a09d888b007def6d07408d00ed0d0631dcda50074c04904e772937")},
      {  150000, uint256S("0x74ad8b452a03670a2b1c1aa297dabed265461da08c5ad4844c64280db3ce19ba")},
      {  210000, uint256S("0x15679eec3a1259f934ac62711a9b5d062d3320f934b72c8387953babd4424160")},
      {  260000, uint256S("0x000000001ae170a745992589cec4394196b83f64c2a80d31b2b0bb10ffcddd37")},
      {  285000, uint256S("0xe9fc3a3969dc5e0c27d5b692678441d0aa41ac38116fc3e71a2d2cdff11dfb8a")},
      {  310000, uint256S("0xd6ba5edf7894f50944ca8c5b6b3bfb70d8d7ce5bc11024d6441afbe20ded5460")},
      {  320626, uint256S("0xb834fa7d076d4750c5b1ccc56e0587ad6460381ec6da90d05a79ed5d831a5c1b")},
      {  360000, uint256S("0xb16ac9b22e23fd2a150acd9b8a30474db8d4b3d94d6cd6b5dee22004f9b83fbf")},
      {  400100, uint256S("0x7fadc9637c0dce601903a99a7cbb2c11e1d9bbd387c3c8c1b0b064f8e871c57e")},
      {  416000, uint256S("0x5e2700253a3631dd30ba5822db33a67bcf8c744e2be581ed82d4c27bbfb46e2a")},
      {  426177, uint256S("0xf486d0eef3eac8b87e54a72847f95949de6f75ea6f23c9a5e3f2fcf165638fa3")},
      {  449050, uint256S("0x50580925a74ea87562ba906bd03fed5b104dd045cbe914f3a4330e258cea0d8b")},
      {  458000, uint256S("0xd6ed9d0e6563fad64901b64ed17c66d85daba0a23d846207e4c1bd5afd68826d")},
      {  478884, uint256S("0xa5ed9dc2b93a9e4e4508e721c359c9fe4148aaa45d6cc9b353fad56f49fd07f4")},
      {  620000, uint256S("0x95d93f7b2b66d34aaabd98303e79d18146b6f632fa415574de53aabad780ba20")},
      {  656200, uint256S("0x0000000000001851b47696b69b127f509cdb6e0e1ebbd1b7fc17b6712a6664ca")},
      {  780000, uint256S("0x01c8067af51386de085f2d3e20e9847b627dbba041ec7214056382291cc61f8f")},
      {  831544, uint256S("0xed27e7a4d8a295bb856c2f98932719a183efe64862ee996cfb956ea79f89bd54")},
      {  982000, uint256S("0x8fb0d003c6390feb93c303a4b18f8743a084d89023c61185ae067a86cccff757")},
      { 1000000, uint256S("0x0000000000001de44b292a038275beeeeb884e1f4033af29c422f5d3b581d1a6")},
      { 1120000, uint256S("0xf203e3db4002cbf2508d16dfd15f7418fbb92d838334526576904c1a4e07436f")},
      { 1250000, uint256S("0xa1e5ab390d1109552bcaccd608d233c6ca537092f96b44260fe44575d3d7c526")},
      { 1375000, uint256S("0x60a96cc82e91efb8760ff59104f412e324af3197d3ff3c837cc3e4952fc05acb")},
      { 1483000, uint256S("0xd60d0826117e20b5e6d6dfaf519e8676b22caa8df914434cc0e030e055613a5d")},
      { 1599000, uint256S("0x000000000000ed0542aa26974aad7c5ed47d4f30cd54b7d837b21dae8f50a024")},
      { 1634000, uint256S("0x3b28deb59c4e98ddc16d796a404303ecc0326d06d8344a7ff3f248ed54f1cba9")},
      { 1704000, uint256S("0x892bbe3370f2a7d382d14921ace09b32a366afabac9d74334b0d04c652152b79")},
         }
        };

        chainTxData = ChainTxData{
            1551047374, // * UNIX timestamp of last known number of transactions
            1765837,  // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.1         // * estimated number of transactions per second after that timestamp
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = false;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.powLimit = ArithToUint256(~arith_uint256(0) >> 20);
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 60 / 4;
        consensus.nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
        consensus.nTargetSpacing = 60; // 60 seconds
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nDiffChangeTarget = 67; // DigiShield Hard Fork Block BIP34Height 67,200
        // Old 1% monthly DEI Reward before 15 secon block change
        consensus.patchBlockRewardDuration = 10; //10080; - No longer used
        //4 blocks per min, x60 minutes x 24hours x 14 days = 80,160 blocks for 0.5% reduction in DEI reward supply - No longer used
        consensus.patchBlockRewardDuration2 = 80; //80160;
        consensus.nTargetTimespanRe = 1*60; // 60 Seconds
        consensus.nTargetSpacingRe = 1*60; // 60 seconds
        consensus.nIntervalRe = consensus.nTargetTimespanRe / consensus.nTargetSpacingRe; // 1 block

        consensus.nAveragingInterval = 10; // 10 blocks
        consensus.multiAlgoTargetSpacing = 30*5; // NUM_ALGOS * 30 seconds
        consensus.multiAlgoTargetSpacingV4 = 15*5; // NUM_ALGOS * 15 seconds
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacing; // 10* NUM_ALGOS * 30
        consensus.nAveragingTargetTimespanV4 = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacingV4; // 10 * NUM_ALGOS * 15

        consensus.nMaxAdjustDown = 40; // 40% adjustment down
        consensus.nMaxAdjustUp = 20; // 20% adjustment up
        consensus.nMaxAdjustDownV3 = 16; // 16% adjustment down
        consensus.nMaxAdjustUpV3 = 8; // 8% adjustment up
        consensus.nMaxAdjustDownV4 = 16;
        consensus.nMaxAdjustUpV4 = 8;

        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nMinActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUpV3) / 100;
        consensus.nMaxActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDownV3) / 100;
        consensus.nMinActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 - consensus.nMaxAdjustUpV4) / 100;
        consensus.nMaxActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 + consensus.nMaxAdjustDownV4) / 100;

        consensus.nLocalTargetAdjustment = 4; //target adjustment per algo
        consensus.nLocalDifficultyAdjustment = 4; //difficulty adjustment per algo


        // DeimOS Hard Fork Block Heights
        consensus.multiAlgoDiffChangeTarget = 145; // Block 145,000 MultiAlgo Hard Fork
        consensus.alwaysUpdateDiffChangeTarget = 400; // Block 400,000 MultiShield Hard Fork
        consensus.workComputationChangeTarget = 1430; // Block 1,430,000 DigiSpeed Hard Fork

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 28224; // 28224 - 70% of 40320
        consensus.nMinerConfirmationWindow = 40320; // nPowTargetTimespan / nPowTargetSpacing 40320 main net - 1 week
        consensus.fRbfEnabled = false;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 27; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 12; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1489997089; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1521891345; // March 24th, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 13; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1490355345; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1521891345; // March 24th, 2018

        // Deployment of BIP65, BIP66, and BIP34.
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].bit = 14; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].nStartTime = 1489997089; // March 24th, 2017 149

        // Reservation of version bits for future algos
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].bit = 12;
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xc3;
        pchMessageStart[1] = 0xb1;
        pchMessageStart[2] = 0xd7;
        pchMessageStart[3] = 0xcc;
        nDefaultPort = 19149;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1521476171, 448844, 0x1e0ffff0, 1, 300);
        consensus.hashGenesisBlock = genesis.GetHash();
        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet-seed.deimoscoin.org");
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "deit";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = {
            {
                {     0, uint256S("0x")},
            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 4096 0000000000000037a8cd3e06cd5edbfe9dd1dbcc5dacab279376ef7cfc2b4c75
            /* nTime    */ 1521476171,
            /* nTxCount */ 1,
            /* dTxRate  */ 0.09
        };

        /* enable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 60 / 4;
        consensus.nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
        consensus.nTargetSpacing = 60; // 60 seconds
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nDiffChangeTarget = 67; // DigiShield Hard Fork Block BIP34Height 67,200

        // Old 1% monthly DEI Reward before 15 secon block change
        consensus.patchBlockRewardDuration = 10; //10080; - No longer used
        //4 blocks per min, x60 minutes x 24hours x 14 days = 80,160 blocks for 0.5% reduction in DEI reward supply - No longer used
        consensus.patchBlockRewardDuration2 = 80; //80;
        consensus.nTargetTimespanRe = 1*60; // 60 Seconds
        consensus.nTargetSpacingRe = 1*60; // 60 seconds
        consensus.nIntervalRe = consensus.nTargetTimespanRe / consensus.nTargetSpacingRe; // 1 block

        consensus.nAveragingInterval = 10; // 10 blocks
        consensus.multiAlgoTargetSpacing = 30*5; // NUM_ALGOS * 30 seconds
        consensus.multiAlgoTargetSpacingV4 = 15*5; // NUM_ALGOS * 15 seconds
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacing; // 10* NUM_ALGOS * 30
        consensus.nAveragingTargetTimespanV4 = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacingV4; // 10 * NUM_ALGOS * 15

        consensus.nMaxAdjustDown = 40; // 40% adjustment down
        consensus.nMaxAdjustUp = 20; // 20% adjustment up
        consensus.nMaxAdjustDownV3 = 16; // 16% adjustment down
        consensus.nMaxAdjustUpV3 = 8; // 8% adjustment up
        consensus.nMaxAdjustDownV4 = 16;
        consensus.nMaxAdjustUpV4 = 8;

        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nMinActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUpV3) / 100;
        consensus.nMaxActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDownV3) / 100;
        consensus.nMinActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 - consensus.nMaxAdjustUpV4) / 100;
        consensus.nMaxActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 + consensus.nMaxAdjustDownV4) / 100;

        consensus.nLocalTargetAdjustment = 4; //target adjustment per algo
        consensus.nLocalDifficultyAdjustment = 4; //difficulty adjustment per algo


        // DeimOS Hard Fork Block Heights
        consensus.multiAlgoDiffChangeTarget = 145; // Block 145,000 MultiAlgo Hard Fork
        consensus.alwaysUpdateDiffChangeTarget = 400; // Block 400,000 MultiShield Hard Fork
        consensus.workComputationChangeTarget = 1430; // Block 1,430,000 DigiSpeed Hard Fork

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 19150;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1521473613, 1840542, 0x1e0ffff0, 1, 300);
        consensus.hashGenesisBlock = genesis.GetHash();
        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {
                {0, uint256S("0x")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "deirt";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
