
var ktory=0;
var rzad=0;
var wyraz="";
var slowa;
var wygraneslowo;
var pauza=false;

function idzdogory() 
{
	document.body.scrollTop = 0;
	document.documentElement.scrollTop = 0;
}

window.onscroll = function() {kiedyscroll()};

var ket;
var faddr = "https://www-users.mat.umk.pl/~adrianpol123/stronainternetowa/slownik.txt";
var link1 = "https://www-users.mat.umk.pl/~adrianpol123/stronainternetowa/pytania.php";
var linkchat = "https://www-users.mat.umk.pl/~adrianpol123/stronainternetowa/chat.txt";
$(function()
{
	$.get(faddr+'?ACAO', callback);
	$.get(linkchat+'?ACAO', wstaw);
	$("#g_quiz").click(function()
	{
		$.getJSON(link1+'?ACAO', rozpocznij_quiz); 
	});
	
	$("#wiadomosc_chatu").keyup(function(event) 
	{
		if (event.keyCode === 13) 
		{
			$("#wyslij").click();
		}
	});

	$("#wyslij").click(function() 
	{
		var textc=$("#wiadomosc_chatu").val();
		$("#wiadomosc_chatu").val("");
		jQuery.ajax({
			type: "POST",
			url: 's.php',
			data: {functionname: 'funkcja', arguments: [textc]}, 
			success:function(data) {
			$.get(linkchat+'?ACAO', wstaw);
        }
		});
		
	});
});


window.setInterval(function()
{
	$.get(linkchat+'?ACAO', wstaw);
}, 2000) 

function wstaw(data)
{
	var ilosc = (data.split('\n')).length;
	var str = data.replace(/(?:\r\n|\r|\n)/g, '<br>');
	$('#chat').html(str);
	$('#chat').scrollTop(100*ilosc);
}

function rozpocznij_quiz(data)
{
	let pytania = '';
	var pyt=1;
	$.each(data,function(key,value)
	{
		pytania+='<li style="font-weight:600;">'+value.Pytanie+'</li>'+'<ol type="a">'+'<li class="odp">'+value.odpowiedz1+'<input type="radio" id="od'+pyt+'1" name="pyt'+pyt+'" style="margin-left:15px;">'+'</li>'+'<li class="odp">'+value.odpowiedz2+'<input type="radio" id="od'+pyt+'2" name="pyt'+pyt+'" style="margin-left:15px;">'+'</li>'+'<li class="odp">'+value.odpowiedz3+'<input type="radio" id="od'+pyt+'3" name="pyt'+pyt+'" style="margin-left:15px;">'+'</li>'+'<li class="odp">'+value.odpowiedz4+'<input type="radio" id="od'+pyt+'4" name="pyt'+pyt+'" style="margin-left:15px;">'+'</li>'+'</ol>';
		pyt++;
	});
	$('#miejsce_quiz')[0].innerHTML='<ol>'+pytania+'</ol>'+'<br>'+'<button id="g_sprawdz" onClick="ok()" style="position:relative;left:10%;">OK</button>';
	
}

function ok()
{
	var pkt=0;
	var wiadomosc;
	if($('input[type=radio][name=pyt1]:checked').attr('id')=="od12")
	{
		pkt++;
	}
	if($('input[type=radio][name=pyt2]:checked').attr('id')=="od21")
	{
		pkt++;
	}
	if($('input[type=radio][name=pyt3]:checked').attr('id')=="od32")
	{
		pkt++;
	}
	if($('input[type=radio][name=pyt4]:checked').attr('id')=="od44")
	{
		pkt++;
	}
	if($('input[type=radio][name=pyt5]:checked').attr('id')=="od54")
	{
		pkt++;
	}
	if($('input[type=radio][name=pyt6]:checked').attr('id')=="od62")
	{
		pkt++;
	}
	if($('input[type=radio][name=pyt7]:checked').attr('id')=="od71")
	{
		pkt++;
	}
	if($('input[type=radio][name=pyt8]:checked').attr('id')=="od83")
	{
		pkt++;
	}
	if($('input[type=radio][name=pyt9]:checked').attr('id')=="od93")
	{
		pkt++;
	}
	if($('input[type=radio][name=pyt10]:checked').attr('id')=="od101")
	{
		pkt++;
	}
	if(pkt==0)
	{
		wiadomosc="Przykro mi ";
	}
	else if(pkt>0&&pkt<=3)
	{
		wiadomosc="Słabo ";
	}
	else if(pkt>3&&pkt<7)
	{
		wiadomosc="Może być ";
	}
	else if(pkt>=7&&pkt<10)
	{
		wiadomosc="Dobrze ";
	}
	else
	{
		wiadomosc="Gratulacje ";
	}
	alert(wiadomosc+pkt+"/10");
	var elementy = document.getElementsByClassName('odp'); 
	for(var i=0;i<40;i++)
	{
		if(i==1||i==4||i==9||i==15||i==19||i==21||i==24||i==30||i==34||i==36)
		{
			elementy[i].style.color = "#408a5c";
		}
		else
		{
			elementy[i].style.color = "#ca3333";
		}
	}
}

