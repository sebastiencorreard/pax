target=oppose

#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

\title{TITRE}

\integer{nb=randint(-50..50)}
\if{\nb=0}{\text{typ=raw}
\text{rep=0,+0,-0}
\text{repsol=0}}{\integer{repsol=-1*\nb}
\text{typ=numexp}}
\integer{absnb=pari(abs(\nb))}
%%Droite graduée pour la solution
\integer{xsize=600}
\integer{marge=40}
\if{\nb>0}{\integer{min=\repsol-2}
\integer{max=\nb+2}}{\integer{max=\repsol+2}
\integer{min=\nb-2}}
\real{ex=(\xsize-2*\marge)/(\max-\min)}
\real{minx=\min-\marge/\ex}
\real{maxx=\max+\marge/\ex}
\integer{ec=\max-\min+1}
\integer{eca=\max-\min}
\real{delet=4/\ex}
\text{tmp2=}
\for{k=0 to \eca}{\integer{aux2=\min+\k}
                  \real{aux=\min+\k-\delet}
                  \if{\aux2=0}{\text{segment=segment \aux2,-0.5,\aux2,0.5,black}
                               \text{tmp2=wims(append line \segment to \tmp2)}
                               \text{tmp=text black,\aux,-0.75,giant,\aux2}
                               \text{tmp2=wims(append line \tmp to \tmp2)}}
                  \if{\aux2=\repsol and \aux2<>0}{\text{segment=segment \aux2,-0.5,\aux2,0.5,red}
                                   \text{tmp2=wims(append line \segment to \tmp2)}
                                   \text{tmp=text red,\aux,-0.75,giant,\aux2}
                                   \text{tmp2=wims(append line \tmp to \tmp2)}}
                  \if{\aux2=\nb and \aux2<>0}{\text{segment=segment \aux2,-0.5,\aux2,0.5,blue}
                                   \text{tmp2=wims(append line \segment to \tmp2)}
                                   \text{tmp=text blue,\aux,-0.75,giant,\aux2}
                                   \text{tmp2=wims(append line \tmp to \tmp2)}}
                 }                                            
\text{essai=range \minx,\maxx,-3,3
linewidth 2
arrow \minx,0,\maxx,0,\marge/2,black
linewidth 3
\tmp2}
\text{url2=draw(600,150
\essai
arrow2 0,1.5,\nb,1.5,10,blue
text blue,\nb/2,2.5,giant,\absnb
arrow2 0,1.5,\repsol,1.5,10,red
text red,\repsol/2,2.5,giant,\absnb)}

\statement{<p><label for ="reply1">Quel est l'opposé du nombre \(\nb\)&nbsp;?</label> \embed{reply1,5}}
\answer{}{\res}{type=\typ}
\condition{Bonne réponse ?}{
(\nb=0 and (\res=+0 or \res=0 or \res=-0)) or (\nb<>0 and \res=\repsol)}
\hint{Deux nombres relatifs ayant la même distance à zéro et des signes contraires sont opposés.}
\solution{<img src="\url2" alt="droite graduée">
<p>L'opposé de \(\nb\) est <span class="nowrap">\(\repsol\).</span></p>
}
