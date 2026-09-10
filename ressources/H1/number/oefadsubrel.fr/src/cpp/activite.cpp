target=actimemsigne actisignediff

#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if TARGET_actimemsigne
\title{TITRE (même signe)}
#endif
#if TARGET_actisignediff
\title{TITRE (signes contraires)}
#endif

\text{signe=shuffle(+,-)}
\text{sign1=\signe[1]}
\if{\sign1=+}{\text{ttsign1=positif,positifs}
\text{tsign1=\plus}}
{\text{ttsign1=négatif,négatifs}
\text{tsign1=\minus}}
#if TARGET_actimemsigne
\text{sign2=\sign1}
\text{tsignerep=\tsign1}
\text{ttsignerep=\ttsign1}
\if{\sign2=+}{\text{ttsign2=positif,positifs}
\text{tsign2=\plus}}
{\text{ttsign2=négatif,négatifs}
\text{tsign2=\minus}}
#endif
#if TARGET_actisignediff
\text{sign2=\signe[2]}
\if{\sign2=+}{\text{ttsign2=positif,positifs}
\text{tsign2=\plus}}{\text{ttsign2=négatif,négatifs}
\text{tsign2=\minus}}
#endif
\text{liste=wims(makelist x for x=1 to 10)}
\text{A=slib(data/random 2,item, \liste)}
\integer{nb1=\A[1]}
\integer{nb2=\A[2]}
\real{res=\sign1\nb1+\sign2\nb2}
\if{\res>0}{\text{trep=\plus}}
\integer{daz=abs(\res)}
\integer{nb=\nb1+\nb2}
\integer{er=abs(\nb1-\nb2)}
\if{\nb1>\nb2}{\text{dist=\(\nb1 - \nb2 = \daz \)}
\text{tsignerep=\tsign1}
\text{ttsignerep=\ttsign1}
\text{solu=<ul><li>On détermine le signe de \(A\) en comparant les distances à zéro des termes de la somme&nbsp;:
<p>Comme \(\nb1>\nb2\) et que \(\tsign1\nb1\) est \ttsign1[1] alors le signe de \(A\) est \ttsignerep[1].</p></li>
<li>On effectue la différence des distances à zéro \dist.</li>
</ul>}
}{\text{dist=\(\nb2 - \nb1 = \daz \)}
\text{tsignerep=\tsign2}
\text{ttsignerep=\ttsign2}
\text{solu=<ul><li>On détermine le signe de \(A\) en comparant les distances à zéro des termes de la somme&nbsp;:
<p>Comme \(\nb2>\nb1\) et que \(\tsign2\nb2\) est \ttsign2[1] alors le signe de \(A\) est \ttsignerep[1].</p></li>
<li>On effectue la différence des distances à zéro \dist.</li>
</ul>}
}
#if TARGET_actimemsigne
\if{\sign1=+}{
\integer{min=-1}
\integer{max=\nb1+\nb2+2}}
\if{\sign1=-}{
\integer{max=1}
\integer{min=-\nb1-\nb2-2}}
#endif
#if TARGET_actisignediff
\if{\nb1>\nb2 and \sign1=+}{
\integer{min=-\nb2-2}
\integer{max=\nb1+2}}
\if{\nb1>\nb2 and \sign1=-}{
\integer{min=-\nb1-2}
\integer{max=\nb2+2}}
\if{\nb2>\nb1 and \sign1=+}{
\integer{min=-\nb2-2}
\integer{max=\nb1+2}}
\if{\nb2>\nb1 and \sign1=-}{
\integer{min=-\nb1-2}
\integer{max=\nb2+2}}
#endif
%%Droite graduée avec slib personnalisée ds drgr.inc
\integer{xsize=600}
\integer{marge=40}
#include "drgr.inc"
\text{url1=draw(600,150
\essai
arrow 0,1,\sign1 \nb1,1,10,blue
text blue,(\sign1 \nb1)/2,1,giant,\sign1 \nb1
arrow 0,1.5,\sign2 \nb2,1.5,10,red
text red,(\sign2 \nb2)/2,1.5,giant,\sign2 \nb2
)}
\text{url2=draw(600,150
\essai
arrow 0,1,\sign1 \nb1,1,10,blue
text blue,(\sign1 \nb1)/2,1,giant,\sign1 \nb1
translate \sign1 \nb1,0
arrow 0,1.5,\sign2 \nb2,1.5,10,red
text red,(\sign2 \nb2)/2,1.5,giant,\sign2 \nb2
killtranslate
)}

