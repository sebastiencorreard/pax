target=spheric0
#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_spheric0
\text{H=2}
#else
\text{H=1}
#endif
\text{h=randitem(1,2)}
\text{choix=random(1,2)}
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
\text{liste1= \liste[\H;]}

\text{T=item(\h,\phii,\the)}
\text{rep= varphi isin \T ? phi: theta}

\matrix{matrice1= \name_matrice[1;] xOz,0, 1
\name_matrice[1;] yOz,1/2,3/2
\name_matrice[2;1..3] xOz \name_matrice[2;4] x>0,0
\name_matrice[2;1..3] xOz \name_matrice[2;4] x<0,1
\name_matrice[2;1..3] yOz \name_matrice[2;4] y>0,1/2
\name_matrice[2;1..3] yOz \name_matrice[2;4] y<0,3/2
\name_matrice[3;] Oz,0,1
\name_matrice[4;] xOy,1/2
\name_matrice[5;1..3] Oz \name_matrice[5;4],0
\name_matrice[5;1..3] Oz \name_matrice[5;5],1
}
\matrix{matrice= \h=2 ? row(1..6,\matrice1):row(7..10,\matrice1)
}
\text{N =\h=2 ? 6:4}
\text{n=randint(1..\N)}
text{n=\choix=1 ? randint(1..\N): random(1,2)}
\if{\h=2}{
	\if{\n=1}{\text{dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
parallel -1.6,-2.2, -1.6,1.4,3.2,3.2,2,grey
parallel 1.6,1.2,-1.6,-2.2,0,3.6,2,grey
fill -0.2,0,grey
dsegment 0,0,1.6,1.6,black
linewidth 2
arc 0, 0, 2, 2, 225,45,red
arrow cos(pi/4-0.2),sin(pi/4-0.2),cos(pi/4),sin(pi/4),10, red
linewidth 1
copy 1.3*cos(3*pi/2+0.2),1.3*sin(3*pi/2+0.2),-1,-1,-1,-1,mathfonts/109/\mtheta
}
	}
	\if{\n=2}{\text{dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
parallel -2,-1, 2,-1,0,4,3,grey
parallel -2,-1,-2,3,4,0,2,grey
fill -0.2,0,grey
arc 0, 0, 1.5, 1,230,0,red
arrow 0.7*cos(-0.2),0.7*sin(-0.2),0.7,0,7, red
arc 0, 0, 3,2,235,180,red
arrow -1.4*cos(0.2),1.4*sin(0.2),-1.4,0,7, red
dsegment -2.5,0,0,0,black
copy 1.3*cos(3*pi/2+0.2),1.3*sin(3*pi/2+0.2),-1,-1,-1,-1,mathfonts/109/\mtheta
}
}
\if{\n=3}{\text {dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
parallel -1.6,-2.2, -1.6,1.4,1.6,1.6,2,grey
parallel 0,-0.6,-1.6,-2.2,0,3.4,2,grey
fill -0.2,0,grey
dsegment 0,0,1.6,1.6,black
copy 1.3*cos(3*pi/2+0.2),1.3*sin(3*pi/2+0.2),-1,-1,-1,-1,mathfonts/109/\mtheta
}
}
\if{\n=4}{\text{dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
parallel 0,-0.6, 0,2.8,1.6,1.6,2,grey
parallel 0,-0.6,1.6,1,0,3.4,2,grey
fill 0.2,0,grey
dsegment 0,0,1.6,1.6,black
linewidth 2
arc 0, 0, 2, 2, 225,45,red
arrow cos(pi/4-0.2),sin(pi/4-0.2),cos(pi/4),sin(pi/4),10, red
linewidth 1
copy 1.3*cos(3*pi/2+0.2),1.3*sin(3*pi/2+0.2),-1,-1,-1,-1,mathfonts/109/\mtheta
}
}
\if{\n=5}{\text{dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
parallel 0,-1, 2,-1,0,4,2,grey
parallel 0,-1,0,3,2,0,2,grey
fill 0.2,0,grey
arc 0, 0, 1.5, 1,230,0,red
arrow 0.7*cos(-0.2),0.7*sin(-0.2),0.7,0,7, red
dsegment -2.5,0,0,0,black
copy 1.3*cos(3*pi/2+0.2),1.3*sin(3*pi/2+0.2),-1,-1,-1,-1,mathfonts/109/\mtheta
}
}
\if{\n=6}{\text{dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
parallel -2,-1, 0,-1,0,4,2,grey
parallel -2,-1,-2,3,2,0,2,grey
fill -0.2,0,grey
arc 0, 0, 3,2,235,180,red
arrow -1.4*cos(0.2),1.4*sin(0.2),-1.4,0,7, red
dsegment -2.5,0,0,0,black
copy 1.3*cos(3*pi/2+0.2),1.3*sin(3*pi/2+0.2),-1,-1,-1,-1,mathfonts/109/\mtheta
}
}
}
\if{\h=1}{
	\if{\n=1}{\text{dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
linewidth 2
arrow sin(0.2),-cos(0.2),0,-1,7, red
arc 0, 0, 2, 2, 270, 90, red
linewidth 1
copy 1.5*cos(3*pi/8),1.5*sin(3*pi/8),-1,-1,-1,-1,mathfonts/109/\mphi
	}
	\text{dessinplanbas= linewidth 2
segment 0,-4.5, 0,4.5, green
	linewidth 1
	}
	}
\if{\n=2}{\text{dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
parallel -3.2,-1.6, 1.6,-1.6,3,3,2,grey
parallel -3.2,-1.6, -0.2,1.4,4.8, 0,2,grey
fill -0.2,0.2,grey
linewidth 1
arrow cos(0.2),sin(0.2),1,0,10, red
arc 0, 0, 2, 2,0, 90, red
copy 1.5*cos(3*pi/8),1.5*sin(3*pi/8),-1,-1,-1,-1,mathfonts/109/\mphi}
}
\if{\n=3}{\text{dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
copy 1.5*cos(3*pi/8),1.5*sin(3*pi/8),-1,-1,-1,-1,mathfonts/109/\mphi
	}
	\text{dessinplanbas= linewidth 2
segment 0,0, 0,4.5, green
	linewidth 1
	}
	}
	\if{\n=4}{\text{dessinplan=xrange -4.5,4.5
yrange -4.5,4.5
linewidth 2
arrow sin(0.2),-cos(0.2),0,-1,7, red
arc 0, 0, 2, 2, 270, 90, red
linewidth 1
copy 1.5*cos(3*pi/8),1.5*sin(3*pi/8),-1,-1,-1,-1,mathfonts/109/\mphi
	}
	\text{dessinplanbas= linewidth 2
segment 0,-4.5, 0,0, green
	linewidth 1
	}
	}
}
\text{A=row(\n,\matrice)}
\text{u=item(4,\A)}
 \text{v=\n<=\h ? item(5,\A): \u}

