* -------- HYDROGEN COSTS -------- *

* Change in revenue when deviating from producing the fixed hydrogen demand
* in the transport sector specified by DH2_T_Y(AAA,S,T). Introduced to make
* it possible to specify more advanced hydrogen supply functions.
* SHOULD THE SUPPLY FUNCTION BE YEAR DEPENDANT?
*No steam reforming plants considered
$ontext
   + SUM(IA,
        SUM((IS3,T), IHOURSINST(IS3,T)
           * (SUM(DH2F_D,VDH2F_T(IA,IS3,T,DH2F_D)* IDEFP_T(IR,IS3,T,DEF_D1)  )


     )

     )
     )

   - SUM(IR,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DEF_U1, VDEF_T(IR,IS3,T,DEF_U1)* IDEFP_T(IR,IS3,T,DEF_U1)  )
     +  SUM(DEF_U2, VDEF_T(IR,IS3,T,DEF_U2)* IDEFP_T(IR,IS3,T,DEF_U2)  ))
     )
     )

revenue sale of hydrogen to the transport sector
+ SUM(DH2F_U,VDH2F_T(IA,IS3,T,DH2F_U) )
*        - SUM(DH2F_D,VDH2F_T(IA,IS3,T,DH2F_D) )
*
$offtext

* Variable Operation and maintainance cost of steam reforming:

   + SUM(IAGK_HASORPOT(Y,IA,IHYDROGEN_GCH4TOH2), IHOURFRAC*GOMVCOSTO(IA,IHYDROGEN_GCH4TOH2) * SUM((IS3,T), IHOURSINST(IS3,T)*VHYDROGEN_GH2_T(Y,IA,IHYDROGEN_GCH4TOH2,IS3,T)))

* Variable Operation and maintainance cost of hydrogen storage:

   + SUM(IAGK_HASORPOT(Y,IA,IHYDROGEN_GH2STO), IHOURFRAC*GOMVCOSTO(IA,IHYDROGEN_GH2STO) * SUM((IS3,T), IHOURSINST(IS3,T)*VHYDROGEN_GH2_T(Y,IA,IHYDROGEN_GH2STO,IS3,T)))

* Variable Operation and maintainance cost of methanation-DAC:

   + SUM(IAGK_HASORPOT(Y,IA,IHYDROGEN_GH2TOBIOMETH), IHOURFRAC*GOMVCOSTO(IA,IHYDROGEN_GH2TOBIOMETH) * SUM((IS3,T), IHOURSINST(IS3,T)*VGBIOMETH_T(Y,IA,IHYDROGEN_GH2TOBIOMETH,IS3,T)))

* Variable Operation and maintainance cost of biogas methanation:

   + SUM(IAGK_HASORPOT(Y,IA,IHYDROGEN_GBIOGASMETHANATION), IHOURFRAC*GOMVCOSTO(IA,IHYDROGEN_GBIOGASMETHANATION) * SUM((IS3,T), IHOURSINST(IS3,T)*VGBIOGASMETHANATION_T(Y,IA,IHYDROGEN_GBIOGASMETHANATION,IS3,T)))

* Variable Operation and maintainance cost of biogas upgrading:

   + SUM(IAGK_HASORPOT(Y,IA,IHYDROGEN_GBIOGASUPGRADING), IHOURFRAC*GOMVCOSTO(IA,IHYDROGEN_GBIOGASUPGRADING) * SUM((IS3,T), IHOURSINST(IS3,T)*VGBIOGASUPGRADING_T(Y,IA,IHYDROGEN_GBIOGASUPGRADING,IS3,T)))


* Fixed O&M and investment costs are included in
* Balmorel.gms


* H2 transmission cost:
+ SUM((IRE,IRI)$IXH2K_HASORPOT(Y,IRE,IRI),
        SUM((IS3,T), IHOURFRAC*IHOURSINST(IS3,T) * (VXH2_T(Y,IRE,IRI,IS3,T) * XH2COST(IRE,IRI))))