function callback(data) 
{
	ket=data;
	slowa = ket.split(new RegExp(",|\r"))
	losujslowo();	
}

function kiedyscroll() 
{
	if (document.body.scrollTop > 80 || document.documentElement.scrollTop > 80) 
	{
		document.getElementById("dogory").style.visibility = "visible";
	}
	else 
	{
		document.getElementById("dogory").style.visibility = "Hidden";
	}
}

function trybciemny()
{
	var elementy = document.getElementsByClassName('suwak1'); 
	var tlo = window.getComputedStyle(elementy[0], null).backgroundColor;
	if(tlo==="rgb(255, 165, 0)")
	{
		elementy[0].style.background = "black";
		elementy[0].style.borderColor= "black";
		elementy[1].style.background = "black";
		elementy[1].style.borderColor= "black";
		elementy = document.getElementsByClassName('suwak2');
		elementy[0].style.background = "orange";
		elementy[0].style.borderColor= "black";
		elementy[1].style.background = "orange";
		elementy[1].style.borderColor= "black";
		elementy = document.getElementsByClassName('podstrona');
		for(var i = 0; i < elementy.length; i++)
		{
			elementy[i].style.backgroundColor = "black";
			elementy[i].style.color = "white";
		}
	}
	else
	{
		elementy[0].style.background = "orange";
		elementy[0].style.borderColor= "white";
		elementy[1].style.background = "orange";
		elementy[1].style.borderColor= "white";
		elementy = document.getElementsByClassName('suwak2');
		elementy[0].style.background = "white";
		elementy[0].style.borderColor= "white";
		elementy[1].style.background = "white";
		elementy[1].style.borderColor= "white";
		elementy = document.getElementsByClassName('podstrona');
		for(var i=0;i<elementy.length;i++)
		{
			elementy[i].style.backgroundColor = "white";
			elementy[i].style.color = "black";
		}
	}
}

function strona(a)
{
	if(a==1)
	{
		document.getElementById("gra").style.display = "none";
		document.getElementById("omnie").style.display = "none";
		document.getElementById("quiz").style.display = "none";
		document.getElementById("uzycieajaxu").style.display = "none";
		document.getElementById("stronaglowna").style.display = "block";
	}
	else if(a==2)
	{
		document.getElementById("gra").style.display = "none";
		document.getElementById("omnie").style.display = "none";
		document.getElementById("quiz").style.display = "none";
		document.getElementById("stronaglowna").style.display = "none";
		document.getElementById("uzycieajaxu").style.display = "block";
	}
	else if(a==3)
	{
		document.getElementById("gra").style.display = "none";
		document.getElementById("stronaglowna").style.display = "none";
		document.getElementById("quiz").style.display = "none";
		document.getElementById("uzycieajaxu").style.display = "none";
		document.getElementById("omnie").style.display = "block";
	}
	else if(a==4)
	{
		document.getElementById("stronaglowna").style.display = "none";
		document.getElementById("omnie").style.display = "none";
		document.getElementById("quiz").style.display = "none";
		document.getElementById("uzycieajaxu").style.display = "none";
		document.getElementById("gra").style.display = "block";
	}
	else
	{
		document.getElementById("gra").style.display = "none";
		document.getElementById("omnie").style.display = "none";
		document.getElementById("stronaglowna").style.display = "none";
		document.getElementById("uzycieajaxu").style.display = "none";
		document.getElementById("quiz").style.display = "block";
	}
}

function schowajmenu()
{
	document.getElementById('flexbox').style.visibility = 'hidden';
}

function pokazmenu()
{
	document.getElementById('flexbox').style.visibility = 'visible';
}

