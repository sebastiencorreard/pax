\text{lang=slib(oef/env lang)}
\language{fr}
\format{html}
#if defined TARGET_pllsec2
\author{Marie-Claude, David ; Nicolas, Segarra}
\email{mcld@math.u-psud.fr }
#endif
#if defined TARGET_pointdroite || defined TARGET_equ_dr_mcd
\author{Marie-Claude, David}
\email{mcld@math.u-psud.fr }
#endif
#if defined TARGET_equ_dr0 ||  defined TARGET_equ_dr1 || defined TARGET_equ_dr2 || defined TARGET_equ_dr4 || defined TARGET_equ_dr5 || defined TARGET_syst1 || defined TARGET_syst2
\author{Frédéric, Pitoun}
\email{frederic.pitoun@free.fr}
#endif
#if defined TARGET_secnico || defined TARGET_ordonnee ||  defined TARGET_para2 || defined TARGET_equdroitevoc ||  defined TARGET_abscisse
\author{Nicolas, Segarra}
\email{Nicolas.Segarra@ac-versailles.fr}
#endif
#if defined TARGET_pllsec2 || defined TARGET_secnico || defined TARGET_ordonnee || defined TARGET_para2 ||  defined TARGET_equdroitevoc || defined TARGET_abscisse || defined TARGET_pointdroite || defined TARGET_equ_dr_mcd
\computeanswer{ no }
#endif
#if defined TARGET_equ_dr0 || defined TARGET_equ_dr1 || defined TARGET_equ_dr2 || defined TARGET_equ_dr4 || defined TARGET_equ_dr5 || defined TARGET_syst1 || defined TARGET_syst2
\computeanswer{yes}
#endif
#if defined TARGET_equ_dr0
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_secnico
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_equ_dr2
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_equ_dr4 
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_ordonnee
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_para2
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_sys3
#endif
#if defined TARGET_sys3_app
#endif
#if defined TARGET_equdroitevoc
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_equ_dr1
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_syst2
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_abscisse
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_syst1
\range{-5..5}
\precision{10000}
#endif
#if defined TARGET_equ_dr5
\range{-5..5}
\precision{10000}
#endif
\text{math_droite=\mathcal{d}}