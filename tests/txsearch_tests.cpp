
#include "../src/MicroCore.h"
#include "../src/CurrentBlockchainStatus.h"
#include "../src/ThreadRAII.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "helpers.h"
#include "mocks.h"

namespace
{

using json = nlohmann::json;



class OUTPUTIDENT_TEST : public ::testing::Test
{
public:

    static void
    SetUpTestCase()
    {
        string config_path {"../config/config.json"};
        config_json = xmreg::BlockchainSetup::read_config(config_path);
    }

protected:


    virtual void
    SetUp()
    {
        bc_setup = xmreg::BlockchainSetup{net_type, do_not_relay, config_json};
        cbs_mock = make_shared<MockCurrentBlockchainStatus>();
    }

     network_type net_type {network_type::TESTNET};
     bool do_not_relay {false};
     xmreg::BlockchainSetup bc_setup;

     std::shared_ptr<MockCurrentBlockchainStatus> cbs_mock;

     static json config_json;
};

json OUTPUTIDENT_TEST::config_json;


TEST_F(OUTPUTIDENT_TEST, DefaultConstruction)
{
    xmreg::OutputInputIdentification oi;

    EXPECT_TRUE(true);
}


string addr_9wq79 {"9wq792k9sxVZiLn66S3Qzv8QfmtcwkdXgM5cWGsXAPxoQeMQ79md51PLPCijvzk1iHbuHi91pws5B7iajTX9KTtJ4bh2tCh"};
string viewkey_9wq79 {"f747f4a4838027c9af80e6364a941b60c538e67e9ea198b6ec452b74c276de06"};

TEST_F(OUTPUTIDENT_TEST, NonDefaultConstruction)
{
    ADDR_VIEWKEY_FROM_STRING(addr_9wq79, viewkey_9wq79, net_type);

    transaction tx;
    crypto::hash tx_hash;
    bool is_coinbase {false};

    xmreg::OutputInputIdentification oi {&address, &viewkey, &tx,
                                         tx_hash, is_coinbase,
                                         cbs_mock};

    EXPECT_TRUE(true);
}

TEST_F(OUTPUTIDENT_TEST, IncomingPreRingctTransaction)
{
    // private testnet tx_hash 01e3d29a5b6b6e1999b9e7e48b9abe101bb93055b701b23d98513fb0646e7570
    string tx_hex {"0100020280e08d84ddcb0107041e6508060e1df9733757fb1563579b3a0ecefb4063dc66a75ad6bae3d0916ab862789c31f6aa0280e08d84ddcb01075f030f17031713f43315e59fbd6bacb3aa1a868edc33a0232f5031f6c573d6d7b23e752b6beee10580d0b8e1981a02e04e4d7d674381d16bf50bdc1581f75f7b2df591b7a40d73efd8f5b3c4be2a828088aca3cf02025c3fb06591f216cab833bb6deb2e173e0a9a138addf527eaff80912b8f4ff47280f882ad1602779945c0e6cbbc7def201e170a38bb9822109ddc01f330a5b00d12eb26b6fd4880e0bcefa757024f05eb53b5ebd60e502abd5a2fcb74b057b523acccd191df8076e27083ef619180c0caf384a302022dffb5574d937c1add2cf88bd374af40d577c7cc1a22c3c8805afd49840a60962101945fd9057dd42ef52164368eab1a5f430268e029f83815897d4f1e08b0e00873dbf5b4127be86ba01f23f021a40f29e29110f780fa0be36041ecf00b6c7b480edb090ba58dea640ca19aa4921a56c4b6dcbf11897c53db427dfdbc2f3072480b6c02f409b45c5d2401a19d8cfb13d9124d858d2774d9945f448f19e1e243e004588368813689c1c1be4e1242c633b7a2eb4936546fda57c99dac7fab81e40d0512e39d04ce285f96ac80f6d91ee39157189d73e198fa6b397bd34d8685dbf20e3f869043b686c291f8d4401f673978c683841ec39c45ce06564ccf87c68a080ad17bcce3d7240cd8d57ecbb190fef27578679cdd39ea3c868ab65d6d1d2c20062e921ceea054f755ceef8cd24e54078f9a5bedea2ca59d90ad277bd250c90605b3dd832aa15a4eb01080210ade74638f1558e203c644aa608147c9f596ce3c03023e99f9ca5b3cae41cbd230bc20f2b87f1e06967c852115abc7e56566ddaf09b5774568375fa0f27b45d946cfb2859f1c7a3ad6b7a8e097e955a6ee77c6db0b083dbda85b317dcd77e4be29079420bf683a91ac94feb0f788d5e3dfe72bef028768d76f9ebffd4cb2fd4a314e293df51cb43f12091632e93f4f97fdab7ab60dd50611233fbb1048dccd6478184b914710c894d8116620fcfd09d73ef304c90af210a4724c9e8adb2c47396a67944d6fe827a9b06f7a3c3b6cd2946f328cc306e0a0d194443734cc90fb94ccdb74f8fa7a19690793ddc2b0b06e52d0d4d8530ac227d58a2936fbbf18bbbc2af03443a44ff2a844be527371fedc03c50cce200e8e2b4fdb501e2fba103aafc2487be7faaa83f3894bdcfad873a6697ad930500bc56e28139ef4c6d9b8ee06390b4bcb1b6bfcc6e3136be89e3bdccff50d104906d354569aedfd8b2a5cb62b8738218760a9ebbc5dff3de038ab2e0369f28e3d0d921d28b388acdf69988b5c77120de5317be614da7c774f1f815a7137625da90f0342ca5df7bbc8515066c3d8fa37f1d69727f69e540ff66578bd0e6adf73fa074ce25809e47f06edc9d8ac9f49b4f02b8fd48ef8b03d7a6e823c6e2fc105ee0384a5a3a4bfefc41cf7240847e50121233de0083bbd904903b9879ecdd5a3b701a2196e13e438cf3980ab0b85c5e4e3595c46f034cb393b1e291e3e288678c90e9aac0abe0723520d47e94584ff65dfec8d4d1b1d2c378f87347f429a2178b10ad530bfe406441d7b21c1f0ea04920c9715434b16e6f5c561eab4e8b31040a30b280fc0e3ebc71d1d85a6711591487a50e4ca1362aae564c6e332b97da65c0c07"};

    // the tx has only one output for 10 xmr, so we check
    // if we can identify it.

    TX_FROM_HEX(tx_hex);
    ADDR_VIEWKEY_FROM_STRING(addr_9wq79, viewkey_9wq79, net_type);

    xmreg::OutputInputIdentification oi {&address, &viewkey, &tx,
                                         tx_hash, is_tx_coinbase,
                                         cbs_mock};
    oi.identify_outputs();

    EXPECT_EQ(oi.identified_outputs.size(), 1);
    EXPECT_EQ(oi.identified_inputs.size(), 0);
    EXPECT_EQ(oi.get_tx_hash_str(), tx_hash_str);
    EXPECT_EQ(oi.get_tx_prefix_hash_str(), tx_prefix_hash_str);
    EXPECT_EQ(oi.get_tx_pub_key_str(), tx_pub_key_str);
    EXPECT_EQ(oi.get_mixin_no(), 7);
    EXPECT_EQ(oi.total_received, 10000000000000ull);
    EXPECT_FALSE(oi.tx_is_coinbase);
    EXPECT_FALSE(oi.is_rct);

    auto out_info = oi.identified_outputs[0];

    EXPECT_EQ(pod_to_hex(out_info.pub_key),
              "2dffb5574d937c1add2cf88bd374af40d577c7cc1a22c3c8805afd49840a6096");

    EXPECT_EQ(out_info.amount, 10000000000000ull);
    EXPECT_EQ(out_info.idx_in_tx, 4);
    EXPECT_TRUE(out_info.rtc_outpk.empty());
    EXPECT_TRUE(out_info.rtc_mask.empty());
    EXPECT_TRUE(out_info.rtc_amount.empty());
}



// private testnet wallet 9wq792k9sxVZiLn66S3Qzv8QfmtcwkdXgM5cWGsXAPxoQeMQ79md51PLPCijvzk1iHbuHi91pws5B7iajTX9KTtJ4bh2tCh
// viewkey f747f4a4838027c9af80e6364a941b60c538e67e9ea198b6ec452b74c276de06
// spendkey 509a9761fde8856fc38e79ca705d85f979143524f178f8e2e0eb539fc050e905
// seed: deftly large tirade gumball android leech sidekick opened iguana voice gels focus poaching itches network espionage much jailed vaults winter oatmeal eleven science siren winter
string addr_9wq792k {"9wq792k9sxVZiLn66S3Qzv8QfmtcwkdXgM5cWGsXAPxoQeMQ79md51PLPCijvzk1iHbuHi91pws5B7iajTX9KTtJ4bh2tCh"};
string viewkey_9wq792k {"f747f4a4838027c9af80e6364a941b60c538e67e9ea198b6ec452b74c276de06"};

// ./xmr2csv --testnet -b /home/mwo/testnet/node_01/testnet/lmdb/ -a 9wq792k9sxVZiLn66S3Qzv8QfmtcwkdXgM5cWGsXAPxoQeMQ79md51PLPCijvzk1iHbuHi91pws5B7iajTX9KTtJ4bh2tCh -v f747f4a4838027c9af80e6364a941b60c538e67e9ea198b6ec452b74c276de06
string known_outputs_csv_9wq792k {"./res/outputs_testnet_9wq792k9.csv"};


TEST_F(OUTPUTIDENT_TEST, OutgingPreRingctTransaction)
{
    // private testnet tx_hash 0889658a54ddfaa61f62fdc0393adc498e1227195d413de45c5f0e0da3f5068d
    string tx_hex {"0100020280e08d84ddcb0107b902e401081b2c10418ba25b21dc2e9fd3d6d8dd69c14888ab0ed429f8cc86a7edba20bdd2bde61bab0280c0caf384a30207d10194012438201e78879c4ee5f780a4fcabc5ce20716080392fc4715db6334f956e210283beed920f0580c0caf384a302020ffede2e6e4a3d613f6ebcca9d3337d54c5b65f7095cc04faf6c9408206b463c80f882ad16021b48cdc46b84e348596f35a0fb4f0107da3a7e5f8b486be6a36fc90ff052117e80d0b8e1981a02e6de1aa8176921a8d5f8ef02a12004f5183f77a601c347f84e7be18c400572e18088aca3cf02022f061ade6afb847d57d29609255089b477d2c33c34d06e13ec5982d18eb785c580c0f9decfae010211c7792d1a8d8c23bbd0e2c4c79b28a711fa4d6ff64906013ddd2b8bca42a6d444022100000000000000000000000000000000000000000000006f70656e6d6f6e65726f0189bb4ab10d9ae0b84096fe0f4b95da56e3949b71c6eca5f284a4a02c83ed174675d6b1d2e529f5e4199bb738a47e7f50fc7acbf86a3908eb0c3023013ea9e808974dd6e0c0fe2c9853d316d63a35206628790b60997a22cefb9383762ba05a0fb11987072d29d76b172700ea6b9cb61ddbdea60372b35de748f9a7fc0d18f30a02b76e272c76446d828b6cef9a2df96f867792da27f08ca116dca121f73bcf09fe4fff1a1b8a099fffafefac87f10ecdaf02f48e0b903ced2d737bcb803f0c0525588ed99e71b21c35878ce0697990bf768bc35e0e6841bf1cf91c1fc116ee0a01343ec7e52ded6bdb89571b40590834d4c04715b4eb28102dad54b455dd6d03380e9eac3c058159e7fa4f5d3da30b3eda24c7e49a87e1523e5b478efdb8020fa03a4788d214a7ec64454366525ebf66ef8692a0db97a2ff96e1ad926e315105104c7ef19f59aff25265f54489f7e0fdde6205e6f62b4beb6b0d5a2a233a4807e5460bd83dfa3929b56bd84705cee12ce7bcaca09539bd128fc9e7513a3e63022297c65ef1ac04bb1807b85fa3ef38342aa8342ec33dfe4979a1590d372218034649bbb7975d6790e04105cef27a6337996896758f4fa6a962425fc802dd790114020c4f14efe604f00b8f829d6c82bd2c9719a60c39565944998d43f299070ab78325c8a20557e03dd2e50e516503d16bd436b5af949a978097e0ce347a700c13c5ce0d039ea7bfc7cc8e975c0710e74b6b0930ffd597eaf80c0fdc18711e0e6c8e1aed3c2bd4ff035df0745e69d30ec0dff351c0d780cda8873c010419d209c19d6fc4c366911170892c6e696709069e6469018ff2c61f5f42b283bd4c590a3e5f71f7934635c1e7cca1cbf0ec91517ce65673c1b6c6c961625537b2e93208db342fb9c2f246c6d636adf66bece8bae648be290140452d63c6d87fb3ff990c86725d7bc4968cac48f10d7b6a4d35b63e3040c42f6e76e7224fa308a042b10807cd36ffe28daca3e2a755645be3f588565f9ee79b19b7f8c572a872bb61fd08c9d6473dfe2a5ae4f100744ed91e2e8817ef417309c4d0f4a5023272b87b8b00c08ee85c037417b5241e6715db7b0e932ef7e08cba00914bf485a46690f0370016d3e2ca265accec86c295cd02c13d67fa6bcc1f51803d537eaef804bdeaef05316c79554916dc5afb6ac1581436a26ac5cd687d83b4ccbbfae8e230eac2aa0c2b87f2db0b70cea9ad4cf9cb3218c4aa37da05245bc401a1ea4afcdcd833d40fadc38c6d38bd75fe63a364a0bed1c9b6656b4f803b944e5947d1c398a9eed200"};

    TX_FROM_HEX(tx_hex);
    ADDR_VIEWKEY_FROM_STRING(addr_9wq792k, viewkey_9wq792k, net_type);


    // the ring members data from the above tx
    //
    // this hex is obtained using onion explorer runnign with --enbale-as-hex flag
    // it is hex, serializied representation of of map of key_images
    // with corresponding ring members output_data_t info structure
    // we do this so that we just mack all the calls, instead of
    // accessing real blockchain for this data.
    string ring_member_data_hex {"011673657269616c697a6174696f6e3a3a6172636869766500000000010200000001070001d102650102890102c10102e10102ff01027702000001070001a03730613039333763663136313063306466363332333864373363323235346163363039623031343565663335333436653034373331656534633166343336643830653031303030303030303030303030643230303030303030303030303030303136336464363832656339373763646461353935333164613366666137323939386136663838333761626164633633366161656463386265313962326437633701a03262306634636561663332353534613665386637306433383662613630343166613664316635346134326430363937663832663436393936396531346336303161313031303030303030303030303030363530313030303030303030303030303136336464363832656339373763646461353935333164613366666137323939386136663838333761626164633633366161656463386265313962326437633701a06137623538633963396133333837653637336464646232306433336632626566336131393239636261653434353338346336656361346361313934646237653263353031303030303030303030303030383930313030303030303030303030303136336464363832656339373763646461353935333164613366666137323939386136663838333761626164633633366161656463386265313962326437633701a03538336531303131363633313133326666383361633364636135393831656335393634626634386434663439366331333537343137653361366539646333333866643031303030303030303030303030633130313030303030303030303030303136336464363832656339373763646461353935333164613366666137323939386136663838333761626164633633366161656463386265313962326437633701a03866363363633930346637643033626131343565366638323039333334353064633332313661306365393537666135613234373139336463323434653063623630303030303030303030303030303030646630313030303030303030303030303136336464363832656339373763646461353935333164613366666137323939386136663838333761626164633633366161656463386265313962326437633701a03832653363626164653363333963323636386534666439303861383662663237376533366637316563326631663465386432636363306666646236363236393133393032303030303030303030303030666430313030303030303030303030303136336464363832656339373763646461353935333164613366666137323939386136663838333761626164633633366161656463386265313962326437633701a035366261663166393130653861316366326264396235313464386333313030633531393731303565383033643462306230636137616664383863643462353764623130323030303030303030303030303735303230303030303030303030303031363364643638326563393737636464613539353331646133666661373239393861366638383337616261646336333661616564633862653139623264376337010700023901021d02022502024002026c02027c0202bd0201070001a06236616662313139646231396538616266656636303062326431383135653332636238626236366130663566363532396434303931313534653163313330623037363031303030303030303030303030336130313030303030303030303030303539613033613331353361393934643732333237653464393234323164336533323931623166613162323430646534346239326437663632656330313238663101a03439346533303462643861376261626131343331633065633563383431623162346236333137626232353131663561636531393461343066653534323366646635613032303030303030303030303030316530323030303030303030303030303539613033613331353361393934643732333237653464393234323164336533323931623166613162323430646534346239326437663632656330313238663101a03732353739376634623939636163373736396362343264646532313434303731346138363362303036363739306431343937386634336138643261653431353436323032303030303030303030303030323630323030303030303030303030303539613033613331353361393934643732333237653464393234323164336533323931623166613162323430646534346239326437663632656330313238663101a03439383766656363333237663463646266323461343564386162366334323535623930303535623263633730323364386161656538626461633133303466343637643032303030303030303030303030343130323030303030303030303030303539613033613331353361393934643732333237653464393234323164336533323931623166613162323430646534346239326437663632656330313238663101a03565663938366461323138346133353333636531396163653365613735333138353363393631323765336534663336613638613139393562333162663037363561393032303030303030303030303030366430323030303030303030303030303539613033613331353361393934643732333237653464393234323164336533323931623166613162323430646534346239326437663632656330313238663101a06462343733353534326330626539376161653635613464646534353162613761396164653666613438393133303765313336393261633361336632373163356462393032303030303030303030303030376430323030303030303030303030303539613033613331353361393934643732333237653464393234323164336533323931623166613162323430646534346239326437663632656330313238663101a034313366633266643236663931333732333233323137366233393031376638643537636234396331643733666530616163303934666139633662343238613930666130323030303030303030303030306265303230303030303030303030303035396130336133313533613939346437323332376534643932343231643365333239316231666131623234306465343462393264376636326563303132386631"};

    MockGettingOutputs::ring_members_mock_map_t mock_ring_members_data;

    ASSERT_TRUE(xmreg::output_data_from_hex(ring_member_data_hex,
                                            mock_ring_members_data));

    MockGettingOutputs get_outputs(mock_ring_members_data);

    EXPECT_CALL(*cbs_mock, get_output_keys(_,_,_))
                 .WillRepeatedly(Invoke(&get_outputs,
                                         &MockGettingOutputs::get_output_keys));

    xmreg::OutputInputIdentification oi {&address, &viewkey, &tx,
                                         tx_hash, is_tx_coinbase,
                                         cbs_mock};

    xmreg::TxSearch::known_outputs_t known_outputs;

    if (!boost::filesystem::exists(known_outputs_csv_9wq792k))
        known_outputs_csv_9wq792k = "./tests/" + known_outputs_csv_9wq792k;

    ASSERT_TRUE(xmreg::populate_known_outputs_from_csv(
                known_outputs_csv_9wq792k, known_outputs));

    oi.identify_outputs();
    oi.identify_inputs(known_outputs);

    EXPECT_EQ(oi.identified_inputs.size(), 2);

    uint64_t found_input_amounts {0};

    for (auto& in_info: oi.identified_inputs)
        found_input_amounts += in_info.amount;

    EXPECT_EQ(found_input_amounts, 17000000000000ull);
}

TEST_F(OUTPUTIDENT_TEST, IncomingPreRingctCoinbaseTransaction)
{
    // private testnet tx_hash af9652cb7682d0b73d4ec588d3d17b5ebfe4773dbb69228fa716242a223fdec0
    string tx_hex {"01f20201ffb60206a4fa8cd60302225670b42320e616c5c7b801a09b4414456a608808b3f712378d90c4a0bd38cd80f882ad1602137972ff6725442bae4f92d6640e2a8036b1c5652afdbe5439789f3c584ef40b80c0fc82aa0202befb33d6df13977c325dc548022a401c37c024dbd88e244bc6825418f8994df78090cad2c60e02e1b0c0394f0652e13f471b422eeb092acb245d5fc679759ca66667ce179f478c80e08d84ddcb010292ed8812901ad9fac78390e008141ebad73a30af51178915de6e1586239a121980c0caf384a302028134f3543a21a2a78dbd2629e47601accd4f703e0b402f07213cffae2d592ab2210169aa02bef903707e96e7591cf9117879ce456b27d44cd0b70ef6d90636f040bd"};

    // the tx has six outputs for 10 xmr, so we check
    // if we can identify it.

    TX_FROM_HEX(tx_hex);
    ADDR_VIEWKEY_FROM_STRING(addr_9wq79, viewkey_9wq79, net_type);

    xmreg::OutputInputIdentification oi {&address, &viewkey, &tx,
                                         tx_hash, is_tx_coinbase,
                                         cbs_mock};
    oi.identify_outputs();

    EXPECT_EQ(oi.identified_outputs.size(), 6);
    EXPECT_EQ(oi.identified_inputs.size(), 0);
    EXPECT_EQ(oi.total_received, 17586985873700ull);
    EXPECT_TRUE(oi.tx_is_coinbase);

    EXPECT_EQ(pod_to_hex(oi.identified_outputs[0].pub_key),
              "225670b42320e616c5c7b801a09b4414456a608808b3f712378d90c4a0bd38cd");

    EXPECT_EQ(pod_to_hex(oi.identified_outputs.back().pub_key),
              "8134f3543a21a2a78dbd2629e47601accd4f703e0b402f07213cffae2d592ab2");
}




class TXSEARCH_TEST : public ::testing::TestWithParam<network_type>
{
public:

    static void
    SetUpTestCase()
    {
        string config_path {"../config/config.json"};
        config_json = xmreg::BlockchainSetup::read_config(config_path);
    }

protected:

    virtual void
    SetUp()
    {
        net_type = GetParam();

        bc_setup = xmreg::BlockchainSetup {
                net_type, do_not_relay, config_json};

        mcore = std::make_unique<MockMicroCore>();
        mcore_ptr = mcore.get();

        rpc = std::make_unique<MockRPCCalls>("dummy deamon url");
        rpc_ptr = rpc.get();

        bcs = std::make_unique<xmreg::CurrentBlockchainStatus>(
                    bc_setup, std::move(mcore), std::move(rpc));
    }

     network_type net_type {network_type::STAGENET};
     bool do_not_relay {false};
     xmreg::BlockchainSetup bc_setup;
     std::unique_ptr<MockMicroCore> mcore;
     std::unique_ptr<MockRPCCalls> rpc;
     std::unique_ptr<xmreg::CurrentBlockchainStatus> bcs;

     MockMicroCore* mcore_ptr;
     MockRPCCalls* rpc_ptr;

     static json config_json;
};

json TXSEARCH_TEST::config_json;



}