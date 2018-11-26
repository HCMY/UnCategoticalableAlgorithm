class Solution {
public:
    int addDigits(int num) {
        while(num>=10){
        	string num_str = std::to_string(num);
        	int sum=0;
        	for(int i=0;i<num_str.length(); i++)
        		sum += (num_str[i]-'0');
        	num = sum;
        }

        return num;
    }
};
