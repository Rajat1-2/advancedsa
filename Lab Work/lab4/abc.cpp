#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<int> profits(N);
    for (int i = 0; i < N; i++) {
        cin >> profits[i];
    }
    
    int K;
    cin >> K;
    
    // Generate all possible ways to select segments with at most K switches
    // A switch happens when we change from one segment to another
    // K switches = at most K+1 segments
    
    int maxProfit = 0;
    
    // Try all possible combinations of segments
    // Use bitmask to represent which elements to include
    for (int mask = 0; mask < (1 << N); mask++) {
        vector<int> segments;
        int currentSegmentStart = -1;
        
        // Find segments in the mask
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                if (currentSegmentStart == -1) {
                    currentSegmentStart = i;
                }
            } else {
                if (currentSegmentStart != -1) {
                    segments.push_back(currentSegmentStart);
                    segments.push_back(i - 1);
                    currentSegmentStart = -1;
                }
            }
        }
        if (currentSegmentStart != -1) {
            segments.push_back(currentSegmentStart);
            segments.push_back(N - 1);
        }
        
        // Check if number of segments is valid (at most K+1)
        int numSegments = segments.size() / 2;
        if (numSegments > K + 1) continue;
        
        // Calculate total profit
        int totalProfit = 0;
        for (int i = 0; i < segments.size(); i += 2) {
            for (int j = segments[i]; j <= segments[i + 1]; j++) {
                totalProfit += profits[j];
            }
        }
        
        maxProfit = max(maxProfit, totalProfit);
    }
    
    cout << maxProfit << endl;
    
    return 0;
}