#if defined TARGET_lineonpnt || defined TARGET_pntonline || defined TARGET_lineonpnt || defined TARGET_lineonpnt2 || defined TARGET_distpl || defined TARGET_par1 || defined TARGET_perp1
\text{name_instruction=Dans le plan muni d'un repère, on considère la droite \(L)
  d'équation cartésienne&nbsp;}
#endif
#if defined TARGET_distpl || defined TARGET_distpl2
\matrix{name_question=Calculer la distance entre \(L) et le point de coordonnées}
\text{name_answer=Distance}
#endif
#if defined TARGET_par1
\matrix{name_question=Une équation de la droite passant par le point de coordonnées
  et parallèle à \(L) est}
\text{name_answer=Équation de la droite}
#endif
#if defined TARGET_perp1
\matrix{name_question=Une équation cartésienne de la droite passant par le point de coordonnées
  et perpendiculaire à \(L) est
}
#endif
#if defined TARGET_pntonline
\matrix{name_question=Le point \(M\) de coordonnées
  appartient à \(L) si et seulement si \(m\) est égal à
}
#endif
#if defined TARGET_lineonpnt || defined TARGET_lineonpnt2
\matrix{name_question=La droite \(L) passe par le point de coordonnées
  si et seulement si \(m\) est égal à}
#endif
#if defined TARGET_parparam || defined TARGET_par2 || defined TARGET_distpl2 || defined TARGET_pntonline2 || defined TARGET_parm2eq || defined TARGET_perp2
\text{name_instruction=Dans le plan muni d'un repère, on considère la droite \(L\)
dont une représentation paramétrique de paramètre réel \(t\) est}
# if defined TARGET_par2
\matrix{name_question=Une équation de la droite passant par le point de coordonnées
  et parallèle à \(L\) est }
# endif
# if defined TARGET_pntonline2
\matrix{name_question=Le point \(M\) de coordonnées
  appartient à \(L) si et seulement si \(m\) est égal à}
# endif
# if defined TARGET_parm2eq
\matrix{name_question=Une équation de \(L\) est }
# endif
# if defined TARGET_perp2
\matrix{name_question=Une équation cartésienne de la droite passant par le point de coordonnées
  et perpendiculaire à \(L) est}
# endif
# if defined TARGET_parparam
\text{name_question=Une représentation paramétrique de la droite \(L') passant par le point \(M\) de coordonnées
   et parallèle à \(L) est&nbsp;}
\matrix{name_condition=La représentation paramétrique donnée est celle d'une droite
  parallèle à
  passant par}
\text{name_feed=Une représentation paramétrique de \(L'\) est&nbsp;}
# endif
#endif
#if defined TARGET_pnt2eq
\text{name_instruction=Dans le plan muni d'un repère, on considère la droite
  passant par les points de coordonnées}
\text{name_question=Une équation cartésienne de cette droite est}
\text{name_and=et}
#endif
#if defined TARGET_par2 || defined TARGET_pnt2eq || defined TARGET_slope2eq || defined TARGET_parm2eq || defined TARGET_perp2
\text{name_inst=L'équation doit être de la forme}
\text{name_answer=Équation de la droite}
#endif
#if defined TARGET_slope2eq
\text{name_instruction=Dans le plan muni d'un repère, trouver une équation de la droite
passant par le point de coordonnées}
\text{name_instruction2=dont le coefficient directeur est égal à}
\text{name_question=Une équation de cette droite est}
#endif
