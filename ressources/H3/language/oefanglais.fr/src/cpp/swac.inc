\text{rename=slib(oef/env rename)}
\text{rename=\confparm2=2 ? }
\text{list_error=slib(oef/env list_error)}
\text{user=slib(oef/env user)}
\text{msg=\user issametext supervisor and \list_error notsametext ?
asis(<em>\name_msg[1]? </em> \name_msg[2]:
<div class="wims_warning">
  \name_msg[3]:)
\list_error
\name_msg[4]</div>}
