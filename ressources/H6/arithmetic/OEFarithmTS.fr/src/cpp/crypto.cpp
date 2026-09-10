target=crypto1 crypto2 crypto3 crypto4
\author{Régine, Mangeard}
\email{regine@mangeard.Fr}
\format{html}

\text{lettres=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z}
#if defined TARGET_crypto1
\title{Chiffrement affine}
%% nombres premiers avec 26
\text{lstp=3,5,7,9,11,15,17,19,21,23}
\text{lstu=-1,1,3,-1,3,-4,2,-8,-4,8}
\text{lstv=9,21,15,3,19,7,23,11,5,17}
\integer{a=26}
\integer{i=randint(1..10)}
\integer{b=\lstp[\i]}
\integer{c=randint(1..25)}
\integer{u=\lstu[\i]}
\integer{v=\lstv[\i]}
\text{lstmots=MATHS,M,A,T,H,S
INCONNUE,I,N,C,O,N,N,U,E
COURBE,C,O,U,R,B,E
CARRE,C,A,R,R,E
RACINE,R,A,C,I,N,E
TANGENTE,T,A,N,G,E,N,T,E
ABSCISSE,A,B,S,C,I,S,S,E
PARABOLE,P,A,R,A,B,O,L,E
COURAGE,C,O,U,R,A,G,E
BRAVO,B,R,A,V,O
EXAMEN,E,X,A,M,E,N
REUSSITE,R,E,U,S,S,I,T,E
CONTROLE,C,O,N,T,R,O,L,E
VACANCES,V,A,C,A,N,C,E,S
}
\text{ind=shuffle(rows(\lstmots))}
\text{cemot=row(\ind[1],\lstmots)}
\text{cecrypt=row(\ind[2],\lstmots)}
\text{mot1=\cemot[1]}
\integer{n1=items(\cemot)-1}
\text{crypt1=}
\for{j1=1 to \n1}
  {
  \integer{x=position(\cemot[\j1+1],\lettres)-1}
  \integer{y=pari(lift(Mod(\b*\x+\c,\a)))}
  \text{crypt1=\crypt1 \lettres[\y+1]}
  }
\text{crypt1=wims(nospace \crypt1)}
\text{mot2=\cecrypt[1]}
\integer{n2=items(\cecrypt)-1}
\text{crypt2=}
\for{j2=1 to \n2}
  {
  \integer{x=position(\cecrypt[\j2+1],\lettres)-1}
  \integer{y=pari(lift(Mod(\b*\x+\c,\a)))}
  \text{crypt2=\crypt2 \lettres[\y+1]}
  }
\text{crypt2=wims(nospace \crypt2)}
\integer{d=pari(lift(Mod(-\v*\c,\a)))}
  \function{g=\v*y+\d}
 \statement{<p>
  On assimile les 26 lettres de l'alphabet \(A, B, \cdots, Z\) aux nombres \(0, \cdots,25\).</p>
  On code alors un nombre \(x) ainsi :
<div class="wimscenter">le nombre codé \(f(x)) est le reste de la division euclidienne de \(\b x+ \c) par \a.
<br>
  donc \(f(x) \equiv \b x + \c \;(26)).</div>
<ol>
<li> Chiffrer le mot \mot1: \embed{reply1}</li>
<li>Déterminer une fonction \(g) de déchiffrage de \(\lbrace 0,1 \cdots ,25 \rbrace\) dans lui-même,
  telle que:
<div class="wimscenter"> \(f(x) \equiv y\;(26) \Leftrightarrow g(y) \equiv x \;(26)\)</div>
<div class="wimscenter"> \(g(y) =) \embed{reply2}</div>
<div class="wims_instruction">\(g(y)) doit être de la forme \(a y + b\) avec \(0 \leq b \leq 25\)</div>
</li>
<li> Déchiffrer le mot \crypt2: \embed{reply3}</li>
</ol>
}
\answer{Cryptage de \mot1}{\crypt1}{type=nocase}
\answer{g}{\g}{type=function}
\answer{Décryptage de \crypt2}{\mot2}{type=nocase}
#endif
#if defined TARGET_crypto2
\title{Chiffrement de Lester Hill}
\integer{det=0}
\while{\det=0}
  {
\text{V=slib(matrix/invertible 2,6,Z)}
\integer{a=pari(lift(Mod(\V[1;1],23)))}
\integer{b=pari(lift(Mod(\V[1;2],23)))}
\integer{c=pari(lift(Mod(\V[2;1],23)))}
\integer{d=pari(lift(Mod(\V[2;2],23)))}
\integer{det=pari(lift(Mod(\a*\d-\b*\c,23)))}
}
\integer{f=pari(lift(Mod(-\c,23)))}
\integer{e=pari(lift(Mod(-\b,23)))}
\text{eq1=texmath(maxima(\a*x+\b*y))}
\text{eq2=texmath(maxima(\c*x+\d*y))}
\text{eq1=wims(replace internal x by x_1 in \eq1)}
\text{eq1=wims(replace internal y by x_2 in \eq1)}
\text{eq2=wims(replace internal x by x_1 in \eq2)}
\text{eq2=wims(replace internal y by x_2 in \eq2)}

