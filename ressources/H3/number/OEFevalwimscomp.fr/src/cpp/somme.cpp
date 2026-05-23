target=somme1 somme2 somme3 somme4
#define TITRE Somme/Différence et comparaison
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
\text{size=50x25x1}
\text{compenonce0=Vous devez répondre à la question sans faire de calcul.}
#if defined TARGET_somme1
 \title{TITRE 1}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \text{sens=randitem(strictement positif,strictement négatif,positif,négatif)}
 \text{enonce0=Compléter la phrase ci-dessous.}
 \text{enonce=Si j'ajoute un nombre \sens à deux nombres \(A\) et \(B\), alors les sommes obtenues ...}
 \text{good=sont rangées dans le même ordre que \(A\) et \(B\)}
 \text{bad=sont rangées dans l'ordre inverse de celui de \(A\) et \(B\)}
#endif

#if defined TARGET_somme2
 \title{TITRE 2}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \text{sens=randitem(strictement positif,strictement négatif,positif,négatif)}
 \text{enonce0=Compléter la phrase ci-dessous.}
 \text{enonce=Si je soustrais un nombre \sens à deux nombres \(A\) et \(B\), alors les différences obtenues ... }
 \text{good=sont rangées dans le même ordre que \(A\) et \(B\)}
 \text{bad=sont rangées dans l'ordre inverse de celui de \(A\) et \(B\)}
#endif

#if defined TARGET_somme3
 \title{TITRE 3}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \integer{a=randint(11..49)}
 \integer{b=randint(51..99)}
 \text{f=texmath(randint(111..999)/randint(111.999))}
 \text{sg=randitem(+,-)}
 \text{expA=\a\sg\f}
 \text{expB=\b\sg\f}
 \integer{ch=randint(1..2)}
 \text{val=\ch=1?\A = \expA \quad ; \quad \B = \expB:\B = \expB \quad ; \quad \A = \expA}
 \text{bad=\A,\B}
 \integer{ch=randint(1..2)}
 \text{sens=item(\ch,petite,grande)}
 \text{enonce0=Parmi les deux expressions ci-dessous, laquelle est la plus \sens &#63;}
 \text{enonce=\(\val)}
 \text{good=item(\ch,\bad)}
 \text{compenonce=\compenonce0}
#endif

#if defined TARGET_somme4
 \title{TITRE 4}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \text{a=\frac{randint(11..49)}{randint(51..99)}}
 \text{b=\frac{randint(51..99)}{randint(11..49)}}
 \real{f=randint(11..99)+0.1*randint(1..9)+randint(0..9)*0.01}
 \text{sg=randitem(+,-)}
 \text{expA=\a\sg\f}
 \text{expB=\b\sg\f}
 \integer{ch=randint(1..2)}
 \text{val=\ch=1?\A = \expA \quad ; \quad \B = \expB:\B = \expB \quad ; \quad \A = \expA}
 \text{bad=\A,\B}
 \integer{ch=randint(1..2)}
 \text{sens=item(\ch,petite,grande)}
 \text{enonce0=Parmi les deux expressions ci-dessous, laquelle est la plus \sens &#63;}
 \text{enonce=\(\val)}
 \text{good=item(\ch,\bad)}
 \text{compenonce=\compenonce0}
#endif

\statement{\if{\enonce0!=}{\enonce0}
<div class="wimscenter bold">\enonce</div>
\if{\compenonce!=}{
<div class="wims_instruction">
\compenonce
</div>}}

\choice{}{\good}{\bad}