\statement{<p>On désire calculer l'expression&nbsp;:
<span class="nowrap">\(A=( \textcolor{blue}{\tsign1 \nb1} ) + ( \textcolor{red}{\tsign2 \nb2} )\).</span></p>
On illustre cette situation par un dessin.
<p><img src="\url1" alt="droite graduée avec flèches séparées" ></p>
On met une flèche au bout de l'autre.
<p><img src="\url2" alt="droite graduée avec flèches bout à bout" ></p>
On lit le résultat sur la droite graduée&nbsp;:
<div class="wims_instruction">Une réponse avec des parenthèses n'est pas acceptée.
<p>Il n'est pas obligatoire d'écrire le signe + d'un résultat positif.</p></div>
<p>\(A=( \tsign1 \nb1 ) + ( \tsign2 \nb2 )\)</p>
<label for="reply1">\(A=\)</label>\embed{r1,3}.
}
\answer{}{\res}{type=numexp}
#if defined TARGET_actimemsigne
\hint{<div style="color:red" class="underline"><b>A retenir&nbsp;:</b></div>
La somme de deux nombres relatifs de même signe a ...
<ul class="wims_nopuce">
<li>pour signe&nbsp;: le signe commun aux deux nombres.</li>
<li>pour distance à zéro&nbsp;: la somme des deux distances à zéro.</li>
</ul>}
#endif
#if defined TARGET_actisignediff
\hint{<div style="color:red" class="underline"><b>A retenir&nbsp;:</b></div>
La somme de deux nombres de signes contraires a...
<ul class="wims_nopuce">
<li>pour signe&nbsp;: le signe du nombre qui a la plus grande distance à zéro,</li>
<li>pour distance à zéro &nbsp;: la différence des distances à zéro.</li></ul>}
#endif
\feedback{(\reply1<0 and \res>0) or (\reply1>0 and \res<0)}{<div class="macss">Attention au signe de la somme, le résultat est \ttsignerep[1].</div>}
#if defined TARGET_actimemsigne
\integer{er=abs(\nb1-\nb2)}
\feedback{abs(\reply1)=\er}{<div class="macss">Vous avez soustrait les distances à zéro au lieu de les additionner.</div>}
#endif
#if defined TARGET_actisignediff
\integer{er=\nb1+\nb2}
\feedback{\reply1=\er}{<div class="macss">Vous avez additionné les distances à zéro au lieu de les soustraire.</div>}
#endif
#if defined TARGET_actimemsigne
\solution{<div style="color:red" class="underline"><b>A retenir&nbsp;:</b></div>
La somme de deux nombres relatifs de même signe a ...
<ul>
<li>pour signe&nbsp;: le signe commun aux deux nombres.</li>
<li>pour distance à zéro&nbsp;: la somme des deux distances à zéro.</li>
</ul>
Pour calculer l'expression <span class="nowrap">\(A=( \tsign1 \nb1 ) + ( \tsign1 \nb2 )\).</span>
<ul><li>On détermine le signe de \(A\)&nbsp;: \(A\) est \ttsign1[1] car les deux termes de la somme sont \ttsign1[2].</li>
<li>On additionne les distances à zéro <span class="nowrap">\(\nb1+\nb2=\nb\).</span></li>
</ul>
On conclut&nbsp;:
<p>\(A=( \tsign1 \nb1 ) + ( \tsign1 \nb2 )\)</p>
<span class="nowrap">\(A= \trep \res\).</span>}
#endif
#if defined TARGET_actisignediff
\solution{<div style="color:red" class="underline"><b>A retenir&nbsp;:</b></div>
La somme de deux nombres de signes contraires a...
<ul>
<li>pour signe&nbsp;: le signe du nombre qui a la plus grande distance à zéro,</li>
<li>pour distance à zéro &nbsp;: la différence des distances à zéro.</li></ul>
Pour calculer l'expression <span class="nowrap">\(A=( \tsign1 \nb1 ) + ( \tsign2 \nb2 )\).</span>
\solu
<p>\(A=( \tsign1 \nb1 ) + ( \tsign2 \nb2 )\)</p>
<span class="nowrap">\(A = \trep \res \).</span>}
#endif
