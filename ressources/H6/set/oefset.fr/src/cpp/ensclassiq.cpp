target=ssensplan ssensclassiq ssensclassiq0
\language{fr}
\author{Sophie, Lemaire}
\email{sophie.lemaire@universite-paris-saclay.fr}
\description{il s'agit de calculer le nombre d'éléments d'un ensemble. Le type de l'ensemble peut varier en renouvelant l'exercice.}
\keywords{set_theory,combinatorics}
\computeanswer{yes}
\precision{10000}
\format{html}
#include "common.inc"
#if defined TARGET_ssensplan
#define GGG C2 -
#endif
#if defined TARGET_ssensclassiq || defined TARGET_ssensclassiq0
#define GGG C3 -
#endif
#include "lang_ensclassiq_fr.inc"
\if{\lang=it}{
#include "lang_ensclassiq_it.inc"
}
\if{\lang=es}{
#include "lang_ensclassiq_es.inc"
}

#if defined TARGET_ssensplan
\title{GGG Cardinal d'un sous-ensemble du plan}
\observation{La question porte sur 6 types d'ensembles sauf si la valeur la plus faible du paramètre "Complexité des ensembles" est choisi. Dans ce dernier cas, la question ne porte que sur 2 types d'ensembles.}
\integer{d=randint(0..40)-20}
\integer{nb2=randint(10..50)}
\integer{f=\nb2+(\d)-1}
\text{E2=\d, ..., \f}

\if{\confparm1=1}{\integer{c=random(5,6)}}{\integer{c=randint(1..6)}}

\if{\c=1}{
\integer{p=randint((\d-(\f)+2)..(\f-(\d)-2))}
\text{ens=\(\{ (x_1, x_2)\in\{\E2\}^2, x_1 - x_2 = \p \}\)}
\integer{nelt=min(\f,\f-(\p))-max(\d, \d-(\p))+1}
}
\if{\c=2}{
\integer{p=randint((2*\d+2)..(2*\f-2))}
\text{ens=\(\{ (x_1, x_2)\in\{\E2\}^2, x_1 + x_2 = \p \}\)}
\integer{nelt=min(\f,\p-(\d))-max(\d, \p-(\f))+1}
}
\if{\c=3}{
\text{ens=\(\{ (x_1,x_2)\in\{\E2\}^2, x_1 < x_2 \} \)}
\integer{nelt=binomial(\nb2,2)}
}
\if{\c=4}{
\text{ens=\(\{ (x_1,x_2)\in\{\E2\}^2, x_1 \leq x_2 \} \)}
\integer{nelt=binomial(\nb2+1,2)}
}
\if{\c=5}{
\integer{n1=randint(2..5)}
\text{ens=\(\{\E2\}^{2} \)}
\integer{nelt=(\nb2)^2}
}
\if{\c=6}{
\integer{d1=randint(0..40)-20}
\integer{nb1=randint(10..50)}
\integer{f1=\nb1+(\d1)-1}
\text{E1=\d1, ..., \f1}
\integer{n1=randint(2..5)}
\text{ens={\E1} x {\E2} }
\integer{nelt=\nb1*\nb2}
}
#endif
#if defined TARGET_ssensclassiq || defined TARGET_ssensclassiq0
# if defined TARGET_ssensclassiq
   \title{GGG Cardinal d'un ensemble classique}
# else
   \title{GGG Cardinal d'un ensemble classique 0}
# endif
\observation{La question porte sur 14 types d'ensembles lorsque le paramètre "Complexité des ensembles" n'est pas fixé ou dans des groupes de 4 à 5 ensembles différents en fonction de la valeur de ce paramètre.}
\integer{n2= \confparm1<3 ? randint(3..6): randint(5..10)}
\integer{n3=randint(2..(\n2-1))}
\integer{p=randint(2..(\n2-1))}
\integer{d=randint(0..20)-10}
\integer{nb1=randint(2..8)}
\integer{nb2=randint(5..8)}
\integer{f=\nb2+(\d)-1}
\text{liste=wims(makelist x for x=-20 to 20)}
\text{elt=slib(data/random \nb1,item, \liste)}
\text{E1=wims(sort numeric list of \elt)}
\text{E2=\d, ..., \f}
\if{\confparm1=1}{\integer{c=randint(0..4)}}
   {\if{\confparm1=2}{\integer{c=randint(5..9)}}
       {\if{\confparm1=3}{\integer{c=randint(10..13)}}
           {\integer{c=randint(0..13)}}
        }
   }

\if{\c=0}{
\text{ens={\({\omega}\), \({\omega}\) \name_vocab[1;] \(\{\E2 \} \)}}
\integer{nelt=2^(\nb2)}
}
\if{\c=1}{
\integer{n1=randint(2..5)}\integer{n2=min(randint(2..5),8-\n1)}
\text{ens=\(\{\E1\}^{\n1}\times\{\E2\}^{\n2} \)}
\integer{nelt=(\nb1)^(\n1)*(\nb2)^(\n2)}
}
\if{\c=2}{
\integer{p=randint(2..(\nb2-1))}
\text{ens={ \(\omega,\; \omega \subset\{\E2\}\) \name_vocab[2;] Card( \({\omega}\) ) = \p } }
\integer{nelt=binomial(\nb2,\p)}
}
\if{\c=3}{
#if defined TARGET_ssensclassiq0
   \text{tmpstr=wims(makelist x_{ v} for v = 1 to \n2)}
   \text{tmpstr =wims (replace internal , by + in \tmpstr)}
   \text{ens={ \((x_1,..,x_{\n2})\) \(\in\{0,1\}^{\n2}\), \(\tmpstr =\p\)} }
#else
    \text{ens={ \((x_1,..,x_{\n2})\) \(\in\{0,1\}^{\n2}\), \(\sum_{i=1}^{\n2}x_i=\p\)} }
#endif
 \integer{nelt=binomial(\n2,\p)}
}
\if{\c=4}{
\integer{n=randint(3..\nb2)}
\text{ens={ \((x_1,..,x_{\n})\) \(\in\{\E2\}^{\n}\), \(\forall i\neq j\), \(x_i\neq x_j\) }}
\integer{nelt=factorial(\nb2)/factorial(\nb2-\n)}
}
niveau 2
\if{\c=5}{
\integer{p=randint(2..(\n3-1))}
#if defined TARGET_ssensclassiq0
  \text{tmpstr=wims(makelist x_{ v} for v = 1 to \n3)}
  \text{tmpstr =wims (replace internal , by + in \tmpstr)}
  \text{ens={ \((x_1,..,x_{\n2})\) \(\in\{0,1\}^{\n2}\), \(\tmpstr=\p\) }}
#else
 \text{ens={ \((x_1,..,x_{\n2})\) \(\in\{0,1\}^{\n2}\), \(\sum_{i=1}^{\n3}x_i=\p\) }}
#endif
\integer{nelt=binomial(\n3,\p)*2^(\n2-\n3)}
}
\if{\c=6}{
\integer{e1=randint(1,2)}
\integer{e2=randint(1,2)}
\if{\e1=1}
  {\text{ED=\E1}\integer{nd=\nb1}}
  {\text{ED=\E2}\integer{nd=\nb2}}
\if{\e2=1}
  {\text{EF=\E1}\integer{nf=\nb1}}
  {\text{EF=\E2}\integer{nf=\nb2}}
\text{ens={ \name_vocab[9;1] \(f\) : {\ED} \(\rightarrow\) {\EF} }}
\integer{nelt=\nf^(\nd)}
}
\if{\c=7}{
\integer{e1=randint(1,2)}
\if{\e1=1}
  {\text{ED=\E1}\integer{nd=\nb1}}
  {\text{ED=\E2}\integer{nd=\nb2}}
\text{ens={ \name_vocab[9;2] \(f\) : {\ED} \(\rightarrow\) {\ED} }}
\integer{nelt=(\nd)!}
}
\if{\c=8}{
\if{\nb1<\nb2}
  {\text{ED=\E1}\text{EF=\E2}\integer{nd=\nb1}\integer{nf=\nb2}}
  {\text{ED=\E2}\text{EF=\E1}\integer{nd=\nb2}\integer{nf=\nb1}}

\text{ens={ \name_vocab[9;3] \(f\) : {\ED} \(\rightarrow\) {\EF} }}
\integer{nelt=(\nf)!/(\nf-\nd)!}
}
\if{\c=9}{
\integer{p=randint(3..(\nb2-1))}
\text{ens=\(\{ (x_1,..,x_{\p})\in\{\E2\}^{\p}, x_1<...<x_{\p} \} \)}
\integer{nelt=binomial(\nb2,\p)}
}
niveau 3 : multinomiale, hypergeometrique, partition avec les tailles de blocs donnes
\if{\c=10}{
\integer{n3=randint(2..(\n2-2))}
\integer{p=randint(1..(\n3-1))}
\integer{p2=randint(1..(\n2-\n3))}
\integer{n4=\n3+1}
\text{ens={ \((x_1,..,x_{\n2})\) \(\in\{0,1\}^{\n2}\), \(\sum_{i=1}^{\n3}x_i=\p\) \name_vocab[2;] \(\sum_{i=\n4}^{\n2}x_i=\p2\) }}
\integer{nelt=binomial(\n3,\p)*binomial(\n2-\n3,\p2)}
}
\if{\c=11}{
\integer{r=randint(3..5)}
\text{l=a,b,c,d,e}
\text{u=shuffle(\r)}
\text{l1=\l[\u[1]]}
\text{l2=\l[\u[2]]}
\integer{p=randint(1..(\n2-2))}
\integer{p2=randint(1..(\n2-\p))}
\integer{p3=\n2-\p-\p2}
\integer{n4=\n3+1}
\text{ens={\( (x_1,..,x_{\n2})\) \(\in\{\l[1..\r]\}^{\n2}\),
Card( {i, \( x_i = \l1\)} ) = \p \name_vocab[2;] Card( {i, \( x_i = \l2\)} ) = \p2 }}
\integer{nelt=binomial(\n2,\p)*binomial(\n2-\p,\p2)*(\r-2)^\p3}
}
\if{\c=12}{
\integer{p=randint(3..(\nb2-1))}
\text{ens=\(\{ (x_1,..,x_{\p})\in\{\E2\}^{\p}, x_1 \leq ...\leq x_{\p} \} \)}
\integer{nelt=binomial(\nb2+\p-1,\p)}
}
\if{\c=13}{
\integer{p=randint(3..5)}
\text{ens=\(\{ (x_1,..,x_{\p})\in\NN^{\p}, x_1 + ...+ x_{\p}=\n2 \} \)}
\integer{nelt=binomial(\n2+\p-1,\n2)}
}

#endif
\statement{
\instruction?
<div class="wimscenter" style="background-color:#F0F0F0">\(E\)= \ens</div>}
\answer{Card( E )}{\var}{type=numeric}
\real{err=pari(abs(\var-\nelt))}
\condition{\name_vocab[3;]}{\err==0}{option=hide}
\feedback{\err==0}{<div class="oef_indgood">
\name_vocab[4;] \nelt \name_vocab[5;2].
</div>}
\feedback{\err>0}{<div class="oef_indbad">
\name_vocab[4;] \nelt \name_vocab[5;2] \name_vocab[6;] \var
\if{\var=1 or \var=0}{\name_vocab[5;1].}{\name_vocab[5;2].}
</div>}
#if defined TARGET_ssensplan
\feedback{\err>0 and \confparm1=1}{<div class="oef_indbad">
\name_vocab[7;]
\if{\c=6}{\name_vocab[8;1] &#91; \d1 ; \f1 &#93; x &#91; \d ; \f &#93;}{\name_vocab[8;2] &#91; \d ; \f &#93;<sup>2</sup>}.</div>}
#endif
