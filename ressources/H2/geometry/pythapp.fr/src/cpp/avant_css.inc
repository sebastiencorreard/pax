%%% css commune autre que css euler et css particuliere %%%
\css{
<style>
.indication{
  font-weight:bold;color:#009999;
  margin-bottom: 0.8em;
  margin-top: 0.8em;
}
.quest{
  color:blue;
  font-weight:bold;
  margin:0;
}

#if defined TARGET_06 || defined TARGET_07 || defined TARGET_08 || defined TARGET_09
  #if defined TARGET_06 || defined TARGET_07 || defined TARGET_08
table.tab_sol td {
  border:solid 1px;
  padding:0.3em;
  }
table.tab_sol th {
  border:solid 1px;
  background-color:#CEE3F6;
  color:#2609AB;
  }
table.tab_sol tr:nth-child(2n+3) {
  background-color:#EFF5FB;
  }
  #endif
.wims_nopuce >li{
  padding-bottom:0.2em;
}

@media(min-width: 40em) {#fig{position:sticky;top:8em;}}
#endif
</style>
}
