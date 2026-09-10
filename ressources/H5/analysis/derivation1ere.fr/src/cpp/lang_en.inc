#if defined TARGET_deriverComp || defined TARGET_deriverInvRac || defined TARGET_deriverPoly
\text{name_answer=Derivative}
#endif
#if defined TARGET_deriverComp || defined TARGET_deriverInvRac
\text{name_write=Write}
\text{name_for=for}
#endif
#if defined TARGET_varInvRac ||  defined TARGET_deriverInvRac || defined TARGET_deriverComp || defined TARGET_deriverComp
\text{name_feed=The derivative is}
#endif
#if defined TARGET_varInvRac
\text{name_answer=Sens de variation sur}
\text{name_choix=strictly increasing, strictly decreasing, not defined}
\text{name_enonce=The function \(f\) is defined on,by}
\text{name_question=On the interval,the function \(f\) is}
\text{name_hint1=The function square root \( sqrt(u)\) is differentiable at any interval \(I\)
  where the function \(u\) is strictly positive and differentiable.
<br>The function \(u\) and its square root \( sqrt(u)\) have
 les mêmes sens de variation sur \(I\).}
\text{name_hint2=The inverse function \( 1 / u \) is differentiable at any interval \(I\)
  where the function \(u\) does not vanish and is differentiable.
<br>The function \(u\) and its inverse \( 1/u\) have
  donc des sens de variation contraires sur \(I\).}
\text{name_hint3=The functions \(u^2\) and \(u\) ont les mêmes sens de variation
  on any interval \(I\) where the function \(u\) is positive.
<br> The functions \(u^2\) and \(u\) ont des sens de variation contraires
on any interval \(I\) where the function \(u\) is negative.}
#endif
#if defined TARGET_deriverComp
\text{name_question=Calculate the derivative of the function \(f\) defined in, by}
\text{name_hint=Let \(f\) be the composite of the affine function \(x\mapsto a x+b\)
  and of the function \(u\). <br> If, when \(x\) varies in the interval \(I\)
  the values \(a x+b\) vary in an interval \(J\) where the function \(u\) is differentiable,
  then \(f\) is differentiable on \(I\) and \(f'(x) = a u'(a x+b)\).}
#endif
#if defined TARGET_deriverInvRac
\text{name_hint1=The function square root \( sqrt(u)) is differentiable at any interval \(I\)
  where the function \(u\) is strictly positive and differentiable.
  <br> Then on the interval \(I) : \( ( \sqrt{u} )' = \frac{u' }{2 \sqrt{u}}\).
  <br> The function \(u\) and its square root \( sqrt(u)) ont donc les mêmes
  sens de variation sur \(I\).}
\text{name_hint2=La fonction inverse \( 1 / u \) is differentiable at any interval \(I)
  where the function \(u\) does not vanish and is differentiable.
  <br>Then one has on the interval \(I\) : \( ( 1 / u )' = - \frac{u' }{u^2} \).
  <br>The function \(u\) and its inverse \( 1/u\) ont donc des sens
  de variation contraires sur \(I\).}
\text{name_enonce=The function \(f\) defined by, is differentiable in}
\text{name_onehas=One has}
#endif
#if defined TARGET_deriverPoly || defined TARGET_deriverPolys
\text{name_ifthen=If,then}
#endif
#if defined TARGET_deriverPolys
\text{name_hint=The following derivation rules are used,
  Derivative of a sum, Derivative of a monomial,In particular}
#endif
#if defined TARGET_deriverPoly
\text{name_enonce= Let \(f\) be the polynomial function defined in \(\,\RR\) by,
  The function \(f\) is differentiable in}
\text{name_question=Calculate its derived function.}
\text{name_forall=For all real numbers}
\text{name_hint=The following derivation rules are used,
  The derivative of a polynomial is determined term by term.,
  We remark}
#endif
#if defined TARGET_varTrinome
\text{name_enonce=Given the function \(f\) defined in \(\,\RR\) by}
\text{name_question=Investigate this function
  and determine the extremum (extrema) of \(f\).}
