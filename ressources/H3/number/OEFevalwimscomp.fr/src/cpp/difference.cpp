target=difference1 difference2 difference3 difference4 difference5
#define TITRE Comparaison et différence
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
\text{size=50x25x1}

#if defined TARGET_difference1
 \title{TITRE 1}
 \text{enonce0=Compléter la phrase ci-dessous.}
 \text{enonce=Si je veux comparer deux nombres, je peux regarder le signe de leur...}
 \text{good=différence}
 \text{bad=produit,somme,quotient}
#endif

#if defined TARGET_difference2
 \title{TITRE 2}
 \text{name=slib(lang/fname fr,boy)}
 \real{n=randint(1111..99999)/10^randint(1..3)}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \integer{ch=randint(1..2)}
 \text{sens=item(\ch,grand,petit)}
 \text{enonc0=Quel est le plus \sens de ces deux nombres &#63;}
 \text{enonce=\(\A-\B=\n)}
 \text{bad=\A,\B,aucun des deux}
 \text{good=item(\ch,\bad)}
#endif

#if defined TARGET_difference3
 \title{TITRE 3}
 \text{name=slib(lang/fname fr,girl)}
 \real{n=-randint(1111..99999)/10^randint(1..3)}
 \text{lt=shuffle(A,B,C,D,E,F)}
 \text{A=\lt[1]}
 \text{B=\lt[2]}
 \integer{ch=randint(1..2)}
 \text{sens=item(\ch,grand,petit)}
 \text{enonce0=\name a calculé la différence entre deux nombres \(A\) et \B. Elle trouve :
 <div class="wimscenter">\(\A -\B=\n)</div> Quel est le plus \sens de ces deux nombres &#63;}
 \text{bad=\B,\A,aucun des deux}
 \text{good=item(\ch,\bad)}
#endif

#if defined TARGET_difference4
 \title{TITRE 4}
 \text{name=slib(lang/fname fr,girl)}
 \integer{x=randint(111111..999999)}
 \integer{a=randint(\x-50..\x-25)}
 \integer{b=randint(\x-24..\x)}
 \integer{c=randint(\x+1..\x+25)}
 \integer{d=randint(\x+26..\x+50)}
 \real{res=\a/\c-\b/\d}
 \if{\res=0}{
  \integer{a=232407}
  \integer{b=232450}
  \integer{c=232469}
  \integer{d=232500}
  \real{res=\a/\c-\b/\d}
 }
 \text{tmp=wims(char 1 to -2 of \times10^{})}
 \text{tmp2=wims(char -1 of 10^{})}
 \text{res=e isin \res?wims(replace internal e by \tmp in \res)\tmp2}
 \text{A=texmath(\a/\c)}
 \text{B=texmath(\b/\d)}
 \integer{ch=randint(1..2)}
 \text{sens=item(\ch,grand,petit)}
 \text{enonce0=\name a calculé la différence entre \(\A) et \(\B) avec sa calculatrice. Voici le résultat :<div class="wimscenter">\(\A - \B = \res)</div> Quel est le plus \sens de ces deux nombres &#63;}
 \text{bad=\res>0?\(\A),\(\B):\(\B),\(\A)}
 \text{good=item(\ch,\bad)}
#endif

#if defined TARGET_difference5
 \title{TITRE 5}
 \integer{x=randint(111111..999999)}
 \integer{a=randint(\x-50..\x-25)}
 \integer{b=randint(\x-24..\x)}
 \integer{c=randint(\x+1..\x+25)}
 \integer{d=randint(\x+26..\x+50)}
 \real{res=\a/\c-\b/\d}
 \if{\res=0}{
  \integer{a=232407}
  \integer{b=232450}
  \integer{c=232469}
  \integer{d=232500}
  \real{res=\a/\c-\b/\d}
 }
 \text{A=texmath(\a/\c)}
 \text{B=texmath(\b/\d)}
 \integer{ch=randint(1..2)}
 \text{sens=item(\ch,grand,petit)}
 \text{enonce0=Lequel de ces deux nombres est le plus \sens  &#63;}
 \text{enonce= \(\A \quad\quad ; \quad\quad \B)}
 \text{bad=\res>0?\(\A),\(\B):\(\B),\(\A)}
 \text{good=item(\ch,\bad)}
#endif

\statement{\if{\enonce0!=}{\enonce0}
\if{\enonce!=}{<div class="wimscenter bold">\enonce</div>}
\if{\compenonce!=}{
<div class="wims_instruction">
\compenonce
</div>}
}
\choice{}{\good}{\bad}
