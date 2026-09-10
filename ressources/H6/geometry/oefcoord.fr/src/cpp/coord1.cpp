target=spheric1 cylindric1
#include "author.inc"

\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\text{H=randitem(1,2)}
#if defined TARGET_spheric1
\text{H=2}
#else
\text{H=1}
#endif
Si H= 1 , coordonnées cylindriques (fonctionne mais pas d'etape 2 pour l'instant)
\text{maph=random(1,2)}
\text{mtheta=\maph=1? theta.gif: varphi.gif}
\text{mphi=\maph=1? varphi.gif:theta.gif}

\text{the=\maph=1 ? \theta: \varphi}
\text{phii=\maph=1 ? \varphi:\theta}
\text{coor=\H=1 ? \name_choicecoord[\H], r,\theta , z : \name_choicecoord[\H] , r, \the, \phii}
\text{coord=item(1,\coor)}
\text{thet=item(3,\coor)}
\matrix{liste= r,\theta , z
 r, \the, \phii
}
\text{liste1= row(\H,\liste)}
\text{choix2=item(1..2,shuffle(1,2,3))}
\integer{u1=item(1,\choix2)}
\integer{u2=item(2,\choix2)}
\text{b=random(1,2,3,4,6,12)}
\integer{c=randint(0..\b)}
\text{b2=random(1,2,3,4,6,12)}
\integer{c2=randint(0..\b2)}
\text{q1=pari(\c/\b)}
\text{q2=pari(\c2/\b2)}
\text{a=\u1=1 ? randint(1..10): \q1}
\text{b=\u2=1 ? randint(1..10): \q2}
\integer{c=randint(1..\b)}

\text{eq1= item(\u1,\liste1)}
\text{eq2= item(\u2,\liste1)}
\text{sol= \H=1 and ((\u1=1 and \u2=3) or (\u2=1 and \u1=3)) ? item(2,\choix)}
\text{sol= \H=1 and ((\u1=1 and \u2=2) or (\u2=1 and \u1=2)) ? item(4,\choix)}
\text{sol= \H=1 and ((\u1=2 and \u2=3) or (\u2=2 and \u1=3)) ? item(3,\choix)}
\text{sol= \H=2 and ((\u1=1 and \u2=3) or (\u2=1 and \u1=3)) ? item(2,\choix)}
\text{sol= \H=2 and ((\u1=1 and \u2=2) or (\u2=1 and \u1=2)) ? item(1,\choix)}
\text{sol= \H=2 and ((\u1=2 and \u2=3) or (\u2=2 and \u1=3)) ? item(3,\choix)}
\text{sol= \H=2 and ((\u1=1 and \u2=3 and \b=0) or (\u2=1 and \u1=3 and \a=0))
  ? item(6,\choix)}
\text{sol= \H=2 and ((\u1=1 and \u2=3 and \b=1) or (\u2=1 and \u1=3 and \a=1))
  ? item(6,\choix)}

\if{\H=2 and ((\u1=1 and \u2=3) or (\u2=1 and \u1=3))}{
  \real{t1= 0}
  \real{t2= 0}
  \real{t3= 1}
}
\if{\H=2 and ((\u1=1 and \u2=2) or (\u2=1 and \u1=2))}{
  \real{t1= \u1=2 ? -sin(\a*pi): -sin(\b*pi)}
  \real{t1= round(10^9*\t1)/1000000000}
  \real{t2= \u1=2 ? cos(\a*pi):cos(\b*pi)}
  \real{t2= round(10^9*\t2)/1000000000}
  \real{t3= 0}
}
\if{\H=2 and ((\u1=2 and \u2=3) or (\u2=2 and \u1=3))}{
  \real{t1= \u1=2 ? cos(\a*pi)*sin(\b*pi): cos(\b*pi)*sin(\a*pi)}
  \real{t1= round(10^9*\t1)/1000000000}
  \real{t2= sin(\a*pi)*sin(\b*pi)}
  \real{t2= round(10^9*\t2)/1000000000}
  \real{t3= \u1=2 ? cos(\b*pi): cos(\a*pi)}
  \real{t3= round(10^9*\t3)/1000000000}
}
\text{c= \u1=1 and \u2=3? \b}
\text{rr= \u1=1 and \u2=3? \a}
\text{c= \u1=3 and \u2=1? \a}
\text{rr= \u1=3 and \u2=1? \b}
\real{uu= \u1*\u2}
\text{test= \uu=3 and (\c=0 or \c=1)? -1:1}
\if{\H=2 and \test=-1}{
  \real{t1= 0}
  \real{t2= 0}
  \real{t3= \c=0? \rr:-\rr}
}
#include "repere.inc"
\matrix{STEP=choice1}

