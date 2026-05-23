target=approchee1 approchee2 approchee3 approchee4 approchee5
#define TITRE Valeur Approchée
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}

\integer{d=randitem(3,7,9,11,13,17)}
\integer{n=randint(1..\d-1)+\d*randint(10..20)}
\integer{a=randint(10..40)}
\integer{d=\a*\d}
\integer{n=\a*\n}
\text{A=randitem(A,B,C,D,E,F)}


#if defined TARGET_approchee1
 \title{TITRE 1}
 \text{name=slib(lang/fname fr,girl)}
 \real{res=\n/\d}
 \text{enonce=\name a utilisé sa calculatrice pour calculer le quotient de \n par \d et a trouvé : <div class="wimscenter"> \(\A = \n \div \d = \res)</div>}
 \integer{type=1}
#endif

#if defined TARGET_approchee2
 \title{TITRE 2}
 \text{name=slib(lang/fname fr,girl)}
 \real{res=\n/\d}
 \text{enonce=\name a utilisé sa calculatrice pour calculer le quotient de \n par \d et a trouvé : <div class="wimscenter"> \(\A = \n \div \d = \res)</div>}
 \text{type=2,3}
#endif

#if defined TARGET_approchee3
 \title{TITRE 3}
 \real{n=\n/10^randint(0..2)}
 \real{d=\d/10^randint(0..2)}
 \real{res=\n/\d}
 \text{enonce=Soit : <div class="wimscenter"> \(\A = \n \div \d)</div>}
 \text{type=1,2,3}
#endif

#if defined TARGET_approchee4
 \title{TITRE 4}
 \real{n=-\n/10^randint(0..2)}
 \real{d=-\d/10^randint(0..2)}
 \real{res=\n/\d}
 \text{enonce=Soit : <div class="wimscenter"> \(\A = \n \div (\d))</div>}
 \text{type=1,2,3}
#endif

#if defined TARGET_approchee5
 \title{TITRE 5}
 \real{n=-\n/10^randint(0..2)}
 \real{d=\d/10^randint(0..2)}
 \real{res=\n/\d}
 \text{enonce=Soit : <div class="wimscenter"> \(\A = \n \div \d)</div>}
 \text{type=2,3}
#endif

\integer{chprec=randitem(1,2,3,4)}
\text{listerme=à l'unité,au dixième,au centième,au millième}
\integer{type=randitem(\type)}
\text{fonction=item(\type,rint,floor,ceil)}
\real{rep=\fonction(\res*10^(\chprec-1))/10^(\chprec-1)}
\text{ltquestion=Quel est l'arrondi
randitem(Quel est l'arrondi par défaut,Quelle est la troncature)
Quel est l'arrondi par excés}
\text{question=row(\type,\ltquestion)}

\statement{
\enonce
<p>
\question \listerme[\chprec] de \A ?</p>
<div>
<b>Votre réponse</b> : \embed{r1,8}
</div>}
\answer{}{\rep}{type=numexp}
