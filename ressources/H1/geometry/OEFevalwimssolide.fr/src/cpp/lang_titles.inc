\text{lang=slib(oef/env lang)}

#include "lang_title_fr.inc"

#if defined TARGET_oefconstpat1 || defined TARGET_oefformpave1 || defined TARGET_oefpatron1 || defined TARGET_oefrecpersp1 || defined TARGET_oefrecpatron1 || defined TARGET_oefconvvol1 || defined TARGET_oefsolide1 || defined TARGET_oefcontvol1 || defined TARGET_oefconvcont1 || defined TARGET_oefconvconvol1 || defined TARGET_oefpaveparaperp1 || defined TARGET_oefvolume1
# define NUM 1
#endif
#if defined TARGET_oefconstpat2 || defined TARGET_oefformpave2 || defined TARGET_oefpatron2 || defined TARGET_oefrecpersp2 || defined TARGET_oefrecpatron2 || defined TARGET_oefconvvol2 || defined TARGET_oefsolide2 || defined TARGET_oefcontvol2 || defined TARGET_oefconvcont2 || defined TARGET_oefconvconvol2 || defined TARGET_oefpaveparaperp2 || defined TARGET_oefvolume2
# define NUM 2
#endif
#if defined TARGET_oefconstpat3 || defined TARGET_oefformpave3 || defined TARGET_oefpatron3 || defined TARGET_oefrecpersp3 || defined TARGET_oefrecpatron3 || defined TARGET_oefconvvol3 || defined TARGET_oefsolide3 || defined TARGET_oefcontvol3 || defined TARGET_oefconvcont3 || defined TARGET_oefconvconvol3 || defined TARGET_oefpaveparaperp3 || defined TARGET_oefvolume3
# define NUM 3
#endif
#if defined TARGET_oefconstpat4 || defined TARGET_oefformpave4 || defined TARGET_oefpatron4 || defined TARGET_oefrecpersp4 || defined TARGET_oefrecpatron4 || defined TARGET_oefconvvol4 || defined TARGET_oefsolide4 || defined TARGET_oefcontvol4 || defined TARGET_oefconvcont4 || defined TARGET_oefconvconvol4 || defined TARGET_oefpaveparaperp4 || defined TARGET_oefvolume4
# define NUM 4
#endif
#if defined TARGET_oefconstpat5 || defined TARGET_oefformpave5 || defined TARGET_oefpatron5 || defined TARGET_oefrecpersp5 || defined TARGET_oefrecpatron5 || defined TARGET_oefconvvol5 || defined TARGET_oefsolide5 || defined TARGET_oefcontvol5 || defined TARGET_oefconvcont5 || defined TARGET_oefconvconvol5 || defined TARGET_oefpaveparaperp5 || defined TARGET_oefvolume5
# define NUM 5
#endif

\title{TITRE NUM}
