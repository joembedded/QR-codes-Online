<?PHP // -------------------------------------------------------------------
    // QR via PHP - requires qr2_cmd as executable on this OS
	error_reporting(E_ALL);

    function exe_qr2($text, $level){ // Level L M Q H
        global $ares;
        $eres="Error"; // Erg.
        $texe="./qr2_cmd"; 
		if(!file_exists($texe)){
			return "*** Binary '$texe' not found ***";
		}
	    $execmd="$texe \"$text\" -s -f1 -l$level"; // Hier Argumente
        // Letzte Zeile des exec
        //echo "exec('$execmd')->\n";
        $ares=array();
        $eres=exec($execmd, $ares); // NotFound: Keine Antwort (""), OK: FileOK 
        if(empty($eres)) $eres="exec($texe) Failure!";
		return $eres;
      } // End Convert


    // ---------------------------- M A I N --------------
    $intxt=@$_GET['t'];
    $lev=@$_GET['l'];
    $dbg=@$_GET['d'];
    $z=@$_GET['z'];
    
    if(empty($intxt)) $intxt="NO_TEXT";
    if(empty($lev)) $lev='L';
    if(@$z<1 || @$z>100) $z=5;
    
    $res=exe_qr2($intxt,$lev);

    $my=count($ares);
    if($dbg || $my<6){
        header('Content-Type: text/plain');
        if($my>5){
            $mx=strlen($ares[5]);
            echo "Text_'$intxt' Level:$lev Size:$mx*$my Pixel\n";
            for($y=0;$y<$my;$y++){
                echo $ares[$y]."\n";
            }
        }else{
            echo $res;  // Prob. ERROR
        }
    }else{
        header("Content-type: image/png");
        $mx=strlen($ares[5]);
                
        
        $bild = ImageCreate($mx*$z,$my*$z);
        $black=ImageColorAllocate($bild,0,0,0); // Schwarz
        $white=ImageColorAllocate($bild,255,255,255); // Fast Weiss
        for($y=0;$y<$my;$y++){
            for($x=0;$x<$mx;$x++){
                if($ares[$y]{$x}=='*') $col=$black;
                else $col=$white;
                Imagefilledrectangle($bild,$x*$z,$y*$z,($x+1)*$z,($y+1)*$z,$col);                    
            }
        }
        ImagePng($bild);
     }
?>