target=inverse1 inverse2 inverse3 inverse4

\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}


#if defined TARGET_inverse1
 \title{Inverse 1}
 \text{v=wims(values v for v=5 to 25)}
 \text{v=shuffle(\v)}
 \text{enonce=\v[1]/\v[2]}
#endif

#if defined TARGET_inverse2
 \title{Inverse 2}
 \text{v=wims(values v for v=5 to 25)}
 \text{v=shuffle(\v)}
 \text{ch=shuffle(-,)}
 \text{enonce=\ch[1]\v[1]/\ch[2]\v[2]}
#endif

#if defined TARGET_inverse3
 \title{Inverse 3}
 \text{v=randitem(1,-1)*randint(5..25)}
 \text{enonce=1/(\v)}
#endif

#if defined TARGET_inverse4
 \title{Inverse 4}
 \text{v=randitem(1,-1)*randitem(3,6,7,9,11,13,14,15,17,18,19)}
 \text{enonce=\v}
#endif

 \text{rep=simplify(1/(\enonce))}
 \text{enonce=texmath(\enonce)}
 \text{A=randitem(A,B,C,D,E,F)}

\statement{
Quel est l'inverse du nombre suivant :
<div class="wimscenter"> \(\A = \enonce )</div>}

\answer{inverse de \(\A)}{\rep}{type=numexp}{option=noreduction}
