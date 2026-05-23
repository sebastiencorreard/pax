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
\matrix{table= infinitief,verleden tijd,voltooid deelwoord,vertaling
  de infinitief, de verleden tijd, het voltooid deelwoord, de vertaling}
#endif
#if defined TARGET_Verbesirrgulie || defined TARGET_Verbesirrgulie2
\text{name_enonce=Geef de verleden tijd en het voltooid deelwoord van het werkwoord}
\text{name_answer=De verleden tijd is ,Het voltooid deelwoord is }
\text{name_feed=En,betekent}
#endif
#if defined TARGET_Verbesirrgulie3 || defined TARGET_Verbesirrgulie4
\matrix{name_enonce=Is de werkwoordsvorm
  de infinitef, de verleden tijd, of het voltooid deelwoord
  vertaling
  Geef}
\text{name_feed=Het is}
\text{name_is=is}
\text{name_answer=Het is ook}
#endif
