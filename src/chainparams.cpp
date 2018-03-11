// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "checkpoints.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc1;
        pchMessageStart[1] = 0x63;
        pchMessageStart[2] = 0xaf;
        pchMessageStart[3] = 0xd6;
        vAlertPubKey = ParseHex("04e6fbf3bd55023679be17f0bab053cd9eb9fd13c016ed9a2f222989769417ed3a16f161528241bc9a2894ad5ebbbd551be1a4bd2d10cdb679228c91e26e26900e");
        nDefaultPort = 10549;
        nRPCPort = 10548;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		
        const char* pszTimestamp = "http://www.bbc.co.uk/news/world-us-canada-43345209"; //Trump-Kim talks show US strategy is working - VP Pence
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 4866437 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1520702940, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1520702940;
        genesis.nBits    = 0x1f00ffff; 
        genesis.nNonce   = 578372;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0xac4082edd509ca3bf8f880e3640bcf622a61a540b54f8cf83652e33f0bb17248"));
        assert(genesis.hashMerkleRoot == uint256("0xfb57b85b949889424e52b7f3c2d59d26017d41eb9f6a3d115abde05ad197e7c5"));

        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,15);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,39);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,95);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x44)(0x3A)(0xC7).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x44)(0x6E)(0x2F).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPOSStartBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa0;
        pchMessageStart[1] = 0x21;
        pchMessageStart[2] = 0x52;
        pchMessageStart[3] = 0xbc;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04e6fbf3bd55023679be17f0bab053cd9eb9fd13c016ed9a2f222989769417ed3a16f161528241bc9a2894ad5ebbbd551be1a4bd2d10cdb679228c91e26e26900e");
        nDefaultPort = 20549;
        nRPCPort = 20548;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 51214089; 
        genesis.nNonce = 95789;

        //assert(hashGenesisBlock == uint256(""));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,16);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,49);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x05)(0x55)(0xF4)(0x7C).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x05)(0x55)(0xB1)(0xB6).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nPOSStartBlock = 1;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
