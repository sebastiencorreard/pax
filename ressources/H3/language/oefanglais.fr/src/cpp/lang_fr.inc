#if defined TARGET_ecrire1 || defined TARGET_ecrire2 || defined TARGET_ecrire3 || defined TARGET_ecrire4
\text{name_msg=Vous êtes en train de préparer une feuille d'exercices&nbsp;,
  attention,
  Les mots suivants n'ont pas été trouvés&nbsp;,
  Il vous est conseillé de reconfigurer l'exercice.}
\text{name_enonce=Écoutez le verbe}
#endif
#if defined TARGET_ecrire1
\text{name_enonce2=Écrivez-le.,À quelle forme est-il}
#endif
#if defined TARGET_ecrire2
\text{name_enonce2=Donner sa forme pleine,1 personne du singulier}
#endif
#if defined TARGET_ecrire3
\text{name_enonce2=Écrire sa forme pleine,1 ère personne du singulier}
#endif
#if defined TARGET_ecrire4
\text{name_enonce2=Donnez les autres formes
  (complète à la 1 personne du singulier ou to + infinitif)}
#endif
#if defined TARGET_Verbesirrgulie || defined TARGET_Verbesirrgulie2 || defined TARGET_Verbesirrgulie3 || defined TARGET_Verbesirrgulie4
\matrix{table= infinitif,preterit,participe passé, traduction
  l'infinitif, le preterit, le participe passé, la traduction}
#endif
#if defined TARGET_Verbesirrgulie || defined TARGET_Verbesirrgulie2
\text{name_enonce=Donner le preterit et le participe passé du verbe}
\text{name_answer=Le preterit est ,Le participe passé est }
\text{name_feed=Et,signifie}
#endif
#if defined TARGET_Verbesirrgulie3 || defined TARGET_Verbesirrgulie4
\matrix{name_enonce=La forme verbale
  est-elle l'infinitif, le preterit ou le participe passé
  traduction
  En donner}
\text{name_feed=C'est à la fois}
\text{name_is=est}
\text{name_answer=C'est}
#endif
