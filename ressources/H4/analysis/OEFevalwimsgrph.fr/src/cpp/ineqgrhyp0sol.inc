\text{goodrep=vide}

#if defined TARGET_ineqgrhyper1
  \rational{y0=0}
  \text{g1=\y0}
  \text{equat= texmath(1/x) }
  \text{equat2= texmath(1/x) }
#else
  \integer{c=random(1..5)}
  \integer{d=random(1..5)}
  \integer{a=\c*(\c+\d)}
#if defined TARGET_ineqgrhyper2
     \integer{b=0}
#else
    \integer{b=\c}
#endif
  \integer{bb=\b}
  \integer{c=\c+\d}
  \integer{cc=\c}
  \rational{ar=simplify(\a/(\c))}
  \rational{br=simplify(\b/(\c))}
  \integer{ix=random(1,2)}
%%%%integer{ix=2}
  \text{sx=\ix=1?+:-}
  \text{sc=+}
  \text{smx=\ix=1?-:+}
  \text{smc=-}
  \function{f=\ar*x \sx (\br) \sc (\c)/x}
  \text{equat= \ar*x }
  \text{equat2= \ar x }
#if defined TARGET_ineqgrhyper5
    \function{f=\a*x \sx (\b) \sc (\c)/x}
    \text{equat= \a*x }
    \text{equat2= \a x }
#endif
  \text{s1=\b>0?+:-}
  \integer{b=\b<0?\b*(-1)}
  \text{s2=\c>0?+:-}
  \integer{c=\c<0?\c*(-1)}
  \text{g1=-(\ar) * x}
  \text{g2= (\ar) * x}
  \text{g3=- (\ar) * x}
  \text{g4= (\ar) * x }
#if defined TARGET_ineqgrhyper5
     \text{g1=-(\ar) * x}
     \text{g2=-(\a) * x}
     \text{g3= (\ar) * x}
     \text{g4= (\a) * x }
#endif
  \if{\b !=0}{
      \rational{mbr=\br*(-1)}
#if defined TARGET_ineqgrhyper5
        \text{equat=\equat \sx \b }
        \text{equat2=\equat2 \sx \b  }
        \text{g1=\g1 \smx (\br)}
        \text{g2=\g2 \smx (\b) }
        \text{g3=\g3 \sx (\br)}
        \text{g4=\g4 \sx (\b) }
#else
        \text{equat=\equat \sx \br  }
        \text{equat2=\equat2 \sx \br  }
        \text{g1=\g1 \smx (\br)}
        \text{g2=\g2 \sx (\br) }
        \text{g3=\g3 \sx (\br)}
        \text{g4=\g4 \smx (\br) }
#endif

    }
#if defined TARGET_ineqgrhyper5
      \text{equat=\equat \s2 \c/x }
      \text{equat2=\equat2 \sc \frac{\c}{x} }
#else
      \text{equat=\equat \s2 1/x }
      \text{equat2=\equat2 \sc \frac{1}{x} }
#endif

#endif

   \integer{indsol=1}

%%%% préparation de la réponse
   \text{grep=\sensineq=1?\crocd,\infg,\ptvirg,\v0,\crocg:\crocd,\v0,\ptvirg,\infd,\crocg}

