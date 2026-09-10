target=ajouter1 ajouter2 ajouter3 ajouter4 ajouter5
#define TITRE Ajouter/soustraire deux fractions
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\conputeanswer{yes}

\text{v=shuffle(2,3,4,5,6,7,8,9)}
\text{A=randitem(A,B,C,D,E,F)}

#if defined TARGET_ajouter1 
 \title{TITRE 1}
 \text{fr1=\v[1]/\v[2]}
 \text{fr2=\v[3]/\v[2]}
 \text{sg=+}
#endif

#if defined TARGET_ajouter2 
 \title{TITRE 2}
 \text{fr1=\v[1]/\v[2]}
 \text{fr2=\v[1]/\v[3]}
 \text{sg=-}
#endif

#if defined TARGET_ajouter3 
 \title{TITRE 3}
 \text{fr1=1/\v[1]}
 \integer{a=\v[1]*\v[2]}
 \text{fr2=1/\a}
 \text{sg=+}
#endif

#if defined TARGET_ajouter4 
 \title{TITRE 4}
 \text{fr1=\v[1]/\v[2]}
 \integer{a=\v[3]*\v[2]}
 \text{fr2=\v[4]/\a}
 \text{sg=+}
#endif

#if defined TARGET_ajouter5 
 \title{TITRE 5}
 \text{fr1=\v[1]/\v[2]}
 \integer{a=\v[3]*\v[2]}
 \text{fr2=\v[4]/\a}
 \text{sg=-}
#endif

\text{enonce=texmath(\fr1) \sg texmath(\fr2)}
\text{rep=simplify(\fr1 \sg \fr2)}

\statement{
Calculer l'expression suivante :
<div class="wimscenter"> \(\A = \enonce) </div>}

\answer{\A}{\rep}{type=numexp}{option=noreduction}