function klawisz(a)
{
	
	if(pauza==false)
	{
		var elementy = document.getElementsByClassName('miejsce'); 
		var temp;
		var i;
		if(a==="Enter")
		{
			if(ktory==5)
			{
				wyraz=wyraz.toLowerCase();
				if(sprawdz(ket,wyraz))
				{
					temp=wygraneslowo;
					for(var i=0;i<5;i++)
					{
						if(wygraneslowo[i]==wyraz[i])
						{
							elementy[rzad*5+i].style.background = "#38761d";
							temp=temp.slice(0,i)+"?"+temp.slice(i+1);
							document.getElementById(wyraz[i]).style.background="#38761d";
						}
					}
					for(var i=0;i<5;i++)
					{
						if(temp.includes(wyraz[i]))
						{
							elementy[rzad*5+i].style.background = "#bf9000";
							temp=temp.replace(wyraz[i],'!');
							document.getElementById(wyraz[i]).style.background="#bf9000";
						}
						else if(temp[i]!="?")
						{
							document.getElementById(wyraz[i]).style.background="#74727b";
							elementy[rzad*5+i].style.background = "#74727b";
						}
					}
					if(wygraneslowo==wyraz)
					{
						ogloszenie("Wygrales, Gratulacje!!");
						pauza=true;
					}
					if(rzad==5&&wygraneslowo!=wyraz)
					{
						przegrana();
					}
					else
					{
						rzad++;
						ktory=0;
						wyraz="";
					}		
				}
				else
				{
					ogloszenie("Nie ma takiego słowa w słowniku");
				}
			}
			else
			{
				ogloszenie("Słowo jest za krótkie");
			}
		}
		else if(a=="Backspace")
		{
			if(ktory!=0)
			{
				ktory--;
				wyraz=wyraz.slice(0, -1);
				elementy[rzad*5+ktory].innerHTML = " ";
			}
		
		}
		else if(a=="q"||a=="Q"||a=="w"||a=="W"||a=="e"||a=="E"||a=="ę"||a=="Ę"||a=="r"||a=="R"||a=="t"||a=="T"||a=="y"||a=="Y"||a=="u"||a=="U"||a=="i"||a=="I"||a=="o"||a=="O"||a=="ó"||a=="Ó"||a=="p"||a=="P"||a=="a"||a=="A"||a=="ą"||a=="Ą"||a=="s"||a=="S"||a=="ś"||a=="Ś"||a=="d"||a=="D"||a=="f"||a=="F"||a=="g"||a=="G"||a=="h"||a=="H"||a=="j"||a=="J"||a=="k"||a=="K"||a=="l"||a=="L"||a=="ł"||a=="Ł"||a=="z"||a=="Z"||a=="ż"||a=="Ż"||a=="x"||a=="X"||a=="ź"||a=="Ź"||a=="c"||a=="C"||a=="ć"||a=="Ć"||a=="v"||a=="V"||a=="b"||a=="B"||a=="n"||a=="N"||a=="ń"||a=="Ń"||a=="m"||a=="M")
		{
			if(ktory<=4)
			{
				wyraz+=a;
				elementy[rzad*5+ktory].innerHTML = a;
				ktory++;
			}
		}
	}
}

function sprawdz(ket,slowo)
{
	if(ket.indexOf(slowo)>-1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}	

function losujslowo()
{
	wygraneslowo= slowa[Math.floor(Math.random()*slowa.length)];
	wygraneslowo=wygraneslowo.slice(1);
}

function ogloszenie(a)
{
	document.getElementById("informacje").style.visibility = "visible";
	document.getElementById("informacje").innerHTML = a;
	setTimeout(function () 
	{
		document.getElementById("informacje").style.visibility = "hidden";
	}, 1300);
}

function nowagra()
{
	ktory=0;
	rzad=0;
	wyraz="";
	losujslowo();
	var elementy = document.getElementsByClassName('miejsce'); 
	var elementy2 =document.getElementsByClassName('bez'); 
	for(var i=0;i<30;i++)
	{
		elementy[i].style.background = "#c2bece";
		elementy[i].innerHTML = " ";
	}
	for(var i=0;i<35;i++)
	{
		elementy2[i].style.background = "#c2bece";
	}
	pauza=false;
}

function przegrana()
{
	pauza=true;
	ogloszenie("Przegrałes, słowo to "+wygraneslowo);
}

