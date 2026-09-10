!set lang_exists=yes
#if defined TARGET_lineonpnt || defined TARGET_pntonline || defined TARGET_lineonpnt || defined TARGET_lineonpnt2 || defined TARGET_distpl || defined TARGET_par1 || defined TARGET_perp1
\text{name_instruction=We consider in the plane the line \(L\)
  defined by the equation}
#endif
#if defined TARGET_distpl || defined TARGET_distpl2
\matrix{name_question=Compute the distance between \(L) and the point of coordinates}
\text{name_answer=Distance}
#endif
#if defined TARGET_par1
\matrix{name_question=An equation of the line passing through the point with coordinates
  and parallel to \(L) is}
\text{name_answer=Equation of the line}
#endif
#if defined TARGET_perp1
\matrix{name_question=An equation of the line passing through the point with coordinates
 and perpendicular to \(L) and is}
#endif
#if defined TARGET_pntonline
\matrix{name_question=The point \(M\) with coordinates
  is on \(L\) if and only if \(m\) is equal to}
#endif
#if defined TARGET_lineonpnt || defined TARGET_lineonpnt2
\matrix{name_question=The line \(L) passes through the point \(M\) with coordinates
  if and only if \(m\) is equal to}
#endif
#if defined TARGET_parparam || defined TARGET_par2 || defined TARGET_distpl2 || defined TARGET_pntonline2 || defined TARGET_parm2eq || defined TARGET_perp2
\text{name_instruction=We consider in the plane the line \(L) defined by the parametric equations}
# if defined TARGET_par2
\matrix{name_question=An equation of the line passing through the point with coordinates
  and parallel to \(L\) is}
# endif
# if defined TARGET_pntonline2
\matrix{name_question=The point \(M\) with coordinates
  is on \(L\) if and only if \(m\) is equal to}
# endif
# if defined TARGET_parm2eq
\matrix{name_question=An equation of \(L\) is  }
# endif
# if defined TARGET_perp2
\matrix{name_question=A vector equation of the line passing through the point with coordinates
  and perpendicular to \(L\) is}
# endif
# if defined TARGET_parparam
\text{name_question=A parametric representation of the line \(L') passing through the point \(M\) with coordinates
  and parallel to \(L\) is }
\matrix{name_condition=Your parametric representation defines a line
  parallel to
  passing through}
\text{name_feed=A parametric representation of \(L'\) is}
# endif
#endif
#if defined TARGET_pnt2eq
\text{name_instruction=In the plane we consider the line passing through the points
  with coordinates}
\text{name_question=A vector equation of this line is}
\text{name_and=and}
#endif
#if defined TARGET_par2 || defined TARGET_pnt2eq || defined TARGET_slope2eq || defined TARGET_parm2eq || defined TARGET_perp2
\text{name_inst=The equation must be of the form}
\text{name_answer=Equation of the line}
#endif
#if defined TARGET_slope2eq
\text{name_instruction=Find an equation of the line in the plane containing the point}
\text{name_instruction2=and with slope equal to}
\text{name_question=Equation of the line}
#endif
