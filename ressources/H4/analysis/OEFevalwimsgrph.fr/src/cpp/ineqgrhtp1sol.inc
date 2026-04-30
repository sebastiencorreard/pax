\if{\sing1>0}{
             \if{\sensineq=1}{
#if defined TARGET_ineqgrhyper1
    \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\v0,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg,\union,\crocg,\tsing1,\ptvirg,\infd,\crocg}
#else
    \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg,\union,\bracg,\tsing1,\bracd}
#if defined TARGET_ineqgrhyper5
    \text{grepp=\strictineq=0?\crocd,\infg,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg,\union,\bracg,\tsing1,\bracd}
    \text{grepm=\strictineq=0?\crocd,\v0,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\v0,\ptvirg,\infd,\crocg}
#endif
#endif
             }{
#if defined TARGET_ineqgrhyper1
    \text{grep=\strictineq=0?\crocd,\v0,\ptvirg,\tsing1,\crocg:\crocd,\v0,\ptvirg,\tsing1,\crocd}
#else
    \text{grep=\strictineq=0?\crocd,\v0,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\v0,\ptvirg,\infd,\crocg}
#if defined TARGET_ineqgrhyper5
    \text{grepp=\strictineq=0?\crocd,\v0,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\v0,\ptvirg,\infd,\crocg}
    \text{grepm=\strictineq=0?\crocd,\infg,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg,\union,\bracg,\tsing1,\bracd}
#endif
#endif
              }
           }{
            %%%% sing1<0
            \if{\sensineq=2}{
#if defined TARGET_ineqgrhyper1
    \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\v0,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\tsing1,\crocd,\union,\crocd,\v0,\ptvirg,\infd,\crocg}
#else
    \text{grep=\strictineq=0?\crocd,\v0,\ptvirg,\infd,\crocg:\bracg,\tsing1,\bracd,\union,\crocd,\v0,\ptvirg,\infd,\crocg}
#if defined TARGET_ineqgrhyper5
    \text{grepp=\strictineq=0?\crocd,\v0,\ptvirg,\infd,\crocg:\bracg,\tsing1,\bracd,\union,\crocd,\v0,\ptvirg,\infd,\crocg}
    \text{grepm=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg}
#endif
#endif
              }{
#if defined TARGET_ineqgrhyper1
    \text{grep=\strictineq=0?\crocd,\tsing1,\ptvirg,\v0,\crocg:\crocg,\tsing1,\ptvirg,\v0,\crocg}
#else
    \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg}
#if defined TARGET_ineqgrhyper5
    \text{grepp=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg}
    \text{grepm=\strictineq=0?\crocd,\v0,\ptvirg,\infd,\crocg:\bracg,\tsing1,\bracd,\union,\crocd,\v0,\ptvirg,\infd,\crocg}
#endif
#endif
               }
           }
