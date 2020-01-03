*** (C)2018-2019 JoEmbedded.de 

This is a simple PHP script to generate a PNG-file via URL.

Note: some browsers display the "pure" image with a dark background, to make the QR-code readable,
a (white) frame is requried around the image.

Parameters for the PHP-Script:

...
    $intxt=@$_GET['t'];
    $lev=@$_GET['l'];
    $z=@$_GET['z'];
    $dbg=@$_GET['d'];
...

t: The Text (tested up to ca. 80 characters)(Without any parameters the QR-code contains the Text "NO TEXT")
l: Level (== Quality) LMQH Quality (Low to High Default='L' (== Smallest Size))
z: (Pixel-) Size of generated QR-code, default is 5
d: Debug (set to any value to display a text output)

***


