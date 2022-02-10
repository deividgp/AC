/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright (c) Digital Equipment Corporation, 1991, 1999    *
 * *                                                               *
 * *   All Rights Reserved.  Unpublished rights  reserved  under   *
 * *   the copyright laws of the United States.                    *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Digital   *
 * *   Equipment Corporation.  Possession, use,  duplication  or   *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Digital Equipment  *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 */

/*
 * HISTORY
 */

/*
 * @(#)$RCSfile: softfp_isqrt_tab.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1996/09/18 14:57:54 $
 */

/*
 * softfp_isqrt_tab.h -- polynomial coefficient tables for SQRT emulation
 */

#ifndef _SOFTFP_ISQRT_TAB_H_
#define _SOFTFP_ISQRT_TAB_H_


const unsigned long softfp_isqrt_tab[] = {

/*
   0  is the Block Number   
   0  Left endpt  (fh)      = t:3fe0000000000000 = 5e-1 
   0  Right endpt (fh_next) = t:3fe0800000000000 = 5.15625e-1 
   0  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   0  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   0  Range distance     = 1.5625e-2 
   0  Number of Terms    = 8 
   0  poly_degree        = 7 
   0  poly accuracy      = 61.4333308081880882021778868034682 
   0  Rounding bit added to leading coefficient.
   0  Coeff signs are (printed) positive.

   0  t:3fe6a09e667f3bcd = 7.071067811865475246529445796372926e-1
   0  t:3fe6a09e667f3bbc = 7.071067811865456546210374766392448e-1
   0  t:3fd6a09e667e8a1e = 3.53553390590748738652165233942171e-1
   0  t:3fd6a09e651a157e = 3.5355338929397096169515365970959e-1
   0  t:3fdc48c49f4d9b1f = 4.41941409654122063674309625613823e-1
   0  t:3fe3cc2bcbf815ed = 6.186732276698286991803779621967863e-1
   0  t:3fed967a06c44444 = 9.246187336121995792694375215781122e-1
   0  t:3ff51b656ea5d1ae = 1.3191885301758748314480962360307

   0  ~sqrt(t:3fe0400000000000) = t:3fe6cdb2bbb212eb = 7.1261e-1 
   0   sqrt(t:3fe0400000000000) = t:3fe6cdb2bbb212eb = 7.1261e-1 
*/

    0x0000000000a8db2b,  /* c7, 41 bit shift ==> 24 significant bits */
    0x000000001d967a07,  /* c6, 36 bit shift ==> 29 significant bits */
    0x00000004f30af2fe,  /* c5, 30 bit shift ==> 35 significant bits */
    0x000000e24624fa6d,  /* c4, 25 bit shift ==> 40 significant bits */
    0x00002d413cca342b,  /* c3, 19 bit shift ==> 46 significant bits */
    0x000b504f333f450f,  /* c2, 13 bit shift ==> 52 significant bits */
    0x05a827999fceeeee,  /* c1, 06 bit shift ==> 59 significant bits */
    0x6a09e667f3bcc912,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   1  is the Block Number   
   1  Left endpt  (fh)      = t:3fe0800000000000 = 5.15625e-1 
   1  Right endpt (fh_next) = t:3fe1000000000000 = 5.3125e-1 
   1  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   1  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   1  Range distance     = 1.5625e-2 
   1  Number of Terms    = 8 
   1  poly_degree        = 7 
   1  poly accuracy      = 61.7831475779178936007820005749765 
   1  Rounding bit added to leading coefficient.
   1  Coeff signs are (printed) positive.

   1  t:3fe6fa6ea162d0f0 = 7.180703308172535826760241040034316e-1
   1  t:3fe6482d37a5a3c4 = 6.963106238227898630004791824532617e-1
   1  t:3fd59b52a2908d6e = 3.37605150942372214130891838745896e-1
   1  t:3fd4f3b4f99ec923 = 3.2737469078996831597732318497318e-1
   1  t:3fd965756c480db4 = 3.968175465999721271274144202001466e-1
   1  t:3fe13cd1c52ce307 = 5.386742449837535058848429769806643e-1
   1  t:3fe8fc85f2945315 = 7.808255899313702158960961985378901e-1
   1  t:3ff1552b37a9e48a = 1.0832931684838364898640361566606

   1  ~sqrt(t:3fe0c00000000000) = t:3fe726d41832a0be = 7.2349e-1 
   1   sqrt(t:3fe0c00000000000) = t:3fe726d41832a0be = 7.2349e-1 
*/

    0x00000000008aa95a,  /* c7, 41 bit shift ==> 24 significant bits */
    0x0000000018fc85f3,  /* c6, 36 bit shift ==> 29 significant bits */
    0x000000044f34714b,  /* c5, 30 bit shift ==> 35 significant bits */
    0x000000cb2bab6240,  /* c4, 25 bit shift ==> 40 significant bits */
    0x000029e769f33d92,  /* c3, 19 bit shift ==> 46 significant bits */
    0x000acda9514846b7,  /* c2, 13 bit shift ==> 52 significant bits */
    0x05920b4de968f105,  /* c1, 06 bit shift ==> 59 significant bits */
    0x6fa6ea162d0f00d0,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   2  is the Block Number   
   2  Left endpt  (fh)      = t:3fe1000000000000 = 5.3125e-1 
   2  Right endpt (fh_next) = t:3fe1800000000000 = 5.46875e-1 
   2  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   2  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   2  Range distance     = 1.5625e-2 
   2  Number of Terms    = 8 
   2  poly_degree        = 7 
   2  poly accuracy      = 62.1226715379880487490852110700109 
   2  Rounding bit added to leading coefficient.
   2  Coeff signs are (printed) positive.

   2  t:3fe752e50db3a3a2 = 7.288689868556625589893216421444322e-1
   2  t:3fe5f3aa673fa906 = 6.859943405700341546708288797962183e-1
   2  t:3fd4a918d9a4e250 = 3.22820866148991741814656616926804e-1
   2  t:3fd371f9446c3514 = 3.03831402606037377059529369649482e-1
   2  t:3fd6e06fac85e05d = 3.57448500136802671794250541026372e-1
   2  t:3fde243f722e0602 = 4.709623923336892797766959489758065e-1
   2  t:3fe53506b95db862 = 6.627229328567063061368284937469042e-1
   2  t:3feca1ced54c919f = 8.947519460676181883270266514962543e-1

   2  ~sqrt(t:3fe1400000000000) = t:3fe77ea35d632e43 = 7.34209e-1 
   2   sqrt(t:3fe1400000000000) = t:3fe77ea35d632e43 = 7.34209e-1 
*/

    0x000000000072873b,  /* c7, 42 bit shift ==> 23 significant bits */
    0x00000000153506b9,  /* c6, 36 bit shift ==> 29 significant bits */
    0x00000003c487ee46,  /* c5, 31 bit shift ==> 34 significant bits */
    0x000000b7037d642f,  /* c4, 25 bit shift ==> 40 significant bits */
    0x000026e3f288d86a,  /* c3, 19 bit shift ==> 46 significant bits */
    0x000a548c6cd27128,  /* c2, 13 bit shift ==> 52 significant bits */
    0x057cea99cfea4179,  /* c1, 06 bit shift ==> 59 significant bits */
    0x752e50db3a3a1b20,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   3  is the Block Number   
   3  Left endpt  (fh)      = t:3fe1800000000000 = 5.46875e-1 
   3  Right endpt (fh_next) = t:3fe2000000000000 = 5.625e-1 
   3  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   3  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   3  Range distance     = 1.5625e-2 
   3  Number of Terms    = 8 
   3  poly_degree        = 7 
   3  poly accuracy      = 62.4524911840732446037527729531743 
   3  Rounding bit added to leading coefficient.
   3  Coeff signs are (printed) positive.

   3  t:3fe7aa10d193c22d = 7.395099728874520054544908220783839e-1
   3  t:3fe5a2cd8c69d612 = 6.761234037828122976111766551099436e-1
   3  t:3fd3c80c631e9407 = 3.09084984585127060146333283219278e-1
   3  t:3fd215fcb1ad5d86 = 2.82591985237978669397336528579245e-1
   3  t:3fd4ab693ab692fc = 3.22962100350465932752444531139702e-1
   3  t:3fda74a0e09cca0d = 4.133684342843089573528870400709323e-1
   3  t:3fe215c70cdacfca = 5.651583911007886725126614368974742e-1
   3  t:3fe7c7460093e8a3 = 7.430753718647518706258772724915218e-1

   3  ~sqrt(t:3fe1c00000000000) = t:3fe7d52f244809e9 = 7.44773e-1 
   3   sqrt(t:3fe1c00000000000) = t:3fe7d52f244809e9 = 7.44773e-1 
*/

    0x00000000005f1d18,  /* c7, 42 bit shift ==> 23 significant bits */
    0x000000001215c70d,  /* c6, 36 bit shift ==> 29 significant bits */
    0x000000034e941c14,  /* c5, 31 bit shift ==> 34 significant bits */
    0x000000a55b49d5b5,  /* c4, 25 bit shift ==> 40 significant bits */
    0x0000242bf9635abb,  /* c3, 19 bit shift ==> 46 significant bits */
    0x0009e406318f4a03,  /* c2, 13 bit shift ==> 52 significant bits */
    0x0568b3631a75846f,  /* c1, 06 bit shift ==> 59 significant bits */
    0x7aa10d193c22ce74,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   4  is the Block Number   
   4  Left endpt  (fh)      = t:3fe2000000000000 = 5.625e-1 
   4  Right endpt (fh_next) = t:3fe2800000000000 = 5.78125e-1 
   4  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   4  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   4  Range distance     = 1.5625e-2 
   4  Number of Terms    = 8 
   4  poly_degree        = 7 
   4  poly accuracy      = 62.7731459348246486659517658230911 
   4  Rounding bit added to leading coefficient.
   4  Coeff signs are (printed) positive.

   4  t:3fe8000000000000 = 7.500000000000000001084202172485504e-1
   4  t:3fe555555555554e = 6.666666666666658836197176252191809e-1
   4  t:3fd2f684bda0e508 = 2.96296296295239363981872601772061e-1
   4  t:3fd0db20a7f9dc85 = 2.6337448505314171311956356058559e-1
   4  t:3fd2ba957d1d4860 = 2.92638179952637831531068318691169e-1
   4  t:3fd74e4968c0908b = 3.64153244301868196170423805368976e-1
   4  t:3fdefbd18dbbf5cd = 4.841197857020603211042081986947849e-1
   4  t:3fe3d9882c639b78 = 6.203041903471406518671450724955463e-1

   4  ~sqrt(t:3fe2400000000000) = t:3fe82a8500794e6c = 7.5519e-1 
   4   sqrt(t:3fe2400000000000) = t:3fe82a8500794e6c = 7.5519e-1 
*/

    0x00000000004f6621,  /* c7, 42 bit shift ==> 23 significant bits */
    0x000000000f7de8c7,  /* c6, 37 bit shift ==> 28 significant bits */
    0x00000002e9c92d18,  /* c5, 31 bit shift ==> 34 significant bits */
    0x00000095d4abe8ea,  /* c4, 25 bit shift ==> 40 significant bits */
    0x000021b6414ff3b9,  /* c3, 19 bit shift ==> 46 significant bits */
    0x00097b425ed07284,  /* c2, 13 bit shift ==> 52 significant bits */
    0x0555555555555392,  /* c1, 06 bit shift ==> 59 significant bits */
    0x8000000000000004,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   5  is the Block Number   
   5  Left endpt  (fh)      = t:3fe2800000000000 = 5.78125e-1 
   5  Right endpt (fh_next) = t:3fe3000000000000 = 5.9375e-1 
   5  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   5  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   5  Range distance     = 1.5625e-2 
   5  Number of Terms    = 8 
   5  poly_degree        = 7 
   5  poly accuracy      = 63.0851314421306663287999408016655 
   5  Rounding bit added to leading coefficient.
   5  Coeff signs are (printed) positive.

   5  t:3fe854bfb363dc39 = 7.603453162872774612223748802453116e-1
   5  t:3fe50b06a8fc6b6a = 6.575959492214285161322019634955183e-1
   5  t:3fd2330cadd3271d = 2.84365815878673997219505328870603e-1
   5  t:3fcf7ae57ebee2f5 = 2.45938002479099935681378097385164e-1
   5  t:3fd104288e5ab276 = 2.65878809945923842722069127542106e-1
   5  t:3fd49a3bc2ccec47 = 3.21913662180751860008047146588517e-1
   5  t:3fdaa7496e33f863 = 4.16460378284574315327099675032585e-1
   5  t:3fe0a6b891b7c6ec = 5.203516813328099642043528261226015e-1

   5  ~sqrt(t:3fe2c00000000000) = t:3fe87eb1990b697a = 7.65466e-1 
   5   sqrt(t:3fe2c00000000000) = t:3fe87eb1990b697a = 7.65466e-1 
*/

    0x0000000000429ae2,  /* c7, 42 bit shift ==> 23 significant bits */
    0x000000000d53a4b7,  /* c6, 37 bit shift ==> 28 significant bits */
    0x000000029347785a,  /* c5, 31 bit shift ==> 34 significant bits */
    0x00000088214472d6,  /* c4, 25 bit shift ==> 40 significant bits */
    0x00001f7ae57ebee3,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0009198656e9938f,  /* c2, 13 bit shift ==> 52 significant bits */
    0x0542c1aa3f1ada8a,  /* c1, 06 bit shift ==> 59 significant bits */
    0x854bfb363dc39652,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   6  is the Block Number   
   6  Left endpt  (fh)      = t:3fe3000000000000 = 5.9375e-1 
   6  Right endpt (fh_next) = t:3fe3800000000000 = 6.09375e-1 
   6  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   6  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   6  Range distance     = 1.5625e-2 
   6  Number of Terms    = 8 
   6  poly_degree        = 7 
   6  poly accuracy      = 63.3889042019504340469567943323848 
   6  Rounding bit added to leading coefficient.
   6  Coeff signs are (printed) positive.

   6  t:3fe8a85c24f70659 = 7.705517503711220563488402957030843e-1
   6  t:3fe4c3abe93bcf6f = 6.488856845230496277697994356170597e-1
   6  t:3fd17c5adf5a97cd = 2.73215025061628589113241552532862e-1
   6  t:3fcd731fc83c7a47 = 2.30075810214616741870147231807664e-1
   6  t:3fceffeaca9f0346 = 2.4218497174845248371679792831479e-1
   6  t:3fd245cf163c9cc5 = 2.85510799136727212732284747476186e-1
   6  t:3fd705401d12d826 = 3.59695461647222415981547255503514e-1
   6  t:3fdc10da65869eed = 4.38528632303571807475942034848515e-1

   6  ~sqrt(t:3fe3400000000000) = t:3fe8d1c0be7f20ac = 7.75605e-1 
   6   sqrt(t:3fe3400000000000) = t:3fe8d1c0be7f20ac = 7.75605e-1 
*/

    0x00000000003821b5,  /* c7, 43 bit shift ==> 22 significant bits */
    0x000000000b82a00f,  /* c6, 37 bit shift ==> 28 significant bits */
    0x0000000248b9e2c8,  /* c5, 31 bit shift ==> 34 significant bits */
    0x0000007bffab2a7c,  /* c4, 26 bit shift ==> 39 significant bits */
    0x00001d731fc83c7a,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0008be2d6fad4be6,  /* c2, 13 bit shift ==> 52 significant bits */
    0x0530eafa4ef3dbc3,  /* c1, 06 bit shift ==> 59 significant bits */
    0x8a85c24f706597de,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   7  is the Block Number   
   7  Left endpt  (fh)      = t:3fe3800000000000 = 6.09375e-1 
   7  Right endpt (fh_next) = t:3fe4000000000000 = 6.25e-1 
   7  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   7  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   7  Range distance     = 1.5625e-2 
   7  Number of Terms    = 8 
   7  poly_degree        = 7 
   7  poly accuracy      = 63.684885573458937410622983546985 
   7  Rounding bit added to leading coefficient.
   7  Coeff signs are (printed) positive.

   7  t:3fe8fae0c15ad38a = 7.806247497997997757709746913246107e-1
   7  t:3fe47f144fe17f9b = 6.405126152203481008744201385951555e-1
   7  t:3fd0d14bbe42b5c0 = 2.62774406243661196340075103528022e-1
   7  t:3fcb9919d51de8e3 = 2.15609768925623405719346932507552e-1
   7  t:3fcc4e413ed1ca2a = 2.21138148950175848875569425966425e-1
   7  t:3fd041c837861a29 = 2.54015020582672859590948541419486e-1
   7  t:3fd3f55bcbff84ac = 3.11850499360000892024556706783045e-1
   7  t:3fd7c1b1af68e046 = 3.71197148607738464521754034874945e-1

   7  ~sqrt(t:3fe3c00000000000) = t:3fe923bd7e25164d = 7.85613e-1 
   7   sqrt(t:3fe3c00000000000) = t:3fe923bd7e25164d = 7.85613e-1 
*/

    0x00000000002f8363,  /* c7, 43 bit shift ==> 22 significant bits */
    0x0000000009faade6,  /* c6, 37 bit shift ==> 28 significant bits */
    0x00000002083906f1,  /* c5, 31 bit shift ==> 34 significant bits */
    0x000000713904fb47,  /* c4, 26 bit shift ==> 39 significant bits */
    0x00001b9919d51de9,  /* c3, 20 bit shift ==> 45 significant bits */
    0x000868a5df215ae0,  /* c2, 13 bit shift ==> 52 significant bits */
    0x051fc513f85fe6cc,  /* c1, 06 bit shift ==> 59 significant bits */
    0x8fae0c15ad389e26,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   8  is the Block Number   
   8  Left endpt  (fh)      = t:3fe4000000000000 = 6.25e-1 
   8  Right endpt (fh_next) = t:3fe4800000000000 = 6.40625e-1 
   8  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   8  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   8  Range distance     = 1.5625e-2 
   8  Number of Terms    = 8 
   8  poly_degree        = 7 
   8  poly accuracy      = 63.9734652953379079847908131637393 
   8  Rounding bit added to leading coefficient.
   8  Coeff signs are (printed) positive.

   8  t:3fe94c583ada5b53 = 7.905694150420948330460803321617647e-1
   8  t:3fe43d136248490c = 6.324555320336755073274206950806331e-1
   8  t:3fd030dc4ea0185c = 2.52982212812985932109824740998683e-1
   8  t:3fc9e7c6e3aaaa98 = 2.02385770001758624216364051973116e-1
   8  t:3fc9e7c65d1e8078 = 2.02385707348188291366110173885584e-1
   8  t:3fcd034e98161ce5 = 2.26663421879698715353189907018017e-1
   8  t:3fd15dbf2b38d4ad = 2.7134684773347824080229513665774e-1
   8  t:3fd4316adf530ad5 = 3.15516203012675085877100644715654e-1

   8  ~sqrt(t:3fe4400000000000) = t:3fe974b2334f2346 = 7.95495e-1 
   8   sqrt(t:3fe4400000000000) = t:3fe974b2334f2346 = 7.95495e-1 
*/

    0x00000000002862d6,  /* c7, 43 bit shift ==> 22 significant bits */
    0x0000000008aedf96,  /* c6, 37 bit shift ==> 28 significant bits */
    0x00000001d034e981,  /* c5, 32 bit shift ==> 33 significant bits */
    0x000000679f19747a,  /* c4, 26 bit shift ==> 39 significant bits */
    0x000019e7c6e3aaab,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0008186e27500c2e,  /* c2, 13 bit shift ==> 52 significant bits */
    0x050f44d8921242e8,  /* c1, 06 bit shift ==> 59 significant bits */
    0x94c583ada5b52922,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   9  is the Block Number   
   9  Left endpt  (fh)      = t:3fe4800000000000 = 6.40625e-1 
   9  Right endpt (fh_next) = t:3fe5000000000000 = 6.5625e-1 
   9  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   9  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   9  Range distance     = 1.5625e-2 
   9  Number of Terms    = 8 
   9  poly_degree        = 7 
   9  poly accuracy      = 64.2550045728806867318738985606403 
   9  Rounding bit added to leading coefficient.
   9  Coeff signs are (printed) positive.

   9  t:3fe99ccc999fff00 = 8.003905296791060858577725178886197e-1
   9  t:3fe3fd8077e70574 = 6.246950475544239630596929369055204e-1
   9  t:3fcf344ba86ea40c = 2.43783433191567035775554860010939e-1
   9  t:3fc85ac46a09fed8 = 1.90269996430280089748962417395273e-1
   9  t:3fc7c2b2b2bc1c55 = 1.85629212639670507272110847041269e-1
   9  t:3fc9f639f98403cf = 2.02826735338048594144600041133675e-1
   9  t:3fce533bfe94fd79 = 2.36915110881436929933237071910224e-1
   9  t:3fd13b715b9c4a63 = 2.69253100837124562230489796532673e-1

   9  ~sqrt(t:3fe4c00000000000) = t:3fe9c4a8969b7077 = 8.05256e-1 
   9   sqrt(t:3fe4c00000000000) = t:3fe9c4a8969b7077 = 8.05256e-1 
*/

    0x00000000002276e3,  /* c7, 43 bit shift ==> 22 significant bits */
    0x000000000794cf00,  /* c6, 38 bit shift ==> 27 significant bits */
    0x000000019f639f98,  /* c5, 32 bit shift ==> 33 significant bits */
    0x0000005f0acacaf0,  /* c4, 26 bit shift ==> 39 significant bits */
    0x0000185ac46a09ff,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0007cd12ea1ba903,  /* c2, 14 bit shift ==> 51 significant bits */
    0x04ff601df9c15d05,  /* c1, 06 bit shift ==> 59 significant bits */
    0x99ccc999fff002ce,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   10  is the Block Number   
   10  Left endpt  (fh)      = t:3fe5000000000000 = 6.5625e-1 
   10  Right endpt (fh_next) = t:3fe5800000000000 = 6.71875e-1 
   10  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   10  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   10  Range distance     = 1.5625e-2 
   10  Number of Terms    = 8 
   10  poly_degree        = 7 
   10  poly accuracy      = 64.5298387972969060655389045488064 
   10  Rounding bit added to leading coefficient.
   10  Coeff signs are (printed) positive.

   10  t:3fe9ec474a261264 = 8.100925873009825289275571968961032e-1
   10  t:3fe3c03650e00e01 = 6.172133998483673908951041564563411e-1
   10  t:3fce18b44a79cd7c = 2.3512891422761216207455280818861e-1
   10  t:3fc6ee40385f211a = 1.7914583923835254098875201245189e-1
   10  t:3fc5d6b6b36b227e = 1.70615041357695616585721590241498e-1
   10  t:3fc74b3b7c81187e = 1.81983409684281790806592050968593e-1
   10  t:3fca904f3d5aac05 = 2.07528977354144355822306716730097e-1
   10  t:3fcd85b34ed5a33f = 2.30642713063639676334282829772704e-1

   10  ~sqrt(t:3fe5400000000000) = t:3fea13a9cb996651 = 8.149e-1 
   10   sqrt(t:3fe5400000000000) = t:3fea13a9cb996651 = 8.149e-1 
*/

    0x00000000001d85b3,  /* c7, 44 bit shift ==> 21 significant bits */
    0x0000000006a413cf,  /* c6, 38 bit shift ==> 27 significant bits */
    0x0000000174b3b7c8,  /* c5, 32 bit shift ==> 33 significant bits */
    0x000000575adacdad,  /* c4, 26 bit shift ==> 39 significant bits */
    0x000016ee40385f21,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0007862d129e735f,  /* c2, 14 bit shift ==> 51 significant bits */
    0x04f00d943803802b,  /* c1, 06 bit shift ==> 59 significant bits */
    0x9ec474a261263d5a,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   11  is the Block Number   
   11  Left endpt  (fh)      = t:3fe5800000000000 = 6.71875e-1 
   11  Right endpt (fh_next) = t:3fe6000000000000 = 6.875e-1 
   11  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   11  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   11  Range distance     = 1.5625e-2 
   11  Number of Terms    = 8 
   11  poly_degree        = 7 
   11  poly accuracy      = 64.798279948548887938133501770224 
   11  Rounding bit added to leading coefficient.
   11  Coeff signs are (printed) positive.

   11  t:3fea3ad12a1da160 = 8.196798155377500815876694317818618e-1
   11  t:3fe38512ba21f51c = 6.099942813304184552466655211411251e-1
   11  t:3fcd0d811508b60f = 2.26974616308709597852139895624024e-1
   11  t:3fc59ee309632eda = 1.68911342223842459993148057417756e-1
   11  t:3fc41cbb1358d212 = 1.5712679333377416950967651182447e-1
   11  t:3fc4f4184569873b = 1.63699182408032788946282767850171e-1
   11  t:3fc7576330f2af36 = 1.82354353809722710764561898200142e-1
   11  t:3fc9614aaff7c093 = 1.98281608506935729443879969091658e-1

   11  ~sqrt(t:3fe5c00000000000) = t:3fea61be6cfec997 = 8.24432e-1 
   11   sqrt(t:3fe5c00000000000) = t:3fea61be6cfec997 = 8.24432e-1 
*/

    0x000000000019614b,  /* c7, 44 bit shift ==> 21 significant bits */
    0x0000000005d5d8cc,  /* c6, 38 bit shift ==> 27 significant bits */
    0x000000014f418457,  /* c5, 32 bit shift ==> 33 significant bits */
    0x0000005072ec4d63,  /* c4, 26 bit shift ==> 39 significant bits */
    0x0000159ee309632f,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0007436045422d84,  /* c2, 14 bit shift ==> 51 significant bits */
    0x04e144ae887d4708,  /* c1, 06 bit shift ==> 59 significant bits */
    0xa3ad12a1da160546,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   12  is the Block Number   
   12  Left endpt  (fh)      = t:3fe6000000000000 = 6.875e-1 
   12  Right endpt (fh_next) = t:3fe6800000000000 = 7.03125e-1 
   12  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   12  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   12  Range distance     = 1.5625e-2 
   12  Number of Terms    = 8 
   12  poly_degree        = 7 
   12  poly accuracy      = 65.060618724954200171190306572254 
   12  Rounding bit added to leading coefficient.
   12  Coeff signs are (printed) positive.

   12  t:3fea887293fd6f34 = 8.291561975888499623076229039231322e-1
   12  t:3fe34bf63d156824 = 6.030226891555270680870051713817759e-1
   12  t:3fcc11662a4d8d21 = 2.1928097787449821255462319158358e-1
   12  t:3fc469beaa238853 = 1.5947707469519175318614905706438e-1
   12  t:3fc28ead1281f679 = 1.44979127919146384432451217516569e-1
   12  t:3fc2e4e9dd7a7ffc = 1.47610886710935930598198768948226e-1
   12  t:3fc492253f43b433 = 1.6071000660977716272524457724602e-1
   12  t:3fc5e4e59edcf42c = 1.71047880716203125524028233472862e-1

   12  ~sqrt(t:3fe6400000000000) = t:3feaaeee979b4838 = 8.33854e-1 
   12   sqrt(t:3fe6400000000000) = t:3feaaeee979b4838 = 8.33854e-1 
*/

    0x000000000015e4e6,  /* c7, 44 bit shift ==> 21 significant bits */
    0x0000000005248950,  /* c6, 38 bit shift ==> 27 significant bits */
    0x000000012e4e9dd8,  /* c5, 32 bit shift ==> 33 significant bits */
    0x0000004a3ab44a08,  /* c4, 26 bit shift ==> 39 significant bits */
    0x00001469beaa2388,  /* c3, 20 bit shift ==> 45 significant bits */
    0x000704598a936348,  /* c2, 14 bit shift ==> 51 significant bits */
    0x04d2fd8f455a0912,  /* c1, 06 bit shift ==> 59 significant bits */
    0xa887293fd6f3416a,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   13  is the Block Number   
   13  Left endpt  (fh)      = t:3fe6800000000000 = 7.03125e-1 
   13  Right endpt (fh_next) = t:3fe7000000000000 = 7.1875e-1 
   13  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   13  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   13  Range distance     = 1.5625e-2 
   13  Number of Terms    = 8 
   13  poly_degree        = 7 
   13  poly accuracy      = 65.3171264359990425150291286645304 
   13  Rounding bit added to leading coefficient.
   13  Coeff signs are (printed) positive.

   13  t:3fead5336963eefc = 8.385254915624211361825125765623312e-1
   13  t:3fe314c3d92a9e8f = 5.962847939999437690372467713029181e-1
   13  t:3fcb2338ac534234 = 2.1201237119977778906778492773455e-1
   13  t:3fc34c3f0e3b0945 = 1.50764352749385955600961578548791e-1
   13  t:3fc1275446466420 = 1.34012731851528067914783477754259e-1
   13  t:3fc113b1eb7cff3b = 1.33413543686396214265461011849734e-1
   13  t:3fc22e440c89d7dd = 1.42036920664110263140805096027108e-1
   13  t:3fc2f2f9ccd61551 = 1.48040032403665945088069334778513e-1

   13  ~sqrt(t:3fe6c00000000000) = t:3feafb41f432002e = 8.43171e-1 
   13   sqrt(t:3fe6c00000000000) = t:3feafb41f432002e = 8.43171e-1 
*/

    0x000000000012f2fa,  /* c7, 44 bit shift ==> 21 significant bits */
    0x00000000048b9103,  /* c6, 38 bit shift ==> 27 significant bits */
    0x00000001113b1eb8,  /* c5, 32 bit shift ==> 33 significant bits */
    0x000000449d51191a,  /* c4, 26 bit shift ==> 39 significant bits */
    0x0000134c3f0e3b09,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0006c8ce2b14d08d,  /* c2, 14 bit shift ==> 51 significant bits */
    0x04c530f64aa7a3dd,  /* c1, 06 bit shift ==> 59 significant bits */
    0xad5336963eefba22,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   14  is the Block Number   
   14  Left endpt  (fh)      = t:3fe7000000000000 = 7.1875e-1 
   14  Right endpt (fh_next) = t:3fe7800000000000 = 7.34375e-1 
   14  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   14  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   14  Range distance     = 1.5625e-2 
   14  Number of Terms    = 8 
   14  poly_degree        = 7 
   14  poly accuracy      = 65.5680566892592585465926072095396 
   14  Rounding bit added to leading coefficient.
   14  Coeff signs are (printed) positive.

   14  t:3feb211b1c70d023 = 8.47791247890658517406131666760416e-1
   14  t:3fe2df60c5df2c9d = 5.897678246195884064280619274445172e-1
   14  t:3fca41ead084526a = 2.05136634650119832308859391112321e-1
   14  t:3fc2441dc8849fa9 = 1.42703745755395485970105917683526e-1
   14  t:3fbfc45ff2338523 = 1.24090191489376649742332192616345e-1
   14  t:3fbef006dd78cbe0 = 1.20850018568304580305337089102258e-1
   14  t:3fc01ca633dc978f = 1.25874305079545633276045905890594e-1
   14  t:3fc073ac9320d73b = 1.28530093994123922846806520881024e-1

   14  ~sqrt(t:3fe7400000000000) = t:3feb46bfc05aeb89 = 8.52386e-1 
   14   sqrt(t:3fe7400000000000) = t:3feb46bfc05aeb89 = 8.52386e-1 
*/

    0x00000000001073ad,  /* c7, 44 bit shift ==> 21 significant bits */
    0x000000000407298d,  /* c6, 38 bit shift ==> 27 significant bits */
    0x00000000f78036ec,  /* c5, 33 bit shift ==> 32 significant bits */
    0x0000003f88bfe467,  /* c4, 27 bit shift ==> 38 significant bits */
    0x000012441dc884a0,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0006907ab421149b,  /* c2, 14 bit shift ==> 51 significant bits */
    0x04b7d83177cb2731,  /* c1, 06 bit shift ==> 59 significant bits */
    0xb211b1c70d023010,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   15  is the Block Number   
   15  Left endpt  (fh)      = t:3fe7800000000000 = 7.34375e-1 
   15  Right endpt (fh_next) = t:3fe8000000000000 = 7.5e-1 
   15  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   15  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   15  Range distance     = 1.5625e-2 
   15  Number of Terms    = 8 
   15  poly_degree        = 7 
   15  poly accuracy      = 65.813646897742839627900878609535 
   15  Rounding bit added to leading coefficient.
   15  Coeff signs are (printed) positive.

   15  t:3feb6c30b83593e6 = 8.569568250501305156229155113312146e-1
   15  t:3fe2abb43c0eb0f3 = 5.834599659915781147542443441089688e-1
   15  t:3fc96c887d5abba9 = 1.98624669273582276266096498240632e-1
   15  t:3fc14f577b505fa1 = 1.35233817302602901346984462516154e-1
   15  t:3fbd76b544aabb51 = 1.15092591537842690066180753594161e-1
   15  t:3fbc1579b888e7a4 = 1.09702689697682981597706610571441e-1
   15  t:3fbca1978f7fc053 = 1.11840698751394733265098879043675e-1
   15  t:3fbca746eb9cbf1c = 1.11927444956333172421602487750514e-1

   15  ~sqrt(t:3fe7c00000000000) = t:3feb916ed68964ec = 8.61503e-1 
   15   sqrt(t:3fe7c00000000000) = t:3feb916ed68964ec = 8.61503e-1 
*/

    0x00000000000e53a3,  /* c7, 45 bit shift ==> 20 significant bits */
    0x00000000039432f2,  /* c6, 39 bit shift ==> 26 significant bits */
    0x00000000e0abcdc4,  /* c5, 33 bit shift ==> 32 significant bits */
    0x0000003aed6a8955,  /* c4, 27 bit shift ==> 38 significant bits */
    0x0000114f577b5060,  /* c3, 20 bit shift ==> 45 significant bits */
    0x00065b221f56aeea,  /* c2, 14 bit shift ==> 51 significant bits */
    0x04aaed0f03ac3cbc,  /* c1, 06 bit shift ==> 59 significant bits */
    0xb6c30b83593e63ea,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   16  is the Block Number   
   16  Left endpt  (fh)      = t:3fe8000000000000 = 7.5e-1 
   16  Right endpt (fh_next) = t:3fe8800000000000 = 7.65625e-1 
   16  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   16  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   16  Range distance     = 1.5625e-2 
   16  Number of Terms    = 8 
   16  poly_degree        = 7 
   16  poly accuracy      = 66.0541196301553704996583652065542 
   16  Rounding bit added to leading coefficient.
   16  Coeff signs are (printed) positive.

   16  t:3febb67ae8584caa = 8.660254037844386467868626477972782e-1
   16  t:3fe279a74590331b = 5.773502691896256715903788803156971e-1
   16  t:3fc8a2345cc03284 = 1.92450089729749968968028350779775e-1
   16  t:3fc06c22e85ccb5a = 1.28300059755555309685655721030351e-1
   16  t:3fbb5ee4930fad85 = 1.06916700271247289643315736551443e-1
   16  t:3fb98b9f1f332451 = 9.97867060824699928642451431104465e-2
   16  t:3fb980a1b0b007ce = 9.96190124861009210403633117036915e-2
   16  t:3fb906312e7e35ca = 9.77507341869660282496971685783915e-2

   16  ~sqrt(t:3fe8400000000000) = t:3febdb55b550fdbc = 8.70524e-1 
   16   sqrt(t:3fe8400000000000) = t:3febdb55b550fdbc = 8.70524e-1 
*/

    0x00000000000c8319,  /* c7, 45 bit shift ==> 20 significant bits */
    0x0000000003301436,  /* c6, 39 bit shift ==> 26 significant bits */
    0x00000000cc5cf8fa,  /* c5, 33 bit shift ==> 32 significant bits */
    0x00000036bdc9261f,  /* c4, 27 bit shift ==> 38 significant bits */
    0x0000106c22e85ccb,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0006288d17300ca1,  /* c2, 14 bit shift ==> 51 significant bits */
    0x049e69d1640cc6de,  /* c1, 06 bit shift ==> 59 significant bits */
    0xbb67ae8584caa73c,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   17  is the Block Number   
   17  Left endpt  (fh)      = t:3fe8800000000000 = 7.65625e-1 
   17  Right endpt (fh_next) = t:3fe9000000000000 = 7.8125e-1 
   17  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   17  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   17  Range distance     = 1.5625e-2 
   17  Number of Terms    = 8 
   17  poly_degree        = 7 
   17  poly accuracy      = 66.2896838232417272327777064315088 
   17  Rounding bit added to leading coefficient.
   17  Coeff signs are (printed) positive.

   17  t:3fec000000000000 = 8.75e-1
   17  t:3fe2492492492492 = 5.71428571428571348820614483887681e-1
   17  t:3fc7e225515a3ffc = 1.86588921282691333507946021552648e-1
   17  t:3fbf31d2b32990a6 = 1.21853989353953718951660729896691e-1
   17  t:3fb97709cec09d87 = 9.94726304785357101360585528604386e-2
   17  t:3fb748239c538448 = 9.09445053726055651160628014173515e-2
   17  t:3fb6c5133858f24a = 8.89446270529755943730679766667802e-2
   17  t:3fb5ea45cb1b0bb5 = 8.5605966650333118749829040827759e-2

   17  ~sqrt(t:3fe8c00000000000) = t:3fec247a85fe81fa = 8.79453e-1 
   17   sqrt(t:3fe8c00000000000) = t:3fec247a85fe81fa = 8.79453e-1 
*/

    0x00000000000af523,  /* c7, 45 bit shift ==> 20 significant bits */
    0x0000000002d8a267,  /* c6, 39 bit shift ==> 26 significant bits */
    0x00000000ba411ce3,  /* c5, 33 bit shift ==> 32 significant bits */
    0x00000032ee139d81,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000f98e95994c8,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0005f88954568fff,  /* c2, 14 bit shift ==> 51 significant bits */
    0x0492492492492464,  /* c1, 06 bit shift ==> 59 significant bits */
    0xc000000000000000,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   18  is the Block Number   
   18  Left endpt  (fh)      = t:3fe9000000000000 = 7.8125e-1 
   18  Right endpt (fh_next) = t:3fe9800000000000 = 7.96875e-1 
   18  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   18  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   18  Range distance     = 1.5625e-2 
   18  Number of Terms    = 8 
   18  poly_degree        = 7 
   18  poly accuracy      = 66.5205358728572117084783594283328 
   18  Rounding bit added to leading coefficient.
   18  Coeff signs are (printed) positive.

   18  t:3fec48c6001f0ac0 = 8.838834764831844055315776542691708e-1
   18  t:3fe21a1851ff6309 = 5.656854249492379508972017543300126e-1
   18  t:3fc72ba43fff2a12 = 1.81019335983663643666226328310387e-1
   18  t:3fbda88051b6431a = 1.15852374982079816608676343242523e-1
   18  t:3fb7ba000e054e2e = 9.26818880300792362328843494723163e-2
   18  t:3fb5423272228fe1 = 8.3041336884491133084296946714753e-2
   18  t:3fb4606536b46f64 = 7.95958765560818549167115994180666e-2
   18  t:3fb33e4bc9a831fa = 7.51693122221651860862868567425554e-2

   18  ~sqrt(t:3fe9400000000000) = t:3fec6ce322982a3f = 8.88292e-1 
   18   sqrt(t:3fe9400000000000) = t:3fec6ce322982a3f = 8.88292e-1 
*/

    0x0000000000099f26,  /* c7, 45 bit shift ==> 20 significant bits */
    0x00000000028c0ca7,  /* c6, 39 bit shift ==> 26 significant bits */
    0x00000000aa119391,  /* c5, 33 bit shift ==> 32 significant bits */
    0x0000002f74001c0b,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000ed44028db22,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0005cae90fffca84,  /* c2, 14 bit shift ==> 51 significant bits */
    0x048686147fd8c25c,  /* c1, 06 bit shift ==> 59 significant bits */
    0xc48c6001f0abfb4c,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   19  is the Block Number   
   19  Left endpt  (fh)      = t:3fe9800000000000 = 7.96875e-1 
   19  Right endpt (fh_next) = t:3fea000000000000 = 8.125e-1 
   19  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   19  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   19  Range distance     = 1.5625e-2 
   19  Number of Terms    = 8 
   19  poly_degree        = 7 
   19  poly accuracy      = 66.7468606180646701301488014027395 
   19  Rounding bit added to leading coefficient.
   19  Coeff signs are (printed) positive.

   19  t:3fec90d29d2d43ce = 8.926785535678562497692752064626376e-1
   19  t:3fe1ec70124e98f9 = 5.60112033611203862144573700776462e-1
   19  t:3fc67e0a2103373d = 1.75721422309317442322310759417192e-1
   19  t:3fbc39c66f86ac93 = 1.1025657866291486359556529850412e-1
   19  t:3fb62346211c5455 = 8.64757376514984807844787194353042e-2
   19  t:3fb37238005ac12b = 7.59615898957732129919014595065274e-2
   19  t:3fb246611c333222 = 7.13864034507385656740932264319177e-2
   19  t:3fb0f0bff609aed5 = 6.61735511472970176386843368931956e-2

   19  ~sqrt(t:3fe9c00000000000) = t:3fecb4951b558d17 = 8.97044e-1 
   19   sqrt(t:3fe9c00000000000) = t:3fecb4951b558d17 = 8.97044e-1 
*/

    0x0000000000087860,  /* c7, 45 bit shift ==> 20 significant bits */
    0x000000000248cc24,  /* c6, 39 bit shift ==> 26 significant bits */
    0x000000009b91c003,  /* c5, 33 bit shift ==> 32 significant bits */
    0x0000002c468c4239,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000e1ce337c356,  /* c3, 21 bit shift ==> 44 significant bits */
    0x00059f828840cdcf,  /* c2, 14 bit shift ==> 51 significant bits */
    0x047b1c0493a63e39,  /* c1, 06 bit shift ==> 59 significant bits */
    0xc90d29d2d43cd84a,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   20  is the Block Number   
   20  Left endpt  (fh)      = t:3fea000000000000 = 8.125e-1 
   20  Right endpt (fh_next) = t:3fea800000000000 = 8.28125e-1 
   20  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   20  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   20  Range distance     = 1.5625e-2 
   20  Number of Terms    = 8 
   20  poly_degree        = 7 
   20  poly accuracy      = 66.9688322304200925127740729570441 
   20  Rounding bit added to leading coefficient.
   20  Coeff signs are (printed) positive.

   20  t:3fecd82b446159f3 = 9.013878188659973232817190780252758e-1
   20  t:3fe1c01aa03be895 = 5.547001962252290707200766406437253e-1
   20  t:3fc5d8be4f0e9e60 = 1.70676983453847516176591844749844e-1
   20  t:3fbae36061261326 = 1.05031989782287205918904528234581e-1
   20  t:3fb4aee786d3ac0a = 8.07938293616389533046578431962903e-2
   20  t:3fb1d1af0a3e5c95 = 6.96057701119222257211808548016396e-2
   20  t:3fb06cb939ccb9a0 = 6.41589895355765314977547139618785e-2
   20  t:3fade64169455f76 = 5.83973351482986292675624040438009e-2

   20  ~sqrt(t:3fea400000000000) = t:3fecfb95bb9dcc0c = 9.05711e-1 
   20   sqrt(t:3fea400000000000) = t:3fecfb95bb9dcc0c = 9.05711e-1 
*/

    0x0000000000077990,  /* c7, 46 bit shift ==> 19 significant bits */
    0x00000000020d9727,  /* c6, 39 bit shift ==> 26 significant bits */
    0x000000008e8d7852,  /* c5, 33 bit shift ==> 32 significant bits */
    0x000000295dcf0da7,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000d71b030930a,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0005762f93c3a798,  /* c2, 14 bit shift ==> 51 significant bits */
    0x047006a80efa2554,  /* c1, 06 bit shift ==> 59 significant bits */
    0xcd82b446159f3610,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   21  is the Block Number   
   21  Left endpt  (fh)      = t:3fea800000000000 = 8.28125e-1 
   21  Right endpt (fh_next) = t:3feb000000000000 = 8.4375e-1 
   21  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   21  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   21  Range distance     = 1.5625e-2 
   21  Number of Terms    = 8 
   21  poly_degree        = 7 
   21  poly accuracy      = 67.1866150194763145380428570052374 
   21  Rounding bit added to leading coefficient.
   21  Coeff signs are (printed) positive.

   21  t:3fed1ed52076fbe9 = 9.100137361600647839120388493672209e-1
   21  t:3fe19507ecf5b9e8 = 5.494422557947560513923190850249512e-1
   21  t:3fc53b350ad1bfe6 = 1.65869360239866356774760501602284e-1
   21  t:3fb9a344e1760089 = 1.00147538227249328272958767138689e-1
   21  t:3fb35968fcc8f683 = 7.55830399657160641996148965626734e-2
   21  t:3fb05af6c74847a6 = 6.38880001572759992570639357711837e-2
   21  t:3fad9569c122103d = 5.77805565126543223639793162710321e-2
   21  t:3faa72bd3525f2f7 = 5.16566398027630732501689833635616e-2

   21  ~sqrt(t:3feac00000000000) = t:3fed41ea0e98af91 = 9.14296e-1 
   21   sqrt(t:3feac00000000000) = t:3fed41ea0e98af91 = 9.14296e-1 
*/

    0x0000000000069caf,  /* c7, 46 bit shift ==> 19 significant bits */
    0x0000000001d9569c,  /* c6, 40 bit shift ==> 25 significant bits */
    0x0000000082d7b63a,  /* c5, 33 bit shift ==> 32 significant bits */
    0x00000026b2d1f992,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000cd1a270bb00,  /* c3, 21 bit shift ==> 44 significant bits */
    0x00054ecd42b46ff9,  /* c2, 14 bit shift ==> 51 significant bits */
    0x046541fb3d6e7a0d,  /* c1, 06 bit shift ==> 59 significant bits */
    0xd1ed52076fbe93ea,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   22  is the Block Number   
   22  Left endpt  (fh)      = t:3feb000000000000 = 8.4375e-1 
   22  Right endpt (fh_next) = t:3feb800000000000 = 8.59375e-1 
   22  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   22  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   22  Range distance     = 1.5625e-2 
   22  Number of Terms    = 8 
   22  poly_degree        = 7 
   22  poly accuracy      = 67.400364163560256548284184333268 
   22  Rounding bit added to leading coefficient.
   22  Coeff signs are (printed) positive.

   22  t:3fed64d51e0db1c6 = 9.185586535436917868160250355558105e-1
   22  t:3fe16b28f55d72d4 = 5.443310539518173164080794279584552e-1
   22  t:3fc4a4ee2c48cc98 = 1.61283275244930692079656231463503e-1
   22  t:3fb8779f04f6746b = 9.55752741924286512066751518579277e-2
   22  t:3fb21fb80c9fcb9f = 7.07964926548769661016373075379526e-2
   22  t:3fae12602e52c2d5 = 5.87339455172518976978966818297545e-2
   22  t:3faab1d8403a7a9e = 5.21380976108407469358108771162463e-2
   22  t:3fa772d38d4ef626 = 4.57979307170542214403962007207571e-2

   22  ~sqrt(t:3feb400000000000) = t:3fed8796e35ddbb2 = 9.22801e-1 
   22   sqrt(t:3feb400000000000) = t:3fed8796e35ddbb2 = 9.22801e-1 
*/

    0x000000000005dcb5,  /* c7, 46 bit shift ==> 19 significant bits */
    0x0000000001ab1d84,  /* c6, 40 bit shift ==> 25 significant bits */
    0x00000000784980b9,  /* c5, 34 bit shift ==> 31 significant bits */
    0x000000243f701940,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000c3bcf827b3a,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0005293b8b123326,  /* c2, 14 bit shift ==> 51 significant bits */
    0x045aca3d575cb4e9,  /* c1, 06 bit shift ==> 59 significant bits */
    0xd64d51e0db1c5bb8,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   23  is the Block Number   
   23  Left endpt  (fh)      = t:3feb800000000000 = 8.59375e-1 
   23  Right endpt (fh_next) = t:3fec000000000000 = 8.75e-1 
   23  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   23  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   23  Range distance     = 1.5625e-2 
   23  Number of Terms    = 8 
   23  poly_degree        = 7 
   23  poly accuracy      = 67.6102263741455664654888134928033 
   23  Rounding bit added to leading coefficient.
   23  Coeff signs are (printed) positive.

   23  t:3fedaa2fefaae1d8 = 9.270248108869578685872769874265487e-1
   23  t:3fe1426fac0654da = 5.393598899705936352026378055590783e-1
   23  t:3fc41573fb5fc762 = 1.5690469526412713497764538778112e-1
   23  t:3fb75ec81fc0ceb0 = 9.12900044939373224268876379217108e-2
   23  t:3fb0ff1d1515a0c7 = 6.63927246547500818848477031897115e-2
   23  t:3fabb0410ec430ed = 5.40790873074870985978668778970668e-2
   23  t:3fa82220054ab2c1 = 4.71353537044243528592534463184105e-2
   23  t:3fa4d5aba510724b = 4.06926764482916327065069230645156e-2

   23  ~sqrt(t:3febc00000000000) = t:3fedcca0d0cbf408 = 9.31229e-1 
   23   sqrt(t:3febc00000000000) = t:3fedcca0d0cbf408 = 9.31229e-1 
*/

    0x000000000005356b,  /* c7, 46 bit shift ==> 19 significant bits */
    0x0000000001822200,  /* c6, 40 bit shift ==> 25 significant bits */
    0x000000006ec1043b,  /* c5, 34 bit shift ==> 31 significant bits */
    0x00000021fe3a2a2b,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000baf640fe067,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0005055cfed7f1d8,  /* c2, 14 bit shift ==> 51 significant bits */
    0x04509beb0195369c,  /* c1, 06 bit shift ==> 59 significant bits */
    0xdaa2fefaae1d7f60,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   24  is the Block Number   
   24  Left endpt  (fh)      = t:3fec000000000000 = 8.75e-1 
   24  Right endpt (fh_next) = t:3fec800000000000 = 8.90625e-1 
   24  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   24  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   24  Range distance     = 1.5625e-2 
   24  Number of Terms    = 8 
   24  poly_degree        = 7 
   24  poly accuracy      = 67.8163405007782675517974194562265 
   24  Rounding bit added to leading coefficient.
   24  Coeff signs are (printed) positive.

   24  t:3fedeeea11683f49 = 9.354143466934853464139591749937352e-1
   24  t:3fe11acee560242a = 5.345224838248487397884302352313313e-1
   24  t:3fc38c5a2ab6ff26 = 1.52720709664202649986594097220038e-1
   24  t:3fb6574279df3bfb = 8.72689769305309732621927197582234e-2
   24  t:3fafea5ecb065ca8 = 6.23349783738203477167919355772518e-2
   24  t:3fa9883437e227aa = 4.9867278882700216353012845696413e-2
   24  t:3fa5db79a1911fc4 = 4.26900872922142664915817582282909e-2
   24  t:3fa28d1f34465564 = 3.6232924586481000711786493173605e-2

   24  ~sqrt(t:3fec400000000000) = t:3fee110c39105faf = 9.39581e-1 
   24   sqrt(t:3fec400000000000) = t:3fee110c39105faf = 9.39581e-1 
*/

    0x000000000004a348,  /* c7, 46 bit shift ==> 19 significant bits */
    0x00000000015db79a,  /* c6, 40 bit shift ==> 25 significant bits */
    0x000000006620d0e0,  /* c5, 34 bit shift ==> 31 significant bits */
    0x0000001fea5ecb06,  /* c4, 28 bit shift ==> 37 significant bits */
    0x00000b2ba13cef9e,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0004e3168aadbfca,  /* c2, 14 bit shift ==> 51 significant bits */
    0x0446b3b958090a61,  /* c1, 06 bit shift ==> 59 significant bits */
    0xdeeea11683f49206,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   25  is the Block Number   
   25  Left endpt  (fh)      = t:3fec800000000000 = 8.90625e-1 
   25  Right endpt (fh_next) = t:3fed000000000000 = 9.0625e-1 
   25  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   25  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   25  Range distance     = 1.5625e-2 
   25  Number of Terms    = 8 
   25  poly_degree        = 7 
   25  poly accuracy      = 68.0188380831164097304419606458168 
   25  Rounding bit added to leading coefficient.
   25  Coeff signs are (printed) positive.

   25  t:3fee3307cc56cf5c = 9.437293044088437121556280084977431e-1
   25  t:3fe0f43a45cdedad = 5.298129428260174966888902681194651e-1
   25  t:3fc3093cf00f9ea6 = 1.4871942254761910072989334469229e-1
   25  t:3fb55fb4b3a4026d = 8.34916056228480290323846514655148e-2
   25  t:3fadff962ab1f4cc = 5.85905959241955474574975980261993e-2
   25  t:3fa793ce02e73ebe = 4.60495356124943473494844255189395e-2
   25  t:3fa3d4a8d7deaa9b = 3.8731838561337295920924007203157e-2
   25  t:3fa08d424f66d898 = 3.2327720825763241478591897282158e-2

   25  ~sqrt(t:3fecc00000000000) = t:3fee54dd4ce75f1e = 9.47859e-1 
   25   sqrt(t:3fecc00000000000) = t:3fee54dd4ce75f1e = 9.47859e-1 
*/

    0x0000000000042351,  /* c7, 46 bit shift ==> 19 significant bits */
    0x00000000013d4a8d,  /* c6, 40 bit shift ==> 25 significant bits */
    0x000000005e4f380c,  /* c5, 34 bit shift ==> 31 significant bits */
    0x0000001dff962ab2,  /* c4, 28 bit shift ==> 37 significant bits */
    0x00000aafda59d201,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0004c24f3c03e7a9,  /* c2, 14 bit shift ==> 51 significant bits */
    0x043d0e91737b6b26,  /* c1, 06 bit shift ==> 59 significant bits */
    0xe3307cc56cf5bdc2,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   26  is the Block Number   
   26  Left endpt  (fh)      = t:3fed000000000000 = 9.0625e-1 
   26  Right endpt (fh_next) = t:3fed800000000000 = 9.21875e-1 
   26  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   26  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   26  Range distance     = 1.5625e-2 
   26  Number of Terms    = 8 
   26  poly_degree        = 7 
   26  poly accuracy      = 68.2178438551675728301427476586257 
   26  Rounding bit added to leading coefficient.
   26  Coeff signs are (printed) positive.

   26  t:3fee768d399dc470 = 9.51971638232988535683991304647833e-1
   26  t:3fe0cea6317186dc = 5.252257314388902037917243592612948e-1
   26  t:3fc28bc0368ee8c4 = 1.4488985694862867130427996897879e-1
   26  t:3fb476e5c08c6151 = 7.99392314041871403115747593548512e-2
   26  t:3fac3a10a0e7271c = 5.513050045153830355719828427985e-2
   26  t:3fa5cd70f1d6da5d = 4.2583016892810057692263583928316e-2
   26  t:3fa205be69ba769f = 3.5200071722312422110092193158759e-2
   26  t:3f9d98038b2bf9bb = 2.8900199288722321067351267442902e-2

   26  ~sqrt(t:3fed400000000000) = t:3fee98180e9b47f2 = 9.56066e-1 
   26   sqrt(t:3fed400000000000) = t:3fee98180e9b47f2 = 9.56066e-1 
*/

    0x000000000003b300,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000001205be7,  /* c6, 40 bit shift ==> 25 significant bits */
    0x000000005735c3c7,  /* c5, 34 bit shift ==> 31 significant bits */
    0x0000001c3a10a0e7,  /* c4, 28 bit shift ==> 37 significant bits */
    0x00000a3b72e04631,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0004a2f00da3ba31,  /* c2, 14 bit shift ==> 51 significant bits */
    0x0433a98c5c61b710,  /* c1, 06 bit shift ==> 59 significant bits */
    0xe768d399dc46f95c,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   27  is the Block Number   
   27  Left endpt  (fh)      = t:3fed800000000000 = 9.21875e-1 
   27  Right endpt (fh_next) = t:3fee000000000000 = 9.375e-1 
   27  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   27  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   27  Range distance     = 1.5625e-2 
   27  Number of Terms    = 8 
   27  poly_degree        = 7 
   27  poly accuracy      = 68.4134762067564585231154519425194 
   27  Rounding bit added to leading coefficient.
   27  Coeff signs are (printed) positive.

   27  t:3feeb97e455b9edb = 9.601432184835760219490490008364958e-1
   27  t:3fe0aa07bd7b7488 = 5.207556439232954494794602950946683e-1
   27  t:3fc2138ee792eb6b = 1.41221869538493769385230011681465e-1
   27  t:3fb39bb963465cc5 = 7.65949122781988848022234790680063e-2
   27  t:3faa9667bb0f01ee = 5.19287505953832491934732580596279e-2
   27  t:3fa43030dd35ec65 = 3.94301672012822642141927423353742e-2
   27  t:3fa067e488d6155e = 3.2042638496060798984323625057669e-2
   27  t:3f9a81a701bfff4f = 2.5885209543047789187525083501318e-2

   27  ~sqrt(t:3fedc00000000000) = t:3feedac054c8f94c = 9.64203e-1 
   27   sqrt(t:3fedc00000000000) = t:3feedac054c8f94c = 9.64203e-1 
*/

    0x0000000000035035,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000001067e49,  /* c6, 40 bit shift ==> 25 significant bits */
    0x0000000050c0c375,  /* c5, 34 bit shift ==> 31 significant bits */
    0x0000001a9667bb0f,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000009cddcb1a32e,  /* c3, 21 bit shift ==> 44 significant bits */
    0x000484e3b9e4badb,  /* c2, 14 bit shift ==> 51 significant bits */
    0x042a81ef5edd220b,  /* c1, 06 bit shift ==> 59 significant bits */
    0xeb97e455b9edb666,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   28  is the Block Number   
   28  Left endpt  (fh)      = t:3fee000000000000 = 9.375e-1 
   28  Right endpt (fh_next) = t:3fee800000000000 = 9.53125e-1 
   28  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   28  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   28  Range distance     = 1.5625e-2 
   28  Number of Terms    = 8 
   28  poly_degree        = 7 
   28  poly accuracy      = 68.6058476067736197184618236527932 
   28  Rounding bit added to leading coefficient.
   28  Coeff signs are (printed) positive.

   28  t:3feefbdeb14f4eda = 9.682458365518542213034453025599646e-1
   28  t:3fe08654a2d4f6da = 5.163977794943222336676580397352154e-1
   28  t:3fc1a05a47498c7c = 1.37706074531795408553503171078525e-1
   28  t:3fb2cd2d18c9883b = 7.34432397380552623097904607618602e-2
   28  t:3fa911915beacf3e = 4.89621567443507700618653567109506e-2
   28  t:3fa2b7ba8fddda7a = 3.6557989179461139515967676993924e-2
   28  t:3f9dea67ed24648b = 2.9214500283249604938677341896269e-2
   28  t:3f97c8eab6023cdf = 2.3227374419147457947263887313716e-2

   28  ~sqrt(t:3fee400000000000) = t:3fef1cd9cceef239 = 9.72272e-1 
   28   sqrt(t:3fee400000000000) = t:3fef1cd9cceef239 = 9.72272e-1 
*/

    0x000000000002f91d,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000000ef533f,  /* c6, 41 bit shift ==> 24 significant bits */
    0x000000004adeea3f,  /* c5, 34 bit shift ==> 31 significant bits */
    0x0000001911915beb,  /* c4, 28 bit shift ==> 37 significant bits */
    0x00000966968c64c4,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0004681691d2631f,  /* c2, 14 bit shift ==> 51 significant bits */
    0x04219528b53db696,  /* c1, 06 bit shift ==> 59 significant bits */
    0xefbdeb14f4ed9b18,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   29  is the Block Number   
   29  Left endpt  (fh)      = t:3fee800000000000 = 9.53125e-1 
   29  Right endpt (fh_next) = t:3fef000000000000 = 9.6875e-1 
   29  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   29  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   29  Range distance     = 1.5625e-2 
   29  Number of Terms    = 8 
   29  poly_degree        = 7 
   29  poly accuracy      = 68.7950649914394699898054167657199 
   29  Rounding bit added to leading coefficient.
   29  Coeff signs are (printed) positive.

   29  t:3fef3db2174e7468 = 9.762812094883317992860365108764853e-1
   29  t:3fe0638331ff307a = 5.121475197315838790487058096445594e-1
   29  t:3fc131d9629e9d02 = 1.34333775667279596018706053217606e-1
   29  t:3fb20a556339fe44 = 7.04701773884091616669792142169104e-2
   29  t:3fa7a8d49d177e04 = 4.62099496614847588958803481506976e-2
   29  t:3fa1603f13530899 = 3.3937426670960838882737083468943e-2
   29  t:3f9b51207cbde6ce = 2.6676662076602401989455998557177e-2
   29  t:3f95616f2fd80f70 = 2.0879494948544630484612259768706e-2

   29  ~sqrt(t:3feec00000000000) = t:3fef5e67fdcbdf44 = 9.80274e-1 
   29   sqrt(t:3feec00000000000) = t:3fef5e67fdcbdf44 = 9.80274e-1 
*/

    0x000000000002ac2e,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000000da8904,  /* c6, 41 bit shift ==> 24 significant bits */
    0x000000004580fc4d,  /* c5, 34 bit shift ==> 31 significant bits */
    0x00000017a8d49d17,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000009052ab19cff,  /* c3, 21 bit shift ==> 44 significant bits */
    0x00044c7658a7a740,  /* c2, 14 bit shift ==> 51 significant bits */
    0x0418e0cc7fcc1e74,  /* c1, 06 bit shift ==> 59 significant bits */
    0xf3db2174e7468786,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   30  is the Block Number   
   30  Left endpt  (fh)      = t:3fef000000000000 = 9.6875e-1 
   30  Right endpt (fh_next) = t:3fef800000000000 = 9.84375e-1 
   30  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   30  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   30  Range distance     = 1.5625e-2 
   30  Number of Terms    = 8 
   30  poly_degree        = 7 
   30  poly accuracy      = 68.981230121430022531429626900304 
   30  Rounding bit added to leading coefficient.
   30  Coeff signs are (printed) positive.

   30  t:3fef7efbeb8d4f12 = 9.842509842514763774689451336641355e-1
   30  t:3fe0418a4806de7d = 5.080005080007619874035013074475842e-1
   30  t:3fc0c7c88c6a2d5b = 1.31096905290500532738568253976474e-1
   30  t:3fb1525b679cde56 = 6.76629188500269304252132847310452e-2
   30  t:3fa659c02ee52e9d = 4.36534936185044338093281298535109e-2
   30  t:3fa026621132d68a = 3.1542839621960429918277055497122e-2
   30  t:3f98fb138c161a5b = 2.4395280289832716833850890895963e-2
   30  t:3f9340a19771a266 = 1.88012360271464731096283584319e-2

   30  ~sqrt(t:3fef400000000000) = t:3fef9f6e4990f227 = 9.88212e-1 
   30   sqrt(t:3fef400000000000) = t:3fef9f6e4990f227 = 9.88212e-1 
*/

    0x0000000000026814,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000000c7d89c,  /* c6, 41 bit shift ==> 24 significant bits */
    0x0000000040998845,  /* c5, 34 bit shift ==> 31 significant bits */
    0x0000001659c02ee5,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000008a92db3ce6f,  /* c3, 21 bit shift ==> 44 significant bits */
    0x000431f2231a8b57,  /* c2, 14 bit shift ==> 51 significant bits */
    0x0410629201b79f2e,  /* c1, 06 bit shift ==> 59 significant bits */
    0xf7efbeb8d4f11e18,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   31  is the Block Number   
   31  Left endpt  (fh)      = t:3fef800000000000 = 9.84375e-1 
   31  Right endpt (fh_next) = t:3ff0000000000000 = 1.0 
   31  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   31  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   31  Range distance     = 1.5625e-2 
   31  Number of Terms    = 8 
   31  poly_degree        = 7 
   31  poly accuracy      = 69.1644399105245967806874375011259 
   31  Rounding bit added to leading coefficient.
   31  Coeff signs are (printed) positive.

   31  t:3fefbfbf7ebc755f = 9.92156741649221471455576820686062e-1
   31  t:3fe02061446ffa9a = 5.039526306789696239590847781641969e-1
   31  t:3fc061e8e8103932 = 1.27987969696229661882265829508931e-1
   31  t:3fb0a47ad354549d = 6.50097623768765725288821394345362e-2
   31  t:3fa52221fe0338a0 = 4.12760374616578653848603282228158e-2
   31  t:3f9e0e5593c10b80 = 2.9351555960839713794183550299444e-2
   31  t:3f96e0895a66718a = 2.2340913908565998251937699536906e-2
   31  t:3f915d72cb5cf81b = 1.695803991537312750432359154118e-2

   31  ~sqrt(t:3fefc00000000000) = t:3fefdfefefebe3d6 = 9.96086e-1 
   31   sqrt(t:3fefc00000000000) = t:3fefdfefefebe3d6 = 9.96086e-1 
*/

    0x0000000000022bae,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000000b7044b,  /* c6, 41 bit shift ==> 24 significant bits */
    0x000000003c1cab28,  /* c5, 35 bit shift ==> 30 significant bits */
    0x000000152221fe03,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000008523d69aa2a,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0004187a3a040e4c,  /* c2, 14 bit shift ==> 51 significant bits */
    0x040818511bfea665,  /* c1, 06 bit shift ==> 59 significant bits */
    0xfbfbf7ebc755e936,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   32  is the Block Number   
   32  Left endpt  (fh)      = t:3fe0000000000000 = 5e-1 
   32  Right endpt (fh_next) = t:3fe0800000000000 = 5.15625e-1 
   32  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   32  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   32  Range distance     = 1.5625e-2 
   32  Number of Terms    = 8 
   32  poly_degree        = 7 
   32  poly accuracy      = 61.4333308081880882021778868034682 
   32  Rounding bit added to leading coefficient.
   32  Coeff signs are (printed) positive.

   32  t:3ff0000000000000 = 1.0000000000000000003252606517457
   32  t:3fefffffffffffe8 = 9.999999999999973557393215251032359e-1
   32  t:3fdfffffffff04b8 = 4.999999999964290774709732567693266e-1
   32  t:3fdffffffe06ea05 = 4.999999981625083578945251822078788e-1
   32  t:3fe3ffff0685199f = 6.249995353071433034633161418547331e-1
   32  t:3febff79ed705301 = 8.749360692478093226684583705310416e-1
   32  t:3ff4ebf6bc888f21 = 1.3076083530986085651627928716501
   32  t:3ffdd98e64369e1f = 1.8656143107017511408940793615763

   32  ~sqrt(t:3ff0400000000000) = t:3ff01fe03f61bad0 = 1.00778 
   32   sqrt(t:3ff0400000000000) = t:3ff01fe03f61bad0 = 1.00778 
*/

    0x000000000077663a,  /* c7, 42 bit shift ==> 23 significant bits */
    0x0000000014ebf6b8,  /* c6, 36 bit shift ==> 29 significant bits */
    0x000000037fef3dae,  /* c5, 31 bit shift ==> 34 significant bits */
    0x0000009ffff83429,  /* c4, 25 bit shift ==> 40 significant bits */
    0x00001ffffffe06ea,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0007ffffffffc12e,  /* c2, 14 bit shift ==> 51 significant bits */
    0x03fffffffffffd06,  /* c1, 07 bit shift ==> 58 significant bits */
    0x0000000000000006,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   33  is the Block Number   
   33  Left endpt  (fh)      = t:3fe0800000000000 = 5.15625e-1 
   33  Right endpt (fh_next) = t:3fe1000000000000 = 5.3125e-1 
   33  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   33  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   33  Range distance     = 1.5625e-2 
   33  Number of Terms    = 8 
   33  poly_degree        = 7 
   33  poly accuracy      = 61.7831475779178936007820005749765 
   33  Rounding bit added to leading coefficient.
   33  Coeff signs are (printed) positive.

   33  t:3ff03f81f636b80c = 1.0155048005794950452713998334531
   33  t:3fef82ec882c0f88 = 9.84731927834659755149632892612388e-1
   33  t:3fde8e78c21a6dbf = 4.774457831897186759699102526210979e-1
   33  t:3fdda16d55cde7dd = 4.62977727692871562242306338053055e-1
   33  t:3fe1f539bbdb18bc = 5.611847561892982329321936940669246e-1
   33  t:3fe860ab47d5c09a = 7.618004229571113714134140970646314e-1
   33  t:3ff1ab0663608055 = 1.1042541391289165701380947659516
   33  t:3ff8831ab4c9cb2a = 1.5320078908959638594152255497427

   33  ~sqrt(t:3ff0c00000000000) = t:3ff05ee68efad48b = 1.02317 
   33   sqrt(t:3ff0c00000000000) = t:3ff05ee68efad48b = 1.02317 
*/

    0x0000000000620c6b,  /* c7, 42 bit shift ==> 23 significant bits */
    0x0000000011ab0660,  /* c6, 36 bit shift ==> 29 significant bits */
    0x000000030c1568fb,  /* c5, 31 bit shift ==> 34 significant bits */
    0x0000008fa9cdded9,  /* c4, 25 bit shift ==> 40 significant bits */
    0x00001da16d55cde8,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0007a39e30869b70,  /* c2, 14 bit shift ==> 51 significant bits */
    0x03f05d910581f0f5,  /* c1, 07 bit shift ==> 58 significant bits */
    0x03f81f636b80bbc8,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   34  is the Block Number   
   34  Left endpt  (fh)      = t:3fe1000000000000 = 5.3125e-1 
   34  Right endpt (fh_next) = t:3fe1800000000000 = 5.46875e-1 
   34  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   34  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   34  Range distance     = 1.5625e-2 
   34  Number of Terms    = 8 
   34  poly_degree        = 7 
   34  poly accuracy      = 62.1226715379880487490852110700109 
   34  Rounding bit added to leading coefficient.
   34  Coeff signs are (printed) positive.

   34  t:3ff07e0f66afed07 = 1.0307764064044151376296418187728
   34  t:3fef0b6848d2af0d = 9.701425001453302043256249342917386e-1
   34  t:3fdd37e9adf2d71a = 4.565376471249337006898076640748485e-1
   34  t:3fdb7feafccfbd27 = 4.296824902402981936888875375002428e-1
   34  t:3fe02d20326864e8 = 5.055085167433874593682051334919691e-1
   34  t:3fe550360f3f306e = 6.66041402605981945714719999473985e-1
   34  t:3fedfdcd759b9c3d = 9.372317597416281057605587367920208e-1
   34  t:3ff43ef4f771fb15 = 1.265370337088545731919764225637

   34  ~sqrt(t:3ff1400000000000) = t:3ff09cfdcd8ed009 = 1.03833 
   34   sqrt(t:3ff1400000000000) = t:3ff09cfdcd8ed009 = 1.03833 
*/

    0x000000000050fbd4,  /* c7, 42 bit shift ==> 23 significant bits */
    0x000000000efee6bb,  /* c6, 37 bit shift ==> 28 significant bits */
    0x00000002aa06c1e8,  /* c5, 31 bit shift ==> 34 significant bits */
    0x0000008169019343,  /* c4, 25 bit shift ==> 40 significant bits */
    0x00001b7feafccfbd,  /* c3, 20 bit shift ==> 45 significant bits */
    0x00074dfa6b7cb5c6,  /* c2, 14 bit shift ==> 51 significant bits */
    0x03e16d091a55e19e,  /* c1, 07 bit shift ==> 58 significant bits */
    0x07e0f66afed06f5e,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   35  is the Block Number   
   35  Left endpt  (fh)      = t:3fe1800000000000 = 5.46875e-1 
   35  Right endpt (fh_next) = t:3fe2000000000000 = 5.625e-1 
   35  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   35  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   35  Range distance     = 1.5625e-2 
   35  Number of Terms    = 8 
   35  poly_degree        = 7 
   35  poly accuracy      = 62.4524911840732446037527729531743 
   35  Rounding bit added to leading coefficient.
   35  Coeff signs are (printed) positive.

   35  t:3ff0bbb307acafdb = 1.0458250331675944351170204349444
   35  t:3fee990cdad55ec6 = 9.561828874675135480753346284288341e-1
   35  t:3fdbf9a55a5c2ce9 = 4.371121771261657093596980638849914e-1
   35  t:3fd993ca603a7dda = 3.996454181414869022631944361911849e-1
   35  t:3fdd3b2f6e1e6c4e = 4.56737382448129435687017227407658e-1
   35  t:3fe2b4f8b36620fc = 5.845912460218012074702337299569876e-1
   35  t:3fe9937e8315ae2a = 7.992546615836932470395941041640953e-1
   35  t:3ff0d05a327bf0c4 = 1.0508672687565630673913602555203

   35  ~sqrt(t:3ff1c00000000000) = t:3ff0da304d95fb06 = 1.05327 
   35   sqrt(t:3ff1c00000000000) = t:3ff0da304d95fb06 = 1.05327 
*/

    0x0000000000434169,  /* c7, 42 bit shift ==> 23 significant bits */
    0x000000000cc9bf42,  /* c6, 37 bit shift ==> 28 significant bits */
    0x00000002569f166d,  /* c5, 31 bit shift ==> 34 significant bits */
    0x00000074ecbdb87a,  /* c4, 26 bit shift ==> 39 significant bits */
    0x00001993ca603a7e,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0006fe6956970b3a,  /* c2, 14 bit shift ==> 51 significant bits */
    0x03d3219b5aabd8bb,  /* c1, 07 bit shift ==> 58 significant bits */
    0x0bbb307acafdaeb0,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   36  is the Block Number   
   36  Left endpt  (fh)      = t:3fe2000000000000 = 5.625e-1 
   36  Right endpt (fh_next) = t:3fe2800000000000 = 5.78125e-1 
   36  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   36  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   36  Range distance     = 1.5625e-2 
   36  Number of Terms    = 8 
   36  poly_degree        = 7 
   36  poly accuracy      = 62.7731459348246486659517658230911 
   36  Rounding bit added to leading coefficient.
   36  Coeff signs are (printed) positive.

   36  t:3ff0f876ccdf6cd9 = 1.060660171779821286789681489271
   36  t:3fee2b7dddfefa5c = 9.428090415820622584384264053269931e-1
   36  t:3fdad1536ffeae49 = 4.190262407016445457010565822653092e-1
   36  t:3fd7d6830d64c719 = 3.7246776874518301776620203547008e-1
   36  t:3fda7c90cd6a03d8 = 4.138528829571987950413335111132795e-1
   36  t:3fe07acd4440cfa8 = 5.149904568738649973842769203002945e-1
   36  t:3fe5e8a487ce6ddc = 6.846487667530100925230088226847158e-1
   36  t:3fec125f120e2d23 = 8.772425987857882199723140448366365e-1

   36  ~sqrt(t:3ff2400000000000) = t:3ff11687a8ae14a3 = 1.068 
   36   sqrt(t:3ff2400000000000) = t:3ff11687a8ae14a3 = 1.068 
*/

    0x00000000003824be,  /* c7, 43 bit shift ==> 22 significant bits */
    0x000000000af45244,  /* c6, 37 bit shift ==> 28 significant bits */
    0x000000020f59a888,  /* c5, 31 bit shift ==> 34 significant bits */
    0x00000069f24335a8,  /* c4, 26 bit shift ==> 39 significant bits */
    0x000017d6830d64c7,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0006b454dbffab92,  /* c2, 14 bit shift ==> 51 significant bits */
    0x03c56fbbbfdf4b84,  /* c1, 07 bit shift ==> 58 significant bits */
    0x0f876ccdf6cd96ca,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   37  is the Block Number   
   37  Left endpt  (fh)      = t:3fe2800000000000 = 5.78125e-1 
   37  Right endpt (fh_next) = t:3fe3000000000000 = 5.9375e-1 
   37  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   37  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   37  Range distance     = 1.5625e-2 
   37  Number of Terms    = 8 
   37  poly_degree        = 7 
   37  poly accuracy      = 63.0851314421306663287999408016655 
   37  Rounding bit added to leading coefficient.
   37  Coeff signs are (printed) positive.

   37  t:3ff13463fa37014e = 1.0752906583803283466129613321627
   37  t:3fedc267bea45541 = 9.299811099505533413481922488941223e-1
   37  t:3fd9bce41a7ff3e2 = 4.021539934909111913842981456124193e-1
   37  t:3fd64280163efe5c = 3.47808858608891001624238009659607e-1
   37  t:3fd81089cf5e9141 = 3.76009418973144052554579211400387e-1
   37  t:3fdd22e4787efbf9 = 4.552546669692101692910202875852477e-1
   37  t:3fe2d8cada448288 = 5.889639151610745972553924432180139e-1
   37  t:3fe78c65d717c076 = 7.358884049445027228722460144183515e-1

   37  ~sqrt(t:3ff2c00000000000) = t:3ff1520cd1372feb = 1.08253 
   37   sqrt(t:3ff2c00000000000) = t:3ff1520cd1372feb = 1.08253 
*/

    0x00000000002f18cc,  /* c7, 43 bit shift ==> 22 significant bits */
    0x00000000096c656d,  /* c6, 37 bit shift ==> 28 significant bits */
    0x00000001d22e4788,  /* c5, 32 bit shift ==> 33 significant bits */
    0x0000006042273d7a,  /* c4, 26 bit shift ==> 39 significant bits */
    0x0000164280163efe,  /* c3, 20 bit shift ==> 45 significant bits */
    0x00066f39069ffcf9,  /* c2, 14 bit shift ==> 51 significant bits */
    0x03b84cf7d48aa813,  /* c1, 07 bit shift ==> 58 significant bits */
    0x13463fa37014e0dc,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   38  is the Block Number   
   38  Left endpt  (fh)      = t:3fe3000000000000 = 5.9375e-1 
   38  Right endpt (fh_next) = t:3fe3800000000000 = 6.09375e-1 
   38  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   38  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   38  Range distance     = 1.5625e-2 
   38  Number of Terms    = 8 
   38  poly_degree        = 7 
   38  poly accuracy      = 63.3889042019504340469567943323848 
   38  Rounding bit added to leading coefficient.
   38  Coeff signs are (printed) positive.

   38  t:3ff16f8334644df9 = 1.0897247358851683881469929460195
   38  t:3fed5d7ea914b930 = 9.176629354822463213009996196856122e-1
   38  t:3fd8ba859bdb4802 = 3.86384393886260209645877247708334e-1
   38  t:3fd4d2f73f53bc5c = 3.2537633117948927262180931763158e-1
   38  t:3fd5eb8a7424b3c1 = 3.42501271649606368841986525630716e-1
   38  t:3fd9d76bbbdd07d9 = 4.037732443431401820792617241018263e-1
   38  t:3fe0472848372698 = 5.086862001855533961481789506642315e-1
   38  t:3fe3d87556e3d31f = 6.201731392926354126480387174424891e-1

   38  ~sqrt(t:3ff3400000000000) = t:3ff18cc821d6d3e3 = 1.09687 
   38   sqrt(t:3ff3400000000000) = t:3ff18cc821d6d3e3 = 1.09687 
*/

    0x000000000027b0eb,  /* c7, 43 bit shift ==> 22 significant bits */
    0x0000000008239424,  /* c6, 37 bit shift ==> 28 significant bits */
    0x000000019d76bbbe,  /* c5, 32 bit shift ==> 33 significant bits */
    0x00000057ae29d093,  /* c4, 26 bit shift ==> 39 significant bits */
    0x000014d2f73f53bc,  /* c3, 20 bit shift ==> 45 significant bits */
    0x00062ea166f6d200,  /* c2, 14 bit shift ==> 51 significant bits */
    0x03abafd522972603,  /* c1, 07 bit shift ==> 58 significant bits */
    0x16f8334644df8860,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   39  is the Block Number   
   39  Left endpt  (fh)      = t:3fe3800000000000 = 6.09375e-1 
   39  Right endpt (fh_next) = t:3fe4000000000000 = 6.25e-1 
   39  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   39  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   39  Range distance     = 1.5625e-2 
   39  Number of Terms    = 8 
   39  poly_degree        = 7 
   39  poly accuracy      = 63.684885573458937410622983546985 
   39  Rounding bit added to leading coefficient.
   39  Coeff signs are (printed) positive.

   39  t:3ff1a9dc8f6df104 = 1.1039701082909808569146314916054
   39  t:3fecfc7da32a920d = 9.058216273156759879947412528178319e-1
   39  t:3fd7c89b99924ad5 = 3.71619129154322970335928150165117e-1
   39  t:3fd383c7e0036f74 = 3.04918259394745726941411065324949e-1
   39  t:3fd403e03e76758c = 3.12736569403420296251079613103485e-1
   39  t:3fd6fda610416894 = 3.59231487154496846760228997985642e-1
   39  t:3fdc39b9653caf6c = 4.410232056277354590831125263905577e-1
   39  t:3fe0cc68397a5425 = 5.249520418752849729724166416566788e-1

   39  ~sqrt(t:3ff3c00000000000) = t:3ff1c6c16b2db870 = 1.11102 
   39   sqrt(t:3ff3c00000000000) = t:3ff1c6c16b2db870 = 1.11102 
*/

    0x00000000002198d0,  /* c7, 43 bit shift ==> 22 significant bits */
    0x00000000070e6e59,  /* c6, 38 bit shift ==> 27 significant bits */
    0x000000016fda6104,  /* c5, 32 bit shift ==> 33 significant bits */
    0x000000500f80f9da,  /* c4, 26 bit shift ==> 39 significant bits */
    0x00001383c7e0036f,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0005f226e66492b5,  /* c2, 14 bit shift ==> 51 significant bits */
    0x039f8fb4655241ac,  /* c1, 07 bit shift ==> 58 significant bits */
    0x1a9dc8f6df103810,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   40  is the Block Number   
   40  Left endpt  (fh)      = t:3fe4000000000000 = 6.25e-1 
   40  Right endpt (fh_next) = t:3fe4800000000000 = 6.40625e-1 
   40  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   40  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   40  Range distance     = 1.5625e-2 
   40  Number of Terms    = 8 
   40  poly_degree        = 7 
   40  poly accuracy      = 63.9734652953379079847908131637393 
   40  Rounding bit added to leading coefficient.
   40  Coeff signs are (printed) positive.

   40  t:3ff1e3779b97f4a8 = 1.1180339887498948483156302469155
   40  t:3fec9f25c5bfedd5 = 8.944271909999153707688385184226831e-1
   40  t:3fd6e5b7d16627ac = 3.57770876399281285946485722804233e-1
   40  t:3fd2515fda5778f4 = 2.8621670076780893895930686643414e-1
   40  t:3fd2515f7b33c529 = 2.86216612162280043132151982621103e-1
   40  t:3fd483e62ec99738 = 3.2055048531616445618014354934644e-1
   40  t:3fd88f3c401de347 = 3.83742392171872054979463173562948e-1
   40  t:3fdc8ea9092667ae = 4.462072934489878975165572799754798e-1

   40  ~sqrt(t:3ff4400000000000) = t:3ff2000000000000 = 1.125 
   40   sqrt(t:3ff4400000000000) = t:3ff2000000000000 = 1.125 
*/

    0x00000000001c8ea9,  /* c7, 44 bit shift ==> 21 significant bits */
    0x000000000623cf10,  /* c6, 38 bit shift ==> 27 significant bits */
    0x00000001483e62ed,  /* c5, 32 bit shift ==> 33 significant bits */
    0x00000049457deccf,  /* c4, 26 bit shift ==> 39 significant bits */
    0x000012515fda5779,  /* c3, 20 bit shift ==> 45 significant bits */
    0x0005b96df45989eb,  /* c2, 14 bit shift ==> 51 significant bits */
    0x0393e4b8b7fdba94,  /* c1, 07 bit shift ==> 58 significant bits */
    0x1e3779b97f4a7c18,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   41  is the Block Number   
   41  Left endpt  (fh)      = t:3fe4800000000000 = 6.40625e-1 
   41  Right endpt (fh_next) = t:3fe5000000000000 = 6.5625e-1 
   41  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   41  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   41  Range distance     = 1.5625e-2 
   41  Number of Terms    = 8 
   41  poly_degree        = 7 
   41  poly accuracy      = 64.2550045728806867318738985606403 
   41  Rounding bit added to leading coefficient.
   41  Coeff signs are (printed) positive.

   41  t:3ff21c5b70d9f824 = 1.1319231422671770783891509459806
   41  t:3fec453d90f0579e = 8.834522085987719309174356907554682e-1
   41  t:3fd61093f43e8ca4 = 3.44761837501389437938984286469157e-1
   41  t:3fd138a56d250491 = 2.69082409464382483983485236378463e-1
   41  t:3fd0cd1df5cc653f = 2.62519350087661190750777662206161e-1
   41  t:3fd25b978050a932 = 2.86840319926926627175844605743826e-1
   41  t:3fd5716f87197273 = 3.35048562939653735213811625026636e-1
   41  t:3fd85eb8e4ee64bb = 3.80781386914872107797786285332542e-1

   41  ~sqrt(t:3ff4c00000000000) = t:3ff2388ac0059c28 = 1.1388 
   41   sqrt(t:3ff4c00000000000) = t:3ff2388ac0059c28 = 1.1388 
*/

    0x0000000000185eb9,  /* c7, 44 bit shift ==> 21 significant bits */
    0x00000000055c5be2,  /* c6, 38 bit shift ==> 27 significant bits */
    0x0000000125b97805,  /* c5, 32 bit shift ==> 33 significant bits */
    0x000000433477d732,  /* c4, 26 bit shift ==> 39 significant bits */
    0x00001138a56d2505,  /* c3, 20 bit shift ==> 45 significant bits */
    0x00058424fd0fa329,  /* c2, 14 bit shift ==> 51 significant bits */
    0x0388a7b21e0af3be,  /* c1, 07 bit shift ==> 58 significant bits */
    0x21c5b70d9f8239f0,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   42  is the Block Number   
   42  Left endpt  (fh)      = t:3fe5000000000000 = 6.5625e-1 
   42  Right endpt (fh_next) = t:3fe5800000000000 = 6.71875e-1 
   42  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   42  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   42  Range distance     = 1.5625e-2 
   42  Number of Terms    = 8 
   42  poly_degree        = 7 
   42  poly accuracy      = 64.5298387972969060655389045488064 
   42  Rounding bit added to leading coefficient.
   42  Coeff signs are (printed) positive.

   42  t:3ff2548eb9151e85 = 1.1456439237389600017003737919552
   42  t:3febee9056fb9c35 = 8.728715609439691713324592503564503e-1
   42  t:3fd5480c7308b6f9 = 3.32522499406749308224632080688288e-1
   42  t:3fd036e4e9aaf1da = 2.53350475493588339636914091856923e-1
   42  t:3fcee2768de82129 = 2.41286105432899661228565019177594e-1
   42  t:3fd078a45d1968c7 = 2.57363406102410555913000134165003e-1
   42  t:3fd2c88b83fdf581 = 2.93490294359649858837004246514546e-1
   42  t:3fd4e019e971ef01 = 3.26178052877125453627325454841746e-1

   42  ~sqrt(t:3ff5400000000000) = t:3ff2706821902e9a = 1.15244 
   42   sqrt(t:3ff5400000000000) = t:3ff2706821902e9a = 1.15244 
*/

    0x000000000014e01a,  /* c7, 44 bit shift ==> 21 significant bits */
    0x0000000004b222e1,  /* c6, 38 bit shift ==> 27 significant bits */
    0x00000001078a45d2,  /* c5, 32 bit shift ==> 33 significant bits */
    0x0000003dc4ed1bd0,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00001036e4e9aaf2,  /* c3, 20 bit shift ==> 45 significant bits */
    0x000552031cc22dbe,  /* c2, 14 bit shift ==> 51 significant bits */
    0x037dd20adf7386b0,  /* c1, 07 bit shift ==> 58 significant bits */
    0x2548eb9151e85334,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   43  is the Block Number   
   43  Left endpt  (fh)      = t:3fe5800000000000 = 6.71875e-1 
   43  Right endpt (fh_next) = t:3fe6000000000000 = 6.875e-1 
   43  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   43  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   43  Range distance     = 1.5625e-2 
   43  Number of Terms    = 8 
   43  poly_degree        = 7 
   43  poly accuracy      = 64.798279948548887938133501770224 
   43  Rounding bit added to leading coefficient.
   43  Coeff signs are (printed) positive.

   43  t:3ff28c17b9337834 = 1.1592023119369629691232173596127
   43  t:3feb9aedba588345 = 8.626621856275070286831051225018285e-1
   43  t:3fd48b1c139b0fe9 = 3.20990580698206597558665501002118e-1
   43  t:3fce938316c91248 = 2.38876711011601232137772574115608e-1
   43  t:3fcc7167a5ea0fee = 2.2221084214481785178683676679201e-1
   43  t:3fcda1f9c2d1a136 = 2.3150560391082714232070631499294e-1
   43  t:3fd0813cabd8b22c = 2.57888000315491731554264423498246e-1
   43  t:3fd1f2477015f79e = 2.80412539919660966050056830067838e-1

   43  ~sqrt(t:3ff5c00000000000) = t:3ff2a79e3a2cd2e6 = 1.16592 
   43   sqrt(t:3ff5c00000000000) = t:3ff2a79e3a2cd2e6 = 1.16592 
*/

    0x000000000011f247,  /* c7, 44 bit shift ==> 21 significant bits */
    0x0000000004204f2b,  /* c6, 38 bit shift ==> 27 significant bits */
    0x00000000ed0fce17,  /* c5, 33 bit shift ==> 32 significant bits */
    0x00000038e2cf4bd4,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000f49c18b6489,  /* c3, 21 bit shift ==> 44 significant bits */
    0x000522c704e6c3fa,  /* c2, 14 bit shift ==> 51 significant bits */
    0x03735db74b106893,  /* c1, 07 bit shift ==> 58 significant bits */
    0x28c17b9337833e52,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   44  is the Block Number   
   44  Left endpt  (fh)      = t:3fe6000000000000 = 6.875e-1 
   44  Right endpt (fh_next) = t:3fe6800000000000 = 7.03125e-1 
   44  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   44  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   44  Range distance     = 1.5625e-2 
   44  Number of Terms    = 8 
   44  poly_degree        = 7 
   44  poly accuracy      = 65.060618724954200171190306572254 
   44  Rounding bit added to leading coefficient.
   44  Coeff signs are (printed) positive.

   44  t:3ff2c2fc595456a7 = 1.172603939955857388637190663605
   44  t:3feb4a293c1d954d = 8.528028654224414866315620575853984e-1
   44  t:3fd3d8d82bb854cf = 3.10110132880549953276116612044255e-1
   44  t:3fccde51b3958205 = 2.25534641921527300513798316994318e-1
   44  t:3fca3e7873f9fe7a = 2.05031448964280651136270205991963e-1
   44  t:3fcab86dc0be3697 = 2.08753317940524057741663414844435e-1
   44  t:3fcd1774526ccfea = 2.2727827095661661308510781420722e-1
   44  t:3fcef68573414493 = 2.41898232724029850658682173902836e-1

   44  ~sqrt(t:3ff6400000000000) = t:3ff2de32c6628741 = 1.17925 
   44   sqrt(t:3ff6400000000000) = t:3ff2de32c6628741 = 1.17925 
*/

    0x00000000000f7b43,  /* c7, 45 bit shift ==> 20 significant bits */
    0x0000000003a2ee8a,  /* c6, 39 bit shift ==> 26 significant bits */
    0x00000000d5c36e06,  /* c5, 33 bit shift ==> 32 significant bits */
    0x000000347cf0e7f4,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000e6f28d9cac1,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0004f6360aee1534,  /* c2, 14 bit shift ==> 51 significant bits */
    0x0369452783b2a9af,  /* c1, 07 bit shift ==> 58 significant bits */
    0x2c2fc595456a6cd2,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   45  is the Block Number   
   45  Left endpt  (fh)      = t:3fe6800000000000 = 7.03125e-1 
   45  Right endpt (fh_next) = t:3fe7000000000000 = 7.1875e-1 
   45  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   45  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   45  Range distance     = 1.5625e-2 
   45  Number of Terms    = 8 
   45  poly_degree        = 7 
   45  poly accuracy      = 65.3171264359990425150291286645304 
   45  Rounding bit added to leading coefficient.
   45  Coeff signs are (printed) positive.

   45  t:3ff2f9422c23c47e = 1.1858541225631422494878053353062
   45  t:3feafc19d8606167 = 8.432740427115676097266118438344762e-1
   45  t:3fd3306d66aadbcf = 2.99830770741604726663774582728905e-1
   45  t:3fcb4a9036adaef1 = 2.13212992380583039121787550240761e-1
   45  t:3fc84246fda2e116 = 1.89522622915099850810513940069235e-1
   45  t:3fc82682a6e110c0 = 1.88675242885556933712296566463262e-1
   45  t:3fc9b62037126c10 = 2.00870539560896052636842709637754e-1
   45  t:3fcacc50d46d28d1 = 2.09360221599416841174279117765433e-1

   45  ~sqrt(t:3ff6c00000000000) = t:3ff3142b30a929ab = 1.19242 
   45   sqrt(t:3ff6c00000000000) = t:3ff3142b30a929ab = 1.19242 
*/

    0x00000000000d6628,  /* c7, 45 bit shift ==> 20 significant bits */
    0x000000000336c407,  /* c6, 39 bit shift ==> 26 significant bits */
    0x00000000c1341537,  /* c5, 33 bit shift ==> 32 significant bits */
    0x00000030848dfb46,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000da5481b56d7,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0004cc1b59aab6f4,  /* c2, 14 bit shift ==> 51 significant bits */
    0x035f833b0c0c2ce7,  /* c1, 07 bit shift ==> 58 significant bits */
    0x2f9422c23c47ded8,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   46  is the Block Number   
   46  Left endpt  (fh)      = t:3fe7000000000000 = 7.1875e-1 
   46  Right endpt (fh_next) = t:3fe7800000000000 = 7.34375e-1 
   46  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   46  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   46  Range distance     = 1.5625e-2 
   46  Number of Terms    = 8 
   46  poly_degree        = 7 
   46  poly accuracy      = 65.5680566892592585465926072095396 
   46  Rounding bit added to leading coefficient.
   46  Coeff signs are (printed) positive.

   46  t:3ff32eee75770416 = 1.1989578808281798853871066845578
   46  t:3feab099ae8f5398 = 8.340576562282988704955313807865025e-1
   46  t:3fd2911cfeff76f8 = 2.90107010861774054500923994415196e-1
   46  t:3fc9d506f33524b2 = 2.01813572648722291914477611207701e-1
   46  t:3fc676751598698e = 1.75490031761750873040995452045721e-1
   46  t:3fc5e04dfed065f8 = 1.70907735272336704386423635038117e-1
   46  t:3fc6c9228775f19c = 1.78013149397782003365334722866375e-1
   46  t:3fc74434e7b8dd0e = 1.81769002099578741676703941276827e-1

   46  ~sqrt(t:3ff7400000000000) = t:3ff3498c97b10540 = 1.20546 
   46   sqrt(t:3ff7400000000000) = t:3ff3498c97b10540 = 1.20546 
*/

    0x00000000000ba21a,  /* c7, 45 bit shift ==> 20 significant bits */
    0x0000000002d92451,  /* c6, 39 bit shift ==> 26 significant bits */
    0x00000000af026ff7,  /* c5, 33 bit shift ==> 32 significant bits */
    0x0000002cecea2b31,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000cea83799a92,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0004a4473fbfddbe,  /* c2, 14 bit shift ==> 51 significant bits */
    0x03561335d1ea7303,  /* c1, 07 bit shift ==> 58 significant bits */
    0x32eee757704167b6,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   47  is the Block Number   
   47  Left endpt  (fh)      = t:3fe7800000000000 = 7.34375e-1 
   47  Right endpt (fh_next) = t:3fe8000000000000 = 7.5e-1 
   47  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   47  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   47  Range distance     = 1.5625e-2 
   47  Number of Terms    = 8 
   47  poly_degree        = 7 
   47  poly accuracy      = 65.813646897742839627900878609535 
   47  Rounding bit added to leading coefficient.
   47  Coeff signs are (printed) positive.

   47  t:3ff3640630445306 = 1.2119199643540822534850537328666
   47  t:3fea6785b41bacf6 = 8.251369970070345721629111179762361e-1
   47  t:3fd1fa3a59f21aee = 2.80897701108570624107000843205917e-1
   47  t:3fc87add12c2fd1e = 1.91249498520826348663213117839987e-1
   47  t:3fc4d580020b4175 = 1.62765503881484044574126657245472e-1
   47  t:3fc3dbba1375e89d = 1.55143031599270482908574722569206e-1
   47  t:3fc43ecde206916e = 1.58166632999506109153679128676018e-1
   47  t:3fc442d2fa4b1df1 = 1.58289310659014445772561040237658e-1

   47  ~sqrt(t:3ff7c00000000000) = t:3ff37e5bd40f95a1 = 1.21835 
   47   sqrt(t:3ff7c00000000000) = t:3ff37e5bd40f95a1 = 1.21835 
*/

    0x00000000000a2169,  /* c7, 45 bit shift ==> 20 significant bits */
    0x000000000287d9bc,  /* c6, 39 bit shift ==> 26 significant bits */
    0x000000009eddd09c,  /* c5, 33 bit shift ==> 32 significant bits */
    0x00000029ab000417,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000c3d6e89617f,  /* c3, 21 bit shift ==> 44 significant bits */
    0x00047e8e967c86bc,  /* c2, 14 bit shift ==> 51 significant bits */
    0x034cf0b683759ebe,  /* c1, 07 bit shift ==> 58 significant bits */
    0x3640630445305a1c,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   48  is the Block Number   
   48  Left endpt  (fh)      = t:3fe8000000000000 = 7.5e-1 
   48  Right endpt (fh_next) = t:3fe8800000000000 = 7.65625e-1 
   48  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   48  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   48  Range distance     = 1.5625e-2 
   48  Number of Terms    = 8 
   48  poly_degree        = 7 
   48  poly accuracy      = 66.0541196301553704996583652065542 
   48  Rounding bit added to leading coefficient.
   48  Coeff signs are (printed) positive.

   48  t:3ff3988e1409212e = 1.2247448713915890490880333807411
   48  t:3fea20bd700c2c3d = 8.164965809277259013200522819175831e-1
   48  t:3fd16b28f55d665c = 2.72165526975731496614604662531711e-1
   48  t:3fc7398bf19fe461 = 1.81443684559584840856362453198614e-1
   48  t:3fc35a9f182df822 = 1.51203047567777087168143686224386e-1
   48  t:3fc21035f4436fca = 1.4111971308636688034079779974217e-1
   48  t:3fc208708eba3777 = 1.40882558528058619362957615273046e-1
   48  t:3fc1b1dca4994db2 = 1.38240414019134715735708136830073e-1

   48  ~sqrt(t:3ff8400000000000) = t:3ff3b29d7d635662 = 1.23111 
   48   sqrt(t:3ff8400000000000) = t:3ff3b29d7d635662 = 1.23111 
*/

    0x000000000008d8ee,  /* c7, 45 bit shift ==> 20 significant bits */
    0x0000000002410e12,  /* c6, 39 bit shift ==> 26 significant bits */
    0x000000009081afa2,  /* c5, 33 bit shift ==> 32 significant bits */
    0x00000026b53e305c,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000b9cc5f8cff2,  /* c3, 21 bit shift ==> 44 significant bits */
    0x00045aca3d575997,  /* c2, 14 bit shift ==> 51 significant bits */
    0x034417ae0185879a,  /* c1, 07 bit shift ==> 58 significant bits */
    0x3988e1409212e7d0,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   49  is the Block Number   
   49  Left endpt  (fh)      = t:3fe8800000000000 = 7.65625e-1 
   49  Right endpt (fh_next) = t:3fe9000000000000 = 7.8125e-1 
   49  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   49  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   49  Range distance     = 1.5625e-2 
   49  Number of Terms    = 8 
   49  poly_degree        = 7 
   49  poly accuracy      = 66.2896838232417272327777064315088 
   49  Rounding bit added to leading coefficient.
   49  Coeff signs are (printed) positive.

   49  t:3ff3cc8a99af5453 = 1.2374368670764581677225246725271
   49  t:3fe9dc22be484456 = 8.081220356417684865598001497932756e-1
   49  t:3fd0e35a9b9cde04 = 2.63876583066547922397718228815222e-1
   49  t:3fc60ed462978f85 = 1.72327564373628087777577319594791e-1
   49  t:3fc201a7fc7f4b80 = 1.40675543107672497091962734994119e-1
   49  t:3fc076746c4963b5 = 1.28614952921251598130900246907959e-1
   49  t:3fc019c74cd47f7a = 1.25786697878534977981259367074696e-1
   49  t:3fbefe1fa709369b = 1.21065119056959970657901676238666e-1

   49  ~sqrt(t:3ff8c00000000000) = t:3ff3e655eefe1367 = 1.24373 
   49   sqrt(t:3ff8c00000000000) = t:3ff3e655eefe1367 = 1.24373 
*/

    0x000000000007bf88,  /* c7, 46 bit shift ==> 19 significant bits */
    0x00000000020338ea,  /* c6, 39 bit shift ==> 26 significant bits */
    0x0000000083b3a362,  /* c5, 33 bit shift ==> 32 significant bits */
    0x00000024034ff8ff,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000b076a314bc8,  /* c3, 21 bit shift ==> 44 significant bits */
    0x000438d6a6e73781,  /* c2, 14 bit shift ==> 51 significant bits */
    0x033b8457c9088ad0,  /* c1, 07 bit shift ==> 58 significant bits */
    0x3cc8a99af5452fe8,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   50  is the Block Number   
   50  Left endpt  (fh)      = t:3fe9000000000000 = 7.8125e-1 
   50  Right endpt (fh_next) = t:3fe9800000000000 = 7.96875e-1 
   50  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   50  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   50  Range distance     = 1.5625e-2 
   50  Number of Terms    = 8 
   50  poly_degree        = 7 
   50  poly accuracy      = 66.5205358728572117084783594283328 
   50  Rounding bit added to leading coefficient.
   50  Coeff signs are (printed) positive.

   50  t:3ff4000000000000 = 1.25
   50  t:3fe9999999999999 = 7.99999999999999902920537475647933e-1
   50  t:3fd0624dd2f1a0c7 = 2.559999999998691533212389487284e-1
   50  t:3fc4f8b588be7613 = 1.63839999932790731114310746330265e-1
   50  t:3fc0c6f77c493c34 = 1.31071983038482673354901270057482e-1
   50  t:3fbe106dcb461506 = 1.17438184859640499511674194971222e-1
   50  t:3fbcd118d9cb3041 = 1.12565568134585640257131280983494e-1
   50  t:3fbb36d5ad9a6793 = 1.06305460818843661377898317244028e-1

   50  ~sqrt(t:3ff9400000000000) = t:3ff419894c2329f0 = 1.25623 
   50   sqrt(t:3ff9400000000000) = t:3ff419894c2329f0 = 1.25623 
*/

    0x000000000006cdb5,  /* c7, 46 bit shift ==> 19 significant bits */
    0x0000000001cd118e,  /* c6, 40 bit shift ==> 25 significant bits */
    0x000000007841b72d,  /* c5, 34 bit shift ==> 31 significant bits */
    0x000000218deef892,  /* c4, 27 bit shift ==> 38 significant bits */
    0x00000a7c5ac45f3b,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0004189374bc6832,  /* c2, 14 bit shift ==> 51 significant bits */
    0x0333333333333317,  /* c1, 07 bit shift ==> 58 significant bits */
    0x4000000000000000,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   51  is the Block Number   
   51  Left endpt  (fh)      = t:3fe9800000000000 = 7.96875e-1 
   51  Right endpt (fh_next) = t:3fea000000000000 = 8.125e-1 
   51  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   51  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   51  Range distance     = 1.5625e-2 
   51  Number of Terms    = 8 
   51  poly_degree        = 7 
   51  poly accuracy      = 66.7468606180646701301488014027395 
   51  Rounding bit added to leading coefficient.
   51  Coeff signs are (printed) positive.

   51  t:3ff432f24fb01c7a = 1.2624381172952597442247363312973
   51  t:3fe95907eb87ab43 = 7.92118034381339363510666357059975e-1
   51  t:3fcfcf18ff68ef2f = 2.48507618629326878522431236440138e-1
   51  t:3fc3f5650486613b = 1.55926348885950210142593667927979e-1
   51  t:3fbf4ebc54f78005 = 1.22295161002966850710335904722781e-1
   51  t:3fbb8043b4fc20f3 = 1.07425910650025537381889104149302e-1
   51  t:3fb9d83a3df15961 = 1.00955619929071992171777834290669e-1
   51  t:3fb7f51727d6ccdd = 9.35835335028971262752678188234778e-2

   51  ~sqrt(t:3ff9c00000000000) = t:3ff44c3b83e57153 = 1.26861 
   51   sqrt(t:3ff9c00000000000) = t:3ff44c3b83e57153 = 1.26861 
*/

    0x000000000005fd46,  /* c7, 46 bit shift ==> 19 significant bits */
    0x00000000019d83a4,  /* c6, 40 bit shift ==> 25 significant bits */
    0x000000006e010ed4,  /* c5, 34 bit shift ==> 31 significant bits */
    0x0000001f4ebc54f8,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000009fab2824331,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0003f9e31fed1de6,  /* c2, 15 bit shift ==> 50 significant bits */
    0x032b20fd70f5686d,  /* c1, 07 bit shift ==> 58 significant bits */
    0x432f24fb01c7a4e4,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   52  is the Block Number   
   52  Left endpt  (fh)      = t:3fea000000000000 = 8.125e-1 
   52  Right endpt (fh_next) = t:3fea800000000000 = 8.28125e-1 
   52  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   52  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   52  Range distance     = 1.5625e-2 
   52  Number of Terms    = 8 
   52  poly_degree        = 7 
   52  poly accuracy      = 66.9688322304200925127740729570441 
   52  Rounding bit added to leading coefficient.
   52  Coeff signs are (printed) positive.

   52  t:3ff465655f122ff6 = 1.2747548783981962074694782582895
   52  t:3fe91a556151761b = 7.844645405527360551654197928783674e-1
   52  t:3fcee55564156fe9 = 2.4137370478535949591583197743061e-1
   52  t:3fc303483d7b7711 = 1.48537664433142909341896073516232e-1
   52  t:3fbd402028552247 = 1.14259729239287388014468128255574e-1
   52  t:3fb93331ed4322eb = 9.84374241117042377027216044915736e-2
   52  t:3fb73a6086985274 = 9.07345131493658136655005262694029e-2
   52  t:3fb524604015d678 = 8.25863033731709593433193555833682e-2

   52  ~sqrt(t:3ffa400000000000) = t:3ff47e7054af0989 = 1.28087 
   52   sqrt(t:3ffa400000000000) = t:3ff47e7054af0989 = 1.28087 
*/

    0x0000000000054918,  /* c7, 46 bit shift ==> 19 significant bits */
    0x000000000173a608,  /* c6, 40 bit shift ==> 25 significant bits */
    0x0000000064ccc7b5,  /* c5, 34 bit shift ==> 31 significant bits */
    0x0000001d40202855,  /* c4, 28 bit shift ==> 37 significant bits */
    0x00000981a41ebdbc,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0003dcaaac82adfd,  /* c2, 15 bit shift ==> 50 significant bits */
    0x03234aac2a2ec35d,  /* c1, 07 bit shift ==> 58 significant bits */
    0x465655f122ff6618,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   53  is the Block Number   
   53  Left endpt  (fh)      = t:3fea800000000000 = 8.28125e-1 
   53  Right endpt (fh_next) = t:3feb000000000000 = 8.4375e-1 
   53  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   53  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   53  Range distance     = 1.5625e-2 
   53  Number of Terms    = 8 
   53  poly_degree        = 7 
   53  poly accuracy      = 67.1866150194763145380428570052374 
   53  Rounding bit added to leading coefficient.
   53  Coeff signs are (printed) positive.

   53  t:3ff4975cd5768088 = 1.2869537676233750395169558311537
   53  t:3fe8dd6b4563a009 = 7.770286898858112816412986589842404e-1
   53  t:3fce068b31faaba6 = 2.34574698833367611882304813730737e-1
   53  t:3fc220ee9baae309 = 1.41630006799253988669000728362057e-1
   53  t:3fbb5d2e0454c823 = 1.06890560204903331019475436203248e-1
   53  t:3fb72142e0d71998 = 9.0351276295314147660100046605125e-2
   53  t:3fb4eb363609206f = 8.17140466616608068591985809814293e-2
   53  t:3fb2b3a2b1d0ef19 = 7.30535205956893798125845185253979e-2

   53  ~sqrt(t:3ffac00000000000) = t:3ff4b02b4f7c0a88 = 1.29301 
   53   sqrt(t:3ffac00000000000) = t:3ff4b02b4f7c0a88 = 1.29301 
*/

    0x000000000004ace9,  /* c7, 46 bit shift ==> 19 significant bits */
    0x00000000014eb363,  /* c6, 40 bit shift ==> 25 significant bits */
    0x000000005c850b83,  /* c5, 34 bit shift ==> 31 significant bits */
    0x0000001b5d2e0455,  /* c4, 28 bit shift ==> 37 significant bits */
    0x00000910774dd572,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0003c0d1663f5575,  /* c2, 15 bit shift ==> 50 significant bits */
    0x031bad68ac740118,  /* c1, 07 bit shift ==> 58 significant bits */
    0x4975cd5768087ba4,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   54  is the Block Number   
   54  Left endpt  (fh)      = t:3feb000000000000 = 8.4375e-1 
   54  Right endpt (fh_next) = t:3feb800000000000 = 8.59375e-1 
   54  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   54  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   54  Range distance     = 1.5625e-2 
   54  Number of Terms    = 8 
   54  poly_degree        = 7 
   54  poly accuracy      = 67.400364163560256548284184333268 
   54  Rounding bit added to leading coefficient.
   54  Coeff signs are (printed) positive.

   54  t:3ff4c8dc2e423980 = 1.2990381056766579701260838630716
   54  t:3fe8a2345cc04425 = 7.698003589195009645717270030385038e-1
   54  t:3fcd32052b8e7f43 = 2.28088995235333847935959954156271e-1
   54  t:3fc14d0c8b81fc28 = 1.35163848990459857846483347765254e-1
   54  t:3fb9a18daf2dc76b = 1.00121360080974211783516342882949e-1
   54  t:3fb54392dbcd8c2d = 8.30623423221800829597573356810614e-2
   54  t:3fb2e04209061ad4 = 7.37344047575832486153589798161256e-2
   54  t:3fb094a3a4f89b9a = 6.47680547486814458453562894091338e-2

   54  ~sqrt(t:3ffb400000000000) = t:3ff4e16fdacff937 = 1.30504 
   54   sqrt(t:3ffb400000000000) = t:3ff4e16fdacff937 = 1.30504 
*/

    0x0000000000042529,  /* c7, 46 bit shift ==> 19 significant bits */
    0x00000000012e0421,  /* c6, 40 bit shift ==> 25 significant bits */
    0x00000000550e4b6f,  /* c5, 34 bit shift ==> 31 significant bits */
    0x00000019a18daf2e,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000008a68645c0fe,  /* c3, 21 bit shift ==> 44 significant bits */
    0x0003a640a571cfe8,  /* c2, 15 bit shift ==> 50 significant bits */
    0x0314468b980884a8,  /* c1, 07 bit shift ==> 58 significant bits */
    0x4c8dc2e42397fd6c,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   55  is the Block Number   
   55  Left endpt  (fh)      = t:3feb800000000000 = 8.59375e-1 
   55  Right endpt (fh_next) = t:3fec000000000000 = 8.75e-1 
   55  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   55  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   55  Range distance     = 1.5625e-2 
   55  Number of Terms    = 8 
   55  poly_degree        = 7 
   55  poly accuracy      = 67.6102263741455664654888134928033 
   55  Rounding bit added to leading coefficient.
   55  Coeff signs are (printed) positive.

   55  t:3ff4f9e6bbc4ecb3 = 1.3110110602126894337616375141309
   55  t:3fe8689cc7e07e7c = 7.627700713964738045511776443063923e-1
   55  t:3fcc671cd5f73afd = 2.21896748042546131324606606405325e-1
   55  t:3fc086772d4a78a6 = 1.29103562464426956836872732725663e-1
   55  t:3fb8096763f14772 = 9.38934916496501303681911955456574e-2
   55  t:3fb394270e61d620 = 7.64793787110069586991298318245924e-2
   55  t:3fb110981988a51d = 6.66594564760498263031730618866089e-2
   55  t:3fad76f2fae013be = 5.75481349224342548117326363171786e-2

   55  ~sqrt(t:3ffbc00000000000) = t:3ff51241356cf6e0 = 1.31696 
   55   sqrt(t:3ffbc00000000000) = t:3ff51241356cf6e0 = 1.31696 
*/

    0x000000000003aede,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000001110982,  /* c6, 40 bit shift ==> 25 significant bits */
    0x000000004e509c3a,  /* c5, 34 bit shift ==> 31 significant bits */
    0x00000018096763f1,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000008433b96a53c,  /* c3, 21 bit shift ==> 44 significant bits */
    0x00038ce39abee760,  /* c2, 15 bit shift ==> 50 significant bits */
    0x030d1398fc0fcf84,  /* c1, 07 bit shift ==> 58 significant bits */
    0x4f9e6bbc4ecb3074,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   56  is the Block Number   
   56  Left endpt  (fh)      = t:3fec000000000000 = 8.75e-1 
   56  Right endpt (fh_next) = t:3fec800000000000 = 8.90625e-1 
   56  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   56  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   56  Range distance     = 1.5625e-2 
   56  Number of Terms    = 8 
   56  poly_degree        = 7 
   56  poly accuracy      = 67.8163405007782675517974194562265 
   56  Rounding bit added to leading coefficient.
   56  Coeff signs are (printed) positive.

   56  t:3ff52a7fa9d2f8ea = 1.322875655532295295201822282749
   56  t:3fe83091e6a7f7e6 = 7.5592894601845441262828045880795e-1
   56  t:3fcba539079b5c86 = 2.15979698862359194158969111221325e-1
   56  t:3fbf98412d240e36 = 1.23416970749581657459080508143501e-1
   56  t:3fb6915300f97de6 = 8.81549718264903132877155153557247e-2
   56  t:3fb20dcb4dcc64af = 7.05229821145560879992091399270926e-2
   56  t:3faee93261cd4990 = 6.03729004275407328816975983248883e-2
   56  t:3faa3c45c856c560 = 5.12410933546429978281352719121644e-2

   56  ~sqrt(t:3ffc400000000000) = t:3ff542a278d2d036 = 1.32877 
   56   sqrt(t:3ffc400000000000) = t:3ff542a278d2d036 = 1.32877 
*/

    0x0000000000034789,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000000f74993,  /* c6, 41 bit shift ==> 24 significant bits */
    0x0000000048372d37,  /* c5, 34 bit shift ==> 31 significant bits */
    0x00000016915300f9,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000007e6104b4904,  /* c3, 22 bit shift ==> 43 significant bits */
    0x000374a720f36b91,  /* c2, 15 bit shift ==> 50 significant bits */
    0x0306123cd4fefcc5,  /* c1, 07 bit shift ==> 58 significant bits */
    0x52a7fa9d2f8e9b78,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   57  is the Block Number   
   57  Left endpt  (fh)      = t:3fec800000000000 = 8.90625e-1 
   57  Right endpt (fh_next) = t:3fed000000000000 = 9.0625e-1 
   57  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   57  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   57  Range distance     = 1.5625e-2 
   57  Number of Terms    = 8 
   57  poly_degree        = 7 
   57  poly accuracy      = 68.0188380831164097304419606458168 
   57  Rounding bit added to leading coefficient.
   57  Coeff signs are (printed) positive.

   57  t:3ff55aaa002a9d5a = 1.3346347815039139013491148455515
   57  t:3fe7fa023f1068d1 = 7.492686492653551360459442121086937e-1
   57  t:3fcaebcca0a21de4 = 2.10321024355138003290172088455279e-1
   57  t:3fbe3a29200a70e7 = 1.18074961016137444400693652657441e-1
   57  t:3fb53649aa3b39f6 = 8.28596153835191284031799416331943e-2
   57  t:3fb0abf55d5b8d04 = 6.51238778041723364057788425718343e-2
   57  t:3fac0b7b144d9771 = 5.4775091389088429944458991452394e-2
   57  t:3fa76863a13e6434 = 4.57183012324055276815609489410308e-2

   57  ~sqrt(t:3ffcc00000000000) = t:3ff572969b8b5cd8 = 1.34048 
   57   sqrt(t:3ffcc00000000000) = t:3ff572969b8b5cd8 = 1.34048 
*/

    0x000000000002ed0c,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000000e05bd9,  /* c6, 41 bit shift ==> 24 significant bits */
    0x0000000042afd575,  /* c5, 34 bit shift ==> 31 significant bits */
    0x000000153649aa3b,  /* c4, 28 bit shift ==> 37 significant bits */
    0x0000078e8a48029c,  /* c3, 22 bit shift ==> 43 significant bits */
    0x00035d79941443bd,  /* c2, 15 bit shift ==> 50 significant bits */
    0x02ff4047e20d1a10,  /* c1, 07 bit shift ==> 58 significant bits */
    0x55aaa002a9d59fe4,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   58  is the Block Number   
   58  Left endpt  (fh)      = t:3fed000000000000 = 9.0625e-1 
   58  Right endpt (fh_next) = t:3fed800000000000 = 9.21875e-1 
   58  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   58  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   58  Range distance     = 1.5625e-2 
   58  Number of Terms    = 8 
   58  poly_degree        = 7 
   58  poly accuracy      = 68.2178438551675728301427476586257 
   58  Rounding bit added to leading coefficient.
   58  Coeff signs are (printed) positive.

   58  t:3ff58a68a4a8d9f3 = 1.3462912017836260078181356836247
   58  t:3fe7c4dd663ebb88 = 7.427813527082074203529947487023577e-1
   58  t:3fca3a5567fe93db = 2.04905200747048292514310499634611e-1
   58  t:3fbcf0eb7b7c03ee = 1.13051145217482688853872976192383e-1
   58  t:3fb3f5997aded94e = 7.79663014389815094075560086839261e-2
   58  t:3faed5598e603524 = 6.02214800165745966409509577071946e-2
   58  t:3fa97cd1adadeea3 = 4.97804188261998978282628358638107e-2
   58  t:3fa4ed0cfec1cca1 = 4.08710537893963813707543745318285e-2

   58  ~sqrt(t:3ffd400000000000) = t:3ff5a22073490377 = 1.35208 
   58   sqrt(t:3ffd400000000000) = t:3ff5a22073490377 = 1.35208 
*/

    0x0000000000029da2,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000000cbe68d,  /* c6, 41 bit shift ==> 24 significant bits */
    0x000000003daab31d,  /* c5, 35 bit shift ==> 30 significant bits */
    0x00000013f5997adf,  /* c4, 28 bit shift ==> 37 significant bits */
    0x0000073c3adedf01,  /* c3, 22 bit shift ==> 43 significant bits */
    0x0003474aacffd27b,  /* c2, 15 bit shift ==> 50 significant bits */
    0x02f89bacc7d770f9,  /* c1, 07 bit shift ==> 58 significant bits */
    0x58a68a4a8d9f3542,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   59  is the Block Number   
   59  Left endpt  (fh)      = t:3fed800000000000 = 9.21875e-1 
   59  Right endpt (fh_next) = t:3fee000000000000 = 9.375e-1 
   59  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   59  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   59  Range distance     = 1.5625e-2 
   59  Number of Terms    = 8 
   59  poly_degree        = 7 
   59  poly accuracy      = 68.4134762067564585231154519425194 
   59  Rounding bit added to leading coefficient.
   59  Coeff signs are (printed) positive.

   59  t:3ff5b9be5d52a9da = 1.3578475614000269655352176600971
   59  t:3fe79113ebbd7729 = 7.364596943186586647765723423475492e-1
   59  t:3fc9905b08655d82 = 1.99717883205021750017845415248186e-1
   59  t:3fbbbaf645c4deb7 = 1.0832156375260636235188316592315e-1
   59  t:3fb2ccdaf30ae936 = 7.34383433690809253366446780753041e-2
   59  t:3fac8cecf6048a35 = 5.57626772226921619952347448923025e-2
   59  t:3fa7338b94884858 = 4.53151339353474152718526633820684e-2
   59  t:3fa2be2e494c0094 = 3.6607214400647649802994151868596e-2

   59  ~sqrt(t:3ffdc00000000000) = t:3ff5d142b6dbadc5 = 1.36359 
   59   sqrt(t:3ffdc00000000000) = t:3ff5d142b6dbadc5 = 1.36359 
*/

    0x00000000000257c6,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000000b99c5d,  /* c6, 41 bit shift ==> 24 significant bits */
    0x000000003919d9ec,  /* c5, 35 bit shift ==> 30 significant bits */
    0x00000012ccdaf30b,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000006eebd917138,  /* c3, 22 bit shift ==> 43 significant bits */
    0x0003320b610cabb0,  /* c2, 15 bit shift ==> 50 significant bits */
    0x02f2227d77aee523,  /* c1, 07 bit shift ==> 58 significant bits */
    0x5b9be5d52a9da214,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   60  is the Block Number   
   60  Left endpt  (fh)      = t:3fee000000000000 = 9.375e-1 
   60  Right endpt (fh_next) = t:3fee800000000000 = 9.53125e-1 
   60  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   60  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   60  Range distance     = 1.5625e-2 
   60  Number of Terms    = 8 
   60  poly_degree        = 7 
   60  poly accuracy      = 68.6058476067736197184618236527932 
   60  Rounding bit added to leading coefficient.
   60  Coeff signs are (printed) positive.

   60  t:3ff5e8add236a58f = 1.3693063937629152836301937856689
   60  t:3fe75e9746a0b098 = 7.302967433402214595576998346082576e-1
   60  t:3fc8ed6e2933ead2 = 1.94745798224025321585591713491326e-1
   60  t:3fba96dbe79bd1c2 = 1.03864425702176388581867479826704e-1
   60  t:3fb1b9e7dd066645 = 6.92429461108981641676084033132366e-2
   60  t:3faa78871daa2142 = 5.17008041106828001124437552832314e-2
   60  t:3fa5274f8fddfb72 = 4.13155425185242181425240414610611e-2
   60  t:3fa0d183aee575af = 3.2848467921876225898236787564821e-2

   60  ~sqrt(t:3ffe400000000000) = t:3ff6000000000000 = 1.375 
   60   sqrt(t:3ffe400000000000) = t:3ff6000000000000 = 1.375 
*/

    0x0000000000021a30,  /* c7, 47 bit shift ==> 18 significant bits */
    0x0000000000a93a7c,  /* c6, 41 bit shift ==> 24 significant bits */
    0x0000000034f10e3b,  /* c5, 35 bit shift ==> 30 significant bits */
    0x00000011b9e7dd06,  /* c4, 28 bit shift ==> 37 significant bits */
    0x000006a5b6f9e6f4,  /* c3, 22 bit shift ==> 43 significant bits */
    0x00031dadc5267d5a,  /* c2, 15 bit shift ==> 50 significant bits */
    0x02ebd2e8d4161308,  /* c1, 07 bit shift ==> 58 significant bits */
    0x5e8add236a58ef08,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   61  is the Block Number   
   61  Left endpt  (fh)      = t:3fee800000000000 = 9.53125e-1 
   61  Right endpt (fh_next) = t:3fef000000000000 = 9.6875e-1 
   61  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   61  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   61  Range distance     = 1.5625e-2 
   61  Number of Terms    = 8 
   61  poly_degree        = 7 
   61  poly accuracy      = 68.7950649914394699898054167657199 
   61  Rounding bit added to leading coefficient.
   61  Coeff signs are (printed) positive.

   61  t:3ff617398f2aaa48 = 1.3806701271484075968249555232958
   61  t:3fe72d59c45f1fc5 = 7.242859683401482253392415777693003e-1
   61  t:3fc851279fdd7da8 = 1.89976647433451670924655328709374e-1
   61  t:3fb9834f57ec8b34 = 9.9659880605526052312407008643147e-2
   61  t:3fb0bad370739bb4 = 6.53507375278497585087259837133278e-2
   61  t:3fa892c5371207fd = 4.79947690701152157795891881747474e-2
   61  t:3fa350e33041e0ac = 3.7726497307575130313859503028429e-2
   61  t:3f9e3c9ae4c8a866 = 2.9528064931732344779592280142877e-2

   61  ~sqrt(t:3ffec00000000000) = t:3ff62e5acd0c3ebe = 1.38632 
   61   sqrt(t:3ffec00000000000) = t:3ff62e5acd0c3ebe = 1.38632 
*/

    0x000000000001e3ca,  /* c7, 48 bit shift ==> 17 significant bits */
    0x00000000009a871a,  /* c6, 41 bit shift ==> 24 significant bits */
    0x0000000031258a6e,  /* c5, 35 bit shift ==> 30 significant bits */
    0x00000010bad37074,  /* c4, 28 bit shift ==> 37 significant bits */
    0x00000660d3d5fb23,  /* c3, 22 bit shift ==> 43 significant bits */
    0x00030a24f3fbafb5,  /* c2, 15 bit shift ==> 50 significant bits */
    0x02e5ab388be3f89a,  /* c1, 07 bit shift ==> 58 significant bits */
    0x617398f2aaa47c94,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   62  is the Block Number   
   62  Left endpt  (fh)      = t:3fef000000000000 = 9.6875e-1 
   62  Right endpt (fh_next) = t:3fef800000000000 = 9.84375e-1 
   62  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   62  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   62  Range distance     = 1.5625e-2 
   62  Number of Terms    = 8 
   62  poly_degree        = 7 
   62  poly accuracy      = 68.981230121430022531429626900304 
   62  Rounding bit added to leading coefficient.
   62  Coeff signs are (printed) positive.

   62  t:3ff645640568c1c3 = 1.391941090707505480537041486766
   62  t:3fe6fd4e79325466 = 7.184212081070995832110352707911005e-1
   62  t:3fc7bb27b6e99dba = 1.85399021446967009454291457071218e-1
   62  t:3fb87f20bcc136ba = 9.56898175074582290882004541321404e-2
   62  t:3faf9bc707c7c81a = 6.17353627202563267859782795282664e-2
   62  t:3fa6d6e68ecf6b69 = 4.46083115891358703082223390035121e-2
   62  t:3fa1aa0079bfc5c3 = 3.4500136243774477146507417141263e-2
   62  t:3f9b3a2319b78644 = 2.658896297896819050483006863228e-2

   62  ~sqrt(t:3fff400000000000) = t:3ff65c55827df1d2 = 1.39754 
   62   sqrt(t:3fff400000000000) = t:3ff65c55827df1d2 = 1.39754 
*/

    0x000000000001b3a2,  /* c7, 48 bit shift ==> 17 significant bits */
    0x00000000008d5004,  /* c6, 41 bit shift ==> 24 significant bits */
    0x000000002dadcd1e,  /* c5, 35 bit shift ==> 30 significant bits */
    0x0000000fcde383e4,  /* c4, 29 bit shift ==> 36 significant bits */
    0x0000061fc82f304e,  /* c3, 22 bit shift ==> 43 significant bits */
    0x0002f764f6dd33b7,  /* c2, 15 bit shift ==> 50 significant bits */
    0x02dfa9cf264a8cd0,  /* c1, 07 bit shift ==> 58 significant bits */
    0x645640568c1c3746,  /* c0, 00 bit shift ==> 65 significant bits */

/*
   63  is the Block Number   
   63  Left endpt  (fh)      = t:3fef800000000000 = 9.84375e-1 
   63  Right endpt (fh_next) = t:3ff0000000000000 = 1.0 
   63  Left endpt  (fl)      = t:3ca0000000000000 = 1.110223e-16
   63  Largest fl in range   = t:3f8fffffffffffc0 = 1.5625e-2
   63  Range distance     = 1.5625e-2 
   63  Number of Terms    = 8 
   63  poly_degree        = 7 
   63  poly accuracy      = 69.1644399105245967806874375011259 
   63  Rounding bit added to leading coefficient.
   63  Coeff signs are (printed) positive.

   63  t:3ff6732f8d0e2f77 = 1.4031215200402280195938337081785
   63  t:3fe6ce6931d5858d = 7.126966450997983417272110817641817e-1
   63  t:3fc72b1587f557ab = 1.81002322565004685896270127110075e-1
   63  t:3fb7893a71af0d4c = 9.19376876400310245369832187756209e-2
   63  t:3fade31549a1e10f = 5.83731319792964934426620152163601e-2
   63  t:3fa540b748833880 = 4.15093685165723843611719490187539e-2
   63  t:3fa02d325ad74852 = 3.1594823445303747064250281945119e-2
   63  t:3f988ed03d9ce182 = 2.3982290039584969937029482016377e-2

   63  ~sqrt(t:3fffc00000000000) = t:3ff689f26c6b01d0 = 1.40868 
   63   sqrt(t:3fffc00000000000) = t:3ff689f26c6b01d0 = 1.40868 
*/

    0x00000000000188ed,  /* c7, 48 bit shift ==> 17 significant bits */
    0x0000000000816993,  /* c6, 41 bit shift ==> 24 significant bits */
    0x000000002a816e91,  /* c5, 35 bit shift ==> 30 significant bits */
    0x0000000ef18aa4d1,  /* c4, 29 bit shift ==> 36 significant bits */
    0x000005e24e9c6bc3,  /* c3, 22 bit shift ==> 43 significant bits */
    0x0002e562b0feaaf5,  /* c2, 15 bit shift ==> 50 significant bits */
    0x02d9cd263ab0b19d,  /* c1, 07 bit shift ==> 58 significant bits */
    0x6732f8d0e2f76d84,  /* c0, 00 bit shift ==> 65 significant bits */


};

#endif /* _SOFTFP_ISQRT_TAB_H_ */



