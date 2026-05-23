target=tableau1 tableau2 tableau3 tableau4

#include "author.inc"
#if defined TARGET_tableau1
# define NUM 1
#endif
#if defined TARGET_tableau2
# define NUM 2
#endif
#if defined TARGET_tableau3
# define NUM 3
#endif
#if defined TARGET_tableau4
# define NUM 4
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_tableau1
 \real{coef=randint(2..9)}
 \text{lg1=shuffle(0,0,0,0)}
 \text{lg2=shuffle(1,1,1,0)}
 \text{enonce=\name_enonce \coef}
#endif
#if defined TARGET_tableau2
 \real{coef=randint(2..9)}
 \text{lg2=shuffle(0,0,0,0)}
 \text{lg1=shuffle(1,1,1,0)}
 \text{enonce=\name_enonce \coef}
#endif
#if defined TARGET_tableau3
 \real{coef=randint(2..9)}
 \matrix{don=0,0,0,1
0,0,1,0
0,1,0,0
1,0,0,0}
 \text{v=shuffle(1,2,3,4)}
 \text{lg1=row(\v[1],\don)}
 \text{lg2=row(\v[2],\don)}
 \text{enonce=\name_enonce}
#endif
#if defined TARGET_tableau4
 \real{coef=randint(2..39)/10}
 \matrix{don=0,0,0,1
0,0,1,0
0,1,0,0
1,0,0,0}
 \text{v=shuffle(1,2,3,4)}
 \text{lg1=row(\v[1],\don)}
 \text{lg2=row(\v[2],\don)}
 \text{enonce=\name_enonce}
#endif

\text{v=wims(values v for v=2 to 20)}
\text{v=shuffle(\v)}
\text{tab=item(1 to 4,\v)}
\text{tab2=}
\text{ltstep=}
\for{k=1 to 4}{
 \real{t=\tab[\k]*\coef}
 \text{tab2=wims(append item \t to \tab2)}
 \text{ltstep=\lg1[\k]=1?wims(append item r\k to \ltstep)}
 \integer{k2=4+\k}
 \text{ltstep=\lg2[\k]=1?wims(append item r\k2 to \ltstep)}
}

\steps{\ltstep}

\statement{
\enonce.
<table class="wimscenter wimsborder">
 <tr>
  \for{m=1 to 4}{<td>\if{\lg1[\m]=1}{\embed{r\m,5}}{\tab[\m]}</td>}
 </tr><tr>
  \for{n=5 to 8}{<td>\if{\lg2[\n-4]=1}{\embed{r\n,5}}{\tab2[\n-4]}</td>}
 </tr>
</table>}

\answer{Première ligne, première colonne}{\tab[1]}{type=numexp}
\answer{Première ligne, deuxième colonne}{\tab[2]}{type=numexp}
\answer{Première ligne, troisième colonne}{\tab[3]}{type=numexp}
\answer{Première ligne, quatrième colonne}{\tab[4]}{type=numexp}
\answer{Deuxième ligne, première colonne}{\tab2[1]}{type=numexp}
\answer{Deuxième ligne, deuxième colonne}{\tab2[2]}{type=numexp}
\answer{Deuxième ligne, troisième colonne}{\tab2[3]}{type=numexp}
\answer{Deuxième ligne, quatrième colonne}{\tab2[4]}{type=numexp}
