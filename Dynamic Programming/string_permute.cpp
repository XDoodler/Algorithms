void permute(string s,string chosen){
    if(s.empty()){cout<<chosen<<' ';}
    else{
        for(int i=0;i<s.length();i++){
            char c = s[i];
            chosen+=c;
            s.erase(i,1);
            permute(s,chosen);
            s.insert(i,1,c);
            chosen.erase(chosen.length()-1,1);
        }
    }
}
