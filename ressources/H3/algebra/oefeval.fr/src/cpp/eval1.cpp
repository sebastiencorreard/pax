target = 1ordre1,1ordre2,1ordre3,2ordre1,2ordre2,2ordre3,factor,fract,all
#define TITRE Remplacer x dans
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand }
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{sizef=10}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?5}
\integer{confparm3=\confparm3=?5}
\integer{confparm1>5?5}

#if #TARGET (1ordre1)
   \title{TITRE x+a}
   \text{no=1}
#endif

#if #TARGET (1ordre2)
   \title{TITRE -x+a}
   \text{no=2}
#endif

#if #TARGET (1ordre3)
   \title{TITRE ax+b}
   \text{no=3}
#endif

#if #TARGET (2ordre1)
   \title{TITRE -x^2+bx+c}
   \text{no=4}
#endif

#if #TARGET (2ordre2)
   \title{TITRE x^2+bx+c}
   \text{no=5}
#endif

#if #TARGET (2ordre3)
   \title{TITRE ax^2+bx+c}
   \text{no=6}
#endif

#if #TARGET (fract)
   \title{Fraction rationnelle}
   \text{no=7}
#endif

#if #TARGET (factor)
   \title{Produit de facteurs}
   \text{no=8}
#endif

#if #TARGET (all)
   \title{Expression quelconque}
   \text{no=1,2,3,4,5,6,7,8}
#endif



\text{lteno=}
\text{ltrep=}
\text{ltval=}
\text{st=}
\text{x=}
\for{i=1 to \confparm1}{
 \text{choix=randitem(\no)}
 \text{coef=randitem(\confparm2)}
 \text{value=randitem(\confparm3)}
 \text{don=slib(polynome \choix,\value,\coef)}
 \text{tmpx=item(1,\don)}
 \text{x=wims(append item \tmpx to \x)}
 \text{enonce=item(2,\don)}
 \text{val=item(3,\don)}
 \text{rep=wims(replace internal \tmpx by (\val) in \enonce)}
 \text{rep=simplify(\rep)}
 \text{enonce=texmath(\enonce)}
 \text{lteno=wims(append item \enonce to \lteno)}
 \text{ltrep=wims(append item \rep to \ltrep)}
 \text{val=texmath(\val)}
 \text{ltval=wims(append item \val to \ltval)}
 \text{st=wims(append item r\i to \st)}
}

\text{lettre=A,B,C,D,E}

\steps{\st}

\statement{
\if{\confparm1=1}
{Quelle est la valeur de l'expression suivante pour \(\x[1] = \ltval[1]) ?
<div class="wimscenter">\(\lettre[1] = \lteno[1]).</div>}
{Calculer les expressions suivantes pour les valeurs données :
<ul>
 \for{k=1 to \confparm1}{<li>\(\lettre[\k] = \lteno[\k]) pour \(\x[\k] = \ltval[\k]).</li>}
</ul>
}
<div class="wims_instruction">
Donner vos réponses sous une forme aussi simple que possible.</div>
<div class="spacer">
\if{\confparm1=1}{
<b>Votre réponse</b> : \(\lettre[1] = )\embed{r1,\sizef}
}{
<b>Vos réponses</b> :
<ul>
 \for{k=1 to \confparm1}{<li>\(\lettre[\k] = )\embed{r\k,\sizef}</li>}
</ul>
}
</div>
}

\answer{\(\lettre[1])}{\ltrep[1]}{type=numexp}
\answer{\(\lettre[2])}{\ltrep[2]}{type=numexp}
\answer{\(\lettre[3])}{\ltrep[3]}{type=numexp}
\answer{\(\lettre[4])}{\ltrep[4]}{type=numexp}
\answer{\(\lettre[5])}{\ltrep[5]}{type=numexp}
