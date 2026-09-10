target=phrase1 phrase2 phrase3 phrase4 phrase5
#define TITRE Ecrire un calcul
\keywords{oper_prec}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}

\text{l=shuffle(2,3,4,5,6,7,8,9)}

#if defined TARGET_phrase1
 \title{TITRE 1}
 \text{enonce=La somme de \l[1] et du produit de \l[2] et \l[3].}
 \text{rep=\l[1]+\l[2]*\l[3]}
#endif

#if defined TARGET_phrase2
 \title{TITRE 2}
 \text{enonce=Le produit de \l[1] par la somme de \l[2] et \l[3].}
 \text{rep=\l[1]*(\l[2]+\l[3])}
#endif

#if defined TARGET_phrase3
 \title{TITRE 3}
 \text{enonce=Le quotient de \l[1] par le quotient de \l[2] par \l[3].}
 \text{rep=\l[1]/(\l[2]/\l[3])}
#endif

#if defined TARGET_phrase4
 \title{TITRE 4}
 \text{enonce=Le quotient de \l[1] par le produit de \l[2] par \l[3].}
 \text{rep=\l[1]/(\l[2]*\l[3])}
#endif

#if defined TARGET_phrase5
 \title{TITRE 5}
 \text{enonce=La différence entre la somme de \l[1] et \l[2] et le produit de \l[3] par \l[4].}
 \text{rep=(\l[1]+\l[2])-\l[3]*\l[4]}
#endif

\text{A=randitem(A,B,C,D,E,F,G,H)}

\statement{
Ecrire l'expression numérique \A correspondant à la phrase suivante :
<div class="wimscenter">\enonce</div>
<div class="wims_instruction">Vous ne devez pas effectuer le calcul.</div>
}

\answer{\A}{\rep}{type=litexp}
