target=calcprod1 calcprod2 calcprod4
#define TITRE Calculer un produit
\author{G.,Bayle;Fabrice,Guerimand}
\email{fwguerima@free.fr}



#if defined TARGET_calcprod1
 \title{TITRE 1}
 \text{s=shuffle(-1,1)}
 \text{l=shuffle(2,3,4,5,6,7,8,9)}
 \text{l=item(1 to 2,\l)}
#endif


#if defined TARGET_calcprod2
 \title{TITRE 2}
 \text{s=-1,-1}
 \text{l=shuffle(2,3,4,5,6,7,8,9)}
 \text{l=item(1 to 2,\l)}
#endif

#if defined TARGET_calcprod4
 \title{TITRE 4}
 \integer{nbf=randint(3..5)}
 \text{s=randrow(-1,-1,1,1
-1,-1,-1,1)}
 \text{s=shuffle(\s),1}
 \text{tmp=shuffle(3,4,6,7,8,9)}
 \text{tmp=item(1 to 2,\tmp)}
 \text{l=2,5,\tmp,-1}
 \text{tmp=wims(values v for v=1 to \nbf)}
 \text{tmp=shuffle(\tmp)}
 \text{l=wims(item \tmp of \l)}
 \text{s=wims(item \tmp of \s)}
#endif

\integer{tmp=\s[1]*\l[1]}
\text{enonce=(\tmp)}
\text{p=\tmp}
\integer{nbf=items(\l)}
\for{k=2 to \nbf}{
 \integer{tmp=\s[\k]*\l[\k]}
 \text{tmp=\tmp>0?+\tmp}
 \text{enonce=\enonce\times(\tmp)}
 \integer{p=\tmp*\p}
}


\statement{
Calculer le produit suivant :
<div class="wimscenter">\(\enonce = ) \embed{r1,8} </div>}

\answer{Réponse}{\p}{type=numexp}
