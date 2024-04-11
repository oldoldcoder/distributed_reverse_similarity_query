#include "she.h"
SHE_key KEY;
void bn_printfHex(BIGNUM *num)
{
    // 发现如果字符串长度超过八千多个的话，就不能全部输出了，所以得进行字符串的截取
    char *tmp = BN_bn2hex(num);
    int cut_length = 6000;
    char *tmp_part1 = (char *)malloc(sizeof(char) * cut_length + 1);
    char *tmp_part2 = (char *)malloc(sizeof(char) * cut_length + 1);
    memset(tmp_part1, 0, cut_length + 1); // 这说明置0的重要性，如果最后一个字符不是斜杠0,打印会有问题，同时上面记得加1.
    memset(tmp_part2, 0, cut_length + 1);
    int len = strlen(tmp);
    // printf("长度为:%d\n", len);
    if (len > cut_length)
    {
        strncpy(tmp_part1, tmp, cut_length);
        strncpy(tmp_part2, tmp + cut_length, len - cut_length);
        // printf("第一部分:\n%s\n", tmp_part1);
        // printf("第二部分:\n%s\n", tmp_part2);
        printf("%s", tmp_part1);
        printf("%s\n", tmp_part2);
    }
    else
    {
        printf("%s\n", tmp);
    }
    free(tmp_part1);
    free(tmp_part2);
    OPENSSL_free(tmp);
}

