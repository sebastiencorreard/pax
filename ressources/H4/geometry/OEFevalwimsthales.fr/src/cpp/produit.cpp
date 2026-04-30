target=produit1 produit2 produit3 produit4 produit5
#define TITRE Quatrième proportionnelle
#if defined TARGET_produit1
# define NUM 1
#endif
#if defined TARGET_produit2
# define NUM 2
#endif
#if defined TARGET_produit3
# define NUM 3
#endif
#if defined TARGET_produit4
# define NUM 4
#endif
#if defined TARGET_produit5
# define NUM 5
#endif
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\title{TITRE NUM}
\integer{size=3}

\text{v=wims(values v for v=2 to 9)}
\text{v=shuffle(\v)}
\integer{d1=\v[1]*\v[3]}
\integer{n1=\v[2]*\v[3]}
\integer{d2=\v[1]*\v[4]}
\integer{n2=\v[2]*\v[4]}
\integer{ch=randint(1..2)}
#if defined TARGET_produit3
\integer{a=randint(5..20)}
\integer{b=\n1+\a}
#endif
#if defined TARGET_produit4
\integer{a=randint(5..20)}
\integer{b=\d1+\a}
#endif
#if defined TARGET_produit5
\integer{b=randint(5..20)}
\integer{a=\n1+\b}
#endif

\statement{
 Compléter l'égalité suivante :
<div class="wimscenter">
#if defined TARGET_produit1
\if{\ch=1}{
  \special{mathmlinput [\frac{reply1}{\d1}=\frac{\n2}{\d2}], \size,noanswer
 reply1
 }
}{
    \special{mathmlinput [\frac{\n2}{\d2}=\frac{reply1}{\d1}], \size,noanswer
 reply1
 }
}
#endif
#if defined TARGET_produit2
\if{\ch=1}{
\special{mathmlinput [\frac{\n1}{reply1}=\frac{\n2}{\d2}], \size,noanswer
 reply1
 }
}{
  \special{mathmlinput [\frac{\n2}{\d2}=\frac{\n1}{reply1}], \size,noanswer
 reply1
 }
}
#endif
#if defined TARGET_produit3
\if{\ch=1}{
\special{mathmlinput [\frac{reply1 - \a}{\d1}=\frac{\n2}{\d2}], \size,noanswer
 reply1
 }
}{
  \special{mathmlinput [\frac{\n2}{\d2}=\frac{reply1 - \a}{\d1}], \size,noanswer
 reply1
 }
}
#endif
#if defined TARGET_produit4
\if{\ch=1}{
 \special{mathmlinput [\frac{\n1}{reply1 - \a}=\frac{\n2}{\d2}], \size,noanswer
 reply1
 }
}{
  \special{mathmlinput [\frac{\n2}{\d2}=\frac{\n1}{reply1 - \a}], \size,noanswer
 reply1
 }
}
#endif
#if defined TARGET_produit5
\if{\ch=1}{
 \special{mathmlinput [\frac{\a-reply1}{\d1}=\frac{\n2}{\d2}], \size,noanswer
 reply1
 }
}{
  \special{mathmlinput [\frac{\n2}{\d2}=\frac{\a-reply1}{\d1}], \size,noanswer
 reply1
 }
}
#endif
</div>
}
#if defined TARGET_produit1
\answer{}{\n1}{type=numexp}
#endif
#if defined TARGET_produit2
\answer{}{\d1}{type=numexp}
#endif
#if defined TARGET_produit3 || defined TARGET_produit4 || defined TARGET_produit5
\answer{}{\b}{type=numexp}
#endif

