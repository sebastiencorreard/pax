target=formulas

\title{Formule}
#include "header.inc"

\if{random(1,2)=1}{
 \text{f=f}\text{g=g}
}{
 \text{f=g}\text{g=f}
}
\text{prime='}'

\text{propsname=formulas}
\text{good=shuffle(
 (\f(x)*\g(x))\prime = \f(x)*\g\prime(x) + \f\prime(x)*\g(x),
 (\f(x)/\g(x))\prime = (\f\prime(x)*\g(x) - \f(x)*\g\prime(x))/\g^2(x),
 (1/\f(x))\prime = -\f\prime(x)/\f^2(x),
 (\f^2(x))\prime = 2*\f(x)*\f\prime(x),
 (\f(\g(x)))\prime = \f\prime(\g(x))*\g\prime(x)
)}
\text{bad=shuffle(
 (\f(x)*\g(x))\prime = \f\prime(x)*\g\prime(x),
 (\f(x)*\g(x))\prime = \f\prime(x) + \g\prime(x),
 (\f(x)*\g(x))\prime = 2*\f\prime(x)*\g\prime(x),
 (\f(x)*\g(x))\prime = \f(x)*\g\prime(x) + \g\prime(x)*\f(x),
 (\f(x)*\g(x))\prime = \f\prime(\g(x))*\g\prime(x),
 
 (\f(x)/\g(x))\prime = (\f(x)*\g\prime(x) - \f\prime(x)*\g(x))/\g^2(x),
 (\f(x)/\g(x))\prime = \f\prime(x)/\g\prime(x),
 (\f(x)/\g(x))\prime = -\f\prime(x)/\g^2(x),
 (\f(x)/\g(x))\prime = (\f\prime(x)*\g(x) + \f(x)*\g\prime(x))/\g^2(x),
 (\f(x)/\g(x))\prime = (\f\prime(x)*\g(x) - \f(x)*\g\prime(x))/\g\prime(x),
 
 (1/\f(x))\prime = \f\prime(x)/\f^2(x),
 (1/\f(x))\prime = 1/\f\prime(x),
 (1/\f(x))\prime = \f(x)/\f\prime(x),
 (1/\f(x))\prime = -1/(\f\prime(x))^2,

 (\f^2(x))\prime = \f(x)*\f\prime(x),
 (\f^2(x))\prime = (\f\prime(x))^2,
 (\f^2(x))\prime = \f\prime\prime(x),

 (\f(\g(x)))\prime = \f(x)*\g\prime(x) + \f\prime(x)*\g(x),
 (\f(\g(x)))\prime = \f\prime(\g(x)),
 (\f(\g(x)))\prime = \f\prime(\g\prime(x)),
 (\f(\g(x)))\prime = \f\prime(x)*\g\prime(x)
)}

#include "goodbad4.inc"

\statement{Naj bosta \(f) in \(g) odvedljivi funkciji.
#include "goodbadlist4.inc"
}

\reply{\cond \propsname so}{\ans;1,2,3,4}{type=checkbox}
