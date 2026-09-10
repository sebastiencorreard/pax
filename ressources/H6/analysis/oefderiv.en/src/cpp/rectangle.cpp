target=rectangle1 rectangle2 rectangle3 rectangle4 rectangle5 rectangle6

#include "xiao.inc"

\text{dir=random(1,2)}
\text{direction=item(\dir,increases,decreases)}
\text{sign=item(\dir,+,-)}
\real{a=randint(15..50)/10}
\text{lw=random(1,2)}
\text{LW=item(\lw,length,width)}
\integer{w=randint(10..30)}
\integer{l=randint(\w+5..2*\w+10)}
\integer{peri=2*(\w+\l)}
\integer{area=\w*\l}

#if defined TARGET_rectangle1
  \title{Rectangle I}
  \text{fix=item(\lw,width,length)}
  \text{fixval=item(\lw,\w,\l)}
  \text{fixunit=centimeters}
  \text{first=\LW}
  \text{ref=the \LW}
  \text{r=item(\lw,\l,\w)}
  \text{runit=centimeters}
  \integer{C=\fixval}
  \real{sol=\sign(\C)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=its area}
#endif
#if defined TARGET_rectangle2
  \title{Rectangle II}
  \text{fix=perimeter}
  \text{fixval=\peri}
  \text{fixunit=centimeters}
  \text{first=\LW}
  \text{ref=the \LW}
  \text{r=item(\lw,\l,\w)}
  \text{runit=centimeters}
  \integer{C=\l+\w}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign(\C-2*\t)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=its area}
#endif
#if defined TARGET_rectangle3
  \title{Rectangle III}
  \text{fix=perimeter}
  \text{fixval=\peri}
  \text{fixunit=centimeters}
  \text{first=\LW}
  \text{ref=the item(\lw,width,length)}
  \text{r=item(\lw,\w,\l)}
  \text{runit=centimeters}
  \integer{C=\l+\w}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign(\C-2*\t)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=its area}
#endif
#if defined TARGET_rectangle4
  \title{Rectangle IV}
  \text{fix=perimeter}
  \text{fixval=\peri}
  \text{fixunit=centimeters}
  \text{first=\LW}
  \text{ref=the area}
  \real{r=\area}
  \text{runit=square centimeters}
  \integer{C=\l+\w}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign(\C-2*\t)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=its area}
#endif
#if defined TARGET_rectangle5
  \title{Rectangle V}
  \text{fix=area}
  \text{fixval=\area}
  \text{fixunit=square centimeters}
  \text{first=\LW}
  \text{ref=the \LW}
  \text{r=item(\lw,\l,\w)}
  \text{runit=centimeters}

  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign 2*(1-\area/(\t^2))*\a}
  \text{solunit=cm/s}
  \text{second=its perimeter}
#endif
#if defined TARGET_rectangle6
  \title{Rectangle VI}
  \text{fix=area}
  \text{fixval=\area}
  \text{fixunit=square centimeters}
  \text{first=\LW}
  \text{ref=the item(\lw,width,length)}
  \text{r=item(\lw,\w,\l)}
  \text{runit=centimeters}

  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign 2*(1-\area/(\t^2))*\a}
  \text{solunit=cm/s}
  \text{second=its perimeter}
#endif
\statement{We have a rectangle
whose \first \direction at a constant speed of \a centimeters per second,
but whose \fix stays constant at \fixval \fixunit.
At the moment when \ref equals \r \runit,
what is the speed (in \solunit) at which \second changes?
}

\answer{The speed}{\sol}

