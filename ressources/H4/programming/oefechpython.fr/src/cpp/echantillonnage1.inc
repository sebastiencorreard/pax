\text{prob=L'échantillonnage au secours de la justice}
\text{imagebd="\imagedir/echa1.png" alt="Justice aux USA"}

\integer{nnn=870}
\integer{zz=randint(0..5)}
\integer{nbrech=100+\zz*25}
\real{p=0.791}
\real{aaxe=0.79}

\real{fob=0.390}

\text{listrep=r5,r6,r7,r8,r9,r10,r11,r12,r13}

\text{enonce=En mars 1972, dans un comté du sud du Texas,
 Rodrigo Partida était condamné à huit ans de prison. En novembre 1976,
  il attaqua ce jugement au motif que
 la désignation des jurés de ce comté était discriminante à l'égard des Américains
 d'origine mexicaine. Alors que 79,1% de la population de ce comté était d'origine
 mexicaine, sur les \nnn personnes convoquées pour être jurés lors d'une certaine période
 de référence, il n'y eut que 339 personnes d'origine mexicaine.<br>}
 
\text{instruction=La simulation est réalisée à l'aide de Python. Le prélèvement est réalisé
 sur des échantillons aléatoires de taille \(\nnn\) dans une population où la fréquence
 des habitants d'origine mexicaine est \(\p\). Initialiser correctement les valeurs
 des variables \(\text{p}\), \(\text{te}\), \(\text{ne}\) et jouer le code. Les fréquences des
 habitants d'origine mexicaine observées sur \(\nbrech\) échantillons simulés sont représentées
 ci-dessous :}

\text{quest1=Quelle est la fréquence des jurés d'origine mexicaine observée dans ce comté du Texas&#8239;?}
\text{quest2=Déterminer la probabilité théorique de la répartition de la population d'origine
 mexicaine dans ce comté.}
