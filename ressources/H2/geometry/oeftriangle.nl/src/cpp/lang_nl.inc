#if defined TARGET_centers
\text{always=always inside}
\text{depend=sometimes outside}
\text{never =always outside}
\matrix{data=
  mid-perpendiculars, circumcenter, \depend, midperpendiculars, center of circumcircle
  altitudes, orthocenter, \depend
  angle-bisectors, incenter, \always, bisectors of angles|bisectors, center of inscribed circle
  medians, center of gravity, \always, , barycenter
}
\text{bad=triangle angle sides perimeter vertex point intersection straight line}
\matrix{name_instruction=Fill-in the text
  The intersection of the three
  of a triangle is the
  of this triangle, which is
  the triangle}
#endif
#if defined TARGET_typesb || defined TARGET_types
\text{right=Het is een rechthoekige driehoek}
\text{acute=Het is een driehoek met een scherpe hoek}
\text{obtuse=Het is een driehoek met een stompe hoek}
\text{non=Het is geen driehoek}
# if defined TARGET_typesb
\text{name_instruction=Tot welke soort behoort ``driehoek'' \(A B C\) met }
\text{name_choice=De driehoek}
\text{name_peri=Omtrek}
# endif
# if defined TARGET_types
\text{name_instruction=Tot welke soort behoort de ``driehoek'' \(A B C\) met 3 zijden}
\text{name_choice=De driehoek}
# endif
#endif
#if defined TARGET_twosides
\text{name_instruction=Hoeveel driehoeken ABC zijn er met \(A C\) een integer}
\text{name_sol=Om \(A B C\) een driehoek te laten zijn, moet
  op zijn minst,en maximaal}
\text{name_answer=Aantal driehoeken}
#endif
#if defined TARGET_twosidesb
\text{name_acute=acute, obtuse}
\text{ans1=Om \(A B C\) een scherphoekige driehoek te laten zijn, moet \(A C^2\) meer zijn dan
  \(\long^2-\short^2=\q2=\q2\) en minder dan
  \(A B^2+B C^2=\q1=\q1\) zijn, de stelling vam Pythagoras.}
\text{ans2=Om \(A B C\) een driehoek te laten zijn, moet \(A C\) op zijn minst
  \max-\min+1 zijn en maximaal \ab+\bc-1.<p>
  Als \long de langste zijde is van de driehoek, moet \(A C\) (stelling van Pythagoras)
  minder zijn dan \sq2.
  Als \(A C\) de langste zijde is, moet deze langer zijn dan \sq1
  (wederom de stelling van Pythagoras),</p><p>
  Hierdoor zijn \n3 (respectievelijk. \n2) stompe driehoeken,
  met als langste zijde \long (resp. \(A C\)).</p>}
\matrix{name_instruction=Hoeveel
  driehoeken \(A B C\) zijn er, met \(A C\) een integer,}
\text{name_answer=Aantal Driehoeken}
#endif
