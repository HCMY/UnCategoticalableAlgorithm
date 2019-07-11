class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size(), left = 0;
        vector<int> m(128);
        for (char c : s1) ++m[c];
        for (int right = 0; right < n2; ++right) {
            if (--m[s2[right]] < 0) {
                while (++m[s2[left++]] != 0) {}
            } else if (right - left + 1 == n1) return true;
        }
        return n1 == 0;
    }
};
