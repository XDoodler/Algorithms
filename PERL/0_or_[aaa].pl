#!/usr/bin/perl
#nuttela
$text1 = "0123";
$text2 = "aaaaaaaabbbbbbb";
$text3 = "bcdefgh";
#$REGEX_GENERATED = /^0|[a]/;
$fl1=0;$fl2=0;$fl3=0;
if($text1 =~ /^0|[a]/){
   $fl1=1;
}
if($text2 =~ /^0|[a]/){
   $fl2=1;
}
if($text3 =~ /^0|[a]/){
   $fl3=1;
}
print "$fl1\n$fl2\n$fl3\n";


#OUTPUT:
#1
#1
#0
