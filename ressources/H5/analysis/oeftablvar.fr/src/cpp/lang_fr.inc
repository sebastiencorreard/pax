#if defined TARGET_TVF1 || defined TARGET_TVF21
\text{choix= décroissante,ni croissante ni décroissante, croissante}
#endif
#if defined TARGET_TVF2 || defined TARGET_TVF22 || defined TARGET_TVF3 || defined TARGET_TVF24
\text{choix=oui,non}
#endif

#if defined TARGET_TVF3
\text{name_pos=positive,négative}
#endif
#if defined TARGET_TVF24
\text{name_majo=majorée,minorée}
#endif

#if defined TARGET_TVF2 || defined TARGET_TVF3
\text{name_cont=continue}
#endif

#if defined TARGET_TVF2 || defined TARGET_TVF3
\text{cont=continue}
#else
\text{cont=}
#endif
