#if defined TARGET_01CliquerHypotenuse || defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
# include "lang_cliquer_fr.inc"
#endif

#if defined TARGET_04ReconTrRect1 || defined TARGET_04ReconTrRect2
# include "lang_3cotes_fr.inc"
#endif

#if defined TARGET_05ReconTrRect3
# include "lang_multicheck_fr.inc"
#endif

#if defined TARGET_06AssocVocTrigo
# include "lang_correspond_fr.inc"
#endif

#if TARGET_07IdentifierLigneTrigo1 || defined TARGET_08IdentifierLigneTrigo2 || defined TARGET_09DonnerLigneTrigo || defined TARGET_10DeuxMesures  || defined TARGET_11LigneTrigoUniteEtape || defined TARGET_12LigneTrigoUnite
# include "lang_identifier_fr.inc"
#endif
