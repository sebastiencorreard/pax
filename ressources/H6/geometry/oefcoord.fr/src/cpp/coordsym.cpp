target=sphericsym
#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\text{H=2}
\text{maph=randitem(1,2)}
\text{mtheta=\maph=1? theta.gif: varphi.gif}
\text{mphi=\maph=1? varphi.gif:theta.gif}
\text{the=\maph=1 ? \theta: \varphi}
\text{phii=\maph=1 ? \varphi:\theta}
\text{coor=\H=1 ? \name_choicecoord[\H], r,\theta , z : \name_choicecoord[\H] , r, \the, \phii}
\text{coord=item(1,\coor)}
\text{thet=item(3,\coor)}
\matrix{liste= r,\theta , z
 r, \the, \phii}
\text{dessin1=arrow 0,0,3,0,10,black
arrow 0,0,0,3, 10,black
arrow 0,0,-1.6,-1.6, 10,black
text blue, -1.8,-1.8, medium, x
text blue,0.5,2.9, medium, z
text blue,2.8, 0.5,medium, y
linewidth 2
segment 0,0,2.2,2.2,green
segment 0,0, 2.2,-0.5,green
dsegment 2.2,-0.5,2.2,2.2,black
dsegment 0,2.5,2.2,2.2,black
arrow cos(-pi/16-0.2),sin(-pi/16-0.2),cos(-pi/16),sin(-pi/16),10, red
arc 0, 0, 2, 2, 225,348.75, red
copy 1.3*cos(3*pi/2+0.2),1.3*sin(3*pi/2+0.2),-1,-1,-1,-1,mathfonts/109/\mtheta
}

\text{dessin2= \maph=1 ?
arc 0, 0, 2, 2, 0,45, red
arrow cos(pi/4-0.2),sin(pi/4-0.2),cos(pi/4),sin(pi/4),10, red
copy 1.5*cos(pi/8),1.5*sin(pi/8),-1,-1,-1,-1,mathfonts/109/\mphi
text black, 0.9,1.8, medium, r:
arc 0, 0, 2, 2, 45, 90, red
arrow cos(pi/4+0.2),sin(pi/4+0.2),cos(pi/4),sin(pi/4),10, red
copy 1.5*cos(3*pi/8),1.5*sin(3*pi/8),-1,-1,-1,-1,mathfonts/109/\mphi
text black, 1.3, 0.9, medium, r
}

\text{dessin=xrange -3,3
yrange -3,3
\dessin1
\dessin2}

\matrix{plan= \maph=1 ? x O y,x,y,-z,r,theta,-phi
x O z,x,-y,z,r,2*pi-theta,phi
y O z,-x,y,z,r,pi-theta, phi}
\text{plan= \maph=2 ? x O y,x,y,-z,r,pi-theta,phi
x O z,x,-y,z,r,theta,2*pi-phi
y O z,-x,y,z,r,theta, pi-phi}
\text{Plan=randomrow(\plan)}
\text{plan=item(1,\Plan)}
\text{rep1= item(2,\Plan)}
\text{rep2= item(3,\Plan)}
\text{rep3= item(4,\Plan)}
\text{rep4= item(5,\Plan)}
\text{rep5= item(6,\Plan)}
\text{rep6= item(7,\Plan)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{150,150}{\dessin}</div>
 <div class="medium_size text_col">
\name_question[1] \(\plan), \name_question[2]
<div class="wimscenter"> <label for="reply1">\( x \mapsto )</label> \embed{reply 1, 5}</div>
<div class="wimscenter"> <label for="reply2">\( y \mapsto )</label> \embed{reply 2, 5}</div>
<div class="wimscenter"> <label for="reply3">\( z \mapsto )</label> \embed{reply 3, 5}</div>
\name_question1 :
<div class="wimscenter"> <label for="reply4">\( r \mapsto )</label> \embed{reply 4, 5}</div>
<div class="wimscenter"> <label for="reply5">\( \theta \mapsto )</label> \embed{reply 5, 5}</div>
<div class="wimscenter"> <label for="reply6">\( \varphi \mapsto )</label> \embed{reply 6, 5}</div>

<div class="wims_instruction">\name_hint \(pi).</div>
</div>
</div>
}
\answer{\(x)}{\rep1,x,y,z}{type=function}
\answer{\(y)}{\rep2,x,y,z}{type=function}
\answer{\(z)}{\rep3,x,y,z}{type=function}
\answer{\(r)}{\rep4,theta, phi,r}{type=function}
\answer{\(\theta)}{\repe5}
\answer{\(varphi)}{\repe6}
\text{s1=wims(replace internal theta by x in \reply5)}
\text{rep5=wims(replace internal theta by x in \rep5)}
\text{s2=wims(replace internal phi by x in \reply6)}
\text{rep6=wims(replace internal phi by x in \rep6)}
\text{test1=pari((\rep5-(\s1))/(2*pi))}
\real{test11=\test1-floor(\test1)}
\text{test2=pari((\rep6-(\s2))/(2*pi))}
\real{test22=\test2-floor(\test2)}
\condition{\(\ \theta)}{x notin \test1 and \test11=0}
\condition{\(\ \phi)}{x notin \test2 and \test22=0}
