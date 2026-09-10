\title{Question 703 NS Associer un diagramme}
\keywords{quizz,descriptive_statistics}
\observation{Question du sujet zéro sujet-specifique-3_0.pdf publié sur EDUSCOL en juin 2025 }

\integer{n=12*randitem(2,3,4,5,10)}
\integer{e2=\n/2}
\integer{e3=\n/3}
\integer{e4=\n/4}
\integer{e6=\n/6}
%%%% MB : modif première colonne A, B, C, D devient 1,2,3,4, colonne 4 feedback
\matrix{eff=1,\e2 personnes dans le groupe 1, \e4 personnes dans le groupe 2 et les autres dans le groupe 3,la moitié dans le groupe 1 et le quart dans le groupe 2 donc le quart dans le groupe 3.
1,\e4 personnes dans le groupe 1, \e2 personnes dans le groupe 2 et les autres dans le groupe 3,le quart dans le groupe 1 et la moitié dans le groupe 2 donc le quart dans le groupe 3.
2,\e2 personnes dans le groupe 1, \e3 personnes dans le groupe 2 et les autres dans le groupe 3,la moitié dans le groupe 1 et le tiers dans le groupe 2 donc un sixième dans le groupe 3.
2,\e2 personnes dans le groupe 1, \e6 personnes dans le groupe 2 et les autres dans le groupe 3,la moitié dans le groupe 1 et le sixième dans le groupe 2 donc deux tiers dans le groupe 3.
3,\e3 personnes dans le groupe 1, \e6 personnes dans le groupe 2 et les autres dans le groupe 1,le tiers dans le groupe 1 et un sixième dans le groupe 2 donc la moitié dans le groupe 3.
3,\e4 personnes dans le groupe 1, les groupes 2 et 3 avec le même nombre de personnes,le quart dans le groupe 1 et la moitié de trois quart \(\frac{3}{8}\) dans les autres groupes.
3,\e4 personnes dans le groupe 2, les groupes 1 et 3 avec le même nombre de personnes,le quart dans le groupe 2 et la moitié de trois quart \(\frac{3}{8}\) dans les autres groupes.
4,plus de la moitié des personnes dans le groupe 1, les autres réparties équitablement dans les groupes 2 et 3,plus de la moitié dans le groupe 1 donc moins d'un quart pour les deux autres groupes avec les même effectifs.}
\text{cas=randomrow(\eff)}

\text{img=imgq703a.png,imgq703b.png,imgq703c.png,imgq703d.png}


\text{enonce=Les \n personnes présentes à une exposition sont réparties dans des groupes&nbsp;&#58; \cas[2]&#44; \cas[3]. <br>Quelle représentation décrit la situation&nbsp;&#58; }

%%% MB
\text{good=<img src="\imagedir/\img[\cas[1]]" alt="" >}
\text{casbad=\cas[1]=1?2,3,4}
\text{casbad=\cas[1]=2?1,3,4}
\text{casbad=\cas[1]=3?2,1,4}
\text{casbad=\cas[1]=4?2,3,1}
\text{bad1=<img src="\imagedir/\img[\casbad[1]]" alt="" >}
\text{bad2=<img src="\imagedir/\img[\casbad[2]]" alt="" >}
\text{bad3=<img src="\imagedir/\img[\casbad[3]]" alt="" >}
\text{bads=\bad1,\bad2,\bad3}
\text{feedback=La bonne réponse est&nbsp;&#58;<div class="wimscenter"><img src="\imagedir/\img[\cas[1]]" width="15%" alt="" ></div> En effet on peut interpréter l'énoncé comme suit&nbsp;&#58; \cas[4]}
