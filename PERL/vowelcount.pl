#!/usr/bin/perl
#nuttela
$text = "abcdefghijklmnopqrstuvwxyz";
$cnt=0;
foreach $v (split //, $text) 
{
     if($v =~ /[aeiou]/g){
         $cnt++;
     }
}
print $cnt;


#OUTPUT:
#5