\text{eq3=texmath(\d*y_1+\f*x_2)}
\text{eq4=texmath(\e*x_1+\a*x_2)}
\integer{ev1=pari(lift(Mod(\a*10+\b*11,23)))}
\integer{ev2=pari(lift(Mod(\c*10+\d*11,23)))}
\text{exc=\lettres[\ev1+1]\lettres[\ev2+1]}
\text{lstmots=MATH,M,A,T,H
COURBE,C,O,U,R,B,E
CARRES,C,A,R,R,E,S
RACINE,R,A,C,I,N,E
REPERE,R,E,P,E,R,E
PLAN,P,L,A,N
DROITE,D,R,O,I,T,E
PLUS,P,L,U,S
CASE,C,A,S,E
BIEN,B,I,E,N
}
\text{ind=shuffle(rows(\lstmots))}
\text{cemot=row(\ind[1],\lstmots)}
\text{cecrypt=row(\ind[2],\lstmots)}
\text{mot1=\cemot[1]}
\integer{n1=(items(\cemot)-1)/2}
\text{crypt1=}
\for{j1=1 to \n1}
  {
  \integer{x1=position(\cemot[2*\j1],\lettres)-1}
  \integer{x2=position(\cemot[2*\j1+1],\lettres)-1}
  \integer{y1=pari(lift(Mod(\a*\x1+\b*\x2,23)))}
  \integer{y2=pari(lift(Mod(\c*\x1+\d*\x2,23)))}
  \text{crypt1=\crypt1 \lettres[\y1+1]\lettres[\y2+1]}
  }
\text{crypt1=wims(nospace \crypt1)}
\text{mot2=\cecrypt[1]}
\integer{n2=(items(\cecrypt)-1)/2}
\text{crypt2=}
\for{j2=1 to \n2}
  {
  \integer{x1=position(\cecrypt[2*\j2],\lettres)-1}
  \integer{x2=position(\cecrypt[2*\j2+1],\lettres)-1}
  \integer{y1=pari(lift(Mod(\a*\x1+\b*\x2,23)))}
  \integer{y2=pari(lift(Mod(\c*\x1+\d*\x2,23)))}
  \text{crypt2=\crypt2 \lettres[\y1+1]\lettres[\y2+1]}
  }
