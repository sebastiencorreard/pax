#if defined TARGET_fusee0
\answer{Méthode}{\var1;\trep}{type=click}{option=nonstop}
\answer{Hauteur phase 1}{\Yc}{type=numeric}
\answer{dH}{\dH}{type=numeric}
\answer{M}{\max}{type=numeric}
\answer{\(g(x) =)}{3;\ga,\gb,\gc,\gd}{type=radio}{option=shuffle}
\answer{\(g(x) =)}{\g1,x}{type=function}
\answer{\(x)}{\s2}{type=numex}
\condition{Choix de la méthode}{1=1}
\text{ETAPE=}

\if{\W=géométrie}{\integer{M1=1}}
\if{\W=tableaux}{\integer{M2=1}}
\if{\W=fonctions}{\integer{M3=1}}
\if{\W=équation}{\integer{M4=1}}

\if{\var1=répondre}{
  \if{\W=répondre}{
    \text{ETAPE=}
  }{
    \text{ETAPE=r2,r3,r4,r5,r6,r7}
    \text{W=répondre}
  }
}{
  \text{ETAPE=r1}
  \text{W=\var1}
}
#endif
#if defined TARGET_fuseerep
\answer{Méthode}{\var1;\trep}{type=radio}{option=nonstop}
\answer{Hauteur phase 1}{\Yc}{type=numeric}
\answer{dH}{\dH}{type=numeric}
\answer{M}{\max}{type=numeric}
\answer{\(g(x) =)}{\var5;\ga,\gb,\gc,\gd}{type=radio}{option=shuffle}{option=nonstop}
\answer{\(g(x) =)}{\g1,x}{type=function}
\answer{\(x)}{\s2}{type=numex}
\answer{Hauteur phase 1}{\var2}{type=numeric}{option=nonstop}
\answer{dH}{\var4}{type=numeric}{option=nonstop}
\answer{M}{\var3}{type=numeric}{option=nonstop}
\answer{\(x)}{\var6}{type=numex}{option=nonstop}
\condition{Choix de la méthode}{1=1}
\condition{Hauteur phase 1}{\var2=\Yc}
\condition{Hauteur supplémentaire}{\var4=\dH}
\condition{Hauteur maximale}{\var3=\max}
\condition{Formule 1 g}{\var5 = \gc}
\feedback{ \var4 < 0}{Le nombre attendu à la question 2 est positif.}

\text{ETAPE=r1}

\if{\var1=répondre}{
  \if{\W=répondre}{
    \text{ETAPE=}
  }{
    \text{ETAPE=r2,r3,r4,r5,r6,r7}
    \text{W=répondre}
  }
}{
  \if{\var2=\Yc}{\integer{M1=1}}{\if{\W=géométrie}{\integer{M1=-1}}}
  \if{\var3=\max}{\integer{M2=1}}{\if{\W=tableaux}{\integer{M2=-1}}}
  \if{\var4=\dH}{\integer{M5=1}}{\if{\W=tableaux}{\integer{M5=-1}}}
  \if{\var5=\gc}{\integer{M3=1}}{\if{\W=fonctions}{\integer{M3=-1}}}
  \if{\var6=\s2}{\integer{M4=1}}{\if{\W=équation}{\integer{M4=-1}}}
  \text{W=\var1}
  \if{\var1=géométrie}{\text{ETAPE=r1,r8}}
    \if{\var1=tableaux}{\text{ETAPE=r1,r9,r10}}
    \if{\var1=fonctions}{\text{ETAPE=r1,r5}}
    \if{\var1=équation}{\text{ETAPE=r1,r11}}
}
#endif
#if defined TARGET_canon8
\answer{Méthode}{\var1;\trep}{type=click}{option=nonstop}
\answer{Forme canonique}{\fc}{type=algexp}
\condition{Choix de la méthode}{1=1}
\text{ETAPE=}
\if{\var1=répondre}{
  \if{\W=répondre}{
    \text{ETAPE=}
  }{
    \text{ETAPE=r2}
    \text{W=répondre}
  }
}{
  \text{ETAPE=r1}
  \text{W=\var1}
  \if{\W=courbe}{\integer{M1=1}}
  \if{\W=résoudre}{\integer{M2=1}}
  \if{\W=factoriser}{\integer{M3=1}}
  \if{\W=formules}{\integer{M4=1}}
}
#endif
#if defined TARGET_canoniq
\answer{Méthode}{\var1;\trep}{type=click}{option=nonstop}
\answer{Forme canonique}{\fc}{type=algexp}
\answer{a}{\a}{type=numeric}
\answer{\(x_S)}{\xS}{type=numeric}
\answer{\(y_S)}{\yS}{type=numeric}
\condition{Choix de la méthode}{1=1}
\if{\var1=répondre}{
  \text{ETAPE=r2}
}{
  \text{ETAPE=r2,r3,r4,r5}
}
\text{W=\var1}
\if{\step>2}{\text{ETAPE=}}
#endif