\matrix{STEP=\H=2? \STEP
reply1, reply2, reply3}
\steps{\STEP}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{150,150}{\dessin}</div>
 <div class="medium_size text_col">
  \name_question \coord
  \if{\H=1}{\(( r,\thet, z))}{
  	\if{\maph=1}{\((r,\thet,\phii)) }{\((r,\thet,\phii)) }
  }
  <p class="wimscenter">
  \if{(r isin \eq1 and i notin \eq1) or z isin \eq1}{\(\eq1=\a)}{
  	\if{\a<>0 and \a<>1}{\(\eq1=\a.\pi) }
  	\if{\a=0}{\(\eq1=0) }
  	\if{\a=1}{\(\eq1=\pi) }
  },
  \if{(r isin \eq2 and i notin \eq2)
      or z isin \eq2}{\(\eq2= \b\)}{
    \if{\b<>0 and \b<>1}{\(\eq2=\b.\pi)}
    \if{\b=0}{\(\eq2=0 )}
    \if{\b=1}{\(\eq2=\pi) }
  }</p>
  \if{\step <=1}{\name_question2[1;]? \embed{c1}}
  \if{\step=2}{
    \if{\H=2 and ((\u1=2 and \u2=3) or (\u2=2 and \u1=3)) and \test=1}
      {\name_question2[2;]:
    <div class="wimscenter">(\embed{reply 1,10},\embed{reply 2,10},\embed{reply 3,10}) </div>}

    \if{\H=2 and (\u1=1 or \u2=1 ) and \test=1}{
      \name_question2[3;]:
      <div class="wimscenter">(\embed{reply 1,10}, \embed{reply 2,10}, \embed{reply 3,10}) </div>
    }
    \if{\H=2 and \test=-1}{
      \name_question2[4;]:
      <div class="wimscenter">(\embed{reply 1,10}, \embed{reply 2,10}, \embed{reply 3,10}) </div>
    }
  }
  </div></div>
}

\choice{\name_type}{\sol}{\choix}
#if defined TARGET_spheric1
\answer{u_x}{\rt1}{type=numeric}
\answer{u_y}{\rt2}{type=numeric}
\answer{u_z}{\rt3}{type=numeric}
teste si la réponse est colinéaire au vecteur (\t1,\t2,\t3)
\if{\step=2}{
  \text{condi=\test=-1? \name_cond[1;]: \name_cond[2;]?}
  \text{unit=\test=-1? \name_cond[3;]?:\name_cond[4;]?}
}
\condition{\condi }{\H=1 or (\H=2 and (\rt1)*(\t2)-(\rt2)*(\t1)=0 and
  (\rt1)*(\t3)-(\rt3)*(\t1)=0 and (\rt3)*(\t2)-(\rt2)*(\t3)=0)
}

teste si la réponse est unitaire ?
\condition{\unit }{\H=1 or (\H=2 and \test=1 and (\rt1)^2+(\rt2)^2+(\rt3)^2=1) or (\H=2 and
  \test=-1 and \rt1=\t1 and \rt2=\t2 and \rt3=\t3) }
\hint{\name_hint!}
\feedback{\step=2 and \H=2 and ((\rt1)*(\t2)-(\rt2)*(\t1) <>0 or
  (\rt1)*(\t3)-(\rt3)*(\t1)<>0 or (\rt3)*(\t2)-(\rt2)*(\t3)<>0)}{
    \if{\test=-1}{ \name_feed[1;].}{\name_feed[2;].}
}

\feedback{\step=2 and \H=2 and \test=1 and (\rt1)^2+(\rt2)^2+(\rt3)^2<>1}{\name_feed[3;].}
\feedback{1=1 and \step=2}{
  \if{\test=1}{
	  \if{\uu=6}{\name_feed[4;1]}{\name_feed[4;2]} \name_feed[4;3] ( \t1,\t2,\t3).
  }{\name_feed[5;] ( \t1,\t2,\t3).}
  }
#endif
