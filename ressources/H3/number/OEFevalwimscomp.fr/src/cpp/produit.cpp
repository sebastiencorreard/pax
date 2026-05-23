target=produit1 produit2 produit3 produit4 produit5
#define TITRE Produit et comparaison
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
\text{size=50x25x1}

\text{compenonce0=Vous devez répondre à la question sans faire de calcul.}
#if defined TARGET_produit1
 \title{TITRE 1}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \text{enonce0=Compléter la phrase ci-dessous.}
 \text{enonce=Si je multiplie deux nombres \(\A\) et \(B\) par un nombre strictement positif, alors les produits obtenus ... }
 \text{good=sont rangées dans le même ordre que \(A\) et \(B\)}
 \text{bad=sont rangées dans l'ordre inverse de celui de \(A\) et \(B\)}
#endif

#if defined TARGET_produit2
 \title{TITRE 2}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \text{enonce0=Compléter la phrase ci-dessous.}
 \text{enonce=Si je multiplie deux nombres \(A\) et \(B\) par un nombre strictement négatif, alors les produits obtenus ... }
 \text{bad=sont rangées dans le même ordre que \(A\) et \(B\)}
 \text{good=sont rangées dans l'ordre inverse de celui de \(A\) et \(B\)}
#endif

#if defined TARGET_produit3
 \title{TITRE 3}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \integer{a=randint(11..49)}
 \integer{b=randint(51..99)}
 \text{sg=randitem(+,-)}
 \text{f=texmath(\sg randint(111..999)/randint(111.999))}
 \text{f=- isin \sg?(\f)}
 \text{expA=\a\times \f}
 \text{expB=\b\times \f}
 \integer{ch=randint(1..2)}
 \text{val=\ch=1?\A = \expA \quad ; \quad \B = \expB:\B = \expB \quad ; \quad \A = \expA}
 \text{bad=+ isin \sg?\A,\B:\B,\A}
 \integer{ch=randint(1..2)}
 \text{sens=item(\ch,petite,grande)}
 \text{enonce0=Parmi les deux expressions ci-dessous, laquelle est la plus \sens &#63;}
 \text{enonce=\(\val)}
 \text{good=item(\ch,\bad)}
 \text{compenonce=\compenonce0}
#endif

#if defined TARGET_produit4
 \title{TITRE 4}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \text{a=\frac{randint(11..49)}{randint(51..99)}}
 \text{b=\frac{randint(51..99)}{randint(11..49)}}
 \text{sg=randitem(+,-)}
 \real{f=randint(11..99)+0.1*randint(1..9)+randint(0..9)*0.01}
 \text{f=- isin \sg?(-\f)}
 \text{expA=\a\times \f}
 \text{expB=\b\times \f}
 \integer{ch=randint(1..2)}
 \text{val=\ch=1?\A = \expA \quad ; \quad \B = \expB:\B = \expB \quad ; \quad \A = \expA}
 \text{bad=+ isin \sg?\A,\B:\B,\A}
 \integer{ch=randint(1..2)}
 \text{sens=item(\ch,petite,grande)}
 \text{enonce0=Parmi les deux expressions ci-dessous, laquelle est la plus \sens &#63;}
 \text{enonce=\(\val)}
 \text{good=item(\ch,\bad)}
 \text{compenonce=\compenonce0}
#endif

#if defined TARGET_produit5
 \title{TITRE 5}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \integer{t=randint(11..99)}
 \real{a=\t+randint(5..9)*+randint(1..9)*0.01+randint(1..9)*0.001}
 \real{a=-\a}
 \real{b=\t+randint(1..4)*+randint(1..9)*0.01+randint(1..9)*0.001}
 \real{b=-\b}
 \text{sg=randitem(+,-)}
 \real{f=randint(11..99)+0.1*randint(1..9)+randint(0..9)*0.01}
 \text{f=- isin \sg?(-\f)}
 \text{expA=\a\times \f}
 \text{expB=\b\times \f}
 \integer{ch=randint(1..2)}
 \text{val=\ch=1?\A = \expA \quad ; \quad \B = \expB:\B = \expB \quad ; \quad \A = \expA}
 \text{bad=+ isin \sg?\A,\B:\B,\A}
 \integer{ch=randint(1..2)}
 \text{sens=item(\ch,petite,grande)}
 \text{enonce0=Parmi les deux expressions ci-dessous, laquelle est la plus \sens &#63;}
 \text{enonce=\(\val)}
 \text{good=item(\ch,\bad)}
#endif

\statement{\if{\enonce0!=}{\enonce0}
<div class="wimscenter bold">\enonce</div>
\if{\compenonce!=}{
<div class="wims_instruction">
\compenonce
</div>}}

\choice{}{\good}{\bad}