\text{aux=row(1,\matrice1)}
\text{choixsol = wims(items2words item(2..3,\aux))}
\for{i=2 to 10}{\text{aux=row(\i,\matrice1)}
\text{choixsol=\choixsol,
 wims(items2words item(2..3,\aux))
 }
}
\text{sol=wims(items2words item(2..3,\A))}

#include "repere.inc"
\text{name_question=wims(replace internal COORD by \name_choicecoord[\H] in \name_question)}
\matrix{STEP=\choix=1? choice1: choice2, reply1, reply2}
\steps{\STEP}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{150,150}{
\dessin}</div>
 <div class="medium_size text_col">
\if{\choix=1}{\name_question[1;] \coord \((\liste1))
	<p class="wimscenter">
\if{\u=1}{ \(\T=\pi )}
\if{\u=0}{ \(\T=0)}
\if{\u=-1}{ \(\T=-\pi )}
\if{\u<>0 and \u<>-1 and \u<> 1}{\(\T=\u.\pi)}
\if{\n <=\h}{ \name_question[5;]
 \if{ \v=1}{ \(\T=\pi )}
 \if{ \v=0}{ \(\T=0)}
 \if{ \v=-1}{ \(\T=-\pi )}
\if{ \v<>0 and \v<>-1 and \v<> 1}{\(\T=\v.\pi)}
}
</p>
\name_question[2;]
\embed{choice 1}.
}{
\name_question[3;1] \A[1] \A[3] \name_question[3;2] de
<div class="wimscenter">\(\ \alpha)= \embed{choice 2} </div>
\name_question[4;]
<div class="wimscenter"> \(\ \alpha\) = \embed{reply 1,5}. \(\ \pi\) \name_question[5;] \embed{reply 2,5}. \pi
</div>
<div class="wims_instruction">
\name_instruction
</div>
 }
</div></div>
}

\choice{\name_type}{\sol}{\choixsol}
\choice{}{\rep}{theta, phi}
\answer{}{\u}{type = default}
\answer{}{\v}{type = default}
\feedback{1=1}{<div class="wimscenter">\draw{200,200}{\dessinplan
\dessin1
\dessinplanbas
}</div>
}