* Investment costs, new H2 transmission capacity
* (the average of the annuities for the two countries in question is used for international transmission):
    + SUM((IRE,IRI)$((IXH2KN(Y,IRI,IRE) OR IXH2KN(Y,IRE,IRI)) AND (NOT (IXH2KN_ES(IRE,IRI) OR IXH2KN_ES(IRI,IRE)))),IOF05*VXH2KN(Y,IRE,IRI)*XH2INVCOST(Y,IRE,IRI)*
      (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYCXH2(C))+SUM(C$CCCRRR(C,IRI),ANNUITYCXH2(C))))*SUM(IYALIAS2$(ORD(IYALIAS2) EQ ORD(Y)),IYHASANNUITYXH2(IYALIAS2,Y)))

    + SUM((IRE,IRI)$(IXH2KN_NGTOH2(Y,IRI,IRE) OR IXH2KN_NGTOH2(Y,IRE,IRI)),IOF05*VXH2KN_NGTOH2(Y,IRE,IRI)*XH2INVCOST_NGTOH2(Y,IRE,IRI)*
      (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYCXH2(C))+SUM(C$CCCRRR(C,IRI),ANNUITYCXH2(C))))*SUM(IYALIAS2$(ORD(IYALIAS2) EQ ORD(Y)),IYHASANNUITYXH2(IYALIAS2,Y)))

*Investment costs, H2 transmission capacity invested in previous years
    + SUM((IYALIAS2,IRE,IRI)$((IXH2KN(IYALIAS2,IRI,IRE) OR IXH2KN(IYALIAS2,IRE,IRI)) AND (NOT (IXH2KN_ES(IRE,IRI) OR IXH2KN_ES(IRI,IRE))) AND (ORD(IYALIAS2) LT ORD(Y))),IOF05*VXH2KN(IYALIAS2,IRE,IRI)*XH2INVCOST(IYALIAS2,IRE,IRI)*
      (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYCXH2(C))+SUM(C$CCCRRR(C,IRI),ANNUITYCXH2(C))))*IYHASANNUITYXH2(IYALIAS2,Y))

    + SUM((IYALIAS2,IRE,IRI)$((IXH2KN_NGTOH2(IYALIAS2,IRI,IRE) OR IXH2KN_NGTOH2(IYALIAS2,IRE,IRI))  AND (ORD(IYALIAS2) LT ORD(Y))),IOF05*VXH2KN_NGTOH2(IYALIAS2,IRE,IRI)*XH2INVCOST_NGTOH2(IYALIAS2,IRE,IRI)*
      (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYCXH2(C))+SUM(C$CCCRRR(C,IRI),ANNUITYCXH2(C))))*IYHASANNUITYXH2(IYALIAS2,Y))


*ECONOMIES OF SCALE
* Investment costs, new transmission capacity
$ifi not %ES_H2TRANS%==yes $goto no_economy_of_scale
    + SUM((IRE,IRI,XES)$((IXH2KN(Y,IRI,IRE) OR IXH2KN(Y,IRE,IRI)) AND (IXH2KN_ES(IRE,IRI) OR IXH2KN_ES(IRI,IRE))),
     VXH2LAMBDA(Y,IRE,IRI,XES)*XH2INVCOST_ES(Y,IRE,IRI,XES)*IOF05*
     (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYCXH2(C))+SUM(C$CCCRRR(C,IRI),ANNUITYCXH2(C))))*SUM(IYALIAS2$(ORD(IYALIAS2) EQ ORD(Y)),IYHASANNUITYXH2(IYALIAS2,Y)))

*Investment costs, transmission capacity invested in previous years

    + SUM((IYALIAS2,IRE,IRI,XES)$((IXH2KN(IYALIAS2,IRI,IRE) OR IXH2KN(IYALIAS2,IRE,IRI)) AND (IXH2KN_ES(IRE,IRI) OR IXH2KN_ES(IRI,IRE)) AND (ORD(IYALIAS2) LT ORD(Y))),
     VXH2LAMBDA(IYALIAS2,IRE,IRI,XES)*XH2INVCOST_ES(IYALIAS2,IRE,IRI,XES)*IOF05*
     (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYCXH2(C))+SUM(C$CCCRRR(C,IRI),ANNUITYCXH2(C))))*IYHASANNUITYXH2(IYALIAS2,Y))
$label no_economy_of_scale