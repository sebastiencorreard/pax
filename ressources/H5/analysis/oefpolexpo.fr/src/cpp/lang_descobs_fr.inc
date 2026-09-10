%%%%%%%%%%%%% DESCRIPTION - OBSERVATION %%%%%%%%%%%%%%%
\description{
Cet exercice demande de calculer la fonction dérivée du 

# if defined TARGET_1k_exp || defined TARGET_2aff_exp || defined TARGET_3secdeg_exp
produit
# endif

# if defined TARGET_4Qexp_k || defined TARGET_5Qexp_aff || defined TARGET_6Qexp_secdeg
quotient
# endif

d'une fonction exponentielle par une 
# if defined TARGET_1k_exp || defined TARGET_4Qexp_k
constante.
# endif
# if defined TARGET_2aff_exp || defined TARGET_5Qexp_aff
fonction affine.
# endif
# if defined TARGET_3secdeg_exp || defined TARGET_6Qexp_secdeg
fonction trinôme du second degré.
# endif
}

\observation{Cet exercice d'apprentissage demande de calculer la fonction dérivée du 

# if defined TARGET_1k_exp || defined TARGET_2aff_exp || defined TARGET_3secdeg_exp
produit
# endif

# if defined TARGET_4Qexp_k || defined TARGET_5Qexp_aff || defined TARGET_6Qexp_secdeg
quotient
# endif

d'une fonction exponentielle par une 
#if defined TARGET_1k_exp || defined TARGET_4Qexp_k
constante.
#endif
#if defined TARGET_2aff_exp || defined TARGET_5Qexp_aff
fonction affine.
#endif
#if defined TARGET_3secdeg_exp || defined TARGET_6Qexp_secdeg
fonction trinôme du second degré.
#endif
}
