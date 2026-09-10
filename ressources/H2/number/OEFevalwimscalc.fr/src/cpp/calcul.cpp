target=calculA1 calculA2 calculA3 calculA4 calculA5 calculB1 calculB2 calculB3 calculB4 calculB5 calculC1 calculC2 calculC3 calculC4 calculC5 calculD1 calculD2 calculD3 calculD4 calculD5 calculE1 calculE2 calculE3 calculE4 calculE5

\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
#define TITRE Calcul
\keywords{calculation}
#if defined TARGET_calculA1
 \title{TITRE A1}
 \integer{a=randint(2..5)*10}
 \integer{b=randint(2..3)*10+randint(2..9)}
 \integer{c=\a-\b}
 \integer{d=randint(5..25)}
 \text{calcul=\b+\d+\c}
 \text{affichage=A}
#endif

#if defined TARGET_calculA2
 \title{TITRE A2}
 \integer{a=randint(2..5)*10}
 \integer{b=randint(2..3)*10+randint(2..9)}
 \integer{c=\a-\b}
 \integer{d=randint(5..19)}
 \text{calcul=\b-\d+\c}
 \text{affichage=A}
#endif

#if defined TARGET_calculA3
 \title{TITRE A3}
 \integer{a=randint(12..29)}
 \integer{b=randint(30..45)}
 \integer{c=\a+\b}
 \integer{d=randint(5..19)}
 \text{calcul=\a+\d+\b-\c}
 \text{affichage=A}
#endif

#if defined TARGET_calculA4
 \title{TITRE A4}
 \integer{a=randint(2..5)*10}
 \real{b=randint(2..3)*10+randint(2..9)+0.01*randint(1..9)+randint(1..9)*0.1}
 \real{c=\a-\b}
 \real{d=randint(5..19)+0.01*randint(1..9)+randint(1..9)*0.1}
 \text{calcul=\b+\d+\c}
 \text{affichage=A}
#endif

#if defined TARGET_calculA5
 \title{TITRE A5}
 \integer{a=randint(2..5)*10}
 \real{b=randint(2..3)*10+randint(2..9)+0.01*randint(1..9)+randint(1..9)*0.1}
 \real{c=\a-\b}
 \real{d=randint(5..19)+randint(1..9)*0.1}
 \text{calcul=\b-\d+\c}
 \text{affichage=A}
#endif

#if defined TARGET_calculB1
 \title{TITRE B1}
 \text{a=randrow(2,5
4,25)}
 \text{a=shuffle(\a)}
 \integer{b=randint(2..3)*10+randint(2..9)}
 \text{calcul=\a[1]*\b*\a[2]}
 \text{affichage=A}
#endif

#if defined TARGET_calculB2
 \title{TITRE B2}
 \text{a=randrow(2,5
4,25)}
 \text{a=shuffle(\a)}
 \integer{b=randint(2..3)*10+randint(2..9)}
 \text{calcul=\a[1]*\b/\a[2]}
 \text{affichage=\a[1] \times \b \div \a[2]}
#endif

#if defined TARGET_calculB3
 \title{TITRE B3}
 \text{a=shuffle(2,3,4)}
 \integer{b=\a[1]*\a[2]}
 \real{c=(randint(2..5)+0.1*randint(1..9))*\a[1]}
 \text{calcul=\c*\b/\a[1]}
 \text{affichage=\c\times \b \div \a[1]}
#endif

#if defined TARGET_calculB4
 \title{TITRE B4}
 \text{a=shuffle(2,3,4)}
 \integer{b=\a[1]*\a[2]}
 \integer{c=randint(2..5)}
 \integer{c=\b*\c*\a[1]}
 \text{calcul=\c/\b/\a[1]}
 \text{affichage=\c \div \b \div \a[1]}
#endif

#if defined TARGET_calculB5
 \title{TITRE B5}
 \text{a=randrow(2,5
4,25)}
 \text{a=shuffle(\a)}
 \real{c=randint(11..29)*\a[1]}
 \text{calcul=\c/\a[1]*\a[2]}
 \text{affichage=\c\div \a[1] \times \a[2]}
#endif

#if defined TARGET_calculC1
 \title{Calcul C1}
 \text{a=randrow(2,5
4,25)}
 \text{a=shuffle(\a)}
 \integer{d=randint(5..25)}
 \text{calcul=\a[1]*\a[2]+\d}
 \text{affichage=A}
#endif

#if defined TARGET_calculC2
 \title{Calcul C2}
 \integer{a=randint(2..5)*10}
 \integer{b=randint(2..3)*10+randint(2..9)}
 \integer{c=\a-\b}
 \integer{d=randint(5..25)}
 \text{calcul=\b+\c*\d}
 \text{affichage=A}
#endif

#if defined TARGET_calculC3
 \title{TITRE C3}
 \integer{a=randint(2..5)*10}
 \integer{b=randint(2..3)*10+randint(2..9)}
 \integer{c=\a+\b}
 \integer{d=randint(5..25)}
 \text{calcul=\c-\b*\d}
 \text{affichage=A}