void bn_printfDec(BIGNUM *num)
{
    // char *tmp = BN_bn2dec(num);
    // printf("%s\n", tmp);
    // OPENSSL_free(tmp);

    // 发现如果字符串长度超过八千多个的话，就不能全部输出了，所以得进行字符串的截取
    char *tmp = BN_bn2dec(num);
    int cut_length = 6000;
    char *tmp_part1 = (char *)malloc(sizeof(char) * cut_length + 1);
    char *tmp_part2 = (char *)malloc(sizeof(char) * cut_length + 1);
    memset(tmp_part1, 0, cut_length + 1); // 这说明置0的重要性，如果最后一个字符不是斜杠0,打印会有问题，同时上面记得加1.
    memset(tmp_part2, 0, cut_length + 1);
    int len = strlen(tmp);
    // printf("长度为:%d\n",len);
    if (len > cut_length)
    {
        strncpy(tmp_part1, tmp, cut_length);
        strncpy(tmp_part2, tmp + cut_length, len - cut_length);
        // printf("第一部分:\n%s\n", tmp_part1);
        // printf("第二部分:\n%s\n", tmp_part2);
        printf("%s", tmp_part1);
        printf("%s\n", tmp_part2);
    }
    else
    {
        printf("%s\n", tmp);
    }
    free(tmp_part1);
    free(tmp_part2);
    OPENSSL_free(tmp);
}
// 0失败1成功
int she_generateRandomKeys(SHE_key *key, int k0, int k1, int k2, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *p, *q, *l, *n, *e_negative1, *negative1, *l_2, *two_big;
    char *str_p, *str_q, *str_l, *str_n;
    BN_CTX_start(ctx);

    negative1 = BN_CTX_get(ctx);
    two_big = BN_CTX_get(ctx);
    p = BN_new();
    q = BN_new();
    l = BN_new();
    n = BN_new();
    l_2 = BN_new();
    e_negative1 = BN_new();

    // // 1. Choose two large prime numbers and a random number l
    do
    {
        if (!BN_generate_prime_ex(p, k0, 0, NULL, NULL, NULL))
            goto end;
        if (!BN_generate_prime_ex(q, k0, 0, NULL, NULL, NULL))
            goto end;
        if (!BN_rand(l, k2, 0, 0))
            goto end;
    } while (BN_cmp(p, q) == 0 || BN_is_zero(l));

    if (!BN_mul(n, p, q, ctx))
        goto end;

    str_p = "F2462229AAF6786BF2BAA3CF941878D000C847AE3E06BC6AAEFCA307D4F009BBA8EED18F2F1ED5B9801B4B033F90CACAEFCF29C893E4E69B7551A0731622482B9698401ECAF7D8D6D7CC232A7C0DE347F2E250E4DAE43C0B09C21CA27DB03752923160D9D5758B0B9D20041488244E6358AA1AC0F52E278E442FC5D2EA22E36F0CBF788356877393BF3E4E879DC9787546751AE47B0ABC998BDCBDD5602CDD4EC12AC97798C9187235CB7E1E99DE6A4BA273CDEFC08D8B75AC5A86C5CEA7445B1BC09ED26F722887440ED03A8D0F32BD256498458B907367916B2DEC39E044E302A61DDE08D065155C25B5CD9BA0EF40C5BAC169222DD94A60C5D3DAD8043ED1";
    str_q = "CEBE976B2CA11995E9E37609BDC2C5173208AE3552FA94337B1EBE00365AB8D5A977443FCD75E55B170578B643041814B752D92242CBFFFA5369A2657695FF0976BA6F5D21D708CA8189F36BD1E8F5E11884391309D758BF4AE9DAA40E5B7DAF29886519D21BE84A7DBA904E4DA14080C9361558B7FCD3C200D09E76BC13B710D9BFBED30DC1B2B3FC5E136C7DEF0EAAE1D3EF403FCAA7A2C8E5AA6985146CE66D26FDEA248254567B99044387F906EB51793BCBED77B2E6F3A3F734DB679F7835137D12C11A7C4BD3563C8D17987040C2DD2FEBA87534F3A9FDC7EB31C61E2DFCEAC4F93E914DE7ED384E45E21232E241FC866C2422F1EA147CCFAED27C54F9";
    str_l = "0ACCD95EFBEE9E193D16A73D32FC11EEF8C104F1EA2A7C58CD1A72E8ACCB175C470F1D828141";
    str_n = "C3A8CED7AE32974772944645C8094FDFCCAC8D2640EAE0441E45887491EB84168E3B0DD7BF6DB3C930FD2CD47F1D4D93A6F133A62A1CD87B429B96ED5BE955893D568E7ECF3D973932BF2CE27C3550C60A671F8BA33E17773EE42E96B098E410C925506091AAE64FD0A4A6A30B4F8ACAEC5A6EF03C965E5D9D402E147CBCFF6FA2F02B982A22B72E18DD43905D57369F3D37D4914CDB6572950DF38AA7B60794DED9F2071E2D66D5F9FB979FE66FD9AD018DE377EA0841F10A2A8A0D88A717797BCFE34CE538CDD8AB5814952C1C98CFD5A87A233A0682BA8BBFB7C2AE0C2AF058A9C74A7DD60198A9B07ACF3F4997A20D1474923812E51A70BDC14BAE211E6AE653C9D08ED96DF237082639681CE5AB7F7619C48D481BD7A6EE92E1E49F9C63CEDC5C5823AA3E7EDF9D28D7411F4CACE74EA1AB74B34379F73F519720A954DDB3F34C8797919EC5738E890C39EB0CEEDA97B456D65967F9737EF9D961991DDBB9A77917A25F0D5731AC932988983D9B9DDB7C0C478B9EF437442751D94059FA48030A9865DD3ECAD74ADB52E7C1A011EBC369B3573356EEB40CE0B77FAA50385AE1A86251391AA20B892C626C6176DD595EED1ACD41C37ABCD0E0515B815284123FEDE3991E27BD9E59D3E23ED3F5E293F476AC951732E6CDCEC658F4C286A2D061CE4759891785B6CA36B32AD2C676C0A3CD122FB8FF20300CAD615FF9AD49";

    BN_hex2bn(&p, str_p);
    BN_hex2bn(&q, str_q);
    BN_hex2bn(&l, str_l);
    BN_hex2bn(&n, str_n);

    BN_set_word(two_big, 2);
    if (!BN_div(l_2, NULL, l, two_big, ctx))
        goto end;

    key->p = p;
    key->q = q;
    key->l = l;
    key->n = n;
    key->l_2 = l_2;

    printf("p,q,l,n,en_neg1\n");
    bn_printfHex(p);
    bn_printfHex(q);
    bn_printfHex(l);
    bn_printfHex(n);

    BN_hex2bn(&negative1, "-1");
    if (!she_encryptBignumRaw(e_negative1, negative1, key, ctx))
        goto end;
    key->e_negative1 = e_negative1;

    bn_printfHex(e_negative1);
    ret = 1;
end:
    if (!ret)
    {
        printf("error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

// 0失败1成功
int she_encryptBignumRaw2(BIGNUM *c, const BIGNUM *m, const SHE_key *key, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX_start(ctx);

    BIGNUM *r = BN_CTX_get(ctx);
    BIGNUM *r_ = BN_CTX_get(ctx);
    // BIGNUM *n = BN_CTX_get(ctx);
    BIGNUM *tmp1 = BN_CTX_get(ctx);
    BIGNUM *tmp2 = BN_CTX_get(ctx);

    do
    {
        if (!BN_rand(r, R_BITS, 0, 0))
            goto end;
    } while (BN_is_zero(r));

    do
    {
        if (!BN_rand(r_, Q_BITS, 0, 0))
            goto end;
    } while (BN_is_zero(r_));

    // if (!BN_mul(n, key->p, key->q, ctx))
    //     goto end;
    if (!BN_mul(tmp1, r, key->l, ctx))
        goto end;
    if (!BN_add(tmp1, tmp1, m)) // rl+m不可能比n大
        goto end;
    if (!BN_mod_mul(tmp2, r_, key->p, key->n, ctx))
        goto end;
    if (!BN_add_word(tmp2, 1))
        goto end;
    if (!BN_mod_mul(c, tmp1, tmp2, key->n, ctx))
        goto end;

    ret = 1;
end:
    if (!ret)
    {
        printf("error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

// 0失败1成功
int she_generateRandomKeys2(SHE_key *key, int k_l, int k_p, int k_q, BN_CTX *ctx)
{
    int ret = 0;
    int i;
    int increment = 100;
    BIGNUM *p, *q, *l, *n, *e_negative1, *negative1, *l_2, *two_big, *tmp;
    char *str_p, *str_q, *str_l, *str_n;
    BN_CTX_start(ctx);

    negative1 = BN_CTX_get(ctx);
    two_big = BN_CTX_get(ctx);
    tmp = BN_CTX_get(ctx);
    p = BN_new();
    q = BN_new();
    l = BN_new();
    n = BN_new();
    l_2 = BN_new();
    e_negative1 = BN_new();

    BN_one(q);
    // // 1. Choose two large prime numbers and a random number l
    do
    {
        if (!BN_generate_prime_ex(p, k_p, 0, NULL, NULL, NULL))
            goto end;

        for (i = 0; i < k_q; i = i + increment)
        {
            if (!BN_generate_prime_ex(tmp, increment, 0, NULL, NULL, NULL))
                goto end;
            BN_mul(q, q, tmp, ctx);
        }
        if (!BN_rand(l, k_l, 0, 0))
            goto end;
    } while (BN_is_zero(l));

    if (!BN_mul(n, p, q, ctx))
        goto end;

    str_p = "D7C676804A499CBA70ED2D3C3AC03B2B9E7AE3476AAFE60F07CAC90632965E16D8419BDC72530733202FED08B9C9AE05A52C9545F09D85F81E05A3DCFF8EA65509976676693790C51571DAFFD3CD7068BC419CD86A6D6562FF732C2CFD87E2186A727A6A8EFCE8EEAE339599A8B5AE93DC8C1CC4224BCD28DFFA6A13AB7076B3";
    str_q = "06118E45DD99590C141410686DB7084F40A2213A1C68DA2210BC2C165EBB1D9B1B6CA0CDE75523C7E1046C48000033F969C1DB9F01562784F069BCC2D8252016AD7AB810A2E6C452445F7CF7838B10CE5F839D1085C9C59277CB28973AB277604B803B28A0BEBD196D4B44020120D3197F9B1044D438AFBAC10B1674C055AB390C936CC5CF83C8A2BCDE606954628DC06D9E635BCDFC1033085ABA33E26C3C00AF83446963D50266227CD946570558318CB5288D2271BAA3B73EBEF420E093EB50AC62E05674CA612A5A2A9A7CA8FB74749402A3CBBDA55C7316C55269CBA7F61FD26FE52CF6CD659363B17EDF5CDBB9A8FD1CA9698546360406D8768A158213FB3DF7B65710A61271A5C1EDF6AC353B21D373CA6B91CC4227A1C37D371A4D5205EBC570BAF3C1A6582C4D34414D182E36FAE80B6351B57DF3E661E0A18A0050076793A7A66D08AC3CB8B8AC27BA71F70E94B2530A16AC13F7D494A00E1AF14B6EC747BC66FAAF2FB4C1B05D8A1187C018F87869EE83A2E0C6248CEA55BDE68ADD6ADB2046D3DD6CFD1DFBCE4B4B5389531F2AB54398EAC375C1D25B4C21142F91CE06492081571C4C9670E05CD6F45DC96F0BD950D15A61A6ACA34617AAAAA4B03C30B2831AF5075E6CA64A7C173DF1717EDFA69EDF8AC707711497859F62D974F484F515059FEC53077687EC48BCFA3D57BE8682C9A43FE080786C80C658055CFA5EA57ADB254ECF22410D6FD060DC8D08F142428EC14D88D8D85BEF067262697D5F09BC469C7CC618DDD40C5F5B7B0AC8D2EFB90B6A7180A56C604E84DA7CBD722197C2462B9A763EE74B54BB024D333745EA2E0B44A27B0919AF80F91B64B8CDCC3B89097D3282EC10B18E4023C8662113DD7869674CD8003E87BBEDC3A603CED38F1B13EFA50BF0C86962429D28509F43D81610E7E2520B3CE233F503E71923561D26A54D21C08CB5702C45DB05575AB251A44E622E389C0AE12E425AF2AF709E4C5A998BEE1D9C72B6B0F42DCC5486F867E497C4EA15117DD7FBACF32B67209D867C3B603D1143FCE69E99FD10483E93EED9376B6AA26D411BF14B88782836A97435857DB6830AE42719EB4537FD5F5160CDE1512A0B7B628B240D1F11514F4D24286645B9C94493428BA0BF4C0042B8597A4077F97E20B52424F5384C550FE4EBB6239AFDFA2336D65A9CF866F01E391806A37786216DFAEA1AA4A922E0B71C3B5C0BC2A53B15FCE906025F18A5AC8B121F1CA5E6F6D6E0FD05097A9B1789E6EB57FC9098271DEBDC4BCC6E2785A4D3198FAA67E5958ECF2F6316A752F3D53B04C79EC7414A042AA5D113675FEA3997C7A913A230C9F7CDDDC8C5D520C4923E74AA4C69BD590F204CA507523588254FF3A87DA4A66B63A02ED947BC05064DD203B40E92302F0B2F716973A1F1565C213DB901E662E2B9AC3CC60A64A2DBF7F79E12A54F8C988FA282721BBEEF55795D51D060319BCBEAAC43EA11643C383BC40B9B42F89511A415246A36B99B68FA33C2E027A717939D3DDB55E17512EA976F5DB974899F0BF5169812602DDA4EF5FDEF4AD6579471CA73AF7CDC7C61698AB11D7A36DEEAAC9661E02B71CD2AD82D7ABFF34F85E388F76E3D2E2176A28D492C184A8D161B2E3CE76729006BB65E795D142D1822EAB897B2B70B8CE92EBC1EE57EF78837638A9B6B0FAD8F21AB75BE8A8CDF1E6FADF57235B3D3F334AC0061E63C5CC57FA8CBE53B251203459899664BBCD77054146E85CA16E82846D2ADCC20C9641AA2BE5225EA42311F11177A2B387B5AADF44E9B2D8B3B6E3EB06FF6EFD69867109548FCA8EE5711AAE4D5FD3661C4172D865BF6C3F979C48FFD4BE8944CFB7DB821D5BA8C5478AE4EA647739C40060E970854A6305C59D3FFB01A2647A2DDE397CA7454A4742A7B926087E9E7DC5911B98503140A12EC1DDC6BE25CD27D6ABC94639589EFEA0D0499FD66DA9712FF3717C71DED0132E8F69772C8AD50690DC39A9AC4D40BE82D6F477788B2E3941D697520B96A10BEE791D530E701E3A2612E996485B32FD5372FB8B7DB89DB645CF1BCCAE2573F36FEFB9B22302D710EBEBFD7548F336B4A377157A0B92FEFFBEA7B6303633CBBE54C903FACF97CE7E64D28F85E75CC0315538A5B2B6CB4B298CB365E046828EAAAFC8B0643A27FF19858C145AA818AF522E37F4FD77D091AFD8F277B13423378CB0D7D6ACC65ADC3F0D4BBB0498215FABDF2697317755DFAB85E6A0F7B141F3E3165FD7BCEA83804D90DEDB10B8D2FCA1979FAD9F3D1A62359978638D2076CDA5427402DA5D397891F837F21DDEF926EAFDDE506FA5351A5CFE0136724D67AD2EE80EDEAF36C3ACE47F0FACF092A288C3A33EAB00DF9A310868760237A45FF756B5F3B3D44186666833C3F230D047110047A8901C2D937656B1FD5F98B3AB15840D68CA8C7F3460DF3B505D80A497301338CDA6894F4C0FDA000902D74BA79E757E4A03D4DD6937CCE98CF3AD3EF4F1E976DD088A87E26691813B4C5F465C468A6091CD98126A13CC6884973215A320A1E2DFABF6DCCDFC470CBF17648891751EF5AAA1DC09DBB748465571E2771AD2CD57377C832EFF549EC1057309D2B93F47E0E9DE4513B340785EE95AADA6AC22842326266AEDA57DA9B35EF8BDA8049A57CD37977BC5027361C839BDEA16D7A64F079B03A189097EFDE9C1DB73A4C47C6672C1EF9BB2B4F9FE50050945CA8B52E336904889A2F72A6330E57CC87716FBEE30835A3CECC061A2C833C13147C29F2C58A1AB6C8FB4F0FD738AED7C836E7AB54860074016AD2F8EC9A5C12AEA52AD8D97511A93DA61B08FF905F0927E140914D6E5FE345EBF1A07C8261C5D002AF4A609A7C595F379A99DDF1487795682EFFC16403C983A21B5D0F50DF7EEAFA6631F542C11A1A8598A4E3A23F5298893DAF6EF66C3EF8B33181A85C6694C83032CDB64B2EFC8149BF1B6AC06AAA674DD67D84D6DB47528B51BD63F94DEBB6B715E2CA6F2BBF033C948A7FBA9ED2BB68E0DFDF46E5A02CE45C1D02C149E43562EAC2FF8E64045BFADE765C570D1A2DCAA9320D43E6AFA973E6A64883873320EA1673D390EBC33344C51B0150B6C4314DFFAACDCC9D7A9175347BD9D8774FDA4F86A2678DBA00ED26C03CC93738DCF50CC379141EFDAD1CF923C112D683BDE31203D5E962CE65B5DE7D464E7FDDBBAA15697BA39871A8FD4BB7E681E582F6623E1BAF8D2020D78C111AD642F46F67CE104DD873C65B7ECF538931668944FE20C14A3DBD56722E7C028D53D3778671874FDE3761591EF09469B739A6B6182207D00899B6FDA03CC3F79EA0BAAC33F5E49626E0A0A2270AC5A9EF780FFDE8460FEAF0760CA44AE45D34B6D2DE3AD9FCCD71B25C8D8A796505537EC5B89BF3CDAAB0B9C46C2879D3289505D6138E1EEAC7E7B0EB159CC985D7BCA0D2D3711DDF334C4C33B559F140D574B202489C01D8CCDFC68F60BD0496BE81B924FF4F07AA105D118546661A4D7733E9E29D705D1F5D1811695D274A4766DC03778F299E181C6B0570706B28F8F97F7AA81D91861E297DC9794FA9F7B6C110A583BD64484479D7186685725A28F783E52795D0C7945FE75B8209054F02ABA0861605FB7A243687BDAE3EE34CE3549F458BA3D66A270FDECAFC6E01D6098ED75E36C949928FFA34F3B9BDC39D7127B6A074325D04C6653CD5B5DA56A24FC4F01E2CFE0822EB5B81A7EAA4728C59EC68C97795013594CC468D67A567DF9CE349FD7BE40B2302DD6A1827EC88B1E2A4453B3BE1C19542A7807509ADC17B6C0E97807DD4DD6FF20ACAD4BAB9706861A64ED3E63261D602C7AA346C6CC8B1D51B329E3CA38EFDBA81B8A19D8130EBA52FCE5C793BD8515AD0799464EF70CFF8133B6F44B492FEF1B2DB5CA676F82B7EBA64182B098D1D7B4A24D1E3D37819D0A895817E00BA3C94EF993BAF8E588B1EBD78657F7AF8733010D6079C56A9A47C0CCE68EF7F6F3A4259877C79DE7D00092803C896143B6E7CC4969212021A857ADB95FC26C5B431F18A5839581EDB3B19BCA1D1D6FE17027C32C92C30F73003FB28C07B3A36DB788E999CFC0F5B1BCEDFD67E71485E8568E294B4FA423346586E49712305EC141E8F71F78E9610660852F112EB5B131CB0C1DA8D63BBC5672E3637A58C53A86315C2885F29DF791029B5BF640776DBDD983EA6A1447C2F4B38C6A95E3AC4B82A41C00C1AE7B8E4B83AC127C30CD0E7411E417C972A2B3FDE19D8372A5EB1A9A2BD0C61E2D08509654435974B2B4763F11A1830B4CF1967DC854993F43A77AE75F08DACB594D94E600684074445A72DACB93B5844234D39277172DE8684FB89C3DCF36B2987386A21048FF210BCF5A0C6035666781C43BBF0E8936242D2155E5AF8213C8EDB07E5812007BDF1FD6314B11621102266415344E0E807A2307C79C0BFF23F75E47189CC5448395B4C679B6FDF09A3211A308C4CA85510F3648200024E222E21BFEBE3EE1C7263DBC90E9F95479A14CD48760EC5EC4C7589DAE1B0577EE1C96167D59E746A760C67328A6F423DCD9CE5F0248FF02478323932DF16466F2C1C4B33F02DB86AF3BB39E9A0F8BA1C2999F5FCFF7562B74592CAEB3A8247F086357B19D295B7186B13E293241B99C83A9C04E9E1F4DF969121DD374C38058755294EEA50821CE6A933C7880492649830ED2C462BF2F2ED9F1E56349C991CBA2316CE6DD61D57AD450206EC4FBBD27FC4E42388C77708AF2ACDB97CA576FE1F714E1C9046BF93E4063CC216A402F940C01CA5C4448E63F375F3F1BFE3A1801ADC4A1C36DF4B078C2FDB4AADEAB7FBF810D2FAFA153A678195C8E737A44E215FFDE4CF29AA94E76063170838D26384DF9B0465E55336D8206C57B01262250FA75269AB5791F70E9DB2A43E65B260891DA34C34643E727B1A205F2B60312EB03BCA2A676ABE38C3E237545404BC449EEC18027C751BD76856503099707425BA150FA85E2DBB166C119768268FF927A5E03F74426E5D882D68DABD62EE54E63EC7D5F98001CDAFA66C8E3E00F3C1D730A128C491A057656F855AB34F2614FFD52EB7EB6F8B13F2082024FD146AAEE5D3CEA7CF045BCC6990399DFD8F9865FB5215D556A64D41F49384EDEC1AB43F13BA71280F3A5B21EBDB020E4E3F8DEA6C91D4E752AA86989454B482FB7FCA55FC7FC32388ADE4CF531DCA71A08E1E11DEF7ACDD3B56F6403BC4FFE837A1CFD5F1D0BA444FB7A7E53B9C618C98ED95ABBFECB7EFCD356421B866563E31347B92A3F43B3ADA8812E94881A40B38DF50D9372B99B5DDF680B5F291513C1AE5308D199D71946F031A07B9E33C6EFA804CC80332B64071E945ED3B921269C3CD31F3D71ECFB77FDD1E969008628CC2D1A4622D39B6C6062605832F50E69DE1901B207E2FB4F2D8D0C90BB4BFF38247D42680A033FDE593B00A1A699E0529675C3FB534387F2D7887F631A31364BAE57DC2116923942EBF670060B474F98CC8F391AB204BAB183068F43EEE5741F819E00DFD2698288A4C5D0DA5318D4EFB40C7BB49FCB8A30519E0C94022F6CB30780973A67EAC4168024E7449C9BCC6F2FB80EDFA3278A850E5BFFCE27D83B65B1F45C5B75F3A5196B3FBDFAD7834EBC43A6E6B2AAD4BC8FC01F854988446943256E490DFFC5C8E525946DF09BAA687769699608F773C1A53307D826EAC3B6C9AF845D3060D9191B84E871A9DAD562F351A6714681AD572F97780D5343994CA32C8E250E8F214DE1E6A80156D4111C5349E6DF3C383B070E00E9CC1ED690EEA707451C1CACF7CC50D5384328CF2BFC67A36AED71D4FDB55FE78A0371A914619487404B0052655780F9D4C863E24848081BABA2EB1FA78C006D33BD66037830D20C1F228DBAB4B5459E8B33850DE506A56F5A0DB381DF44D7BC8E286D3734662E6CB4F24ACCFDB1885D8D98D72CA44125DB7F4E74CDA4C48AE72458457272978CB7CD3EEB4F3241391E41093667487D955BD51BE0B";
    str_l = "0FF2AA900E918095CF30D722231948571EDD0B943E50FA8BA79F51A61F0E75DED433A98DD448EC6650CCA191A6DC9AD76FA1A6D346B4F52243DE66883BBF1823246F1272ACDCB599CB8A4FB15C61CC29C98A423047F32913F1532B699FE4670C5059AD958599D7";
    str_n = "051D72DFD943575062083C6DCF94E6DC1EA7A3B775495ACABEBAAA969264F67755717E66AA6B3870CD5FD00F2645FE1F2D62A2F91ABE68CB2FFF42681CA3496C70D93DF6E82FB319D4CF9DBE3BD82D78B8FF2221A4717307108D34BBF9298A569B776039718735CE06D09A46F59B5C6558A49A2A33AD9823C5D91D179B5C8BA912212ADB26E84D6C10164E30181D090D15E57F7FFFFCD75C7A7315EAFA8B3839419CA908DA1541AC2336F569A7F006B54184284F5494536089B70168EC8A6836509F7F167B54CED66BAB4F464EB95E5FE8E85E7511B030753831306DEE73A75AB19EB4ECC6F3199AB193DCD6AE967283C071ED972C88008A72A466BCE86252AA54FE659A6FF55BAC2D5F186E5623C8EFA9A6A1835B773B9A4EF4FC0079ADB1F94E0233C06F61FD3A124D870A21D32EE73598DAC47B030CA80450CC435BD3FEAC6A127CFCE5D16EDC8EF07E689F32F8B71EF01B3F6753D09D9D4126BF0549019F9128416707348F0A6F310D87F684812FF6161C474166B21C70B81B4D1BFF95DE8FA9154677792FDB4859CBBED2CB37E8A9BBA23ADA92B3A62D6A866363C2F161E30392A3D710EEAC10CF5B53DE67251ACF3489FB53910D0B0B34AD835A0AB64455881DAD92F764AFBECBD71FBE5DAADD66D4805086AAC440E17AE04227DF864BC728C51D419756695A26167C2E3FE6C38FB1D7014814C84CD7B4A895A0A0828C8C1A2E40BF1804F63D6FA671411BC948A8FBBAF012CDEB6C83EE7A791F4666061764EF0322AD03F36600059D7ED66F36210F37D7127BECD43D5694433FA2FC2D690991514DD2EF4D351AF5D88D1361869299199BFEEA4F89A148110C69DBFF2DE5403C6F889636EEEAD0BFB6843D05E1C8A2EE659FC10F64990097CAA18573E2FFF524417C6999ABC82AEF0A85544FAD07799FADDB4BDB2306B1EB4902F20BBF3E9EF3ABA229E3447675C811BB851492D148D250FB19D5D72F162C44A2D8A820380B655A9C5741810FCF2C2BB92C0DEB11C3B9D0AE1233D3CDAA6451262E3DA7A200FF32B1CDD53495C703FAECEEDAA8B14EF59BE9E53A09B7DD8E3F88F8BD01920E1E0922F4202FD072CF74FE37E309B838ABC85DCAE93BA1C92C6853E2D22D2E3F756A2A88BFCAAE292CF288389CE76F9F77378AFE98837F77040D8339252E58F42D6B0111975C9731D11DA31AF079901F78B7C353B82A785AFBED9601A608995FEA5FD18F7C53E801413A0AEA64D3E315D5B364E69AAA5A53624E8F8CCE74DF5A6BD5AA40132714AE57AA7CFF281650C9D04B1909FF4053EAFA474E9A8866F4C412A923FF0263E3E455EACD8361F35D9D53D27BE280D015F89979FF47DB5726D5AD2D36CA5FC6B3EB2827F2B51D17EC9C9E1435BEBF262B15008A4727393120CF35DBE05BDFD2A657E4995A7F37622EDF29961E40633E10277D32CD7B440874D2073EA31BF0FD46BB78BF57CBD5DEB6D9752C58AA829F277E073684599FF33A94D629CDDC784914DCBA986D4464988011E512B5321D673C784D88E24FFA9CEE843D6AF9E7B238DC348ABA7EA554BD0E2BB064513B7F1D4770642DC79EC8E2DC46833779B6C02C728AC9BEDFC0B7ED44FA65E181EC5C95F6641C541B0E2FAB4BF58DBE55A9F95A2A5736DFA6745F4E3AF712CFD60E412193A6FCFA5E4E19BA819D0DB069C8229F9F2D162A7CA961ADF34C82188FE76427DA275B5AB9577770CBF7CEC7EB155A2D633147A1E53A40788B07EF0ED8E64F45D5A3C2439F50F4B4F6B718AD685E13E0F9091D7E1EE0EFD4A036AE46A2B9C08AF391355CBCC4F49A9B8CDC4A868B5628DEDB5D9F63709EFC5D216DF714A55CAB59F3B3157DF09F3E67D4F8820CB8A3B04DB4E62497BD091F1FA242D23905CD69FC47A1D9783809FEBE93BFC09885FDEBEEFE6CFB8AAED59530B7B6051DAD1246F8B682D3A82BF0A476ADA68F75A30776ED91711CC75787E59BA363779BBE04F1C179E52EDB121BE45743DB5B249E6E5615F43A7C22AEBB4814C912E1FEF89A4A87328B7A7B9CC0F5D086596F3054A2A916818E72BC340E04E9A77809ACE7CA583885D47E3E3A4C59C01CE2539A8BFA4989FF98351E9733974E1069F0D8AFC5C2B86820E7DE682C3947670400F77D89FDD70A2C9D6897E8E47DFE9EA33B5678F4C1945BAB0568598CDE1FF05BD3E1D365331258DD0FCFED89B6D4C15F96F97E54148A0B85981FCB55F9B06C40222DD6C99916FBE801466E122BEB1727A09006561804193060E5302F2A29B9BC891B8E4C9B6500C14170FF917DE92B590242F968C345E00C1AC5EC4683A8E74D6EA06ADCC3B20CC447BF562573A926D222862F5EC563DF4B831AAB01A63BD733B6104622266008C25572FFE0BFA45AD9C3250787D0FFB8DE2591D243FA9D49430D30916F43CB5517DA28FD7910E776235566E3265759CA319ECCABBBB24F0CAF86D6C21F455DEB56342F342B84972245B1CCB6B886189DFB9EBDB384CAF78DCA807D95F0065BFFCF00BE66EEE4381FE22CB2563100B2C1936F197B82478F5BC8F75B78A024D65276B4829BE37E99463E06392BCB75E29D220E5670F3D81B7E3925A5AFEDF85ABE520E3EC4406354F481FAF4EA90E8A8F3FA047A613C743A4D82851184B8021B8588BCE2328EA9E37810EADA0EB8A3D4009ADF44EA41E5D4465FEF380BA4F9755DF5A44315E28817E2A60991BAF9C0DA4FD84C92011FB0AC5D7F4C6930E03AEC8FDE471B50D9649AB608DC32D5AEA469DD2FB5A5C852317DFA0996B610E6293C0CD581C2A9D59977F513280FF162D37B786D6B2B618B22DF2E6AFBA0F4D483D2CB1286C905190485600B4A87089AEA52BDFCD01402A81C5423972435573C7CE403D611A4D65147C3CE1C8A06F40176AE81578E944493702D1FA3417C7E35D9E814C65B8CC73486DE3B8303E71D1CE835F686DEFB40C468D1B1A23439514A100840F7AAFE273691C6CBB5FD4832DE5D7F4F7F199FD98944A1FA0ACCAB984E92866276C09D5D5984EDEC51E2A9CF4750C2EDB3DA0A92C8F1D37927D3B69E222C1070F06A634C1C487B4C14730ACDB8546452BC58542874DE1AD6284C0FDE45F437176A0B8F7B87D6E79BE7925161C59F9B40F01D353C6F677A2D19E6CD6AB12AD3D4819825E80801FBFB64755E1DA9C8C00B95ACFFF554F289055E0D341FCAAA46AFEDA4404C541D3074D7EAB41FAFD48B5654B8C9F49468933308BB62B4A78FE956C6547FC31C085D736AFBA58326A71249AE9854B3BA99B7221D98464CFAE3A5C62A0B06395CDADE93BDC05CBD0D97BF6B4EA14CA65CE71C84FD9F09EC8FD42664A5480B8E820BA88D96F10F309641BBD3376B9EEFB5BE31B275385FDA5DEADA48718416390553C53824E9828AA7BE8E19F1C9004CAAF94C6EB9C45C8C54437BE648EDF07DF1A05A548DB83071A0FDC94D6F560ACA85FC25A7AA8A220348A778552D997062CCF6FA78349DB7BD29219CA36237914396B3A99F9A10AC963B51D4227F6F8D39B7F3FC09372D30F06A19808D0CC7832EB777113CEF7F128FAD450FF6467B56545A94BD05A0D9214172F1A36665729058F47D968B9B8F1D5ABE3726AFC1838FD23C4702C6AF64B065B44ECD48647AB5BCBB599F9DB6DFAE18081961045573E9E6EC8C5C8D76645A29656C9B72A5BB2C94F7684A27F4ADC5AE526DC2DDCB46FB2C61A7CE69178BC338D857D53210F10B403D09B6A7A6DC13D6B7EB632F7917D502C41606ED6DD4A30715FEA57ABDEF826A198284BF973A2D0103CFB2319D7DE24DBDC313DCAFA7EC7676E08A3DC4E4D9842A26F588CB7B08C12B396BFA3616732109DDDA0248A3A940EC86DB15604F9B78DEF74AF45FB3CF7D09D89E8225BBE81D15F741E8F612E1D4FEBE485E78F26E903A3CD76E74055601F07CC2DCE5DEF27CA7D422A8A73EC5DB0600BA57244DB4A8E8EE9BD5CAA625DD326A241E292E55A56C8AD48B605D7927D70954AFDC3CD7DF5C479E91DCD451FB997A75F71D3792AD6A01289D95A65BF0706E6BC05D133DB92DF62B8A8AFCF0C9154A8520057682F3549FCB362C36E81FB91D57E7A72E015F0F30E9076E1DD3F5FA91D15D56F9D5D5A984381664B6262A07A64AD2E05191B18EE13C8B5BDC475A279FB554A9C8BD5582369A06C7946DDB75DA7AC7369153DCE0C4AA2D55229B81872028CCA881AACA1CACB1823CDD288672960FE63D57EEB370EB4194FDFB3E49EBDA05D0C0402E77D4AF56B9143607F39802573851D2A3456A0529C9446712F979AB5E09129BE0037AE2D31EF020C97234986E157687977D84B85CA094FEDB2C74CCFF03A3984A5BF9126A4B55A9583BD803B5B3CEB329F2FDCDE256A7C7859578A468E887B13FBB929A78A6733AABAFEC92F8E8F42D5EB61E43724E3D51068198DC304AE0F501482B5027918754663B48F9702DA24F71BB55D76D4CB96FAA82ED57FCC53CCB805D265FC8760E3620A4FC330450551DAF4F06415C1600E3B3289AF31C51694787A2D3D7A023DFFB4792891B8C82FDD8EB9CDA1611B917478BA09435E7F38AD03A8F1B74CE8EE83B9BB830F71A6C2946FC643070087E4850B4D0BDB986AFD68B5D61C62DB25496C0E4FFEC067C0619039FEF2139FA1A4108A150270DB5FD948C15CBF9D37250122555EA4ADC8A9AAA9F9BB34B7C7FA5E904637B1D363FEB20C6A0AEE070CFE8027BDC2F5D6AAFC8DD7E91AB56C47AF90659F392CE486AADE2A7BE21B913FF9D1927C3DA6EEA017A9D538D2C7B24DEAED81673715C86F11BDF6EC353F991B1EB8D0F9B78143E42A4D8D96D175E83B480740B1642113CB29AAC33D3CE2F2DE81CE537AF0DE8168EB304094B66AFB5BFC8A41AB4CD2A8EB96AD0EAFD2FD4E6726C0B2407555917A51AA1395FE312C5CB2F7B30FEF1F9C01BFA09038DDFF0252F466CA9090F5C82851B3CEA58868DE429CAC32D0414175B34E8ED3DD5E582815AC807C7B24BF0AC474A78106E4A68B38F1D3B6A98101C8587492D64DF7DCC554F36E71DBBA77BEE34A81EC6E2208BEE11D182C4BD00B3A3A30DAE36A6CFEE928A3BCF5BA01E7D3C8215FDB96FB7A497C55F27C339F959C83057800115841679C16BC921CE0DE87225B4F3A44B918D913523FA9119C51E39E6220655F514C2F57506D62F245E719D039645C7339AFB5BF17381D289D9DF1BF702F4B34B99E69C09F82F676306BFB7F4C643992BD0A3B21D80D792F388A6BBD7367C3489DC6A28B506217064345935C3810C75CFA3C62340B7ABE8F2A8AF3C333BA54457B3CD9D41C88C8577FC1DFD760F968CF95BB0F46F45AF7C6EBBAAD79ABEF650C27E6BBD1AF00867A8C509252D72EADB3D6DB00E12B0705DE205CB4A1164E815FAB61083845BF57556B1ECCB190FC8C391604D8017E78617DFAC16D6F95A29C4A73C21C63F7557E723B56EB318B9C400B8328DAD71B4A33265D21284507693BFB9373B1DAAF28932EFDA56D6AA2355AC8C7264B5992AC7402FD71378D57134D100A400A58D8EBF0A4E52A4740A27BB84E6374B4CA29253D4555679C175699FABCFF212F7B3090B7DE08EF0E169D26E863287A5918F0C1CDE0CE4D8DAC64DF198837808A13BD5A1E99CAED616BC6C70670250F4D080BBD91CA7FEA07DA210557BAA604CD23B9A11E45FAD8F8B800A7F8B0B4AF1A5352B33530B78DA15A64D3E1EB9F505B9E136371528A29B8A1F6C46EBA0A47F1A9B86416AEF1C092172D41516DBAB4F6567382D3E8FBD6E885BD26F821339AE271A54B62428F2D840E0520191F03F8419AB1776352A0374262B78837173DCA7D7517670DEBF27EFF27FA45D909C1C556249124C3230753BE9E8BBD326F11DF1FF32B5A07C6EA45F38E1F7AC6D1EF24C3DE25DB36F558D29FAA69498850A28A785E9DD0516847AF6B008B7B220640BCB81F63C4F09CC8E1BCFE27A657EA21B19696736C21689528CEB361AA04E5F637E5123519E0516649F4A28C41D0AA4977821A0ED49BADA0BFC7B21100489703E19DAB4F580F0AC39905329A982DEB71439B77DA06E6B87EF69D60BC0CEB1D0E61726B46DF09DE7555B1C5930B35B851F188217E949188BE817E339CD2044C1BC5F005ADAE176C529C6CEAA19AE007124CA0030907E0884CF5245CCE714B33AF5A0684A3B7B30E3F1AAF2DC55BAEE7A9F1438F9F526EC4B09173CCD85A292BC8B90F3B1";
    BN_hex2bn(&p, str_p);
    BN_hex2bn(&q, str_q);
    BN_hex2bn(&l, str_l);
    BN_hex2bn(&n, str_n);

    BN_set_word(two_big, 2);
    if (!BN_div(l_2, NULL, l, two_big, ctx))
        goto end;

    KEY.p = p;
    KEY.q = q;
    KEY.l = l;
    KEY.n = n;
    KEY.l_2 = l_2;

    // printf("p,q,l,n,en_neg1\n");
    // printf("p:\n");
    // bn_printfHex(p);
    // printf("q:\n");
    // bn_printfHex(q);
    printf("l:\n");
    bn_printfHex(l);
    printf("n:\n");
    bn_printfHex(n);

    BN_hex2bn(&negative1, "-1");
    if (!she_encryptBignumRaw2(e_negative1, negative1, &KEY, ctx))
        goto end;
    KEY.e_negative1 = e_negative1;
    // printf("e_negative1:\n");
    // bn_printfHex(e_negative1);
    ret = 1;
end:
    if (!ret)
    {
        printf("error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

// 0失败1成功
int she_encryptBignumRaw(BIGNUM *c, const BIGNUM *m, const SHE_key *key, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX_start(ctx);

    BIGNUM *r = BN_CTX_get(ctx);
    BIGNUM *r_ = BN_CTX_get(ctx);
    // BIGNUM *n = BN_CTX_get(ctx);
    BIGNUM *tmp1 = BN_CTX_get(ctx);
    BIGNUM *tmp2 = BN_CTX_get(ctx);

    do
    {
        if (!BN_rand(r, DEFAULT_K2, 0, 0))
            goto end;
    } while (BN_is_zero(r));

    do
    {
        if (!BN_rand(r_, DEFAULT_K0, 0, 0))
            goto end;
    } while (BN_is_zero(r_));

    // if (!BN_mul(n, key->p, key->q, ctx))
    //     goto end;
    if (!BN_mul(tmp1, r, key->l, ctx))
        goto end;
    if (!BN_add(tmp1, tmp1, m)) // rl+m不可能比n大
        goto end;
    if (!BN_mod_mul(tmp2, r_, key->p, key->n, ctx))
        goto end;
    if (!BN_add_word(tmp2, 1))
        goto end;
    if (!BN_mod_mul(c, tmp1, tmp2, key->n, ctx))
        goto end;

    ret = 1;
end:
    if (!ret)
    {
        printf("error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

// add support for negative numbers.
int she_encryptBignumSupportNegative(BIGNUM *c, const BIGNUM *m, const SHE_key *key, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX_start(ctx);

    BIGNUM *m_positive = BN_CTX_get(ctx);
    int positive_flag = 1;

    if (BN_is_negative(m) == 1)
    {
        BN_copy(m_positive, m);
        BN_set_negative(m_positive, 0);
        positive_flag = 0;
    }
    else
    {
        BN_copy(m_positive, m);
    }
    if (!she_encryptBignumRaw(c, m_positive, key, ctx))
        goto end;
    if (positive_flag == 0)
    {
        if (!BN_mod_mul(c, c, key->e_negative1, key->n, ctx))
            goto end;
    }
    ret = 1;
end:
    if (!ret)
    {
        printf("error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

// add support for negative numbers.
int she_encryptBignumSupportNegative2(BIGNUM *c, const BIGNUM *m, const SHE_key *key, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX_start(ctx);

    BIGNUM *m_positive = BN_CTX_get(ctx);
    int positive_flag = 1;

    if (BN_is_negative(m) == 1)
    {
        BN_copy(m_positive, m);
        BN_set_negative(m_positive, 0);
        positive_flag = 0;
    }
    else
    {
        BN_copy(m_positive, m);
    }
    if (!she_encryptBignumRaw2(c, m_positive, key, ctx))
        goto end;
    if (positive_flag == 0)
    {
        if (!BN_mod_mul(c, c, key->e_negative1, key->n, ctx))
            goto end;
    }
    ret = 1;
end:
    if (!ret)
    {
        printf("she_encryptBignumSupportNegative2 Error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

int she_decryptBignum(BIGNUM *plain, const BIGNUM *c, const SHE_key *key, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX_start(ctx);

    BIGNUM *tmp = BN_CTX_get(ctx);
    if (!BN_mod(tmp, c, key->p, ctx))
        goto end;
    if (!BN_mod(plain, tmp, key->l, ctx))
        goto end;
    if (BN_cmp(key->l_2, plain) == -1)
    {
        // printf("the bignum is negative\n");
        BN_sub(plain, plain, key->l);
    }
    ret = 1;
end:
    if (!ret)
    {
        printf("error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

int she_decryptBignum2(BIGNUM *plain, const BIGNUM *c, const SHE_key *key, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX_start(ctx);

    BIGNUM *tmp = BN_CTX_get(ctx);
    if (!BN_mod(tmp, c, key->p, ctx))
        goto end;
    if (!BN_mod(plain, tmp, key->l, ctx))
        goto end;
    ret = 1;
end:
    if (!ret)
    {
        printf("error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

int she_encryptTeeStringBignum(char *str_c, BIGNUM *m)
{
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);
    char *tmp;
    BIGNUM *c = BN_CTX_get(ctx);
    if (!she_encryptBignumSupportNegative(c, m, &KEY, ctx))
        goto end;
    tmp = BN_bn2hex(c);
    memcpy(str_c, tmp, strlen(tmp) + 1);
    OPENSSL_free(tmp);
    ret = 1;
end:
    if (!ret)
    {
        printf("encryptTeeString error\n");
    }
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}

int she_encryptTeeStringBignum2(char *str_c, BIGNUM *m)
{
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);
    char *tmp;
    BIGNUM *c = BN_CTX_get(ctx);
    if (!she_encryptBignumSupportNegative2(c, m, &KEY, ctx))
        goto end;
    tmp = BN_bn2hex(c);
    memcpy(str_c, tmp, strlen(tmp) + 1);
    OPENSSL_free(tmp);
    ret = 1;
end:
    if (!ret)
    {
        printf("she_encryptTeeString2 Error\n");
    }
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}

int she_generateRandomKeysTee()
{
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);
    if (!she_generateRandomKeys(&KEY, DEFAULT_K0, DEFAULT_K1, DEFAULT_K2, ctx))
        goto end;
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    ret = 1;
end:
    if (!ret)
    {
        printf("generateRandomKeysTee ERROR\n");
    }
    return ret;
}

int she_generateRandomKeysTee2()
{
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);
    if (!she_generateRandomKeys2(&KEY, L_BITS, P_BITS, Q_BITS, ctx))
        goto end;
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    ret = 1;
end:
    if (!ret)
    {
        printf("generateRandomKeysTee2 ERROR\n");
    }
    return ret;
}

int she_encryptTeeString(char *str_c, char *str_m)
{
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);

    char *tmp;
    BIGNUM *m = BN_CTX_get(ctx);
    BIGNUM *c = BN_CTX_get(ctx);

    BN_hex2bn(&m, str_m);
    if (!she_encryptBignumSupportNegative(c, m, &KEY, ctx))
        goto end;
    tmp = BN_bn2hex(c);
    memcpy(str_c, tmp, strlen(tmp) + 1); // 但在C里面是可以加一的，不会出错
    OPENSSL_free(tmp);
    ret = 1;
end:
    if (!ret)
    {
        printf("encryptTeeString error\n");
    }
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}

int she_decryptTeeStringBignum(char *str_plain, BIGNUM *c)
{
    // printf("shou dao miwen:%s\n",str_c);
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);

    char *tmp_;
    BIGNUM *plain = BN_CTX_get(ctx);
    // BIGNUM *c = BN_CTX_get(ctx);
    // BN_hex2bn(&c, str_c);
    if (!she_decryptBignum(plain, c, &KEY, ctx))
        goto end;
    // printf("TEE内解密结果为：\n");
    // bn_printfDec(plain);
    // printf("TEE内对应二进制为：\n");
    // bn_printfHex(plain);
    // tmp_ = BN_bn2hex(plain);
    tmp_ = BN_bn2dec(plain);
    // memcpy(str_plain,tmp_,strlen(tmp_)+1);
    memcpy(str_plain, tmp_, strlen(tmp_) + 1);
    OPENSSL_free(tmp_);
    ret = 1;
end:
    if (!ret)
    {
        printf("decryptTeeStringBignum error\n");
    }
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}

int she_decryptTeeStringBignum2(char *str_plain, BIGNUM *c)
{
    // printf("shou dao miwen:%s\n",str_c);
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);

    char *tmp_;
    BIGNUM *plain = BN_CTX_get(ctx);
    // BIGNUM *c = BN_CTX_get(ctx);
    // BN_hex2bn(&c, str_c);
    if (!she_decryptBignum(plain, c, &KEY, ctx))
        goto end;
    printf("解密结果为：\n");
    bn_printfDec(plain);
    tmp_ = BN_bn2hex(plain);
    // memcpy(str_plain,tmp_,strlen(tmp_)+1);
    memcpy(str_plain, tmp_, strlen(tmp_) + 1);
    OPENSSL_free(tmp_);
    ret = 1;
end:
    if (!ret)
    {
        printf("decryptTeeStringBignum2 error\n");
    }
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}

int she_decryptTeeString(char *str_plain, char *str_c)
{
    // printf("shou dao miwen:%s\n",str_c);
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);

    char *tmp_;
    BIGNUM *plain = BN_CTX_get(ctx);
    BIGNUM *c = BN_CTX_get(ctx);
    BN_hex2bn(&c, str_c);
    if (!she_decryptBignum(plain, c, &KEY, ctx))
        goto end;
    // printf("jie mi hou:\n");
    // BN_printf_she(plain);
    tmp_ = BN_bn2hex(plain);
    // memcpy(str_plain,tmp_,strlen(tmp_)+1);
    memcpy(str_plain, tmp_, strlen(tmp_) + 1);
    OPENSSL_free(tmp_);
    ret = 1;
end:
    if (!ret)
    {
        printf("decryptTeeString error\n");
    }
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}

// E(m1)+E(m2)
int she_addTest(const SHE_key *key, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX_start(ctx);

    BIGNUM *plain1 = BN_CTX_get(ctx);
    BIGNUM *plain2 = BN_CTX_get(ctx);
    BIGNUM *cipher1 = BN_CTX_get(ctx);
    BIGNUM *cipher2 = BN_CTX_get(ctx);
    BIGNUM *tmp1 = BN_CTX_get(ctx);
    BIGNUM *tmp2 = BN_CTX_get(ctx);
    BIGNUM *res1 = BN_CTX_get(ctx);
    BIGNUM *res2 = BN_CTX_get(ctx);

    if (!she_encryptBignumSupportNegative(cipher1, plain1, key, ctx))
        goto end;
    if (!she_encryptBignumSupportNegative(cipher2, plain2, key, ctx))
        goto end;
    if (!BN_mod_add(tmp1, cipher1, cipher2, key->n, ctx))
        goto end;
    if (!she_decryptBignum(res1, tmp1, key, ctx))
        goto end;
    if (!BN_mod_add(res2, plain1, plain2, key->n, ctx))
        goto end;
    if (BN_cmp(res1, res2) == 0)
    {
        printf("同态性质加法验证通过\n");
    }
    else
    {
        printf("同态性质加法验证不通过\n");
    }
    ret = 1;
end:
    if (!ret)
    {
        printf("she_addTest Error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

// E(m1)+E(m2)
int she_mulTest(const SHE_key *key, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX_start(ctx);

    BIGNUM *plain1 = BN_CTX_get(ctx);
    BIGNUM *plain2 = BN_CTX_get(ctx);
    BIGNUM *cipher1 = BN_CTX_get(ctx);
    BIGNUM *cipher2 = BN_CTX_get(ctx);
    BIGNUM *tmp1 = BN_CTX_get(ctx);
    BIGNUM *tmp2 = BN_CTX_get(ctx);
    BIGNUM *res1 = BN_CTX_get(ctx);
    BIGNUM *res2 = BN_CTX_get(ctx);

    if (!she_encryptBignumSupportNegative(cipher1, plain1, key, ctx))
        goto end;
    if (!she_encryptBignumSupportNegative(cipher2, plain2, key, ctx))
        goto end;
    if (!BN_mod_mul(tmp1, cipher1, cipher2, key->n, ctx))
        goto end;
    if (!she_decryptBignum(res1, tmp1, key, ctx))
        goto end;
    if (!BN_mod_mul(res2, plain1, plain2, key->n, ctx))
        goto end;
    if (BN_cmp(res1, res2) == 0)
    {
        printf("同态性乘法验证通过\n");
    }
    else
    {
        printf("同态性质乘法验证不通过\n");
    }
    ret = 1;
end:
    if (!ret)
    {
        printf("she_mulTest Error\n");
    }
    BN_CTX_end(ctx);
    return ret;
}

int addString(char *str1, char *str2, char *str3)
{
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);

    BIGNUM *cipher1 = BN_CTX_get(ctx);
    BIGNUM *cipher2 = BN_CTX_get(ctx);
    BIGNUM *res = BN_CTX_get(ctx);

    BN_hex2bn(&cipher1, str1);
    BN_hex2bn(&cipher2, str2);
    BN_mod_add(res, cipher1, cipher2, KEY.n, ctx);
    char *tmp_ = BN_bn2hex(res);
    memcpy(str3, tmp_, strlen(tmp_) + 1);
    OPENSSL_free(tmp_);
    ret = 1;
end:
    if (!ret)
    {
        printf("error\n");
    }
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}

int mulString(char *str1, char *str2, char *str3)
{
    int ret = 0;
    BN_CTX *ctx = BN_CTX_new();
    BN_CTX_start(ctx);

    BIGNUM *cipher1 = BN_CTX_get(ctx);
    BIGNUM *cipher2 = BN_CTX_get(ctx);
    BIGNUM *res = BN_CTX_get(ctx);

    BN_hex2bn(&cipher1, str1);
    BN_hex2bn(&cipher2, str2);
    BN_mod_mul(res, cipher1, cipher2, KEY.n, ctx);
    char *tmp_ = BN_bn2hex(res);
    memcpy(str3, tmp_, strlen(tmp_) + 1);
    OPENSSL_free(tmp_);
    ret = 1;
end:
    if (!ret)
    {
        printf("error\n");
    }
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}
