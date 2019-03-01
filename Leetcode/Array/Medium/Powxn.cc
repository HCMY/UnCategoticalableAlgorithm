
std::vector<int> tength2binary(int n){
	int reminder;
	std::vector<int> binary;
	while(n>1){
		reminder = n%2;
		n/=2;
		binary.push_back(reminder);
	}
	binary.push_back(n);

	return binary;
}

class Solution {
public:
    double myPow(double x, int n) {
    	if(n==1)
    		return x;
    	if(n==-1)
    		return 1.0/x;
        if(x==1)
            return x;
        if(x==-1){
            if(n%2==0)
                return -x;
            return x;
        }

    	std::vector<int> binary=tength2binary(std::abs(n));
		double mute = 1.000;
		//for(auto item:binary)
          //2 10  cout<<item<<" ";

		for(int idx=binary.size()-1;idx>=0;idx--){
            int item = binary[idx];
			if(item==1)
				mute = pow(mute,2)*x;
			else
				mute = pow(mute,2);
		}

		if(n<0)
			return 1.000/mute;
		return mute;
    }
};


