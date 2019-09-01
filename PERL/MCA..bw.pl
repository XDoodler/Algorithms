#!/usr/bin/perl
#nuttela
$text1 = "MCAhellonbw";
$text2 = "MCAhellonbabb";
$text3 = "MChellonbw";
#$REGEX_GENERATED = /^(MCA)[a-z]*(bw)$/;
$fl1=0;$fl2=0;$fl3=0;
if($text1 =~ /^(MCA)[a-z]*(bw)$/){
   $fl1=1;
}
if($text2 =~ /^(MCA)[a-z]*(bw)$/){
   $fl2=1;
}
if($text3 =~ /^(MCA)[a-z]*(bw)$/){
   $fl3=1;
}
print "$fl1\n$fl2\n$fl3\n";