\text{name_question1=The function \(f\) is differentiable in,
  For all real numbers \(x\), The derivative function \(f'\) is zero at}
\text{name_answer=Derivative number,is zero at, Sign of,
  Nature of the extremum,Value of the extremum of,Derivative of,
  Sens de variation de,Extremum of}
\text{name_hint=If the direction of variation of the function \(f\) changes,
  one says, is a "local" extremum of}
\text{name_question2=is strictly,on the interval}
\text{name_choix=increasing,decreasing}
\text{name_question3=reaches in, with value}
\text{choix7=a minimum,a maximum}
#endif
#if defined TARGET_varPolydeg3
\text{name_enonce=Let \(f\) be the function defined by,on the interval}
\text{name_question1=Calculate,developed form}
\text{name_repquest=Answer to the question}
\matrix{name_question2=The calculation of derivative gives
  It is assumed that \(f'(x)\) is written in factored form (product) in the following way
  Complete then the sign table of}
\text{name_inst=select an icon from the list below
  and drag and paste it into a box}
\text{name_answer=Sign of,var. of, Extremum}
\matrix{name_question3=The study of signs of the derivative, gives the results recorded in the table.
  Complete this table to indicate the<b>variation direction</b> of the function}
\text{name_quest=Question}
\text{name_question4=The table of the variations
  of the function \(f\) is shown.}
\text{name_question41=According this table, the XXXX of the function \(f\) is,
  and this XXXX is reached for}
#endif
#if defined TARGET_nbdergraph || defined TARGET_nbdergraph2
\text{name_enonce=Given the plane,
The <span style="color:blue">curve CCCC</span> represents the
<span style="color:blue">function \(f\)</span> defined in,
<span style="color:green">The line \(T\)</span> is the tangent of CCCC at the point \(A\) of the coordinates}
\text{name_hint=The derivative number \(f'(a)\) is the slope coefficient of the tangent
  \(T_a\) at the representative curve of \(f\) at the point of abscissa \(a\).}
\text{name_answer=Derivative number}
\text{name_feed1=You were wrong about the slope sign
  of the tangent. If the function increases in the neighbourhood
  , then the tangent \(T\) "goes up" and, is of positive sign.
  If the function decreases in the neighbourhood,
  then the tangent \(T) "goes down" and, is of negative sign.
}
\text{name_feed2=The derivative number, is the slope coefficient \(m\) of the line \(T\)
  and \(m\) is equal to the average growth \(\frac{\Delta y}{\Delta x} = \frac{y_B - y_A}{
x_B - x_A} = MMMM\) (see red arrows on the graphic).
  Rounding to the tenth is }
# if defined TARGET_nbdergraph
\text{name_question=Knowing that \(T\) goes also through the point \(B\) of the coordinates,
  calculate the value of, rounded up to one tenth.}
# endif
# if defined TARGET_nbdergraph2
\text{name_question=It is known that \(T\) goes also through the point \(B\) of the coordinates,
  Which value of the derivative function \(f'\) can be deduced,
  Give this value rounded to the nearest tenth.}
# endif
#endif
#if defined TARGET_deriverProduit
\text{name_question=Determine the derivative of a function , in ,defined by,with}
\text{name_question1=The functions \(u\) and \(v\) are differentiable in \(\,\RR)}
\text{name_question2=The derivation formula is applied,
  The derivative in developed polynomial form is}
\text{name_answer=Derivative number,The applied rule of differentiation}
\text{name_sol=Solution.,
  The normal form of \(f'(x)\) is,
  The factorized form of \(f'(x)\) is}
#endif
#if defined TARGET_deriverQuotient
\text{name_answer=The numerator \(u\) is defined by,
  The denominator \(v\) is defined by,
  The derivative of the numerator,
  The derivative of the denominator,
  Differentiable in,
  Formule de dérivation,
  The derivative \(f'\) is defined by}
\text{name_feed=Solution.,
  The derivative function \(f'\) is defined for all real \(x\),
  different of, by,factored form}
\text{name_enonce=Given the function  \(f\) defined in,by,
  We will now determine the derivative of \(f'(x)\) in a few steps.}
\text{name_question1=We rewrite \(f) as a fraction \(\frac{u}{v}),
  wherein the functions \(u\) and \(v\) are defined in \(\,\RR\) by}
\text{name_and=and}
\text{name_question2=The functions \(u\) and \(v\) are differentiable in }
\text{name_with=with}
\text{name_question3=The fraction, is differentiable in}
\text{name_question4=Which rule on differentiation do we apply}
\text{name_oneget=We will get}
#endif
