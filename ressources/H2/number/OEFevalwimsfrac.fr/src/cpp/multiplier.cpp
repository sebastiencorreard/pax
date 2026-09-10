target=multiplier1 multiplier2 multiplier3 multiplier4 multiplier5
#define TITRE Multiplier deux fractions
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\conputeanswer{yes}

\text{v=shuffle(2,3,4,5,6,7,8,9)}
\text{A=randitem(A,B,C,D,E,F)}

#if defined TARGET_multiplier1 
 \title{TITRE 1}
 \text{fr1=\v[1]/\v[2]}
 \text{fr2=\v[3]/\v[2]}
#endif

#if defined TARGET_multiplier2 
 \title{TITRE 2}
 \text{fr1=\v[1]/\v[2]}
 \text{fr2=\v[1]/\v[3]}
#endif

#if defined TARGET_multiplier3 
 \title{TITRE 3}
 \text{fr1=1/\v[1]}
 \integer{a=\v[1]*\v[2]}
 \text{fr2=1/\a}
#endif

#if defined TARGET_multiplier4 
 \title{TITRE 4}
 \text{fr1=\v[1]/\v[2]}
 \text{fr2=\v[4]}
#endif

#if defined TARGET_multiplier5 
 \title{TITRE 5}
 \text{fr1=\v[1]/\v[2]}
 \integer{a=\v[3]*\v[2]}
 \text{fr2=\v[4]/\a}
#endif

\text{enonce=texmath(\fr1) \times texmath(\fr2)}
\text{rep=simplify(\fr1 * \fr2)}

\statement{
Calculer l'expression suivante :
<div class="wimscenter"> \(\A = \enonce) </div>}

\answer{\A}{\rep}{type=numexp}{option=noreduction}
