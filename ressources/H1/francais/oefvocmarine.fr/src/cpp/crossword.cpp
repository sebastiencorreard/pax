target=crosswordniv1 crosswordniv2 crosswordniv3 crosswordniv4
:Mots croisés
Un mot croisé est proposé à partir de mots et de leurs définitions.
<p>
Auteur du modèle : Bernadette Perrin-Riou <bpr@math.u-psud.fr>
</p>
#define TITRE Les noms de la marine.
#if defined TARGET_crosswordniv1
 \title{Les noms de la marine. Niveau facile. MC}
 \text{data=wims(record 1 of crossword1)}
#endif
#if defined TARGET_crosswordniv2
\text{data=wims(record 1 of crossword2)}
\title{TITRE Niveau moyen. MC}
#endif
#if defined TARGET_crosswordniv3
\text{data=wims(record 1 of crossword3)}
 \title{TITRE Niveau difficile. MC}
#endif
#if defined TARGET_crosswordniv4
\text{data=wims(record 1 of crossword4)}
\title{TITRE Niveau excellent. MC}
#endif

:%%%%%%%% Paramètres d'exemples à redéfinir %%%%%%%%%%%%%%%%%

:\author{Anne, Dumont-Védrines; Sylvain, Dumont}
:Consigne

\text{instruction=}

:Nombre de mots maximum

\integer{N=\confparm1 iswordof 3 4 5 ? \confparm1 + 2 : 5}

:Si le paramètre est "allhelp", toutes les définitions apparaissent. Si le paramètre est "tooltip", les définitions apparaîtront
en "pop-up" en cliquant sur le numéro. Mettre un blanc pour qu'elles apparaissent
une par une sur le côté.
\text{none=allhelp}


:%%%%%%%%%%%%%% Rien à modifier avant l'énoncé %%%%%%%%%%%%%%%%

\text{cnt=rows(\data)}
\text{cnt=shuffle(\cnt)}
\text{choix=\cnt[1..\N]}
\matrix{data=\data}
\text{data=\data[\choix;]}

\text{data=slib(text/crossword \data) }

\statement{ \embed{r1} }
\answer{}{\data}{type=crossword}{option=\none}
