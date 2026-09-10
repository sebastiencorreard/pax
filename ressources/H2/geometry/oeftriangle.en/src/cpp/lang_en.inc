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
\text{right=It is a right triangle}
\text{acute=It is an acute triangle}
\text{obtuse=It is an obtuse triangle}
\text{non=It is not a triangle}
# if defined TARGET_typesb
\text{name_instruction=How is a ``triangle'' \(A B C\) with }
\text{name_choice=The triangle }
\text{name_peri=perimeter}
# endif
# if defined TARGET_types
\text{name_instruction=How is a ``triangle'' \(A B C\) with 3 sides}
\text{name_choice=The triangle }
# endif
#endif
#if defined TARGET_twosides
\text{name_instruction=How many triangles \(A B C\) are there, with \(A C\) an integer and}
\text{name_sol=In order that \(A B C\) be a triangle, must be at least,and at most}
\text{name_answer=Number of triangles}
#endif
#if defined TARGET_twosidesb
\text{name_acute=acute, obtuse}
\text{ans1=In order that \(A B C\) be an acute triangle, \(A C^2\) must be more than
  \(\long^2-\short^2=\q2=\q2\) and less than
  \(A B^2+B C^2=\q1\), by Pythagorean Theorem.}
\text{ans2=In order that \(A B C\) be a triangle, \(A C\) must be at least
  \max-\min+1 and at most \ab+\bc-1.<p>
  When \long is the longest side of the triangle, \(A C\) must be less than \sq2 by
  Pythagorean Theorem. When \(A C\) is the longest side, it must be more than \sq1,
  again by Pythagorean Theoerem.</p><p>
  Therefore, there are \n3 (resp. \n2) obtuse triangles whose
  longest side is \long (resp. \(A C\)).</p>}
\matrix{name_instruction=How many
  triangles \(A B C\) are there, with \(A C\) an integer and}
\text{name_answer=Number of triangles}
#endif
