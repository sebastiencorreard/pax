target= point1 point2 ligne1 ligne2 ligne3 cercle1 cercle2 cercle3 cercle4 cercle5

#include "header.inc"

#if defined TARGET_point1 
\text{rep=f,A=Point,\correct}
\text{extra=}
\integer{max=}
\text{nothing=nothing}
#endif

#if defined TARGET_point2 
\text{rep=f,B=Point,\correct}
\text{extra=}
\integer{max=}
\text{nothing=nothing}
#endif

#if defined TARGET_ligne1 
\text{rep=f,=Line[A,B],\correct}
\text{extra=yes}
\integer{max=3}
\text{nothing=nothing}
#endif

#if defined TARGET_ligne2 
\text{rep=f,=Segment[A,B],\correct}
\text{extra=yes}
\integer{max=3}
\text{nothing=nothing}
#endif

#if defined TARGET_ligne3 
\text{rep=f,=Ray[A,B],\correct}
\text{extra=yes}
\integer{max=3}
\text{nothing=nothing}
#endif

#if defined TARGET_cercle1
\integer{choix=randitem(1,2)}
\text{A=\choix=1 ? A : B}
\text{B=\choix=1 ? B : A}
\text{rep=f,=Circle[\A,\B],\correct}
\text{extra=yes}
\integer{max=3}
\text{nothing=nothing}
#endif

#if defined TARGET_cercle2
\integer{choix=randitem(4,5,6,7,8,9,10,11,12)}
\text{rep=f,=Circle[A,\choix],\correct}
\text{extra=yes}
\integer{max=3}
\text{nothing=nothing}
#endif

#if defined TARGET_cercle3
\integer{choix=randitem(4,5,6,7,8,9,10,11,12)}
\real{ray=\choix/2}
\text{rep=f,=Circle[A,\ray],\correct}
\text{extra=yes}
\integer{max=3}
\text{nothing=nothing}
#endif

#if defined TARGET_cercle4 
\text{rep=f,A=Point,\Point A;f,B=Point,\Point B;f,P=Point,\Point P;f,=Circle[A,B,P],\Cercle}
\text{extra=}
\integer{max=}
\text{nothing=nocoord}
#endif

#if defined TARGET_cercle5 
\text{rep=f,=Circle[C,A],\correct}
\text{extra=yes}
\integer{max=4}
\text{nothing=nothing}
#endif

\text{appletoption=height=400
width=600
showToolBar=true
enableRightClick=true
file=blanc.ggb
}

#include "lang_titles.inc"
#include "lang.inc"

\statement{\name_instruction
<div class="wimscenter">
\embed{r1, 600 x 400
\appletoption}
</div>
}

\answer{}{\rep ?}{type=geogebra}{option=extra=\extra output=\nothing max=\max weights=1&1&0}

\if{e isin \aide }{
\hint{\aide}
}

\feedback{.5 isin \sc_reply1}{<span class="oef_indbad">\penalty</span>}
