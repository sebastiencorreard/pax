target=tabvalaf2 tabvalaf3 tabvalaf1
#define TITRE Tableau de valeurs d'une fonction affine
#if defined TARGET_tabvalaf3
#define NUM 3
#endif
#if defined TARGET_tabvalaf2
#define NUM 2
#endif
#if defined TARGET_tabvalaf1
#define NUM 1
#endif
\title{TITRE NUM}
\language{fr}
\author{Rémi, Belloeil}
\email{remi.belloeil@orange.fr}
\format{html}

%% choix de la question

\integer{orient=random(0,0,1)}

%% Choix et calculs des coefficients %%
#if defined TARGET_tabvalaf2
\integer{a=random(2..5)}
\integer{a=\orient=0?\a:-\a}
#endif
#if defined TARGET_tabvalaf3
\integer{a=random(2..9)}
\integer{a=\orient=0?\a:-\a}
#endif
#if defined TARGET_tabvalaf1
\integer{a=random(2..5)}
#endif
\integer{b=random(-1,1)*randint(1..9)}
#if defined TARGET_tabvalaf2
\integer{b=\a>0?\b:\b-20*\a}
%% Choix de deux valeurs données
\integer{x1=randint(6..10)}
#endif
#if defined TARGET_tabvalaf3
%% Choix de deux valeurs données
\integer{x1=randint(6..12)}
#endif
#if defined TARGET_tabvalaf1
%% Choix de deux valeurs données
\integer{x1=randint(6..12)}
#endif
\integer{dx=randint(2..5)}
\integer{x2=\x1+\dx}
\integer{y1=\a*\x1+\b}
\integer{y2=\a*\x2+\b}
#if defined TARGET_tabvalaf1
\integer{dy=\y2-\y1}
#endif
%% Choix des autres valeurs

\integer{x0=\x1-\dx}
\integer{x3=\x2+\dx}
\integer{x4=\x3+1}

\integer{y0=\a*\x0+\b}
\integer{y3=\a*\x3+\b}
\integer{y4=\a*\x4+\b}
#if defined TARGET_tabvalaf1
\integer{h=\a*\x0}
\text{Sol=<ul><li>Lorsque \(x\) augmente de \dx, l'image \(f(x)\) augmente de \dy.</li><li>
  Lorsque \(x\) augmente de 1, l'image \(f(x)\) augmente de \a.</li><li>
  Lorsque \(x\) diminue de \dx, l'image \(f(x)\) diminue de \dy.</li><li>
  Lorsque \(x\) diminue de \x0, l'image \(f(x)\) diminue de \h.</li></ul>}
#endif
%% préparation de la réponse
#if defined TARGET_tabvalaf3
\function{f=\a*x+\b}
#endif

%%%%%%# enoncé de l'exo %%%%%%#
\text{size=10}
\text{name_question1=Compléter le tableau de valeurs d'une fonction affine.}
#if defined TARGET_tabvalaf2
\text{name_question2=Le coefficient directeur de \(f\) est \(a =\)}
#endif
#if defined TARGET_tabvalaf3
\text{name_question2=Donner la formule \(f(x)=\)}
#endif
#if defined TARGET_tabvalaf2
\text{name_hint=<ul><li>Les écarts sur les images \(f(x)\) sont proportionnels aux écarts sur les \(x\).</li><li>
  Le coefficient de proportionnalité est le coefficient directeur \(a\).</li><li>
  Autrement dit \(a = \frac{f(\x2) - f(\x1)}{\x2 - \x1}\).</li></ul>
}
#endif
#if defined TARGET_tabvalaf3
\text{name_hint=<ul><li>Les écarts sur les images \(f(x)\) sont proportionnels aux écarts sur les \(x\).</li><li>
  Le coefficient de proportionnalité est le coefficient directeur \(a\).</li><li>
  L'ordonnée à l'origine \(b\) est \(f(0)\).</li><li>
  Et \(f(x)= a*x+b\)</li></ul>
}
#endif
#if defined TARGET_tabvalaf2 || defined TARGET_tabvalaf3
\matrix{matrice=\(x\),0,\x0,\x1,\x2,\x3,\x4
\(f(x)\),reply1,reply2,\y1,\y2,reply3,reply4}
\text{mat=slib(text/matrixhtml [\matrice],wimscenter wimsborder,TH=[1;1] CAPTION="Tableau")}
#endif
#if defined TARGET_tabvalaf1
\text{name_hint=Les écarts sur les images \(f(x)\) sont proportionnels aux
  écarts sur les \(x\).
  De combien augmente \(x\) de \x1 à \x2 ? et \(f(x)\) de \y1 à \y2 ?
}
\matrix{matrice=,,,,+ reply5,,
\(x\),0,\x0,\x1,,\x2,\x3,\x4
\(f(x)\),reply1,reply2,\y1,,\y2,reply3,reply4
,,,,+ reply6,,}
\text{mat=slib(text/matrixhtml [\matrice],wimscenter wimsborder,TH=[;1] CAPTION="Tableau")}
#endif
\statement{
\name_question1
#if defined TARGET_tabvalaf2 || defined TARGET_tabvalaf3
\special{codeinput [\mat],\size, div
reply1
reply2
reply3
reply4}
#endif
#if defined TARGET_tabvalaf1
\special{codeinput [\mat],\size, div
reply1
reply2
reply3
reply4
reply5
reply6}
#endif
#if defined TARGET_tabvalaf2 || defined TARGET_tabvalaf3
<label for="reply5">\name_question2</label> \embed{reply5,\size}
#endif
}
%%#indication%%#
\hint{\name_hint}

%%%% soumission de réponse %%%%
\answer{\(f(0)\)}{\b}{type=default}
\answer{\(f(\x0)\)}{\y0}{type=default}
\answer{\(f(\x3)\)}{\y3}{type=default}
\answer{\(f(\x4)\)}{\y4}{type=default}
#if defined TARGET_tabvalaf2
\answer{\(a\)}{\a}{type=default}
#endif
#if defined TARGET_tabvalaf3
\answer{\(f(x)\)}{\f}{type=formal}
#endif

#if defined TARGET_tabvalaf1
\answer{\x2 - \x1}{\dx}{type=default}
\answer{\y2 - \y1}{\dy}{type=default}
\solution{\Sol}
#endif
