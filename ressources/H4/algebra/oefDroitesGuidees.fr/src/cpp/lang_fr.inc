\text{name_solution=Solution}

#if defined TARGET_alignement
\text{name_choix=n'est pas, est}
\text{name_choix2=vérifient,ne vérifient pas}
\text{name_choix3=sont alignés,ne sont pas alignés}
\text{name_answer=Pente,Coefficient,Valeur de,Ordonnée de,Coordonnées de}
\text{name_quest=Question}
#endif
#if defined TARGET_appartenance
\matrix{name_choix=vérifient,ne vérifient pas
  appartient,n'appartient pas}
\text{name_answer=calcul de,ordonnée de}
#endif
#if defined TARGET_droitespara
\matrix{name_choix=verticale,non verticale
  égales,distinctes
  ne peut pas,peut}
\text{name_choix1=l'une des droites est verticale mais l'autre non,les deux droites sont verticales,aucune droite n'est verticale et il faut calculer les coefficients directeurs}
\text{name_choix2=les droites sont parallèles,les droites ne sont pas parallèles}
#endif
#if defined TARGET_droitespara2
\text{name_choix=parallèles,non parallèles,colinéaires,non colinéaires}
\text{name_answer=Abscisse, Ordonnée, Coefficient,Droites}
#endif
#if defined TARGET_ordonneeorigine
\text{name_feed=La droite \(D\) est représentée ci-dessous. Elle coupe l'axe des ordonnées
  au point \(B\).}
#endif
#if defined TARGET_parallele
\text{pentes=égaux,opposés,inverses,différents}
\text{name_answer=Nature de,Pente de,Valeur de,Natures des pentes}
#endif
#if defined TARGET_perpendiculaire
\text{name_answer=Nature de,Pente de,Valeur de}
#endif
#if defined TARGET_parallele || defined TARGET_perpendiculaire
\text{natures=non verticale,verticale}
#endif
#if defined TARGET_perpendiculaire || defined TARGET_ordonneeorigine
\text{name_tooltip=Dans un repère orthonormal du plan&#44;
  la pente d'une droite est son coefficient directeur.}
#endif


