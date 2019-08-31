void find_cycle(int a){
    int b=a;
    int j=2;
    vector<int>::iterator it;
    while(true){
 
        int xx = a%10;
        it = std::find (digi.begin(), digi.end(), xx); 
        if (it == digi.end())digi.pb(xx);else {upto = a-b;break;}
        a = b*(j++);
        
    }
}
