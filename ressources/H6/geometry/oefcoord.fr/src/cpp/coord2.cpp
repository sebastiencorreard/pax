target=spheric2 cylindric2
#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_spheric2
\text{H=2}
#else
\text{H=1}
#endif
H=1 : coord cylind fonctionne
\text{maph=random(1,2)}
\text{mtheta=\maph=1? theta.gif: varphi.gif}
\text{mphi=\maph=1? varphi.gif:theta.gif}

\text{the=\maph=1 ? \theta: \varphi}
\text{phii=\maph=1 ? \varphi:\theta}
\text{coor=\H=1 ? \name_coord[\H], r,\theta , z : \name_coord[\H] , r, \the, \phii}
\text{h=\H=1 ? random(1,2,2,3,3,4):random(1,2,2,3,3)}
\text{coord=item(1,\coor)}
\text{thet=item(3,\coor)}
\if{\H=2}{\text{ph=item(4,\coor )}}
\real{a=randint(4..9)}
\real{c=randint(0..\a)}
\text{eq= \h<4? item(\h+1,\coor): z}
\text{b=z notin \eq and r notsametext \eq ? simplify((\c)/\a):\a}
\text{b=z isin \eq and \h=4? r}
\text{sol= \H=1 and \h=1 ? 2: 5}
\text{sol= \H=1 and \h=2 ? 1}
\text{sol= \H=1 and \h=4 ? 4}
\text{sol=\H=2 and \h=1 ? 3}
\text{sol=\H=2 and \h=3 ? 4}
\text{sol=\H=2 and \h=2 ? 1}
\text{sol=\H=2 and \h=3 and (\b=0 or \b=1) ? 7}
\text{sol=\H=2 and \h=3 and \b=1/2 ? 5}
\real{b2=(\b)^2}
\text{sol2= \H=1 and \h=1 ? simplify(x^2+y^2)=\b2}
\function{sol2= \H=1 and \h=2 ? simplify(cos(\b*pi)*y-sin(\b*pi)*x)}
\text{sol2= \H=1 and \h=2 ? \sol2=0}
\text{sol2= \H=1 and \h=3 ? z=\b}
\text{sol2= \H=1 and \h=4 ? z^2=x^2+y^2}
\text{sol2=\H=2 and \h=1 ? x^2+y^2+z^2=\b2}
\function{sol2= \H=2 and \h=3? simplify(sin(\b*\pi)^2*(x^2+y^2)-cos(\b*\pi)^2*z^2)}
\text{sol2= \H=2 and \h=3? \sol2=0}
\text{sol2=\H=2 and \h=3 and \b=1/2?z=0}
\function{sol2=\H=2 and \h=2 ? simplify(cos(\b*\pi)*y-sin(\b*\pi)*x)}
\text{sol2=\H=2 and \h=2 ? \sol2=0}

\text{sol3=\H=2 and \h=3 and \b<1/2?1:2}
\text{sol3=\H=2 and \h=3 and \b=0?1}
\text{sol3=\H=2 and \h=3 and \b=1?2}

#include "repere.inc"
\text{STEPS=\H=2 and \h=3 and (\b <> 1/2 and \b <> 0 and \b<>1) ? r1
r3, r2:
r1
r2}
\text{STEPS=\H=2 and \h=3 and ( \b = 0 or \b =1)? r1
r3}
\steps{\STEPS}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{150,150}{\dessin}</div>
 <div class="medium_size text_col">
\name_question[1;] \coord
  \if{\H=1}{\(( r,\thet, z)\)}{
	  \if{\maph=1}{\((r,\thet,\ph)\) }{\((r,\thet,\ph)\) }
  }
	<div class="wimscenter">
  \if{z notin \eq and r notsametext \eq}{
    \if{\b=1}{\(\eq=\pi)}
    \if{\b<>1 and \b<>-1 and \b<>0}{\(\eq=\b\pi)}
    \if{\b=-1}{\(\eq=-\pi)}
    \if{\b=0}{\(\eq=0)}
  }{\(\eq=\b )}
  </div>
  \if{\step <=1}{\name_question[2;]? \embed{r1}}
  \if{\step=2}{
    \if{\H=2 and \h=3 and \b<>1/2 }{
      \if{\b<>0 and \b<>1}{
 	      \name_question[3;]?
 	      <div class="wimscenter">\embed{r3}</div>
 	      <label for="reply2">\name_question[4;]:</label>
 	      <div class="wimscenter">\embed{r2}</div>
      }
      \if{\H=2 and \h=3 and (\b=0 or \b=1)}{
        \name_question[5;]?
        <div class="wimscenter">\embed{r3}</div>
      }
    }{
    <label for="reply2">
    \if{(\H=1 and \h=2) or (\H=2 and \h=3) or (\H=2 and \h=2)}{}{\name_question[6;]}
    \if{(\H=1 and \h=2) or (\H=2 and \h=2)}{\name_question[7;]}
    \if{(\H=2 and \h=3) or (\H=1 and \h=4) }{\name_question[8;]}
    </label><div class="wimscenter">\embed{r2}</div>
    }
  }
</div></div>
}
\answer{\name_answer[1]}{\sol;\choix}{type=menu}
\answer{\name_answer[2]}{\sol2}{type=equation}
\answer{\name_answer[3]}{\sol3;\choix2}{type=radio}

\hint{\name_hint[1;]!
  \if{\H=2 and \h=3}{\name_hint[2;] \(z^2= r^2 sin^2(\phii)).}
}
