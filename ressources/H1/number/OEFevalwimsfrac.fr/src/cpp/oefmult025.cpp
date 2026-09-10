target=oefmult0251 oefmult0252 oefmult0253 oefmult0254 oefmult0255
#define TITRE Multiplication par 0,5 0,25 0,75

\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

#if defined TARGET_oefmult0251
\title{TITRE 1}
\text{ch=random(0,2,4,6,8),random(2,4,6,8),random(0,2,4,6,8)}
\real{d=0.5}
\integer{nb=\ch[1]\ch[2]\ch[3]}
#endif

#if defined TARGET_oefmult0252
\title{TITRE 2}
\text{ch=randint(1..9),random(1,3,5,7,9),random(0,2,4,6,8)}
\real{d=0.5}
\integer{nb=\ch[1]\ch[2]\ch[3]}
#endif

#if defined TARGET_oefmult0253
\title{TITRE 3}
\text{ch=random(4,8,12,16,20)}
\integer{n=randint(6..24)*4}
\integer{nb=\ch\n}
\real{d=0.25}
#endif

#if defined TARGET_oefmult0254
\title{TITRE 4}
\integer{nb=randint(26..99)*4}
\real{d=0.25}
#endif

#if defined TARGET_oefmult0255
\title{TITRE 5}
\text{ch=randint(2..9),random(2,4,6)}
\integer{n=\ch[1]\ch[2]}
\integer{nb=\n*4}
\real{d=0.75}
#endif

\real{res=\nb*\d}
\text{res=slib(numeration/ecriturenombre \res)}
\text{res=wims(translate . to , in \res)}

\statement{
Donnez le résultat de la multiplication :
<div class="wimscenter">
 \nb \(\times) \d = \embed{r1,8}
</div>
<div class="wims_instruction">Vous utiliserez la virgule comme séparateur décimal,
et vous respecterez l'espace tous les trois chiffres et éviterez les zéros inutiles.
</div>}

\answer{}{\res}{type=raw}
