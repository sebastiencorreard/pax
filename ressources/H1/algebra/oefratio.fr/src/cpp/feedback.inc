#if defined TARGET_ratio2confparm

feedback{(\reply1=\nbre2 and \reply2=\nbre1) or (\reply8=\nbre2 and \reply15=\nbre1) or (\reply24=\nbre2 and \reply25=\nbre2)}{<div class="macss">Vous n'avez pas respecté l'ordre donné dans l'énoncé.
<br>Le premier nombre du ratio correspond à la première personne et le deuxième nombre du ratio correspond à la seconde personne.</div>}

\feedback{(\reply5=\rep2 and \reply6=\rep1) or (\reply22=\rep2 and \reply23=\rep1) or (\reply29=\rep2 and \reply30=\rep1) or (\reply31=\rep2 and \reply32=\rep1)}{<div class="macss">Faites attention à la conclusion, vous avez inversé vos réponses&nbsp;!</div>}

#endif
#if defined TARGET_ratio3confparm
\feedback{\reply1=\nbre1 and \reply2=\nbre3 and \reply3=\nbre2  or \reply2=\nbre2 and \reply1=\nbre3 and \reply3=\nbre1 or \reply3=\nbre3 and \reply1=\nbre2 and \reply2=\nbre1 or \reply1=\nbre2 and \reply2=\nbre3 and \reply3=\nbre1 or \reply1=\nbre3 and \reply2=\nbre1 and \reply3=\nbre2
\text{listerep=\rep1,\rep2,\rep3}}{ <div class="macss">Vous n'avez pas respecté l'ordre donné dans l'énoncé.
le premier nombre du ratio correspond à la première personne, le deuxième nombre du ratio correspond à la deuxième personne et le troisième nombre du ratio à la troisième personne.</div>}

\feedback{(\reply9 isitemof \listerep and \reply9!=listerep[1]) or (\reply10 isitemof \listerep and \reply10!=listerep[2]) or (\reply11 isitmof \listerep and \reply12!=listerep[3])}{<div class="macss">
Faites attention à la conclusion, vous avez inversé vos réponses&nbsp;!</div>}

\integer{tot=\reply9+\reply10+\reply11}
\feedback{\tot<>\eff}{<div class="macss">, La somme \tot de vos réponses n'est pas égale à \eff.</div>}

#endif

#if defined TARGET_ratio2

feedback{(\reply2=\nbre2 and \reply1=\nbre1) or (\reply9=\nbre2 and \reply16=\nbre1) or (\reply25=\nbre2 and \reply26=\nbre2)}{
<div class="macss">Vous n'avez pas respecté l'ordre donné dans l'énoncé.
<br>Le premier nombre du ratio correspond à la première personne et le deuxième nombre du ratio correspond à la seconde personne.</div>}

\feedback{(\reply6=\rep2 and \reply7\rep1) or (\reply23=\rep2 and \reply24=\rep1) or (\reply30=\rep2 and \reply31=\rep1) or (\reply32=\rep2 and \reply33=\rep1)}{<div class="macss">
Faites attention à la conclusion, vous avez inversé vos réponses&nbsp;!</div>}

#endif
