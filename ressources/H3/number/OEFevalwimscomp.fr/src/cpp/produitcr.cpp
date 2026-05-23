target=produitcr1 produitcr2 produitcr3 produitcr4 produitcr5


#define TITRE Egalité de fractions
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
\text{size=50x25x1}

#if defined TARGET_produitcr1
 \title{TITRE 1}
 \text{lt=shuffle(a,b,c,d)}
 \text{enonce0=Compléter la phrase ci-dessous.}
 \text{enonce=Pour vérifier si \(\frac{\lt[1]}{\lt[2]}=\frac{\lt[3]}{\lt[4]}), il faut vérifier que ... }
 \text{good=\(\lt[1]\times \lt[4] = \lt[3]\times \lt[2])}
 \text{bad=\(\lt[1] + \lt[4] = \lt[3] + \lt[2]\char32),\(\lt[1] - \lt[4] = \lt[3] - \lt[2]\char32)}
#endif

#if defined TARGET_produitcr2
 \title{TITRE 2}
 \text{lt=shuffle(a,b,c,d)}
 \text{enonce0=Compléter la phrase ci-dessous.}
 \text{enonce=Pour vérifier si \(\frac{\lt[1]}{\lt[2]}=\frac{\lt[3]}{\lt[4]}), il faut vérifier que ... }
 \text{good=\(\lt[1]\times \lt[4] = \lt[3]\times \lt[2])}
 \text{bad=\(\lt[1]\times \lt[3] = \lt[4]\times \lt[2]),\(\lt[1]\times \lt[2] = \lt[3]\times \lt[4])}
#endif

#if defined TARGET_produitcr3
 \title{TITRE 3}
 \text{lt=shuffle(2,3,4,5,6,7,8,9)}
 \text{enonce0=Compléter la phrase ci-dessous.}
 \text{enonce=Pour vérifier si \(\frac{\lt[1]}{\lt[2]}) et \(\frac{\lt[3]}{\lt[4]}) sont égaux, il faut vérifier que ... }
 \text{good=les produits \(\lt[1]\times \lt[4]) et \(\lt[3]\times \lt[2]) sont égaux}
 \text{bad=les produits \(\lt[1]\times \lt[3]) et \(\lt[4]\times \lt[2]) sont égaux,les produits \(\lt[1]\times \lt[2]) et \(\lt[3]\times \lt[4]) sont égaux}
#endif

#if defined TARGET_produitcr4
 \title{TITRE 4}
 \text{lt=shuffle(2,3,4,5,6,7,8,9)}
 \integer{ch=randint(1..2)}
 \integer{a=randitem(2,3,5)}
 \integer{b=\lt[1]*\a}
 \integer{c=\lt[2]*\a}
 \text{lt=\ch=1?\lt[1],\lt[2],\b,\c}
 \text{enonce=Les nombres \(\frac{\lt[1]}{\lt[2]}) et \(\frac{\lt[3]}{\lt[4]}) sont-ils égaux &#63;}
 \text{good=\lt[1]*(\lt[4])=\lt[3]*(\lt[2])?Oui:Non}
 \text{bad=Oui,Non}
#endif

#if defined TARGET_produitcr5
 \title{TITRE 5}
 \text{lt=shuffle(2,3,4,5,6,7,8,9)}
 \integer{a=randitem(2,3,5)}
 \integer{ch=randint(1..2)}
 \text{sg1=shuffle(-1,1)}
 \text{sg2=shuffle(-1,1)}
 \integer{b=\sg1[1]*\lt[1]}
 \integer{c=\sg1[2]*\lt[2]}
 \integer{d=\ch=1?\sg2[1]*\lt[1]*\a:\sg2[1]*\lt[3]}
 \integer{e=\ch=1?\sg2[2]*\lt[2]*\a:\sg2[2]*\lt[4]}
 \text{enonce=Les nombres \(\frac{\b}{\c}) et \(\frac{\d}{\e}) sont-ils égaux &#63;}
 \text{good=\b*(\e)=\c*(\d)?Oui:Non}
 \text{bad=Oui,Non}
#endif

\statement{\if{\enonce0!=}{\enonce0}
<div class="wimscenter bold">\enonce</div>
\if{\compenonce!=}{
<div class="wims_instruction">
\compenonce
</div>}}

\choice{}{\good}{\bad}
