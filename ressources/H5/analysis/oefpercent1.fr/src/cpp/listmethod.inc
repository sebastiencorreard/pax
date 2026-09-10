<div class="wims_instruction">\consigne</div>
<ul class="inline">
\for{tt=1 to \nb_meth}{
  \if{\MM[\tt]=0}{
    <li>
    \embed{reply1,\tt,<img src="gifs/images/methods/\ListImage[\tt]" alt="\Listdesc[\tt]">}
    \slib{text/balloon}{[\tch[\tt]],\color[\tt],250,100,triangle=left-in}
    </li>
  }
}
</ul>