\text{crypt2=wims(nospace \crypt2)}
\integer{dd=\a*\d-\b*\c}
\text{bm=pari(lift(Mod(-\b,23)))}
\text{cm=pari(lift(Mod(-\c,23)))}
\statement{
  On assimile les 23 lettres de l'alphabet \(A,B,\cdots,W) aux nombres \(0,\cdots,22).<p>
  La fonction de codage agit sur des couples de nombres choisis dans \(\lbrace 0,1,\cdots,22 \rbrace):
</p>
<div class="wimscenter">\(f:(x_1;x_2) \mapsto (y_1;y_2))</div>
  Dans cet exemple, on a :
<div class="wimscenter">\(\begin{array}{lll} y_1 &\equiv &\eq1 \;(23) \\ y_2 &\equiv &\eq2\;(23) \end{array})</div>
  ainsi le mot "KL" correspondant au couple \((x_1;x_2)=(10;11)) est codé par le couple \((y_1;y_2)=(\ev1;\ev2)), soit "\exc".
<ol>
<li> Chiffrer le mot \mot1: \embed{reply1}</li>
<li>Déterminer une fonction \(g) de déchiffrage de \(\lbrace 0,1 \cdots ,22 \rbrace) dans lui même, telle que:
<div class="wimscenter"> \(f(x_1;x_2) \equiv (y_1;y_2)\;(23) \Leftrightarrow g(y_1;y_2) \equiv (x_1;x_2) \;(23))</div>
  sous la forme:
<div class="wimscenter"> \(\det x_1 \equiv ) \embed{reply2,4}\(y_1)+\embed{reply3,4}\(y_2 \; (23))</div>
<div class="wimscenter"> \(\det x_2 \equiv ) \embed{reply4,4}\(y_1)+\embed{reply5,4}\(y_2 \; (23))</div>
<div class="wims_instruction">
Donner les réponses sous forme d'un entier entre 0 et 22.
</div>
</li>
<li> Trouver un couple d'entiers relatifs \((u;v)\) avec \(0 \leq u \leq 22\) tel que \(\det u +23 v = 1\):
<div class="wimscenter"> \(u=) \embed{reply6,4} et \(v=) \embed{reply7,4}</div></li>
<li> Déchiffrer le mot \crypt2: \embed{reply8}</li>
</ol>
}
\answer{Cryptage de \mot1}{\crypt1}{type=nocase}
\answer{Coefficient 1 de g}{\d}{type=numeric}
\answer{Coefficient 2 de g}{\bm}{type=numeric}
\answer{Coefficient 3 de g}{\cm}{type=numeric}
\answer{Coefficient 4 de g}{\a}{type=numeric}
\answer{u}{\u}{type=numeric}
\answer{v}{\v}{type=numeric}
\answer{Décryptage de \crypt2}{\mot2}{type=nocase}
\condition{\det*\u+23*\v=1 and \u >0 and \u <23}
#endif
#if defined TARGET_crypto4
\title{Chiffrement à clé publique RSA}
\text{lstp=2,3,5,7,11,13,17,19,23,29,31,37,41,43}
\integer{p=\lstp[randint(2..5)]}
\integer{q=\lstp[randint(6..14)]}
\integer{n=\p*\q}
\integer{ve=(\p-1)*(\q-1)}
\integer{xi=randint(0..25)}
\text{mstep=r1,r2
r3,r4}
\steps{\mstep}
\statement{
  On considère les nombres premiers \(p = \p\) et \(q = \q\), ainsi que le nombre \(n=p\times q =\n\).
\if{\step=1}
 {
<ol>
<li> Déterminer un entier \(e\) inférieur à 15, premier avec \((p-1)(q-1)\):
<div class="wimscenter"> \(e=) \embed{reply1}</div></li>
<li> Déterminer un entier naturel \(d\) tel que \(e \times d -1\) soit divisible par \((p-1)(q-1)\):
<div class="wimscenter"> \(d=\) \embed{reply2}</div></li>
</ol>
 }
 {<p>
  On a choisi les entiers \(e=\e\) et \(d = \d\).<br>
  On veut coder la lettre \lettres[\xi+1] correspondant au nombre \(x=\xi\).
</p><ol>
<li> Calculer le reste \(c\) de la division de \(x^e\) par \(n\): \(c=)\embed{reply3,4}</li>
<li> Calculer le reste \(y\) de la division de \(c^d\) par \(n\): \(y=)\embed{reply4,4}</li>
</ol>
}
}
\answer{e}{\e}{type=numeric}
\answer{d}{\d}{type=numeric}
\answer{c}{\ci}{type=numeric}
\answer{y}{\yi}{type=numeric}
\integer{rnul=pari(lift(Mod(\e*\d-1,\ve)))}
\integer{cf=pari(lift(Mod(\xi^\e,\n)))}
\integer{yf=pari(lift(Mod(\ci^\d,\n)))}
\condition{entier e}{gcd(\e,\ve)=1}
\condition{entier d}{\rnul=0}
\condition{entier c}{\ci=\cf}
\condition{entier y}{\yi=\yf}
\feedback{gcd(\e,\ve)!=1}{Utiliser la décomposition en facteurs premiers de \((p-1)(q-1)=\ve\)
  et choisir un entier \(e\) n'apparaissant pas dans cette décomposition!}
\feedback{rnul<>0}{Il faut calculer les coefficients de la relation de bezout liant \(e) et \((p-1)(q-1) = \ve\).}
\feedback{gcd(\e,\ve)!=1 and \rnul=0 and \ci<>\cf}{On trouve \(c = \cf\)}
\feedback{gcd(\e,\ve)!=1 and \rnul=0 and \ci=\cf and \yi<>\yf}{On doit retrouvert \(y = x\)}
#endif
#if defined TARGET_crypto3
\title{Chiffrement à clé secrète}
\text{lstcles=MATH,M,A,T,H
PLAN,P,L,A,N
PLUS,P,L,U,S
CASE,C,A,S,E
BIEN,B,I,E,N
TOIT,T,O,I,T
COIN,C,O,I,N
FORT,F,O,R,T
}
\text{cemot=randomrow(\lstcles)}
\text{cle=\cemot[1]}
\text{suite=}
\for{i=1 to 4}
 {
 \integer{jl=position(\cemot[\i+1],\lettres)}
 \text{suite=wims(append item \jl to \suite)}
 }
\text{lstmots=MATHS,M,A,T,H,S
INCONNUE,I,N,C,O,N,N,U,E
COURBE,C,O,U,R,B,E
CARRE,C,A,R,R,E
RACINE,R,A,C,I,N,E
TANGENTE,T,A,N,G,E,N,T,E
ABSCISSE,A,B,S,C,I,S,S,E
PARABOLE,P,A,R,A,B,O,L,E
COURAGE,C,O,U,R,A,G,E
BRAVO,B,R,A,V,O
EXAMEN,E,X,A,M,E,N
REUSSITE,R,E,U,S,S,I,T,E
CONTROLE,C,O,N,T,R,O,L,E
VACANCES,V,A,C,A,N,C,E,S
}
\text{ind=shuffle(rows(\lstmots))}
\text{cemot=row(\ind[1],\lstmots)}
\text{cecrypt=row(\ind[2],\lstmots)}
\text{mot1=\cemot[1]}
\integer{n1=items(\cemot)-1}
\text{crypt1=}
\text{add=}
\for{j1=1 to \n1}
  {
  \integer{x1=position(\cemot[\j1+1],\lettres)-1}
  \integer{k=pari(lift(Mod(\j1,4)))}
  \integer{k=\k=0?4}
  \text{add=wims(append item \suite[\k] to \add)}
  \integer{y1=pari(lift(Mod(\x1+\suite[\k],26)))}
  \text{crypt1=\crypt1 \lettres[\y1+1]}
  }
\text{crypt1=wims(nospace \crypt1)}
\text{mot2=\cecrypt[1]}
\integer{n2=items(\cecrypt)-1}
\text{crypt2=}
\for{j2=1 to \n2}
  {
  \integer{x1=position(\cecrypt[\j2+1],\lettres)-1}
  \integer{k=pari(lift(Mod(\j2,4)))}
  \integer{k=\k=0?4}
  \integer{y1=pari(lift(Mod(\x1+\suite[\k],26)))}
  \text{crypt2=\crypt2 \lettres[\y1+1]}
  }
\text{crypt2=wims(nospace \crypt2)}
\statement{
  On dispose d'une clé qui peut être un mot, une phrase, etc. et
  celle-ci fournit une suite de nombres: la liste des rangs dans
  l'alphabet dans l'ordre des lettres qui la forment.<br>
  Par exemple, \cle fournit la suite \suite.<br>
  Avec cette clé, pour chiffrer un texte, on remplace chaque lettre
  par son rang \(x) dans l'alphabet (avec 0 pour A, 1 pour B, et 25 pour Z), on ajoute \suite[1] au rang de la
  première lettre, \suite[2] au rang de la deuxième lettre, \suite[2] au rang de la
  troisième lettre, \suite[4] au rang de la quatrième lettre et on recommence
  avec la même clé, \suite[1] au rang de la cinquième lettre, etc.<br>
  On obtient les rangs des lettres qui remplacent.<br>
  Ces rangs sont les restes de la division de \(x+k) par 26, \(k) varie
  pour chaque lettre en fonction de la clé.<br>
  L'intérêt est qu'une lettre n'est pas toujours codée de la même façon.
<ol>
<li>
  Chiffrer le message \mot1 avec la clé \cle.
  <div class="wimscenter"> message crypté= \embed{reply1}
</div></li>
<li>
  Déchiffrer le message \crypt2 avec la clé \cle.
  <div class="wimscenter"> message décrypté= \embed{reply2}
</div></li>
</ol>
}
\answer{Cryptage de \mot1}{\crypt1}{type=nocase}
\answer{Décryptage de \crypt2}{\mot2}{type=nocase}
#endif
