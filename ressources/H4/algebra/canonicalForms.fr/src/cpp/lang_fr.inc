#if defined TARGET_varfct2degcomp || defined TARGET_varffctinv
\text{choix1=strictement croissante,strictement décroissante}
\text{choix3=strictement croissante sur,strictement décroissante sur}
# if defined TARGET_varfct2degcomp
\text{choix2=positives,négatives}
# endif
# if defined TARGET_varffctinv
\text{choix2=positives non nulles ,négatives non nulles}
# endif
#endif
