target=horizon1 horizon2 horizon3
horizon3 à faire ?
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1}
Pour le dessin
\text{Rd=10}
\text{hd=2}
randint(2..3)
\real{thed=acos(\Rd/(\Rd+\hd))}
\real{the2d=randint(2..5)*pi/30} th-th2
\real{h2d=\Rd/cos(\the2d)-\Rd} r=cos*(r+h) h=r/cos-r
\text{dessin=xrange -2*\Rd,2*\Rd
yrange -2*\Rd,2*\Rd
circles black,0,0,\Rd
fcircles orange,0,0,\Rd
dashed
polygon red,0,0,\Rd*sin(\thed),\Rd*cos(\thed),0,\Rd+\hd
arrows2 blue,5,0,\Rd,0,\Rd+\hd
text blue,-2,\Rd+\hd/2,large,h
text blue,\Rd/2*sin(\thed),\Rd/2*cos(\thed),large,R
halfline 0,\Rd+\hd,\Rd*sin(\thed),\Rd*cos(\thed),black
}
\text{dessin2=dashed
segments blue,0,0,(\Rd+10)*cos(\the2d),(\Rd+10)*sin(\the2d)
text blue,0,\Rd+\hd,large,A
text blue,(\Rd+1)*cos(\the2d),(\Rd+1)*sin(\the2d),large,B
}

#if defined TARGET_horizon1
\real{h=randint(1000..3000)}hauteur de l'observation en m
\text{R=6371000} rayon de la Terre en m
D = distance de l'horizon
\real{D = sqrt(2*\h*\R + \h^2)}
text{D=pari(round(\D))}
\text{enonce=wims(replace internal RRRR by \R in \name_enonce)}
\text{enonce=wims(replace internal HHHH by \h in \enonce)}
\text{rep=\D}
#endif
#if defined TARGET_horizon2
\real{h=randint(1000..3000)}
\real{D=randint(160..200)*1000}
\text{R=pari(round((\D^2-\h^2)/(2*\h)))}
\text{enonce=wims(replace internal YYYY by \D in \name_enonce)}
\text{enonce=wims(replace internal HHHH by \h in \enonce)}
\text{rep=\R}
#endif
#if defined TARGET_horizon3
\text{dessin=\dessin
\dessin2}
\real{h=randint(1000..3000)}hauteur de l'observation en m
\real{h1=randint(1000..3000)}
\text{R=6371000} rayon de la Terre en m
\real{h=randint(1000..3000)}
\real{D1 = sqrt(2*\h*\R + \h^2)}
\real{h1=randint(1000..3000)}
\real{D2 = sqrt(2*\h1*\R + \h1^2)}
\real{D=round(\D1+\D2)}
\text{enonce=wims(replace internal RRRR by \R in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \D in \enonce)}
\text{enonce=wims(replace internal HHHH by \h in \enonce)}
\text{rep=\h1}
#endif
\statement{
<div class="wims_columns">
  <div class="medium_size img_col">\canvasdraw{400,400}{\dessin}</div>
  <div class="medium_size text_col">
  \enonce
  <br><label for="reply1">\name_answer[1]:</label>\embed{r1} m
  <div class="wims_instruction">\name_inst</div>
  </div></div>

}
\answer{name_answer[2]}{\rep}{type=numeric}{option=absolute}
