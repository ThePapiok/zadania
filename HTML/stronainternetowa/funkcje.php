<?php
function pisz($wiadomosc)
{
	$plik = fopen("chat.txt", "a");
	fwrite($plik, $wiadomosc);
	fwrite($plik, PHP_EOL);
	fclose($plik);
}
?>