#endif

#if defined TARGET_calculC4
 \title{TITRE C4}
 \real{a=randint(2..7)*10+randint(1..9)+0.1*randint(1..9)}
 \integer{c=randint(5..15)}
 \integer{b=\c*randitem(2,4,5,3,9)}
 \text{calcul=\a+\b/\c}
 \text{affichage=\a+\b \div \c}
#endif

#if defined TARGET_calculC5
 \title{TITRE C5}
 \real{a=randint(2..7)*10+randint(1..9)+0.1*randint(1..9)}
 \integer{c=randint(5..15)}
 \integer{p=randint(1..2)}
 \real{b=\c*randitem(2,4,5,3,9)/10^\p}
 \text{calcul=\a-\b/\c}
 \text{affichage=\a-\b \div \c}
#endif

#if defined TARGET_calculD1
 \title{TITRE D1}
 \integer{a=randint(2..5)*10}
 \integer{b=randint(2..3)*10+randint(2..9)}
 \integer{c=\a-\b}
 \integer{d=randint(5..25)}
 \text{calcul=(\b+\c)*\d}
 \text{affichage=A}
#endif

#if defined TARGET_calculD2
 \title{TITRE D2}
 \text{l=shuffle(2,3,4,5,6,7)}
 \integer{a=(\l[2]+\l[2])*randint(5..25)}
 \text{calcul=\a/(\l[1]+\l[2])}
 \text{affichage=\a \div (\l[1]+\l[2])}
#endif

#if defined TARGET_calculD3
 \title{TITRE D3}
 \text{l=shuffle(2,3,4,5,6,7)}
 \integer{a=(\l[2]*\l[2])*randint(5..25)/10}
 \text{calcul=\a/(\l[1]*\l[2])}
 \text{affichage=\a \div (\l[1] \times \l[2])}
#endif

#if defined TARGET_calculD4
 \title{TITRE D4}
 \integer{a=randint(4..7)*10}
 \real{b=randint(2..3)*10+randint(2..9)+0.1*randint(1..9)}
 \integer{c=\a-\b}
 \integer{d=randint(1..2)*10+randint(1..9)}
 \integer{a=randint(4..7)*10+randint(1..9)}
 \text{calcul=(\b+\c)*(\a-\d)}
 \text{affichage=A}
#endif

#if defined TARGET_calculD5
 \title{TITRE D5}
 \text{l=shuffle(2,3,4,5,6)}
 \real{c=randint(1..4)*10+randint(1..9)}
 \real{b=(\l[1]+\l[2])*(randint(2..3)*10+randint(2..9))+\c}
 \text{calcul=(\b-\c)/(\l[1]+\l[2])}
 \text{affichage=(\b-\c) \div (\l[1]+\l[2])}
#endif

#if defined TARGET_calculE1
 \title{TITRE E1}
 \text{a=randrow(2,5
4,25)}
 \text{a=shuffle(\a)}
 \integer{b=randint(2..3)*10+randint(2..9)}
 \text{calcul=\a[1]*\b/\a[2]}
 \text{affichage=A}
#endif

#if defined TARGET_calculE2
 \title{TITRE E2}
 \text{a=randint(2,3,4,5,6,7)}
 \integer{c=randint(1..9)+0.1*randint(1..9)}
 \integer{b=randint(21..55)*\a+\c}
 \text{calcul=(\b-\c)/\a}
 \text{affichage=A}
#endif

#if defined TARGET_calculE3
 \title{TITRE E3}
 \text{l=shuffle(2,3,4,5,6,7)}
 \integer{a=(\l[2]+\l[2])*randint(5..25)}
 \real{c=randint(11..55)+0.1*randint(1..9)}
 \text{calcul=\a/(\l[1]+\l[2])+\c}
 \text{affichage=A}
#endif

#if defined TARGET_calculE4
 \title{TITRE E4}
 \text{l=shuffle(2,3,4,5,6)}
 \real{c=randint(1..4)*10+randint(1..9)}
 \real{b=(\l[1]+\l[2])*(randint(2..3)*10+randint(2..9))+\c}
 \text{calcul=(\b-\c)/(\l[1]+\l[2])}
 \text{affichage=A}
#endif

#if defined TARGET_calculE5
 \title{TITRE E5}
 \text{l=shuffle(2,3,4,5,6,7)}
 \integer{a=(\l[2]*\l[2])*randint(5..25)/10}
 \real{c=randint(11..55)+0.1*randint(1..9)}
 \text{calcul=\c-\a/(\l[1]*\l[2])}
 \text{affichage=A}
#endif


\text{A=randitem(A,B,C,D,E,F,G,H)}
\text{affichage=A isin \affichage?texmath(\calcul)}
\real{rep=\calcul}

\statement{
Calculer l'expression suivante :
<div class="wimscenter">\(\A = \affichage)</div>}

\answer{\A}{\rep}{type=numexp}{option=noreduction}
