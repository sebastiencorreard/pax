function zirkel2wims(type,name){
    var data="";
    xmlString =document.applets[0].getDrawing("\""+type+"\"","\""+name+"\"");
    data=xmlString;
    var test=data.indexOf("error");
    if(test!=-1){
	alert(r19+data); return 0;
    }
    else{
	return data;
    }
}